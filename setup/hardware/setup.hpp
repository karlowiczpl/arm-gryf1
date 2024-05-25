#ifndef PLC_SPECIAL_SETUP_HPP
#define PLC_SPECIAL_SETUP_HPP

#include <cstdio>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "one_wire.h"

#define OUTPUTS { 2 , 3 , 4 , 5 , 6 , 7 };
#define OUTPUTS_COUNT 6

#define INPUTS { 10 , 11 , 12 , 13 , 14 };
#define INPUTS_COUNT 5

#define PWM_T { 20 , 21 , 22 , 26};
#define PWM_COUNT 4

#define TEMPERATURE { 15 , 16 , 17 , 18 , 19};
#define TEMPERATURE_COUNT 5

struct
{
    uint8_t outputs[OUTPUTS_COUNT] = OUTPUTS;
    uint8_t pwm[PWM_COUNT] = PWM_T;
    uint8_t temperature[TEMPERATURE_COUNT] = TEMPERATURE;
    uint8_t inputs[INPUTS_COUNT] = INPUTS;
}HardwareInfo;

class Setup {


#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 8
#define UART1_RX_PIN 9

#define BAUD_RATE 9600


    static void setupOutputs();
    static void setupInputs();
    static void setupPwm();
    static void setupCommunication();
    static void loadStatesFromEeprom();

public:

    static void setup();
};

#endif
