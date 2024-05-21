#ifndef CPP_ANALISC_H
#define CPP_ANALISC_H

#include <iostream>
#include <string>
#include <vector>
#include "pico/stdlib.h"

#include "../eeprom/eprom.h"
#include "../setup/setup.hpp"

class KomendyAT {
    struct
    {
        uint8_t integralPart[TEMPERATURE_COUNT];
        uint8_t decimalPart[TEMPERATURE_COUNT];
    }Temperature;


public:
//    static void sendCommandToUartVector(uart_inst_t* uart , char* function , const std::vector<uint8_t>& states);
    static void sendCommandToUartTabble(uart_inst_t *uart, char *function, uint8_t* states , uint8_t sizeOfStates , char* id);
    void sendCommandTemperature(float temp , char* id, uint8_t pin);
    static void parseMessage(const std::string& message , uart_inst_t* uart);
};

#endif //CPP_ANALISC_H
