#include "eprom.h"
#include "hardware/flash.h"
#include <cstring>
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (512 * 1024)
#define FLASH_TARGET_COMMANDS_OFFSET (550 * 1024)

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void EepromStruct::loadDataFromEeprom() {
  memcpy(&CommonEeprom, flash_target_contents, sizeof(CommonEeprom));
  memcpy(&EepromData, flash_target_contents, sizeof(EepromData));
}


void EepromStruct::saveDataToEeprom() {
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_OFFSET, sizeof(CommonEeprom));
  restore_interrupts(ints);
  flash_range_program(FLASH_TARGET_OFFSET, reinterpret_cast<uint8_t*>(&CommonEeprom), sizeof(CommonEeprom));
  restore_interrupts(ints);
  EepromStruct::loadDataFromEeprom();

}
void EepromStruct::setId(uint8_t newId)
{
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_OFFSET, sizeof(CommonEeprom));
  restore_interrupts(ints);

  CommonEeprom.id = newId;

  ints = save_and_disable_interrupts();
  flash_range_program(FLASH_TARGET_OFFSET, reinterpret_cast<uint8_t*>(&CommonEeprom), sizeof(CommonEeprom));
  restore_interrupts(ints);
  EepromStruct::loadDataFromEeprom();
}
void EepromStruct::saveDataToCommands()
{
  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_COMMANDS_OFFSET, sizeof(EepromData));
  restore_interrupts(ints);
  flash_range_program(FLASH_TARGET_COMMANDS_OFFSET, reinterpret_cast<uint8_t*>(&EepromData), sizeof(EepromData));
  restore_interrupts(ints);

  memcpy(&EepromData, flash_target_contents, sizeof(EepromData));

}
