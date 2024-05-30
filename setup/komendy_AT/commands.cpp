#include "commands.h"
#include "../../program_files/communication/communication.h"

#define commands eeprom.EepromData.Commands

std::map<std::string, std::pair<KomendyAT::enable_fun_ptr, Functions::ErrorStruct>> KomendyAT::cmGoodIdMap = {
    {"CM+InputInit" , {Commands::inputInit , {2 , enumFunctions.other , 255}}},
    {"CM+SetOut" , {Commands::setOut , {2 , enumFunctions.other , 255}}},
    {"CM+Stop" , {Commands::stop , {0 , enumFunctions.other , 255}}},
    {"CM+Delay" , {Commands::delay , {2 , enumFunctions.other , 255}}},
    {"CM+Equal" , {Commands::equal , {2 , enumFunctions.other , 255}}},
    {"CM+EqualTrue" , {Commands::equalTrue , {2 , enumFunctions.other , 255}}},
    {"CM+EqualFalse" , {Commands::equalFalse , {2 , enumFunctions.other , 255}}},
    {"CM+Reset" , {Commands::reset , {1 , enumFunctions.other , 255}}},
    {"CM+Else" , {Commands::elseFun , {0 , enumFunctions.other , 255}}},
};

void Commands::inputInit(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();

  commands.function[0][states.states[1] - 1] =  1;
//  commands.queue1[0][states.states[1] - 1] =  states.states[1];
//  commands.queue2[0][states.states[1] - 1] =  states.states[2];
  commands.size[states.states[1] - 1] = 1;

  eeprom.programingPin = states.states[1] - 1;

  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
}
void Commands::setOut(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::setOut;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[1] - 1;
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[2];
  commands.size[eeprom.programingPin]++;

  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
}
void Commands::stop(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
}
void Commands::delay(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::mDelay;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[1] - 1;
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[2];
  commands.size[eeprom.programingPin]++;

  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
}
void Commands::equal(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::equal;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[1];
//  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  3;
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[2];
  commands.size[eeprom.programingPin]++;

  vTaskDelay(100);

//  char message[50];
//  sprintf(message , "%d , %d , %d\n" , commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] , commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] , commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin]);
//  Communication::sendDataToUart(uart0 , message);
//  Communication::sendDataToUart(uart1 , message);


  eeprom.saveDataToEeprom();
  eeprom.loadDataFromEeprom();
}
void Commands::reset(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  if(states.states[1] != 0)
  {
    commands.size[states.states[1]] = 0;
  }
  else
  {
    for(uint8_t i = 0; i < INPUTS_COUNT; i++)
    {
      commands.size[i] = 0;
    }
  }
    eeprom.saveDataToEeprom();
    eeprom.loadDataFromEeprom();
}
void::Commands::elseFun(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::elseFun;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  0;
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  0;
  commands.size[eeprom.programingPin]++;
}

void Commands::equalTrue(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::equalTrue;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[1];
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[2];
  commands.size[eeprom.programingPin]++;

  vTaskDelay(100);
}
void Commands::equalFalse(Functions::STATE_T states)
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  commands.function[commands.size[eeprom.programingPin]][eeprom.programingPin] =  funEnum::equalFalse;
  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[1];
  //  commands.queue1[commands.size[eeprom.programingPin]][eeprom.programingPin] =  3;
  commands.queue2[commands.size[eeprom.programingPin]][eeprom.programingPin] =  states.states[2];
  commands.size[eeprom.programingPin]++;

  vTaskDelay(100);
}

void Commands::newFunction(void *pvParameters)
{
  EepromStruct& eeprom = EepromStruct::getInstance();

  char mess[50];

//  char message[] = "TEST\n";
//  Communication::sendDataToUart(uart0 , message);
//  Communication::sendDataToUart(uart1 , message);

  for(uint8_t j = 1; j < commands.size[eeprom.inputPin]; j++)
  {
    sprintf(mess , "%d, %d, %d\n" , commands.function[j][eeprom.inputPin] , commands.queue1[j][eeprom.inputPin] , commands.queue2[j][eeprom.inputPin]);
      Communication::sendDataToUart(uart0 , mess);
      Communication::sendDataToUart(uart1 , mess);
    if(commands.function[j][eeprom.inputPin] == funEnum::setOut)
    {
      if(commands.queue2[j][eeprom.inputPin] != 3)
      {
        gpio_put(HardwareInfo.outputs[commands.queue1[j][eeprom.inputPin]] , commands.queue2[j][eeprom.inputPin] == 1 ? 1 : 0);
      } else
      {
        gpio_put(HardwareInfo.outputs[commands.queue1[j][eeprom.inputPin]] , !gpio_get_out_level(HardwareInfo.outputs[commands.queue1[j][eeprom.inputPin]]));
      }
    }
    else if(commands.function[j][eeprom.inputPin] == funEnum::mDelay)
    {
      vTaskDelay(commands.queue2[j][eeprom.inputPin] * commands.queue1[j][eeprom.inputPin]);
    }
    else if(commands.function[j][eeprom.inputPin] == funEnum::equal)
    {
      uint8_t x;
      if(commands.queue1[j][eeprom.inputPin] == pinsType::input)   x = gpio_get(HardwareInfo.inputs[commands.queue2[j][eeprom.inputPin]]);
      else x = gpio_get_out_level(HardwareInfo.outputs[commands.queue2[j][eeprom.inputPin]]);

      if(x == gpio_get(HardwareInfo.inputs[HardwareInfo.inputs[eeprom.inputPin]]))
      {
        continue;
      }
      else
      {
        break;
      }

    }
    else if(commands.function[j][eeprom.inputPin] == funEnum::equalTrue) {
      uint8_t x;
      if (commands.queue1[j][eeprom.inputPin] == pinsType::input)
        x = gpio_get(HardwareInfo.inputs[commands.queue2[j][eeprom.inputPin]]);
      else
        x = gpio_get_out_level(
            HardwareInfo.outputs[commands.queue2[j][eeprom.inputPin]]);

      if (x == 1) {
        continue;
      } else {
        while (j < commands.size[eeprom.inputPin]) {
          if (commands.function[j][eeprom.inputPin] == funEnum::elseFun) {
            j++;
            break;
          }
          j++;
        }
      }
    }
    else if(commands.function[j][eeprom.inputPin] == funEnum::equalFalse) {
      uint8_t x;
      if (commands.queue1[j][eeprom.inputPin] == pinsType::input)
        x = gpio_get(HardwareInfo.inputs[commands.queue2[j][eeprom.inputPin]]);
      else
        x = gpio_get_out_level(
            HardwareInfo.outputs[commands.queue2[j][eeprom.inputPin]]);

      if (x == 0) {
        continue;
      } else {
        while (j < commands.size[eeprom.inputPin]) {
          if (commands.function[j][eeprom.inputPin] == funEnum::elseFun) {
            j++;
            break;
          }
          j++;
        }
      }
    }
  }
  vTaskDelete(NULL);
}
