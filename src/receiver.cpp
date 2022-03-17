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

#define DATA_TRANSFER_PIN 2
#define DATA_FISTBIT_DELAY 200

uint8_t firstBit = 0;

void readBits()
{
	Serial.println("data");
	firstBit = 0;
}

void waitingForFirstBit()
{
	int counter1;

	while (1)
	{
		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			counter1++;
			_delay_us(10);
		}
	}
}

int main (void)
{
	//AVR timing
	unsigned long timeShift, timeShift2; 

	//pinout setup AVR
	setup(DATA_TRANSFER_PIN, 0);

	//Serialline setup AVR
	init();
	Serial.begin(9600);

	while (1)
	{
   		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			timeShift = micros(); //get time of first signal rise (microseconds)

			while (readValueAVR(DATA_TRANSFER_PIN) == 1)
				;
			
			timeShift2 = micros(); //get time of first signal fall (microseconds)

			if (timeShift2 - timeShift <= 530 && timeShift2 - timeShift > 470)
			{
				Serial.println("ano");
			}
			else
				continue;
		}

	}
	return 0;
}