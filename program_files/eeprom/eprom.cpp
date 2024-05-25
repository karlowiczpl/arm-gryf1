#include "eprom.h"
#include "hardware/flash.h"
#include <cstring>
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (512 * 1024)

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void EepromStruct::loadDataFromEeprom() {
  memcpy(&eepromData, flash_target_contents, sizeof(eepromData));
}


void EepromStruct::saveDataToEeprom() {
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_OFFSET, sizeof(eepromData.id));
  restore_interrupts(ints);
  flash_range_program(FLASH_TARGET_OFFSET, reinterpret_cast<uint8_t*>(&eepromData), sizeof(eepromData));
  restore_interrupts(ints);
  EepromStruct::loadDataFromEeprom();

}
void EepromStruct::setId(uint8_t newId)
{
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_OFFSET, sizeof(eepromData.id));
  restore_interrupts(ints);

  eepromData.id = newId;

  ints = save_and_disable_interrupts();
  flash_range_program(FLASH_TARGET_OFFSET, reinterpret_cast<uint8_t*>(&eepromData), sizeof(eepromData));
  restore_interrupts(ints);
  EepromStruct::loadDataFromEeprom();
}
