#include <stdio.h>
#include <time.h>
#include <sys/time.h> 
#include <stdint.h>
#include <string.h>
#include <pigpiod_if2.h>   //Rpi

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

extern int portAddress;
extern int portState;

void writeValue2(int pinID, int value);
int readValue2(int pinID);
void preciseDelay(int us);
long getMicrotime();

#endif