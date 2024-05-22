#ifndef EEPROM_H
#define EEPROM_H

#include "pico/stdlib.h"

#include "../setup/setup.hpp"

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
        uint16_t longPressTime[INPUTS_COUNT];
        uint16_t shortPressTime[INPUTS_COUNT];
        uint8_t keyState[INPUTS_COUNT];
    } eepromData;

    void loadDataFromEeprom();
    void saveDataToEeprom();

private:


    EepromStruct() = default;
    ~EepromStruct() = default;
    EepromStruct(const EepromStruct&) = delete;
    EepromStruct& operator=(const EepromStruct&) = delete;
};

#endif