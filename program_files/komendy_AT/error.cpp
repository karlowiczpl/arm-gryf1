#include "error.h"
#include "../communication/communication.h"

bool error::checkCommand(Functions::STATE_T states, uint8_t function, uint8_t sizeOfStates, uint8_t range)
{
  EepromStruct& eeprom = EepromStruct::getInstance();

  if(states.notCount != 0)
  {
    char message[30];
    snprintf(message, sizeof(message), "ERROR=%d,%d,%d\n", eeprom.eepromData.id , function, states.notCount);
    Communication::sendDataToUart(uart1, message);
    Communication::sendDataToUart(uart0, message);
    return false;
  }
  else if(states.states.size() != sizeOfStates + 1 && sizeOfStates != 0)
  {
    char message[30];
    snprintf(message, sizeof(message), "ERROR=%d,%d,1\n", eeprom.eepromData.id , function);
    Communication::sendDataToUart(uart1, message);
    Communication::sendDataToUart(uart0, message);
    return false;
  }
  for(uint8_t i = 0; i < sizeOfStates; i++ && range != 0)
  {
    if(states.states[i + 1] > range)
    {
      char message[30];
      snprintf(message, sizeof(message), "ERROR=%d,%d,4\n", eeprom.eepromData.id , function);
      Communication::sendDataToUart(uart1, message);
      Communication::sendDataToUart(uart0, message);
      return false;
    }
  }

  return true;
}
