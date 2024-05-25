#include <string>
#include <vector>
#include <cstdio>

#include "../communication/communication.h"
#include "error.h"
#include "komendyAT.h"

bool isNumber(const std::string& s)
{
  for(uint8_t i = 0; i < s.size(); i++) {
    if (!isdigit(s[i]))     return false;
  }
  return true;
}


void KomendyAT::parseMessage(const std::string& message, uart_inst_t* uart)
{
  uint8_t counter = 0;
  uint8_t notCount = 0;
  std::string function, bar;
  size_t position = message.find('=');
  if (position != std::string::npos)
  {
    function = message.substr(0, position);
    bar = message.substr(position + 1);

    static std::vector<std::string> cStates;
    std::vector<uint8_t> states;
    size_t start = 0, end;

    while ((end = bar.find(',', start)) != std::string::npos)
    {
      std::string token = bar.substr(start, end - start);
      if (!token.empty() )
      {
        if(isNumber(token))
        {
          cStates.push_back(token);
          states.push_back(static_cast<uint8_t>(std::stoi(token)));
        }
        else
        {
          if(counter == 0)  notCount = 2;
          else notCount = 5;
        }
        counter++;
      }
      start = end + 1;
      if (bar.find(',', start) == std::string::npos)    break;

    }

    std::string lastToken = bar.substr(start);
    if (!lastToken.empty())
    {
      if(isNumber(lastToken))
      {
        cStates.push_back(lastToken);
        states.push_back(static_cast<uint8_t>(std::stoi(lastToken)));
      }
      else
      {
        if(counter == 0)  notCount = 2;
        else notCount = 5;
      }
      counter++;
    }
    EepromStruct& eeprom = EepromStruct::getInstance();
    if (states[0] == eeprom.eepromData.id)
    {
      KomendyAT::withGoodId(function, {notCount, uart, "0", states});
    }
    else
    {
      KomendyAT::withBadId(function, {notCount, uart, message, states});
    }
  }

}
void KomendyAT::sendCommandToUart(uart_inst_t *uart, char *function, uint8_t* states, uint8_t sizeOfStates, char* id) {
    std::vector<char> message;

    for (size_t i = 0; function[i] != '\0'; ++i) {
        message.push_back(function[i]);
    }
    message.push_back('=');
    for (uint8_t i = 0; i < 3; i++) {
        if (id[i] != '\0') {
            message.push_back(id[i]);
        } else {
            break;
        }
    }
    if(sizeOfStates != 0)
    {
        message.push_back(',');
        for (size_t i = 0; i < sizeOfStates; i++) {
            if(i != sizeOfStates - 1)
            {
                message.push_back(states[i] + '0');
                message.push_back(',');
            } else
            {
                message.push_back(states[i] + '0');
                message.push_back('\n');
            }
        }
    } else
    {
        message.push_back('\n');
    }
    message.push_back('\0');
    char messageInChar[50];
    for(size_t i = 0; i < message.size() + 1; i++)
    {
        messageInChar[i] = message[i];
    }
    if(uart != nullptr)
    {
        Communication::sendDataToUart(uart , messageInChar);
    }
    else
    {
        Communication::sendDataToUart(uart1 , messageInChar);
        Communication::sendDataToUart(uart0 , messageInChar);
    }

}

void KomendyAT::sendCommandTemperature(float temp, char *id, uint8_t pin) {
    int integerPart = static_cast<int>(temp);
    int decimalPart = static_cast<int>((temp - (float)integerPart) * 10);
    char message[50];

    sprintf(message, "T=%s,%d,%d,%d\n", id, pin + 1, integerPart, decimalPart);

    if(Temperature.decimalPart[pin] != decimalPart || Temperature.integralPart[pin] != integerPart)
    {
        Communication::sendDataToUart(uart0 , message);
        Communication::sendDataToUart(uart1 , message);

        Temperature.decimalPart[pin] = decimalPart;
        Temperature.integralPart[pin] = integerPart;
    }
}

void KomendyAT::withGoodId(std::string& flag_name , Functions::STATE_T state) {
  auto it = goodIdMap.find(flag_name);
  if (it != goodIdMap.end()) {
    if(error::checkCommand(state , it->second.second.functionNumber ,it->second.second.sizeOfFunction , it->second.second.functionRange))   it->second.first(state);
  }
}
void KomendyAT::withBadId(std::string& flag_name , Functions::STATE_T state) {
  auto it = goodIdMap.find(flag_name);
  if (it != goodIdMap.end()) {
    if(error::checkCommand(state , it->second.second.functionNumber ,it->second.second.sizeOfFunction , it->second.second.functionRange))   it->second.first(state);
  }
  else
  {
    Functions::badIdCommandDontExist(state);
  }
}


