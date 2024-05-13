#ifndef PLCSPECIAL_SETUP_HPP
#define PLCSPECIAL_SETUP_HPP

#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../pico-onewire/api/one_wire.h"

class Setup {

#define OUTPUTS { 2 , 3 , 4 , 5 , 6 , 7 }
#define OUTPUTS_COUNT 6

#define INPUTS {  };
#define INPUTS_COUNT 0

#define PWM {  };
#define PWM_COUNT 0

#define TEMPERATURE {  };
#define TEMPERATURE_COUNT 0

#define UART0_PIN 0
#define UART1_PIN 8

    uint8_t inputs[INPUTS_COUNT];
    uint8_t outputs[OUTPUTS_COUNT];
    uint8_t temperature[TEMPERATURE_COUNT];
    uint8_t pwm[PWM_COUNT];

    void setupOutputs();
    void setupInputs();
    void setupPwm();
    void setupTemperature();
    void setupCommunication();

public:

    struct
    {
        uint8_t outputs[OUTPUTS_COUNT] = OUTPUTS;
        uint8_t pwm[PWM_COUNT] = PWM;
        uint8_t temperature[TEMPERATURE_COUNT] = TEMPERATURE;
        uint8_t inputs[INPUTS_COUNT] = INPUTS;
    }HardwareInfo;

    void setup();

};

#endif //PLCSPECIAL_SETUP_HPP
