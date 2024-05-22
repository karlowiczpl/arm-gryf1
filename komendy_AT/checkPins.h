#ifndef PLC_SPECIAL_CHECK_PINS_H
#define PLC_SPECIAL_CHECK_PINS_H

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../setup/setup.hpp"

struct
{
    uint8_t input[INPUTS_COUNT];
    uint8_t outputs[OUTPUTS_COUNT];
    uint32_t inputsTime[INPUTS_COUNT];
    uint32_t inpTime[INPUTS_COUNT];
}States;

class CheckPins {

public:

    static void checkInputPins(uint32_t time);
    static void writeActualInputState();
    static void writeActualOutputState();
    static void timerOfButtonPress(uint8_t time);
};


#endif
