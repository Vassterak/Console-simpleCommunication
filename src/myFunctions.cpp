#include "myFunctions.h"

int portState = 0, portAddress = 0;

//---------------------------------------------Setup for school's x86 platform---------------------------------------------
/* int setup(int newPortAddress)
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
}; */

//writeValue function for x86 platform
/* int writeValue(int bitPos, int value)
{
	if (value == 1)
		portState |= (1<<bitPos);
	else
		portState &= ~(1<<bitPos);
	
	printf("Write to port\n");
	outb(portState, portAddress);
	return portState;
};

int readReceivedValue()
{
	if (inb(PORT_ADDRESS)&(1<<0))
		return 1;
	else
		return 0;
}; */

/*void myDelay(int delayMS)
{
	clock_t startTime = clock();
	while (clock() < startTime + delayMS * 1000)
	;
};*/

/*
int myDelay2(long miliseconds)
{
   struct timespec rem;
   struct timespec req= {
       (int)(miliseconds / 1000),
       (miliseconds % 1000) * 1000000
   };

   return nanosleep(&req , &rem);
}*/

//---------------------------------------------Setup for AVR platform---------------------------------------------
void setup(int pinSelection, bool isTransmiter)
{
	if (isTransmiter)
	{
		DDRD = (0x01 << pinSelection);
		PORTD = 0x00;
	}
		
	else
		DDRD = 0x00;
}

void writeValueAVR(int bitPos, int value)
{
	if (value == 1)
		PORTD |= (1 << bitPos);
	else
		PORTD &= ~(1 << bitPos);
}

int readValueAVR(int bitPos)
{
/* 	if ((PIND & 0b00000100) == 0)
		return 0;
	else
		return 1; */
	return (PIND & (1 << bitPos));
}
