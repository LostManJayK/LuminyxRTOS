#include "UART.h"
#include <stdio.h>


#define USART2EN (0b1 << 17)
#define GPIOAEN (0b1 << 0)

#define CR1_TE (0b1 << 3)
#define CR1_RE (0b1 << 2)
#define CR1_UE (0b1 << 0)

#define ISR_TXE (0b1 << 7)

#define SYS_FREQ 12000000
#define APB_CLK  SYS_FREQ
#define UART_BAUDRATE 9600


void UARTInit(void)
{
    //Enable GPIO clock
    RCC->IOPENR |= GPIOAEN;

    //Set GPIO pins to alternate function mode

    //PB6 TX
    GPIOA->MODER &= ~(0b1 << 4);
    GPIOA->MODER |= (0b1 << 5);

    //PB7 RX
    GPIOA->MODER &= ~(0b1 << 6);
    GPIOA->MODER |= (0b1 << 7);

    //Select alternate function for each pin

    //PA2 AF1
    GPIOA->AFR[0] &= ~(0b111 << 9);
    GPIOA->AFR[0] |= (0b1 << 8);

    //PA3 AF1
    GPIOA->AFR[0] &= ~(0b111 << 13);
    GPIOA->AFR[0] |= (0b1 << 12);




    //Enable clock for USART2
    RCC->APBENR1 |= USART2EN;

    //Check if HSICLK is enabled
    while (!(RCC->CR & 0b1 << 8));

    //Ensure the HSI prescaler is set to 4 (default)
    while (!(RCC->CR & (0b010 << 11)));

    //Configure Baud Rate
    setBaudRate(APB_CLK, UART_BAUDRATE);

    //Configure Transfer direction
    USART2->CR1 = CR1_TE | CR1_RE;

    //Enable uart module
    USART2->CR1 |= CR1_UE;
}

//write the fractional baud rate to the BRR
static void setBaudRate(uint32_t periphClock, uint32_t baudRate)
{
    USART2->BRR = computeBaudRate(periphClock, baudRate);
}

//Calculate the fractional baud rate
static uint32_t computeBaudRate(uint32_t periphClock, uint32_t baudRate)
{
    //Compute whole number part of baud
    uint32_t whole = (periphClock / (16 * baudRate));

    //Compute fractional part of baud
    uint32_t fraction = ((periphClock % (16 * baudRate)) * 16) / (16 * baudRate);

    //Combine and return
    return (whole << 4) | (fraction & 0x0F);

}

int __io_putchar(uint8_t ch)
{
    UARTWrite(ch);
    return ch;
}

static void UARTWrite(uint8_t ch)
{
    //Check is transmit data register is empy
    while (!(USART2->ISR & ISR_TXE));

    //Write transmit data register
    USART2->TDR = ch;
}

void UARTTransmit(uint8_t *str, unsigned size)
{
    for(unsigned i=0; i<size; i++)
        UARTWrite(str[i]);
}