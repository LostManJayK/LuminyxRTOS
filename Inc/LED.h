#ifndef LED_H
#define LED_H

#include "stm32c031xx.h"

void delay(unsigned);

void LEDInit(void);

void LEDOn(void);

void LEDOff(void);

void LEDToggle(void);


#endif