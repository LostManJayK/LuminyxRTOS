#include "LED.h"
#include "UART.h"
#include "timebase.h"


int main(void)
{

    char str[] = "Hello World!\r\n";
    unsigned lenStr = sizeof(str) / sizeof(char) - 1;

    uint8_t rxArr[100];


    LEDInit();
    UARTInit();
    timebaseInit();

    while(1)
    {
        
    }
}