#include "eprom.h"
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include <string>
#include <cstring>
#include "hardware/sync.h"


void EepromStruct::setId(uint8_t newId)
{
    eepromData.id = newId;
    EepromStruct eepromStruct;
    eepromStruct.saveDataToEeprom();
}

void EepromStruct::loadDataFromEeprom()
{
    for(uint8_t i = 0; i < INPUTS_COUNT; i++)
    {
        eepromData.longPressTime[i] = 2000;
        eepromData.shortPressTime[i] = 400;
        eepromData.keyState[i] = 1;
    }
}

void EepromStruct::saveDataToEeprom() {

}
