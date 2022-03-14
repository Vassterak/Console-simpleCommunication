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

//I aware that this step is not memory efficient whole int array takes up 512 bytes (when int is one byte) And I know that I can store just ascii values and convert it to binary on the fly before sending.
//But for this purpose of school homework I have settled for this solution. So convert all ascii values to binary and save it in 2d array. (I know that I'm wasting a lot of memory)
uint8_t rawBinaryMessage[128][8], currentIndex;

void ConvertToBinary(int asciiChar)
{
	for (int i = 0; i < 8; i++)
	{
		if (asciiChar & 1 == 1)
		{
			rawBinaryMessage[currentIndex][i] = 1;
			//Serial.print("1 ");
		}
		else
		{
			rawBinaryMessage[currentIndex][i] = 0;
			//Serial.print("0 ");
		}

		asciiChar = asciiChar >> 1;
	}

	//Serial.println("");
}

void convertText(char text[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		currentIndex = i;
		ConvertToBinary(text[i]);
	}
}

void arrayCheck()
{
	for (int i = 0; i < currentIndex +1; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			//Serial.print(rawBinaryMessage[i][j]);
			writeValueAVR(DATA_TRANSFER_PIN, rawBinaryMessage[i][j]);
			_delay_ms(1);
		}
		//Serial.print("\n");
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
		convertText("hello");
		arrayCheck();
		_delay_ms(2000);;
	}
	return 0;
}