#include "LED.h"

#define GPIOAEN (0b1 << 0)
#define OD5 (0b1 << 5)

void LEDInit(void)
{
    //Enable GPIOA clock
    RCC->IOPENR |= GPIOAEN;

    //Set PA5 to output
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &= ~(1U<<11);
}

void LEDOn(void)
{
    //Set LED pin high
    GPIOA->ODR |= OD5;
}

void LEDOff(void)
{
    //Set LED pin off
    GPIOA->ODR &= ~(OD5);
}

void LEDToggle(void)
{
    //Write LED pin to oposite value
    GPIOA->ODR ^= OD5;
}
