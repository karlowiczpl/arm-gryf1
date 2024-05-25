#ifndef CPP_ANALISE_H
#define CPP_ANALISE_H

#include <iostream>
#include <string>
#include <vector>
#include "pico/stdlib.h"
#include "map"

#include "../eeprom/eprom.h"
#include "../../setup/hardware/setup.hpp"
#include "error.h"

class KomendyAT {
    struct
    {
        uint8_t integralPart[TEMPERATURE_COUNT];
        uint8_t decimalPart[TEMPERATURE_COUNT];
    }Temperature;


public:

  typedef void (*enable_fun_ptr)(Functions::STATE_T state);

  static std::map<std::string, std::pair<enable_fun_ptr, Functions::ErrorStruct>> goodIdMap;
  static std::map<std::string, std::pair<enable_fun_ptr, Functions::ErrorStruct>> badIdMap;

  static void withGoodId(std::string& flag_name , Functions::STATE_T state);
  static void withBadId(std::string& flag_name, Functions::STATE_T state);
  static void sendCommandToUart(uart_inst_t *uart, char *function, uint8_t* states , uint8_t sizeOfStates , char* id);
  void sendCommandTemperature(float temp , char* id, uint8_t pin);
  static void parseMessage(const std::string& message , uart_inst_t* uart);
};

#endif //CPP_ANALISE_H
