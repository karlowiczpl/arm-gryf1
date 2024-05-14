#include "eprom.h"
#include "pico/stdlib.h"

Eeprom::EEPROM_T Eeprom::loadFromEeprom()
{
    static char id[4] = "932";
    EepromStruct.id = id;
}
Eeprom::EEPROM_T Eeprom::saveToEeprom()
{

}