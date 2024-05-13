#ifndef PLCSPECIAL_COMMUNICATION_H
#define PLCSPECIAL_COMMUNICATION_H

#include <iostream>
#include <hardware/uart.h>

class Communication {


public:
    std::string readDataFromUart(uart_inst_t* uart);
    void sendDataToUart(uart_inst_t* uart, char* message);
};


#endif //PLCSPECIAL_COMMUNICATION_H
