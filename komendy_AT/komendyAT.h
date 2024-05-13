#ifndef CPP_ANALISC_H
#define CPP_ANALISC_H

#include <iostream>
#include <string>
#include <vector>
#include "pico/stdlib.h"

#include "../eeprom/eprom.h"

class KomendyAT {
    uint8_t id = 1;

    void setOut(std::vector<uint8_t> states);
    void setPwm(std::vector<uint8_t> states);
    void setKey(std::vector<uint8_t> states);
    void setId(std::vector<uint8_t> states);
    void reset(std::vector<uint8_t> states);
    void ping(std::vector<uint8_t> states);

public:
    struct PARSED_MESSAGE_T {
        std::string funtion;
        uint8_t sizeOfBar;
        std::vector<uint8_t> bar;
    };
    static void parseMessage(std::string message);
};

#endif //CPP_ANALISC_H
