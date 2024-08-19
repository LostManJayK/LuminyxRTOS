#ifndef UART_H
#define UART_H

#include "stm32c031xx.h"
#include <stdint.h>
//#include <stdio.h>
#include <stdlib.h>

#define MAX_TRANSFER_SIZE 0xFFFFFFFF

//Configure and select UART
void UARTInit(void);

//Transmit a string of bytes over UART
void UARTTransmit(uint8_t*, uint32_t);

//Receive a string of bytes over UART
void UARTReceive(uint8_t*, uint32_t);

#endif