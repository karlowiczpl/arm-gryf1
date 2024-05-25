#include <cstring>
#include "hardware/watchdog.h"

#include "../../program_files/communication/communication.h"
#include "../../program_files/komendy_AT/checkPins.h"
#include "functions.h"
#include "hardware/pwm.h"

std::map<std::string, std::pair<KomendyAT::enable_fun_ptr, Functions::ErrorStruct>> KomendyAT::goodIdMap = {
    {"AT+SetOut" , {Functions::setOut , {6 , enumFunctions.setOut , 4}}},
    {"AT+Ping" , {Functions::ping , {0 , enumFunctions.other , 255}}},
    {"AT+SetLED" , {Functions::setLed , {2 , enumFunctions.other , 100}}},
    {"AT+Search" , {Functions::search , {1 , enumFunctions.other , 255}}},
    {"AT+SetDefault" , {Functions::setDefault, {0 , enumFunctions.other , 255}}},
    {"AT+SetKey" , {Functions::setKey , {4 , enumFunctions.other , 255}}},
    {"AT+RST" , {Functions::resetGoodId , {0 , enumFunctions.other , 255}}},
};

std::map<std::string, std::pair<KomendyAT::enable_fun_ptr, Functions::ErrorStruct>> KomendyAT::badIdMap = {
    {"AT+Search" , {Functions::search , {1 , enumFunctions.other , 255}}},
    {"AT+RST" , {Functions::resetBadId , {0 , enumFunctions.other , 255}}},
};


void Functions::setOut(STATE_T state) {
  EepromStruct& eeprom = EepromStruct::getInstance();
  for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
  {
    switch (state.states[i+1])
    {
    case 1:   gpio_put(HardwareInfo.outputs[i], 1); break;
    case 2:   gpio_put(HardwareInfo.outputs[i], 0); break;
    case 3:   gpio_put(HardwareInfo.outputs[i], !(gpio_get_out_level(HardwareInfo.outputs[i]))); break;
    }
  }
  for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)  eeprom.eepromData.outputsStates[i] = gpio_get_out_level(HardwareInfo.outputs[i]);
  eeprom.saveDataToEeprom();
}

void Functions::ping(Functions::STATE_T state)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  char function[] = "PING" , id[3];
  sprintf(id , "%d" , eeprom.eepromData.id);
  KomendyAT::sendCommandToUart(state.uart, function, nullptr, 0, id);
}

void Functions::setLed(Functions::STATE_T state) {
  pwm_set_gpio_level(HardwareInfo.pwm[state.states[1] - 1], ((state.states[2] * 255) / 100) * (state.states[2] * 255) / 100);
        EepromStruct& eeprom = EepromStruct::getInstance();
        eeprom.eepromData.pwmStates[state.states[1] - 1] = state.states[2];
        eeprom.saveDataToEeprom();
        eeprom.loadDataFromEeprom();
}


void Functions::search(Functions::STATE_T state) {
  if(state.states[0] == state.states[1])
  {
    EepromStruct& eeprom = EepromStruct::getInstance();
    eeprom.setId(state.states[0]);
  } else
  {
    char message[50];
    sprintf(message , "AT+Search=%d,%d\n", state.states[0] + 1 , state.states[1]);
    Communication::sendDataToUart(state.uart == uart0 ? uart1 : uart0 , message);
  }
}
void Functions::badIdCommandDontExist(Functions::STATE_T state)
{
      char message[state.message.size() + 1];
      state.message.push_back('\n');
      std::strcpy(message, state.message.c_str());
      if(error::checkCommand(state , enumFunctions.other , 0 , 0))    Communication::sendDataToUart(state.uart == uart0 ? uart1 : uart0 , message);
}
void Functions::setDefault(Functions::STATE_T state)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  for(uint8_t i = 0; i < INPUTS_COUNT; i++)
  {
    eeprom.eepromData.longPressTime[i] = 2000;
    eeprom.eepromData.shortPressTime[i] = 400;
    eeprom.eepromData.keyState[i] = 0;
  }
  for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
  {
    eeprom.eepromData.outputsStates[i] = 0;
  }
  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
  Setup::setup();
}
void Functions::setKey(Functions::STATE_T state)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  eeprom.eepromData.shortPressTime[--state.states[1]] = (state.states[2] * 10);
  eeprom.eepromData.longPressTime[state.states[1]] = (state.states[3] * 10);
  eeprom.eepromData.keyState[state.states[1]] = (state.states[4]);
  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();

}
void Functions::resetGoodId(Functions::STATE_T state)
{
  watchdog_reboot(0 , SRAM_END , 0);
}

void Functions::resetBadId(Functions::STATE_T state)
{
  char message[50];
  sprintf(message , "AT+RST=%d\n" , state.states[0]);
  Communication::sendDataToUart(state.uart == uart0 ? uart1 : uart0 , message);
  if(state.states[0] == 0)
  {
    watchdog_reboot(0 , SRAM_END , 0);
  }


}
