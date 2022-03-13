//#include <sys/io.h>
//#include <stdio.h>
//#include <time.h>
#include "myFunctions.h"

/* #define PORT_ADDRESS 0x300
#define MAX_PACKET_SIZE 16 //in bytes, min size is 

char userInput[16];
int currentCharPosition = 0;

void userInput()
{
    fgets(userInput,16,stdin);
};

int returnBinaryValue()
{


};

int main(void)
{	
	//End program when port access is denied.
	if (setup(PORT_ADDRESS) == 1)
		return 1;
	
	writeValue(0,0); //set first bit to LOW (Transmit mode)
	
	while (1)
	{
		printf("Transmiter\n");
		writeValue(1, 0);
		delay(50);
		writeValue(1, 1);
		delay(50);
	}
	return 0;
} */

#define DATA_TRANSFER_PIN 2
int asciiText[256];

void ConvertToBinary(int asciiChar)
{
	for (int i = 0; i < 8; i++)
	{
		if (asciiChar & 1 == 1)
			Serial.print("1 ");
		else
			Serial.print("0 ");

		Serial.println("");
		asciiChar = asciiChar >> 1;
	}
	
}

void convertText()
{
	char text[] = "hello";
	for (int i = 0; text[i] != '\0'; i++)
	{
		asciiText[i] = text[i];
		//printf("%d", ch);
		Serial.println(asciiText[i], DEC);
		ConvertToBinary(asciiText[i]);
	}
}

void Checksum()
{

}


int main (void)
{
	setup(DATA_TRANSFER_PIN, 1);
	init();
	Serial.begin(9600);

	while (1)
	{
		_delay_ms(1000);
		writeValueAVR(DATA_TRANSFER_PIN, 0);
		//Serial.println("sdfsdfsf");
		convertText();
		_delay_ms(1000);
		writeValueAVR(DATA_TRANSFER_PIN, 1);
	}
	return 0;
}