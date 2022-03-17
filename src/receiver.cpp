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

/* struct timeval {
    time_t      tv_sec;
    suseconds_t tv_usec;    
}; */

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

	setup(DATA_TRANSFER_PIN, 0);
	init();
	Serial.begin(9600);

	while (1)
	{
/*   		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			if (firstBit == 0)
			{
				Serial.println("bit1");
				//timeStarted = clock();
				timeShit = micros();
				firstBit = 1;
				continue;
			}

			if (micros() > timeShit + DATA_FISTBIT_DELAY)
			{
				if (micros() > timeShit + DATA_FISTBIT_DELAY+300)
				{
					firstBit = 0;
					continue;
				}

				else if (readValueAVR(DATA_TRANSFER_PIN) == 0)
					readBits();
			}		
		} */
/* 
		if (readValueAVR(DATA_TRANSFER_PIN) == 1)
		{
			timeStarted = clock();
		}  */
		waitingForFirstBit();
	}
	return 0;
}