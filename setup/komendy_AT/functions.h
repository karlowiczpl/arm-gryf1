#ifndef PLC_SPECIAL_FUNCTIONS_H
#define PLC_SPECIAL_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <map>
#include "pico/stdlib.h"
#include "hardware/uart.h"

class Functions {
public:
  typedef struct {
    uint8_t notCount;
    uart_inst_t *uart;
    std::string message;
    std::vector<uint8_t> states;
  } STATE_T;

  typedef struct
  {
    uint8_t sizeOfFunction;
    uint8_t functionNumber;
    uint8_t functionRange;
  }ErrorStruct;
public:
  static void setOut(STATE_T state);
  static void ping(STATE_T state);
  static void setLed(STATE_T state);
  static void search(STATE_T state);

  static void badIdCommandDontExist(STATE_T state);
};


#endif
