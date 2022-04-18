#include "myFunctions.h"

int portState = 0, portAddress = 0;

//---------------------------------------------Setup for school's x86 platform---------------------------------------------
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

//writeValue function for x86 platform
void writeValue(int bitPos, int value)
{
	if (value == 1)
		portState |= (1<<bitPos);
	else
		portState &= ~(1<<bitPos);

	outb(portState, portAddress);
};

int getState(int portInput, int bitPosition)
{
	if((portInput&(1<<bitPosition)) == 0)
		return 1;
	else
		return 0;
};

void myDelay(int delayus)
{
	clock_t startTime = clock();
	while (clock() < startTime + delayus)
	;
};

int myDelay2(long miliseconds)
{
   struct timespec rem;
   struct timespec req= {
       (int)(miliseconds / 1000),
       (miliseconds % 1000) * 1000000
   };

   return nanosleep(&req , &rem);
}
