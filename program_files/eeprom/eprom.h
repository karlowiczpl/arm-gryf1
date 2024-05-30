#ifndef EEPROM_H
#define EEPROM_H

#include "one_wire.h"
#include "pico/stdlib.h"
#include <vector>

#include "../../setup/hardware/setup.hpp"
#include "../../setup/komendy_AT/commands.h"

#define MAX_SIZE 10

class EepromStruct {
public:

    void setId(uint8_t newId);

    static EepromStruct& getInstance() {
        static EepromStruct instance;
        return instance;
    }
    struct
    {
        uint8_t id;
        uint8_t outputsStates[OUTPUTS_COUNT];
        uint8_t pwmStates[PWM_COUNT];
    } CommonEeprom;
    struct
    {
      struct
      {
        uint8_t queue1[MAX_SIZE][INPUTS_COUNT];
        uint8_t queue2[MAX_SIZE][INPUTS_COUNT];
        uint8_t function[MAX_SIZE][INPUTS_COUNT];
        uint8_t size[INPUTS_COUNT];
      }Commands;
      uint16_t longPressTime[INPUTS_COUNT];
      uint16_t shortPressTime[INPUTS_COUNT];
      uint8_t keyState[INPUTS_COUNT];
    }EepromData;

    std::vector<One_wire> one_wires;
    uint8_t programingPin;
    uint8_t inputPin;

    void loadDataFromEeprom();
    void saveDataToEeprom();
    void saveDataToCommands();

private:


    EepromStruct() = default;
    ~EepromStruct() = default;
    EepromStruct(const EepromStruct&) = delete;
    EepromStruct& operator=(const EepromStruct&) = delete;
};

#endif