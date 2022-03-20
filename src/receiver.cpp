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

int readIncommingPacket()
{
	int outputData = 0;
	_delay_us(500);

	for (uint8_t i = 0; i < 8; i++)
	{
		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			_delay_us(1000);
			if (readValueAVR(DATA_TRANSFER_PIN) == 0)
			{
				//toggle value when value is read (debug only)
				PORTD = PORTD ^ 0b00001000;

				outputData |= 0 << i;
				_delay_us(1000);
			}
		}

		else
		{
			_delay_us(1000);
			if (readValueAVR(DATA_TRANSFER_PIN) == 1)
			{
				//toggle value when value is read (debug only)
				PORTD = PORTD ^ 0b00001000;

				outputData |= 1 << i;
				_delay_us(1000);
			}
		}
	}
	//DEBUG ONLY
	writeValueAVR(3,0);
	
	return outputData;
}

//Not required because I'm already sending values in right order
int byteReverse(int toReverseNum)
{
    int pos = 8 - 1;     // maintains shift, 8bits are in this int (platform dependent)
 
    // store reversed bits of `n`. Initially, all bits are set to 0
    int reversed = 0;
 
    // do till all bits are processed
    while (pos >= 0 && toReverseNum)
    {
        // if the current bit is 1, then set the corresponding bit in the result
        if (toReverseNum & 1)
            reversed = reversed | (1 << pos);
 
        toReverseNum >>= 1;                // drop current bit (divide by 2)
        pos--;                  // decrement shift by 1
    }
 
    return reversed;
}

int main (void)
{
	//AVR timing
	unsigned long timeShift, timeShift2;

	//Received value
	int dataPacket = 0;

	//pinout setup AVR
	setup(DATA_TRANSFER_PIN, 0);

	//DEBUG ONLY
	DDRD = 0b00001000;

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
				dataPacket = readIncommingPacket();
				//dataPacket = byteReverse(outputValue);

				//DEBUG ONLY
				//Serial.println(dataPacket, BIN);
				//Serial.println(dataPacket, DEC);
				Serial.println((char)dataPacket);
				//Serial.println("----------");
			}
			else
				continue;
		}
	}
	return 0;
}