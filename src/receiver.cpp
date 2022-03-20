//#include <sys/io.h>
//#include <stdio.h>
//#include <time.h>
#include "myFunctions.h"

/* #define PORT_ADDRESS 0x301

int main(void)
{	
	//End program when port access is denied.
	if (setup(PORT_ADDRESS) == 1)
		return 1;
	
	writeValue(0,1); //set first bit to HIGH (Receiver mode)
	
	while (1)
	{
		if (readReceivedValue())
			printf("OneReceived\n");
	}
	return 0;
} */

#define DATA_TRANSFER_PIN 2 //pin number in register D

//for first bit indicating incomming packet (define tolerances for signal duration)
#define START_TOLERANCE 490 //us
#define END_TOLERANCE 510 //us

uint16_t readIncommingPacket()
{
	uint16_t outputData = 0;
	_delay_us(500);

	for (uint8_t i = 0; i < 12; i++)
	{
		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			_delay_us(1000);
			if (readValueAVR(DATA_TRANSFER_PIN) == 0)
			{
				outputData |= 0 << i;
				_delay_us(1000);
			}
		}

		else
		{
			_delay_us(1000);
			if (readValueAVR(DATA_TRANSFER_PIN) == 1)
			{
				outputData |= 1 << i;
				_delay_us(1000);
			}
		}
	}	
	return outputData;
}

void integrityCheck(uint16_t receivedPacket)
{
	uint8_t checksum = (receivedPacket & 0xFF);
	uint8_t data = (receivedPacket >> 8);

	Serial.println(receivedPacket, BIN);
	Serial.println(data, BIN);
	Serial.println(checksum, BIN);
}

int main (void)
{
	//AVR timing
	unsigned long timeShift, timeShift2;

	//Received value
	uint16_t dataPacket = 0;

	//pinout setup AVR
	setup(DATA_TRANSFER_PIN, 0);

	//Serialline setup AVR
	init();
	Serial.begin(9600);

	while (1)
	{
		//Check if value on port is high
   		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			//get time of first signal rise (get cpu time in microseconds)
			timeShift = micros();

			//Do nothing while port value is high
			while (readValueAVR(DATA_TRANSFER_PIN) == 1)
				;
			
			//get time of signal fall change 1 -> 0 (get cpu time in microseconds)
			timeShift2 = micros();

			//Check if data transmission started (each packet has starting value, used for sync)
			if (timeShift2 - timeShift <= END_TOLERANCE && timeShift2 - timeShift > START_TOLERANCE)
			{
				_delay_us(2000);
				integrityCheck(readIncommingPacket());

				//DEBUG ONLY
				//Serial.println(dataPacket, BIN);
			}
			else
				continue;
		}
	}
	return 0;
}