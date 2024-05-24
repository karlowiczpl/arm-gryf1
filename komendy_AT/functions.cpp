#include "functions.h"
#include "../setup/setup.hpp"
#include "komendyAT.h"
#include "hardware/pwm.h"
#include "../communication/communication.h"
#include <cstring>
#include "checkPins.h"
#include "error.h"

std::map<std::string, Functions::enable_fun_ptr> Functions::goodIdMap = {
        {"AT+SetOut", Functions::setOut},
        {"AT+Ping",   Functions::ping},
        {"AT+SetLed", Functions::setLed},
        {"AT+Search", Functions::search},
};
std::map<std::string, Functions::enable_fun_ptr> Functions::badIdMap = {
        {"AT+Search", Functions::search},

};

void Functions::setOut(STATE_T state) {
    if(error::checkCommand(state , enumFunctions.setOut , OUTPUTS_COUNT , 4))
    {
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
}

void Functions::ping(Functions::STATE_T state)
{
  if(error::checkCommand(state , enumFunctions.other , 0 , 255))
  {
    EepromStruct& eeprom = EepromStruct::getInstance();
    char function[] = "PONG" , id[3];
    sprintf(id , "%d" , eeprom.eepromData.id);
    KomendyAT::sendCommandToUartTabble(state.uart, function, nullptr, 0, id);
  }

}

void Functions::setLed(Functions::STATE_T state) {
  if(error::checkCommand(state , enumFunctions.other, 2 , 100))
  {
    pwm_set_gpio_level(HardwareInfo.pwm[state.states[1] - 1], ((state.states[2] * 255) / 100) * (state.states[2] * 255) / 100);
  }
}


void Functions::search(Functions::STATE_T state) {
    if(error::checkCommand(state , enumFunctions.other , 1 , 255))
    {
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

}
void Functions::withGoodId(std::string& flag_name, STATE_T state) {
    auto it = goodIdMap.find(flag_name);
    if (it != goodIdMap.end()) {
        it->second(state);
    }
}
void Functions::withBadId(std::string& flag_name, STATE_T state) {
    auto it = badIdMap.find(flag_name);
    if (it != badIdMap.end()) {
        it->second(state);
    } else
    {
        char message[state.message.size() + 1];
        state.message.push_back('\n');
        std::strcpy(message, state.message.c_str());
        if(error::checkCommand(state , enumFunctions.other , 0 , 0))
          Communication::sendDataToUart(state.uart == uart0 ? uart1 : uart0 , message);
    }
}

