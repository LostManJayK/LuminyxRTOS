#include "LED.h"
#include "UART.h"
#include "timebase.h"


int main(void)
{

    char str[] = "Hello World!\r\n";
    unsigned lenStr = sizeof(str) / sizeof(char) - 1;


    LEDInit();
    UARTInit();
    timebaseInit();

    while(1)
    {
        UARTTransmit((uint8_t*)str, lenStr);
        delay(1000);
    }
}