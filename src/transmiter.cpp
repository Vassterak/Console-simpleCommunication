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
#define DATA_HOLD_TIME 998 //2us removed because that's the average time that is used for rest of the program

//I aware that this step is not memory efficient whole int array takes up 512 bytes (when int is one byte) And I know that I can store just ascii values and convert it to binary on the fly before sending.
//But for this purpose of school homework I have settled for this solution. So convert all ascii values to binary and save it in 2d array. (I know that I'm wasting a lot of memory)
static uint8_t rawBinaryMessage[64][8], currentIndex;
static uint8_t sizeOfMessage = 0;
//ascii: hello
/* uint8_t testData[5][8] =
{
    {0, 1, 1, 0, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 1},
	{0, 1, 1, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 1, 1, 1, 1}
}; */

void ConvertToBinary(int asciiChar)
{
	for (int i = 0; i < 8; i++)
	{
		if ((asciiChar & 1) == 1)
		{
			rawBinaryMessage[currentIndex][i] = 1;
			Serial.println(rawBinaryMessage[currentIndex][i]);
		}

		else
		{
			rawBinaryMessage[currentIndex][i] = 0;
			Serial.println(rawBinaryMessage[currentIndex][i]);
		}

		asciiChar = asciiChar >> 1;
	}
	Serial.println("---");
}

void convertText(char text[])
{
	sizeOfMessage = sizeof(text) / sizeof(char*);
	for (int i = 0; text[i] != '\0'; i++)
	{
		currentIndex = i;
		ConvertToBinary(text[i]);
		//Serial.println(text[i]); is working
	}
}

void startDelay(int delayTime)
{
	writeValueAVR(DATA_TRANSFER_PIN, 1);
	_delay_us(delayTime);
	writeValueAVR(DATA_TRANSFER_PIN, 0);
	_delay_us(2000);
}


void dataSend()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		startDelay(500);
		for (uint8_t j = 0; j < 8; j++)
		{
			if (rawBinaryMessage[i][j] == 0)
			{
				writeValueAVR(DATA_TRANSFER_PIN, 1);
				_delay_us(DATA_HOLD_TIME);
				writeValueAVR(DATA_TRANSFER_PIN, 0);
				_delay_us(DATA_HOLD_TIME);
			}
			else
			{
				writeValueAVR(DATA_TRANSFER_PIN, 0);
				_delay_us(DATA_HOLD_TIME);
				writeValueAVR(DATA_TRANSFER_PIN, 1);
				_delay_us(DATA_HOLD_TIME);
			}
		}
		writeValueAVR(DATA_TRANSFER_PIN, 0);
		_delay_ms(20); //debug only
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
		writeValueAVR(DATA_TRANSFER_PIN, 0);
		convertText("hello");
		dataSend();
		_delay_ms(2000);;
	}
	return 0;
}