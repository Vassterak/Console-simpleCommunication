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

int main (void)
{
	pinMode(13, OUTPUT);
	//setup(2,0);
	init();
	Serial.begin(9600);
	while (1)
	{
		delay(500);
		digitalWrite(13,HIGH);
		//writeValueAVR(2,0);
		Serial.println("sdfsdfsf");
		delay(500);
		digitalWrite(13,LOW);
		//writeValueAVR(2,1);
	}
	return 0;
}