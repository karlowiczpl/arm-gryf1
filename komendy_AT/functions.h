#ifndef PLC_SPECIAL_FUNCTIONS_H
#define PLC_SPECIAL_FUNCTIONS_H

#include "pico/stdlib.h"
#include <iostream>
#include "hardware/uart.h"
#include <vector>
#include <map>

class Functions {
public:

  typedef struct {
    uint8_t notCount;
    uart_inst_t *uart;
    std::string message;
    std::vector<uint8_t> states;
  } STATE_T;

  static void withGoodId(std::string& flag_name, STATE_T state);
  static void withBadId(std::string& flag_name, STATE_T state);

private:
    typedef void (*enable_fun_ptr)(STATE_T);
    static void setOut(STATE_T state);
    static void ping(STATE_T state);
    static void setLed(STATE_T state);
    static void search(STATE_T state);
    static std::map<std::string, enable_fun_ptr> goodIdMap;
    static std::map<std::string, enable_fun_ptr> badIdMap;
};


#endif
