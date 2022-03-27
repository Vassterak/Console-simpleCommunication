#include <sys/io.h>
#include <stdio.h>
#include <time.h>

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

//---------------------------------------------Setup for school's x86 platform---------------------------------------------
extern int portAddress;
extern int portState;

int setup(int newPortAddress);
int writeValue(int bitPos, int value);
int readReceivedValue(int portID);
void delay(int delayMS);

#endif