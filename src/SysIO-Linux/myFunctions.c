#include "myFunctions.h"

int portState = 0;
int portAddress = 0;

int setup(int newPortAddress)
{
 	if (ioperm(newPortAddress,1,1) !=0)
	{
		printf("Program nemam pristup k portu.\n");
		return 1;
	}
	
	else
	{
		portAddress = newPortAddress;
		portState = 0;
		outb(portState, newPortAddress);
		printf("Program inicializoval hodnoty na 0.\n");
		return 0;
	}
};

void writeValue(int bitPos, int value)
{
	if (value == 1)
		portState |= (1<<bitPos);
	else
		portState &= ~(1<<bitPos);

	outb(portState, portAddress);
};

int readValue(int portInput, int bitPosition)
{
	int value = inb(portInput);
	if((value&(1<<bitPosition)) != 0)
		return 1;
	else
		return 0;
};

//precise delay
long getMicrotime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

//precise delay
void preciseDelay(int us)
{
    long startTime = getMicrotime();
    while (startTime + us > getMicrotime())
    {} 
}
