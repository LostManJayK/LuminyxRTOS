#ifndef UART_H
#define UART_H

#include "stm32c031xx.h"
#include <stdint.h>

void UARTInit(void);

static void setBaudRate(uint32_t, uint32_t);

static uint32_t computeBaudRate(uint32_t, uint32_t);

static void UARTWrite(uint8_t ch);

void UARTTransmit(uint8_t*, unsigned);

void UARTReceive(void);

#endif