#include <cstring>

#include "../../communication/communication.h"
#include "../../komendy_AT/checkPins.h"
#include "../../komendy_AT/error.h"
#include "../../komendy_AT/komendyAT.h"
#include "../hardware/setup.hpp"
#include "functions.h"
#include "hardware/pwm.h"

std::map<std::string, std::pair<KomendyAT::enable_fun_ptr, Functions::ErrorStruct>> KomendyAT::goodIdMap = {
    {"AT+SetOut" , {Functions::setOut , {6 , enumFunctions.setOut , 4}}},
    {"AT+Ping" , {Functions::ping , {0 , enumFunctions.other , 255}}},
    {"AT+SetLED" , {Functions::setLed , {2 , enumFunctions.other , 100}}},
    {"AT+Search" , {Functions::search , {1 , enumFunctions.other , 255}}},
};

std::map<std::string, std::pair<KomendyAT::enable_fun_ptr, Functions::ErrorStruct>> KomendyAT::badIdMap = {
    {"AT+Search" , {Functions::search , {1 , enumFunctions.other , 255}}},
};


void Functions::setOut(STATE_T state) {
  for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
  {
    switch (state.states[i+1])
    {
    case 1:   gpio_put(HardwareInfo.outputs[i], 1); break;
    case 2:   gpio_put(HardwareInfo.outputs[i], 0); break;
    case 3:   gpio_put(HardwareInfo.outputs[i], !(gpio_get_out_level(HardwareInfo.outputs[i]))); break;
    }
  }
}

void Functions::ping(Functions::STATE_T state)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  char function[] = "PONG" , id[3];
  sprintf(id , "%d" , eeprom.eepromData.id);
  KomendyAT::sendCommandToUart(state.uart, function, nullptr, 0, id);
}

void Functions::setLed(Functions::STATE_T state) {
  pwm_set_gpio_level(HardwareInfo.pwm[state.states[1] - 1], ((state.states[2] * 255) / 100) * (state.states[2] * 255) / 100);
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
