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

}

void EepromStruct::saveDataToEeprom() {

}
