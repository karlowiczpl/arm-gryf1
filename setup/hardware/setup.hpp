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

#define PWM_T { 20 , 21 , 22 };
#define PWM_COUNT 3

#define RGB {}
#define RGB_COUNT 0

#define TEMPERATURE { 15 , 16 , 17 , 18 , 19};
#define TEMPERATURE_COUNT 5

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 8
#define UART1_RX_PIN 9

#define BAUD_RATE 9600

struct
{
#if OUTPUTS_COUNT
  uint8_t outputs[OUTPUTS_COUNT] = OUTPUTS;
#endif
#if PWM_COUNT
  uint8_t pwm[PWM_COUNT] = PWM_T;
#endif
#if TEMPERATURE_COUNT
  uint8_t temperature[TEMPERATURE_COUNT] = TEMPERATURE;
#endif
#if INPUTS_COUNT
  uint8_t inputs[INPUTS_COUNT] = INPUTS;
#endif
//#if RGB_COUNT
  uint8_t rgb[RGB_COUNT][3] = RGB;
//#endif
}HardwareInfo;

class Setup {

#if OUTPUTS_COUNT
  static void setupOutputs();
#endif
#if INPUTS_COUNT
  static void setupInputs();
#endif
#if PWM_COUNT
  static void setupPwm();
#endif
  static void setupCommunication();
//#if RGB_COUNT
  static void setupRGB();
//#endif
#if INPUTS_COUNT || OUTPUTS_COUNT || PWM_COUNT || RGB_COUNT
  static void loadStatesFromEeprom();
#endif

public:

    static void setup();
};

#endif
