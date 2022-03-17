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
#define DATA_FISTBIT_DELAY 200 //us (microseconds)

//for first bit indicating incomming packet (define tolerances for signal duration)
#define START_TOLERANCE 470 //us
#define END_TOLERANCE 530 //us

void readIncommingPacket()
{

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
			if (timeShift2 - timeShift <= 530 && timeShift2 - timeShift > 470)
			{
				_delay_us(2000);
				readIncommingPacket();
			}
			else
			{
				//Serial.println(timeShift2-timeShift);
				continue;
			}
		}
	}
	return 0;
}