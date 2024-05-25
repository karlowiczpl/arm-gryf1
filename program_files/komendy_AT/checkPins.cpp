#include "checkPins.h"
#include "../communication/communication.h"
#include "../task/myTask.h"
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
            KomendyAT::sendCommandToUart(nullptr, fun, States.input,INPUTS_COUNT, id);
            vTaskDelay(20);
        }
    }
}
void CheckPins::checkOutputPins()
{
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
            KomendyAT::sendCommandToUart(nullptr, fun, States.outputs,OUTPUTS_COUNT, ids);
        }
    }
}
void CheckPins::writeActualInputState()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    char fun[] = "I";
    char id[3];
    sprintf(id , "%d" , eeprom.eepromData.id);
    KomendyAT::sendCommandToUart(nullptr, fun, States.input, INPUTS_COUNT, id);
}
void CheckPins::writeActualOutputState()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    char fun[] = "O";
    char id[3];
    sprintf(id , "%d" , eeprom.eepromData.id);
    KomendyAT::sendCommandToUart(nullptr, fun, States.outputs, OUTPUTS_COUNT,
                                 id);
}

void CheckPins::pushButton()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    for(uint8_t i = 0; i < INPUTS_COUNT; i++) {
        uint8_t currentState = gpio_get(HardwareInfo.inputs[i]);

        if (currentState != PushButton.oldState[i]) {
            if (currentState == !eeprom.eepromData.keyState[i]) {
                PushButton.lastTime[i] = time_us_32();
                PushButton.enable[i] = true;
            } else {
                if (us_to_ms(time_us_32() - PushButton.lastTime[i]) > 30 &&
                    us_to_ms(time_us_32() - PushButton.lastTime[i]) < eeprom.eepromData.shortPressTime[i]) {
                    char message[20];
                    sprintf(message, "PS=%d,%d\n", eeprom.eepromData.id, i + 1);
                    Communication::sendDataToUart(uart0, message);
                    Communication::sendDataToUart(uart1, message);
                }
                PushButton.lastTime[i] = time_us_32();
                PushButton.enable[i] = false;
            }
            PushButton.oldState[i] = currentState;
        }

        if (us_to_ms(time_us_32() - PushButton.lastTime[i]) > eeprom.eepromData.longPressTime[i] &&
            PushButton.enable[i] && PushButton.lastTime[i] != eeprom.eepromData.keyState[i]) {
            char message[20];
            sprintf(message, "PL=%d,%d\n", eeprom.eepromData.id, i + 1);
            Communication::sendDataToUart(uart0, message);
            Communication::sendDataToUart(uart1, message);
            PushButton.enable[i] = false;
        }
    }
}
