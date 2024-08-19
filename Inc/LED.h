#ifndef LED_H
#define LED_H

#include "stm32c031xx.h"

//Initialize LED clock and parameters
void LEDInit(void);

//Set the LED to on
void LEDOn(void);

//Set LED to off
void LEDOff(void);

//Toggle LED
void LEDToggle(void);


#endif