//#include <sys/io.h>
//#include <stdio.h>
//#include <time.h>
#include "myFunctions.h"

#define PORT_ADDRESS 0x301

int readReceivedValue()
{
	if (inb(PORT_ADDRESS)&(1<<0))
		return 1;
	else
		return 0;
};

int main(void)
{	
	//End program when port access is denied.
	if (setup(PORT_ADDRESS) == 1)
		return 1;
	
	writeValue(0,1); //set first bit to HIGH (Receiver mode)
	
	while (1)
	{
		if (readReceivedValue())
			printf("OneReceived\n");
	}
	return 0;
}