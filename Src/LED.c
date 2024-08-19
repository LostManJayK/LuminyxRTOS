#include "LED.h"

#define GPIOAEN (0b1 << 0)
#define OD5 (0b1 << 5)

//Initialize LED clock and parameters
void LEDInit(void)
{
    //Enable GPIOA clock
    RCC->IOPENR |= GPIOAEN;

    //Set PA5 to output
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &= ~(1U<<11);
}

//Set the LED to on
void LEDOn(void)
{
    //Set LED pin high
    GPIOA->ODR |= OD5;
}

//Set LED to off
void LEDOff(void)
{
    //Set LED pin off
    GPIOA->ODR &= ~(OD5);
}

//Toggle LED
void LEDToggle(void)
{
    //Write LED pin to oposite value
    GPIOA->ODR ^= OD5;
}
