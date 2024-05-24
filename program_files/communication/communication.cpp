#include "hardware/uart.h"
#include <cstring>

#include "communication.h"
#include "../komendy_AT/komendyAT.h"

char* Communication::readDataFromUart(uart_inst_t* uart)
{
    if(uart_is_readable(uart))
    {
        static char message[50];
        memset(message , 0 , sizeof(message));
        uint8_t counter = 0;
        while ( true )
        {
            message[counter] = uart_getc(uart);
            if(message[counter] == '\n')
            {
                message[counter] = '\0';
                return message;
            }
            counter++;
        }
    }
}

void Communication::sendDataToUart(uart_inst_t* uart, char* message) {
    uart_puts(uart , message);
}

void Communication::oneWireTemperature()
{
    EepromStruct& eeprom = EepromStruct::getInstance();
    KomendyAT kom{};
    rom_address_t address {};
    for(uint8_t i = 0; i < TEMPERATURE_COUNT; i++)
    {
        eeprom.one_wires[i].single_device_read_rom(address);
        if(address.rom[0] != 0)
        {
            eeprom.one_wires[i].convert_temperature(address , true , false);
            char id[3];
            sprintf(id , "%d" , eeprom.eepromData.id);
            kom.sendCommandTemperature(eeprom.one_wires[i].temperature(address) , id , i);
        }
    }
}
