#ifndef PLC_SPECIAL_MY_TASK_H
#define PLC_SPECIAL_MY_TASK_H

#include <vector>
#include "../lib/pico-onewire/api/one_wire.h"

#include "../setup/setup.hpp"

struct
{
    uint32_t time[INPUTS_COUNT];
    uint8_t inputs[INPUTS_COUNT];
    bool enable[INPUTS_COUNT];
}PushButton;

class Task {
public:
    static void readFromUart0(void *pvParameters);
    static void readFromUart1(void *pvParameters);
    static void writeToUart(void *pvParameters);
    static void writeStatusCommand(void *pvParameters);
    static void temperature(void *pvParameters);
    static void pressButton(void *pvParameters);

    const std::vector<int> temperature_pins = TEMPERATURE;
};

#endif
