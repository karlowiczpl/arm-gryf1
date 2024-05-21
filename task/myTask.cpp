#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"

#include "myTask.h"
#include "../communication/communication.h"
#include "../komendy_AT/checkPins.h"
#include "../komendy_AT/komendyAT.h"

void Task::readFromUart0(void *pvParameters)
{
    char* message;

    while (true)
    {
        message = Communication::readDataFromUart(uart0);
        KomendyAT::parseMessage(message , uart0);
    }
}
void Task::readFromUart1(void *pvParameters)
{
    char* message;

    while (true)
    {
        message = Communication::readDataFromUart(uart1);
        KomendyAT::parseMessage(message , uart1);
    }

}
void Task::writeToUart(void *pvParameters)
{
    while (true)
    {
        CheckPins::checkInputPins();
    }
}
void Task::writeStatusCommand(void *pvParameters)
{
    while (true)
    {
        CheckPins::writeActualOutputState();
        CheckPins::writeActualInputState();
        vTaskDelay(5000);
    }
}

void Task::temperature(void *pvParameters) {
    KomendyAT kom{};
    Setup::setup();
    std::vector<One_wire> one_wires;
    for(unsigned char i : HardwareInfo.temperature)
    {
        One_wire oneWire(i);
        oneWire.init();
        one_wires.push_back(oneWire);
    }
    rom_address_t address {};
    EepromStruct& eeprom = EepromStruct::getInstance();
    while (true)
    {
        for(uint8_t i = 0; i < TEMPERATURE_COUNT; i++)
        {
            one_wires[i].single_device_read_rom(address);
            if(address.rom[0] != 0)
            {
                one_wires[i].convert_temperature(address , true , false);
                char id[3];
                sprintf(id , "%d" , eeprom.eepromData.id);
                kom.sendCommandTemperature(one_wires[i].temperature(address) , id , i);
            }
        }
        vTaskDelay(3000);
    }
}



