#include "UART.h"
//#include "NVIC.h"
#include "timebase.h"


#define USART2EN (0b1 << 17)
#define GPIOAEN (0b1 << 0)

#define CR1_TE (0b1 << 3)
#define CR1_RE (0b1 << 2)
#define CR1_UE (0b1 << 0)
#define CR1_RXFNEIE (0b1 << 5)

#define ISR_TXE (0b1 << 7)
#define ISR_RXNE (0b1 << 5)
#define ISR_TC (0b1 << 6)

#define ISER_USART2 (0b1 << 28)
#define ISCR_USART2 (0b1 << 28)

#define SYS_FREQ 12000000
#define APB_CLK  SYS_FREQ
#define UART_BAUDRATE 9600


//Declare universal rx buffer
#define BUFFER_SIZE 1000
static uint8_t rxBuffer[BUFFER_SIZE];

static uint8_t dataMsg[50] = "Data Received: ";

//Set the Baud Rate for the UART
static void setBaudRate(uint32_t, uint32_t);

//Calculate the Baud Rate
static uint32_t computeBaudRate(uint32_t, uint32_t);

//Write a byte to the UART register
static void UARTWrite(uint8_t ch);

//Read a byte from the UART Register
static uint8_t UARTRead(void);


//Configure and select UART
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

    //Check if CLK is enabled
    while (!(RCC->CR & 0b1 << 8));

    //Ensure the HSI prescaler is set to 4 (default)
    while (!(RCC->CR & (0b010 << 11)));

    //Configure Baud Rate
    setBaudRate(APB_CLK, UART_BAUDRATE);

    //Configure Transfer direction
    USART2->CR1 = CR1_TE | CR1_RE;

    //Enable uart module
    USART2->CR1 |= CR1_UE;

    //Enable interrupts for UART2
    NVIC->ISER[0] |= ISER_USART2;

    //Enable UART Receive interrupt
    USART2->CR1 |= CR1_RXFNEIE;

    //Enable global interrupt
    __enable_irq();
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

//Overload printf for UART Transmit
int __io_putchar(uint8_t ch)
{
    UARTWrite(ch);
    return ch;
}

//Write a byte to the UART register
static void UARTWrite(uint8_t ch)
{
    //Check is transmit data register is empy
    while (!(USART2->ISR & ISR_TXE));

    //Write transmit data register
    USART2->TDR = ch;

    //Wait for transmit complete
    while(!(USART2->ISR & ISR_TC));
}

//Transmit a string of bytes over UART
void UARTTransmit(uint8_t *str, uint32_t size)
{
    for(unsigned i=0; i<size; i++)
        UARTWrite(str[i]);
}

//Read a byte from the UART Register
uint8_t UARTRead(void)
{
    // //Wait for data to enter the RDR register
    // while(!(USART2->ISR & ISR_RXNE));

    //Read the data from the register
    return USART2->RDR;


}

//Receive a string of bytes over UART
void UARTReceive(uint8_t* rxArr, uint32_t size)
{
    for(uint32_t i=0; i<size; i++)
        rxArr[i] = rxBuffer[i];

}

//UART interrupt handler
void USART2_IRQHandler(void)
{
    uint32_t rxPos = 0;

    while(USART2->ISR & ISR_RXNE)
    {
        if(rxPos < BUFFER_SIZE)
            rxBuffer[rxPos++] = UARTRead();
        else
            (void)UARTRead();
    }


    UARTTransmit(rxBuffer, rxPos);


}

