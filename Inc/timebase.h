#ifndef TIMEBASE_H
#define TIMEBASE_H

#nclude "stm32c031xx.h"

//Clock frequency
#define ONE_SEC_LOAD 12000000


//DECLARE SYSTICK REGISTERS
#define STK_BASE 0xE000E010

//SYSTICK Typdef Declaration
typedef struct
{
    uint32_t CSR            //Control and Status Register: Offset 0x0
    uint32_t RVR            //Reset value register: Offset 0x4
    uint32_t CVR            //Current Value Register: Offset 0x8
    uint32_t CALIBRATION    //Calibration register: Offset 0xC
} SYSTICK_Typedef;

#define STK (SYSTICK_Typedef*) STK_BASE

//Timebase configuratoin;
void timebaseInit(void);



#endif