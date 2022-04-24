#include "myFunctions.h"

int portState = 0;
int portAddress = 0;

void writeValue2(int pinID, int value) //Rpi
{
	gpioWrite(pinID, value);
};

int readValue2(int pinID)
{
	return gpioRead(pinID);
}

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
