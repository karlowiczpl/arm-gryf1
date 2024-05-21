#include "checkPins.h"
#include "komendyAT.h"

void CheckPins::checkInputPins()
{
    for(uint8_t i = 0; i < INPUTS_COUNT; i++)
    {
        if(gpio_get(HardwareInfo.inputs[i]) != States.input[i])
        {
            EepromStruct& eeprom = EepromStruct::getInstance();
            States.input[i] = gpio_get(HardwareInfo.inputs[i]);
            char fun[] = "I";
            char id[3];
            sprintf(id , "%d" , eeprom.eepromData.id);
            KomendyAT::sendCommandToUartTabble(nullptr , fun , States.input , INPUTS_COUNT , id);
        }
    }
    for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
    {
        if(gpio_get_out_level(HardwareInfo.outputs[i]) != States.outputs[i])
        {
            for(uint8_t j = 0; j < OUTPUTS_COUNT; j++)
            {
                States.outputs[j] = gpio_get_out_level(HardwareInfo.outputs[j]);
            }
            EepromStruct& eeprom = EepromStruct::getInstance();
            char fun[] = "O";
            char ids[3];
            sprintf(ids , "%d" , eeprom.eepromData.id);
            KomendyAT::sendCommandToUartTabble(nullptr , fun , States.outputs , OUTPUTS_COUNT , ids);
        }
    }
}
void CheckPins::writeActualInputState()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    char fun[] = "I";
    char id[3];
    sprintf(id , "%d" , eeprom.eepromData.id);
    KomendyAT::sendCommandToUartTabble(nullptr , fun , States.input , INPUTS_COUNT , id);
}
void CheckPins::writeActualOutputState()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    char fun[] = "O";
    char id[3];
    sprintf(id , "%d" , eeprom.eepromData.id);
    KomendyAT::sendCommandToUartTabble(nullptr , fun , States.outputs , OUTPUTS_COUNT , id);
}