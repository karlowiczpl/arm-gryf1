#ifndef EEPROM_H
#define EEPROM_H

#include "pico/stdlib.h"

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
        uint8_t data[255];
    } eepromData;

private:

    void loadDataFromEeprom();
    void saveDataToEeprom();

    EepromStruct() = default;
    ~EepromStruct() = default;
    EepromStruct(const EepromStruct&) = delete;
    EepromStruct& operator=(const EepromStruct&) = delete;
};

#endif