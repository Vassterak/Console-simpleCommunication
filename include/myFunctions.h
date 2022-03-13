#include <stdio.h>
#include <time.h>
#include <Arduino.h>

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

//---------------------------------------------Setup for school's x86 platform---------------------------------------------
/* extern int portAddress;
extern int portState;

int setup(int newPortAddress);
int writeValue(int bitPos, int value);
int readReceivedValue();
void delay(int delayMS); */

//---------------------------------------------Setup for AVR platform---------------------------------------------
void setup(int pinSelection, bool isTransmiter);
void writeValueAVR(int bitPos, int value);
int readValueAVR(int bitPos);
void myDelay(int delayMS);

#endif