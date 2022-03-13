//#include <sys/io.h>
//#include <stdio.h>
//#include <time.h>
#include "myFunctions.h"

int portState = 0, portAddress = 0;

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

int writeValue(int bitPos, int value)
{
	if (value == 1)
		portState |= (1<<bitPos);
	else
		portState &= ~(1<<bitPos);
	
	printf("Write to port\n");
	outb(portState, portAddress);
	return portState;
};

void delay(int delayMS)
{
	clock_t startTime = clock();
	while (clock() < startTime + delayMS * 1000)
	;
};