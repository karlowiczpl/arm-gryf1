#include <iostream>

#include "checkPins.h"
#include "../setup/setup.hpp"
#include "../eeprom/eprom.h"

char* CheckPins::checkInputPins()
{
    Setup s1;
    for(uint8_t i = 0; i < INPUTS_COUNT; i++)
    {
        if(gpio_get(s1.HardwareInfo.inputs[i]) != States.input[i])
        {
            States.input[i] = gpio_get(s1.HardwareInfo.inputs[i]);
            static char message[50] = "I=";
            uint8_t counter = 2;
            char id[4] = "12";
            for(uint8_t i = 0; i < 3; i++)
            {
                if(id[i] != '\0')
                {
                    message[counter] = id[i];
                    counter++;
                } else break;
            }
            message[counter] = ',';
            counter++;

            for(uint8_t i = 0; i < INPUTS_COUNT; i++)
            {
                message[counter] = (States.input[i] + 48);
                counter++;
                message[counter] = ',';
                counter++;
            }
            message[counter -= 1] = '\n';

            printf("%s\n" , message);
            return message;
        }
    }
    return 0;
}
char* CheckPins::writeActualInputState()
{
    Setup s1;
    static char message[50] = "I=";
    uint8_t counter = 2;
    char id[4] = "12\0";
    for(uint8_t i = 0; i < 3; i++)
    {
        if(id[i] != '\0')
        {
            message[counter] = id[i];
            counter++;
        } else break;
    }
    message[counter] = ',';
    counter++;
    for(uint8_t i = 0; i < INPUTS_COUNT; i++)
    {
        message[counter] = (48 + gpio_get(s1.HardwareInfo.inputs[i]));
        counter++;
        message[counter] = ',';
        counter++;
    }
    message[counter - 1] = '\n';
    return message;
}
char* CheckPins::writeActualOutputState()
{
    Setup s1;
    static char message[50] = "0=";
    uint8_t counter = 2;
    char id[4] = "12";
    for(uint8_t i = 0; i < 3; i++)
    {
        if(id[i] != '\0')
        {
            message[counter] = id[i];
            counter++;
        } else break;
    }
    message[counter] = ',';
    counter++;
    for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
    {
        message[counter] = (48 + gpio_get_out_level(s1.HardwareInfo.outputs[i]));
        counter++;
        message[counter] = ',';
        counter++;
    }
    message[counter - 1] = '\n';
    return message;
}