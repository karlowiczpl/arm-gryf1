#include "setup.hpp"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include "../../program_files/eeprom/eprom.h"

void Setup::setup()
{
    stdio_init_all();

    Setup::setupOutputs();
    Setup::setupCommunication();
    Setup::setupInputs();
    Setup::setupPwm();

    Setup::loadStatesFromEeprom();
}

void Setup::setupOutputs()
{
    for(unsigned char output : HardwareInfo.outputs)
    {
        gpio_init(output);
        gpio_set_dir(output , GPIO_OUT);
    }
}
void Setup::setupInputs()
{
    for(unsigned char input : HardwareInfo.inputs)
    {
        gpio_init(input);
        gpio_set_dir(input , GPIO_IN);
    }
}
void Setup::setupPwm()
{
    for(unsigned char i : HardwareInfo.pwm)
    {
        gpio_init(i);
        gpio_set_function(i , GPIO_FUNC_PWM);

        uint8_t sliceNum = pwm_gpio_to_slice_num(i);

        pwm_config config = pwm_get_default_config();
        pwm_config_set_clkdiv(&config, 4.f);
        pwm_init(sliceNum, &config, true);
    }
}
void Setup::setupCommunication()
{
    gpio_init(UART1_TX_PIN);
    gpio_init(UART1_RX_PIN);
    gpio_init(UART0_TX_PIN);
    gpio_init(UART0_RX_PIN);

    gpio_set_function(UART1_TX_PIN , GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_PIN , GPIO_FUNC_UART);
    gpio_set_function(UART0_TX_PIN , GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN , GPIO_FUNC_UART);

    uart_init(uart0 , BAUD_RATE);
    uart_init(uart1 , BAUD_RATE);

    EepromStruct& eeprom = EepromStruct::getInstance();

    for(unsigned char i : HardwareInfo.temperature)
    {
        One_wire oneWire(i);
        oneWire.init();
        eeprom.one_wires.push_back(oneWire);
    }
}
void Setup::loadStatesFromEeprom()
{
  EepromStruct& eeprom = EepromStruct::getInstance();
  eeprom.loadDataFromEeprom();
  for(uint8_t i = 0; i < OUTPUTS_COUNT; i++)
  {
    gpio_put(HardwareInfo.outputs[i] , eeprom.eepromData.outputsStates[i]);
  }
//  eeprom.loadDataFromEeprom();
//  for(uint8_t i = 0; i < PWM_COUNT; i++)
//  {
//    pwm_set_gpio_level(HardwareInfo.pwm[HardwareInfo.pwm[i]], ((eeprom.eepromData.pwmStates[i] * 255) / 100) * (eeprom.eepromData.pwmStates[i] * 255) / 100);
//  }
}
