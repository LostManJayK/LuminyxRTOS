#include "timebase.h"

#define CSR_EN (0b1 << 0) //Enable timer
#define CSR_TICKINT (0b1 << 1) //Enable timer interrupt
#define CSR_CLKSOURCE (0b1 << 2) //Set clock source
#define CSR_COUNTFLAG (0b1 << 16) //Count flag

#define MAX_DELAY 0xFFFFFFFF //Maximum delay time

volatile uint32_t curTick; //current tick value from cvr
volatile uint32_t curTick_p;
volatile uint32_t tickFreq = 1; //Increment value

//Increment system tick counter
void tickIncrement(void)
{
    curTick += tickFreq;
}

//Get current system tick count
uint32_t getTick(void)
{
    //Disable interrupt
    __disable_irq();

    //Set store current tick value
    curTick_p = curTick;

    //Enable interrupts
    __enable_irq();

    //Return value
    return curTick_p;
}

//Delay function
void delay(uint32_t timeMs)
{
    //Get current time;
    uint32_t startTime = getTick();

    //Assign variable for wiat time
    uint32_t wait = timeMs;

    //Check if value is less than max delay
    if(wait < MAX_DELAY)
    {
        wait += (uint32_t)(tickFreq);
    }

    //Wait for duration of delay
    while((getTick() - startTime) < wait);
}

//Timebase configuratoin & initialization;
void timebaseInit(void)
{

    //Reload timer with number of cycles per second
    STK->RVR = ONE_MS_LOAD - 1;

    //Clear SYSTICK CVR
    STK->CVR = 0;

    //Select internal clock source
    STK->CSR |= CSR_CLKSOURCE;

    //Enable interrupt
    STK->CSR |= CSR_TICKINT;

    //Enable SYSTICK
    STK->CSR |= CSR_EN;

    //Enable global interrupt
    __enable_irq();
}

//SysTick interrupt handler
void SysTick_Handler(void)
{
    tickIncrement();
}