#include "myFunctions.h"

#define PIN_ID 26 //Transmitter pin
#define DATA_HOLD_TIME 999 //2us removed because that's the average time that is used for rest of the program
#define START_PULSE 500 //us
#define START_DELAY 2000//us delay betweeen start and actual data
#define DELAY_BETWEEEN_PACKETS 20000 //us = 20ms

//I aware that this step is not memory efficient whole int array takes up 512 bytes (when int is one byte) And I know that I can store just ascii values and convert it to binary on the fly before sending.
//But for this purpose of school homework I have settled for this solution. So convert all ascii values to binary and save it in 2d array. (I know that I'm wasting a lot of memory)
static uint8_t rawBinaryMessage[64][8];
static uint8_t currentIndex = 0;
static uint8_t sizeOfMessage = 0;
static uint8_t checkSumNum[64];

void ConvertToBinary(uint8_t asciiChar)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if ((asciiChar & 1) == 1)
		{
			rawBinaryMessage[currentIndex][i] = 1;
			checkSumNum[currentIndex]++;
		}

		else
			rawBinaryMessage[currentIndex][i] = 0;

		asciiChar = asciiChar >> 1;
	}
};

void breakUpText(char text[])
{
	sizeOfMessage = strlen(text);

	for (uint8_t i = 0; text[i] != '\0'; i++)
	{
		currentIndex = i;
		ConvertToBinary(text[i]);
	}
};

void startDelay()
{
	writeValue2(PIN_ID, 1);
	preciseDelay(START_PULSE);
	writeValue2(PIN_ID, 0);
	preciseDelay(START_DELAY);
};

//Sent 4bit checksum
void checkSum(uint8_t packetID)
{
	uint8_t number = checkSumNum[packetID];
	//Serial.println(number);

	for (uint8_t i = 0; i < 4; i++)
	{
		if ((number >> (i)) & 1)
		{
			writeValue2(PIN_ID, 0);
			preciseDelay(DATA_HOLD_TIME);
			writeValue2(PIN_ID, 1);
			preciseDelay(DATA_HOLD_TIME);
		}
		else
		{
			writeValue2(PIN_ID, 1);
			preciseDelay(DATA_HOLD_TIME);
			writeValue2(PIN_ID, 0);
			preciseDelay(DATA_HOLD_TIME);
		}
	}
	checkSumNum[packetID] = 0;
};

void dataSend()
{
	for (uint8_t i = 0; i < sizeOfMessage; i++)
	{
		//NEW PACKET
		startDelay();
		for (uint8_t j = 0; j < 8; j++)
		{
			if (rawBinaryMessage[i][j] == 0)
			{
				writeValue2(PIN_ID, 1);
				preciseDelay(DATA_HOLD_TIME);
				writeValue2(PIN_ID, 0);
				preciseDelay(DATA_HOLD_TIME);
			}
			else
			{
				writeValue2(PIN_ID, 0);
				preciseDelay(DATA_HOLD_TIME);
				writeValue2(PIN_ID, 1);
				preciseDelay(DATA_HOLD_TIME);
			}
		}
		//_delay_us(2000);
		checkSum(i);
		writeValue2(PIN_ID, 0);
		preciseDelay(DELAY_BETWEEEN_PACKETS); //delay between packets
	}
};

int setup()
{
    if (gpioInitialise()< 0)
   {
       gpioSetMode(PIN_ID, PI_OUTPUT);
       return 1;
   } 
    else
        return 0;
}

int main (void)
{

/* 	if (setup(PORT_ADDRESS) == 1) LINUX SKOLA
		return 1; */

	if (setup() == 1) //Raspberry Pi
    {
        printf("Chypa pristupu\n");
        return 1;
    }
	
	writeValue2(PIN_ID,0); //set first bit to LOW (Transmit mode) bit pos 0

	while (1)
	{
		char inputMessage[32];

		printf("Zadej text: ");
		scanf("%s", inputMessage);
		writeValue2(PIN_ID, 0); //bit pos 1
		breakUpText(inputMessage);
		dataSend();
	}

	return 0;
};