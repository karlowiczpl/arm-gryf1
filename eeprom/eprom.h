#ifndef PLCSPECIAL_EPROM_H
#define PLCSPECIAL_EPROM_H

#include <iostream>
#include "pico/stdlib.h"

class Eeprom {

public:
    typedef struct
    {
        uint8_t id;
        uint8_t* outputStates;
    }EEPROM_T;

    EEPROM_T loadFromEeprom();
    EEPROM_T saveToEeprom();
};


#endif //PLCSPECIAL_EPROM_H
