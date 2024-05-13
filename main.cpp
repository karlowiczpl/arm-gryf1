#include <iostream>
#include "pico/stdlib.h"
//#include "FreeRTOS.h"
//#include "task.h"

#include "komendy_AT/komendyAT.h"
#include "setup/setup.hpp"
#include "communication/communication.h"

void coreOne()
{
    Communication com;
    std::string message;
    while (true)
    {
        message = com.readDataFromUart(uart1);
        std::cout<<message<<std::endl;
    }
}
void coreZero()
{
    Communication com;
    uint8_t states[7] = { 1 , 1,1,1,1,1,1};
    char message[] = "AT+SetOut=1,1,1,1,1,1,1\n";
    while (true)
    {
        com.sendDataToUart(uart0 ,message);
        sleep_ms( 1000 );
    }
}

int main(void) {

    Setup setup;
    KomendyAT at;
    Communication com;
    setup.setup();


    return 0;
}