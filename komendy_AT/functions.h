#ifndef PLC_SPECIAL_FUNCTIONS_H
#define PLC_SPECIAL_FUNCTIONS_H

#include "pico/stdlib.h"
#include <iostream>
#include "hardware/uart.h"
#include <vector>
#include <map>

class Functions {

    typedef struct {
        std::vector<uint8_t> states;
        uart_inst_t *uart;
        std::string message;
    } STATE_T;

    typedef void (*enable_fun_ptr)(STATE_T);

    static void setOut(STATE_T state);
    static void ping(STATE_T state);
    static void setLed(STATE_T state);
    static void search(STATE_T state);

    static std::map<std::string, enable_fun_ptr> goodIdMap;
    static std::map<std::string, enable_fun_ptr> badIdMap;

public:
    static void withGoodId(std::string& flag_name, STATE_T state);
    static void withBadId(std::string& flag_name, STATE_T state);
};

#endif
