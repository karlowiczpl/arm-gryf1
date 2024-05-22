#include "checkPins.h"
#include "komendyAT.h"
#include "../task/myTask.h"

void CheckPins::checkInputPins(uint32_t time)
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
            vTaskDelay(20);
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

void CheckPins::timerOfButtonPress(uint8_t time)
{
    for(unsigned long i : States.inputsTime)
    {

//        if((time - i) < 4000)
//        {
//            printf("Zmienil sie stan\n");
//            printf("%ld\n" , time - i);

//        }
        printf("Wartosc: %ld\n" , time - States.inputsTime[i]);

    }
}
