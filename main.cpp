#include <iostream>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "setup/setup.hpp"
#include "task/myTask.h"
#include "eeprom/eprom.h"

int main() {

    Setup::setup();
    EepromStruct& eeprom = EepromStruct::getInstance();
    eeprom.loadDataFromEeprom();

    xTaskCreate(Task::readFromUart0 , "readFromUart0" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
    xTaskCreate(Task::readFromUart1 , "readFromUart1" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
    #if INPUTS_COUNT || OUTPUTS_COUNT
    xTaskCreate(Task::writeToUart , "writeToUart" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
    xTaskCreate(Task::writeStatusCommand , "writeStatus" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
    #endif
    #if TEMPERATURE_COUNT
    xTaskCreate(Task::temperature, "temperature", 2048, nullptr, 3, nullptr);
    #endif



    vTaskStartScheduler();

    while (true)     {}
}

//#include <iostream>
//#include "pico/stdlib.h"
//#include "hardware/uart.h"
//#include "pico/multicore.h"
//#include "cstring"
//
//void read()
//{
//    char readed[50];
//    while ( 1 )
//    {
//        readed[0] = 0;
//        scanf("%s" , readed);
//        if(readed[0] != 0)
//        {
//            printf("Sending: %s\n" , readed);
//            if(uart_is_writable(uart0))
//            {
//                uart_puts(uart0 , readed);
//                uart_putc(uart0 , '\n');
//            }
//        }
//    }
//}
//
//int main() {
//    stdio_init_all();
//    gpio_init(0);
//    gpio_init(1);
//    gpio_init(8);
//    gpio_init(9);
//
//    gpio_set_function(0, GPIO_FUNC_UART);
//    gpio_set_function(1, GPIO_FUNC_UART);
//
//    uart_init(uart0, 9600);
//
//    gpio_set_function(8, GPIO_FUNC_UART);
//    gpio_set_function(9, GPIO_FUNC_UART);
//
//    uart_init(uart1, 9600);
//
//    multicore_launch_core1(read);
//
//    char c;
//    while (1) {
//
//        if(uart_is_readable(uart0))
//        {
//            std::cout<<uart_getc(uart0);
//        }
//    }
//}

