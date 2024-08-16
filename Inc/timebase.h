#ifndef TIMEBASE_H
#define TIMEBASE_H

#include "stm32c031xx.h"

//Clock frequency
#define ONE_MS_LOAD 12000 //One milliseod


//DECLARE SYSTICK REGISTERS
#define STK_BASE 0xE000E010

//SYSTICK Typdef Declaration
typedef struct
{
    uint32_t CSR;            //Control and Status Register: Offset 0x0
    uint32_t RVR;            //Reset value register: Offset 0x4
    uint32_t CVR;            //Current Value Register: Offset 0x8
    uint32_t CALIBRATION;    //Calibration register: Offset 0xC

} SYSTICK_Typedef;

#define STK ((SYSTICK_Typedef*)STK_BASE)

//Timebase configuratoin;
void timebaseInit(void);

//Get current tick count
uint32_t getTick(void);

//Delay function
void delay(uint32_t);

//Increment global tick count
void tickIncrement(void);



#endif