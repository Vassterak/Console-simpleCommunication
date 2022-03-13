#include <stdio.h>
#include <sys/io.h>
#include <time.h>

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

extern int portAddress;
extern int portState;

int setup(int newPortAddress);
int writeValue(int bitPos, int value);
void delay(int delayMS);

#endif