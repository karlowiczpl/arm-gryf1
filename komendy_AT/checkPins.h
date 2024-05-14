#ifndef PLCSPECIAL_CHECKPINS_H
#define PLCSPECIAL_CHECKPINS_H

#include "pico/stdlib.h"

#include "../setup/setup.hpp"

class CheckPins {

    struct
    {
        uint8_t input[INPUTS_COUNT];
    }States;

public:
    char* checkInputPins();
    static char* writeActualInputState();
    char* writeActualOutputState();
};


#endif //PLCSPECIAL_CHECKPINS_H
