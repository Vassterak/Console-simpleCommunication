#include "myFunctions.h"

#define DATA_TRANSFER_PIN 2
#define DATA_HOLD_TIME 998 //2us removed because that's the average time that is used for rest of the program
#define START_PULSE 500 //us
#define START_DELAY 2000//us delay betweeen start and actual data
#define DELAY_BETWEEEN_PACKETS 20 //ms

//I aware that this step is not memory efficient whole int array takes up 512 bytes (when int is one byte) And I know that I can store just ascii values and convert it to binary on the fly before sending.
//But for this purpose of school homework I have settled for this solution. So convert all ascii values to binary and save it in 2d array. (I know that I'm wasting a lot of memory)
static uint8_t rawBinaryMessage[64][8], currentIndex = 0, sizeOfMessage = 0, checkSumNum[64];

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
}

void breakUpText(char text[])
{
	sizeOfMessage = strlen(text);

	for (uint8_t i = 0; text[i] != '\0'; i++)
	{
		currentIndex = i;
		ConvertToBinary(text[i]);
	}
}

void startDelay()
{
	writeValueAVR(DATA_TRANSFER_PIN, 1);
	_delay_us(START_PULSE);
	writeValueAVR(DATA_TRANSFER_PIN, 0);
	_delay_us(START_DELAY);
}

//Sent 4bit checksum
void checkSum(uint8_t packetID)
{
	uint8_t number = checkSumNum[packetID];
	//Serial.println(number);

	for (uint8_t i = 0; i < 4; i++)
	{
		if ((number >> (i)) & 1)
		{
			writeValueAVR(DATA_TRANSFER_PIN, 0);
			_delay_us(DATA_HOLD_TIME);
			writeValueAVR(DATA_TRANSFER_PIN, 1);
			_delay_us(DATA_HOLD_TIME);
		}
		else
		{
			writeValueAVR(DATA_TRANSFER_PIN, 1);
			_delay_us(DATA_HOLD_TIME);
			writeValueAVR(DATA_TRANSFER_PIN, 0);
			_delay_us(DATA_HOLD_TIME);
		}
	}
	checkSumNum[packetID] = 0;
}

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
		//_delay_us(2000);
		checkSum(i);
		writeValueAVR(DATA_TRANSFER_PIN, 0);
		_delay_ms(DELAY_BETWEEEN_PACKETS); //delay between packets
	}
}

int main (void)
{
	setup(DATA_TRANSFER_PIN, 1);
	init();
	Serial.begin(9600);

	while (1)
	{
		writeValueAVR(DATA_TRANSFER_PIN, 0);
		breakUpText("helo");
		dataSend();
		_delay_ms(2000); //delay betweeen sending values
	}
	return 0;
}