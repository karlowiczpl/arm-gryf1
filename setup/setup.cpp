#include "setup.hpp"
#include "pico/stdlib.h"
#include "stdio.h"
//#include "hardware/pwm.h"

void Setup::setup()
{

    stdio_init_all();

    Setup s1;
    s1.setupOutputs();
    s1.setupCommunication();
    s1.setupInputs();
}

void Setup::setupOutputs()
{
    for(uint8_t i = 0; i < sizeof(HardwareInfo.outputs); i++)
    {
        gpio_init(HardwareInfo.outputs[i]);
        gpio_set_dir(HardwareInfo.outputs[i] , GPIO_OUT);
    }
}
void Setup::setupInputs()
{
    for(uint8_t i = 0; i < sizeof(HardwareInfo.inputs); i++)
    {
        gpio_init(HardwareInfo.inputs[i]);
        gpio_set_dir(HardwareInfo.inputs[i] , GPIO_IN);
    }
}
void Setup::setupTemperature()
{
    for(uint8_t i = 0; i < sizeof(HardwareInfo.temperature); i++)
    {
        //implementacja one-wire
    }
}
void Setup::setupPwm()
{
    for(uint8_t i = 0; i < sizeof(HardwareInfo.pwm); i++)
    {
        gpio_init(HardwareInfo.pwm[i]);
        gpio_set_function(HardwareInfo.pwm[i] , GPIO_FUNC_PWM);

//        uint8_t sliceNum = pwm_gpio_to_slice_num(HardwareInfo.pwm[i]);
//
//        pwm_config config = pwm_get_default_config();
//        pwm_config_set_clkdiv(&config, 4.f);
//        pwm_init(sliceNum, &config, true);
    }
}
void Setup::setupCommunication()
{
    gpio_init(UART1_PIN);
    gpio_init(UART1_PIN + 1);
    gpio_init(UART0_PIN);
    gpio_init(UART0_PIN + 1);

    gpio_set_function(UART1_PIN , GPIO_FUNC_UART);
    gpio_set_function(UART1_PIN + 1 , GPIO_FUNC_UART);
    gpio_set_function(UART0_PIN , GPIO_FUNC_UART);
    gpio_set_function(UART0_PIN + 1 , GPIO_FUNC_UART);

    uart_init(uart0 , 9600);
    uart_init(uart1 , 9600);

    printf("SKONFIGUROWANO");
}
