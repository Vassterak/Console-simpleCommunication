#include <sys/io.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h> 
#include <stdint.h>
#include <string.h>

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

extern int portAddress;
extern int portState;

// int setup(int newPortAddress); VYPNUTO PRO RPi
void writeValue(int bitPos, int value);
int readValue(int portInput, int bitPosition);
void preciseDelay(int us);
long getMicrotime();

#endif