#include "myFunctions.h"

#define PORT_ADDRESS 0x301
//for first bit indicating incomming packet (define tolerances for signal duration)
#define START_TOLERANCE 490 //us
#define END_TOLERANCE 510 //us
#define DELAY_BEFORE_READ 2000 //us
#define DELAY_BEFORE_FIRST_VALUE 500 //us
#define DELAY_BETWEEN_READS 1000 //us

static uint8_t dataPacket = 0;

uint16_t readIncommingPacket()
{
	uint16_t outputData = 0;
	preciseDelay(DELAY_BEFORE_FIRST_VALUE);

	for (uint8_t i = 0; i < 12; i++)
	{
		if (readValue(PORT_ADDRESS,1) == 1)
		{
			preciseDelay(DELAY_BETWEEN_READS);
			if (readValue(PORT_ADDRESS,1) == 0)
			{
				outputData |= 0 << i;
				preciseDelay(DELAY_BETWEEN_READS);
			}
		}

		else
		{
			preciseDelay(DELAY_BETWEEN_READS);
			if (readValue(PORT_ADDRESS,1) == 1)
			{
				outputData |= 1 << i;
				preciseDelay(DELAY_BETWEEN_READS);
			}
		}
	}	
	return outputData;
}

uint8_t integrityCheck(uint16_t receivedPacket)
{
	uint8_t data = (receivedPacket & 0xFF);
	uint8_t checksum = (receivedPacket >> 8);
	uint8_t numberOfOnesData = 0, dataOneBitsNum = data;

    while (dataOneBitsNum > 0)
	{
        if (dataOneBitsNum & 1)
            numberOfOnesData++;
		
        dataOneBitsNum = dataOneBitsNum >> 1;
    }

	if (numberOfOnesData == checksum)
	{
		dataPacket = data;
		return 0;
	}
	else
		return 1;
}

int main(void)
{	
	//End program when port access is denied.
 	if (setup(PORT_ADDRESS) == 1)
		return 1;

	
	writeValue(0,1); //set first bit to HIGH (Receiver mode)

	while (1)
	{
		long timeShift, timeShift2;
		//Check if value on port is high
   		if (readValue(PORT_ADDRESS,1) == 1)
		{
			//get time of first signal rise (get cpu time in microseconds)
			timeShift = getMicrotime();

			//Do nothing while port value is high
			while (readValue(PORT_ADDRESS,1) == 1)
				;
			
			//get time of signal fall change 1 -> 0 (get cpu time in microseconds)
			timeShift2 = getMicrotime();

			//Check if data transmission started (each packet has starting value, used for sync)
			if (timeShift2 - timeShift <= END_TOLERANCE && timeShift2 - timeShift > START_TOLERANCE)
			{
				preciseDelay(DELAY_BEFORE_READ);
				if (integrityCheck(readIncommingPacket()) == 0 && dataPacket < 127)
					printf("%c",dataPacket);
				else
					printf("%c",63);
			}
			else
				continue;
		}
	}
	return 0;
}
