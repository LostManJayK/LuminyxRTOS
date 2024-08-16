#include "LED.h"
#include "UART.h"

void delay(unsigned count)
{
    while(--count > 0);
}

int main(void)
{

    char str[] = "Hello World!\r\n";
    unsigned lenStr = sizeof(str) / sizeof(char) - 1;


    LEDInit();
    UARTInit();

    while(1)
    {
        UARTTransmit((uint8_t*)str, lenStr);
        delay(1000000);
    }
}