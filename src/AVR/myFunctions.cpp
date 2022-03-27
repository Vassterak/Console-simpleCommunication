#include "myFunctions.h"

int portState = 0, portAddress = 0;

//---------------------------------------------Setup for AVR platform---------------------------------------------
void setup(int pinSelection, bool isTransmiter)
{
	//set register as output, leave other alone (for protection input is preferred)
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
 	if ((PIND & (1 << bitPos)) == 0)
		return 0;
	else
		return 1;
	//return (PIND & (1 << bitPos));
}
