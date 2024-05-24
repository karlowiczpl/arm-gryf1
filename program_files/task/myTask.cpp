#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"

#include "../../communication/communication.h"
#include "../../komendy_AT/checkPins.h"
#include "myTask.h"

void Task::readFromUart0(void *pvParameters)
{
    while (true)
    {
        KomendyAT::parseMessage(Communication::readDataFromUart(uart0) , uart0);
    }
}
void Task::readFromUart1(void *pvParameters)
{
    while (true)
    {
        KomendyAT::parseMessage(Communication::readDataFromUart(uart1) , uart1);
    }

}
void Task::writeToUart(void *pvParameters)
{
    while (true)
    {
        #if INPUTS_COUNT
        CheckPins::checkInputPins();
        CheckPins::pushButton();
        #endif
        #if OUTPUTS_COUNT
        CheckPins::checkOutputPins();
        #endif
    }
}
void Task::writeStatusCommand(void *pvParameters)
{
    while (true)
    {
        #if OUTPUTS_COUNT
        CheckPins::writeActualOutputState();
        #endif
        #if INPUTS_COUNT
        CheckPins::writeActualInputState();
        #endif
        vTaskDelay(5000);
    }
}

void Task::temperature(void *pvParameters) {
    while (true)
    {
        Communication::oneWireTemperature();
        vTaskDelay(5000);
    }
}
