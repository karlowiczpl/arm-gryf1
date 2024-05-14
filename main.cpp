#include <iostream>
#include "pico/stdlib.h"
//#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "task.h"

#include "komendy_AT/komendyAT.h"
#include "setup/setup.hpp"
#include "communication/communication.h"
#include "komendy_AT/checkPins.h"

void readTask(void *pvParameters);
void writeTask(void *pvParameters);
void statusComand(void *pvParameters);

int main(void) {

    Setup setup;
    KomendyAT at;
    Communication com;
    Eeprom epreom;
    setup.setup();
    epreom.loadFromEeprom();

    stdio_init_all();

    xTaskCreate(readTask , "readFromUart" , configMINIMAL_STACK_SIZE, NULL , 1, NULL);
    xTaskCreate(writeTask , "writeToUart" , configMINIMAL_STACK_SIZE, NULL , 1, NULL);
    xTaskCreate(statusComand , "writeStatus" , configMINIMAL_STACK_SIZE, NULL , 1, NULL);


    vTaskStartScheduler();

    while ( 1 )     {}

    return 0;
}

void readTask(void *pvParameters)
{
    Communication com;
    std::string message;
    while (1)
    {
        message = com.readDataFromUart(uart1);
//        KomendyAT::parseMessage(message);
        std::cout<<message<<std::endl;
    }
}
void writeTask(void *pvParameters)
{
    Communication com;
    CheckPins c1;
    char* message;
    while (1)
    {

        c1.checkInputPins();
        vTaskDelay(10);
    }
}
void statusComand(void *pvParameters)
{
    CheckPins c1;
    Communication com;
    char* message;
    while ( 1 )
    {
        TickType_t xNextWakeTime = xTaskGetTickCount();
        message = c1.writeActualInputState();
        com.sendDataToUart(uart0 , message);
        com.sendDataToUart(uart1 , message);
        message = c1.writeActualOutputState();
        com.sendDataToUart(uart0 , message);
        com.sendDataToUart(uart1 , message);
        vTaskDelayUntil(&xNextWakeTime, 500);
    }
}
