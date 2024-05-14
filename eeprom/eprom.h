#ifndef PLCSPECIAL_EPROM_H
#define PLCSPECIAL_EPROM_H

#include <iostream>
#include "pico/stdlib.h"

class Eeprom {

public:
    typedef struct
    {
        char* id;
        uint8_t* outputStates;
    }EEPROM_T;

    struct
    {
        char* id;
        uint8_t* outputStates;
    }EepromStruct;

    EEPROM_T loadFromEeprom();
    EEPROM_T saveToEeprom();
};


#endif //PLCSPECIAL_EPROM_H
