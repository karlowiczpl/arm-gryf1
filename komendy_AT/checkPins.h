#ifndef PLC_SPECIAL_CHECK_PINS_H
#define PLC_SPECIAL_CHECK_PINS_H

#include "pico/stdlib.h"

#include "../setup/setup.hpp"

struct
{
    uint8_t input[INPUTS_COUNT];
    uint8_t outputs[OUTPUTS_COUNT];
}States;

class CheckPins {

public:

    static void checkInputPins();
    static void writeActualInputState();
    static void writeActualOutputState();
};


#endif
