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
        CheckPins::checkInputPins(time_us_32());
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

void Task::pressButton(void *pvParameters) {
    EepromStruct& eeprom = EepromStruct::getInstance();

    uint8_t oldState[INPUTS_COUNT] = {0};
    uint32_t lastTime[INPUTS_COUNT] = {0};
    bool enable[INPUTS_COUNT] = {false};

    while (true)
    {
        for(uint8_t i = 0; i < INPUTS_COUNT; i++)
        {
            uint8_t currentState = gpio_get(HardwareInfo.inputs[i]);

            if(currentState != oldState[i])
            {
                if(currentState == 1)
                {
                    lastTime[i] = time_us_32();
                    enable[i] = true;
                }
                else
                {
                    if(us_to_ms(time_us_32() - lastTime[i]) > 30 && us_to_ms(time_us_32() - lastTime[i]) < eeprom.eepromData.shortPressTime[i])
                    {
                        char message[20];
                        sprintf(message , "PS=%d,%d\n" , eeprom.eepromData.id , i + 1);
                        Communication::sendDataToUart(uart0 , message);
                        Communication::sendDataToUart(uart1 , message);
                    }
                    lastTime[i] = time_us_32();
                    enable[i] = false;
                }
                oldState[i] = currentState;
            }

            if(us_to_ms(time_us_32() - lastTime[i]) > eeprom.eepromData.longPressTime[i] && enable[i] && lastTime[i] != 0)
            {
                char message[20];
                sprintf(message , "PL=%d,%d\n" , eeprom.eepromData.id , i + 1);
                Communication::sendDataToUart(uart0 , message);
                Communication::sendDataToUart(uart1 , message);
                enable[i] = false;
            }
        }
    }
}