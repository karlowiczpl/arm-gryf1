#include "hardware/uart.h"
#include <cstring>

#include "communication.h"

char* Communication::readDataFromUart(uart_inst_t* uart)
{
    if(uart_is_readable(uart))
    {
        static char message[50];
        memset(message , 0 , sizeof(message));
        uint8_t counter = 0;
        while ( true )
        {
            message[counter] = uart_getc(uart);
            if(message[counter] == '\n')
            {
                message[counter] = '\0';
                return message;
            }
            counter++;
        }
    }
}

void Communication::sendDataToUart(uart_inst_t* uart, char* message) {
    uart_puts(uart , message);
}
