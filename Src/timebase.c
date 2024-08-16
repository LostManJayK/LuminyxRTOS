#include "timebase.h"

#define CSR_EN (0b1 << 0) //Enable timer
#define CSR_TICKINT (0b1 << 1) //Enable timer interrupt
#define CSR_CLKSOURCE (0b1 << 2) //Set clock source
#define CSR_COUNTFLAG (0b1 << 16) //Count flag

//Timebase configuratoin & initialization;
void timebaseInit(void)
{
    /*
        1. Enable SYSTICK  timer
        2. Enable SYSTICK interrupt
        3. Set clock source to processor clock
    */
    STK->CR |= ( (CSR_EN) | (CSR_TICKINT) | (CSR_CLKSOURCE) );
}