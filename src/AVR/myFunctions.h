#include <stdio.h>
#include <time.h>
#include <Arduino.h>

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

//---------------------------------------------Setup for AVR platform---------------------------------------------
void setup(int pinSelection, bool isTransmiter);
void writeValueAVR(int bitPos, int value);
int readValueAVR(int bitPos);

#endif