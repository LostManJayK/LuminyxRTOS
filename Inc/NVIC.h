#ifndef NVIC_H
#define NVIC_H


//Define NVIC base address
#define NVIC_BASE 0xE000E100


//Create memory mapped struct for NVIC registers
typedef struct
{
    uint32_t ISER[32];        //Interrupt Set-Enable register: 0x00
    uint32_t ISCR[32];           //Interrupt Set-Enable register: 0x04
    uint32_t ISPR[32];           //Interrupt set-pending register: 0x08
    uint32_t ICPR[32];           //Interrupt clear-pending register: 0x0C
    uint32_t IPR0_7[8];      //Interrupt priority register: 0x0
} NVIC_Typedef;

#define NVIC ((NVIC_Typedef*) NVIC_BASE)


#endif