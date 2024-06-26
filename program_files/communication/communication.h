#ifndef PLC_SPECIAL_COMMUNICATION_H
#define PLC_SPECIAL_COMMUNICATION_H

#include "hardware/uart.h"
#include "one_wire.h"
#include <iostream>

#include "../eeprom/eprom.h"
#include "../komendy_AT/komendyAT.h"

class Communication {

public:
    static char* readDataFromUart(uart_inst_t* uart);
    static void sendDataToUart(uart_inst_t* uart , char* message);
    static void oneWireTemperature();
};


#endif
