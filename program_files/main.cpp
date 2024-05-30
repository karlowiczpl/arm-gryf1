#include "FreeRTOS.h"
#include "task.h"

#include "../setup/hardware/setup.hpp"
#include "task/myTask.h"

int main() {
  Setup::setup();


  xTaskCreate(Task::readFromUart0 , "readFromUart0" , 2048, nullptr , 2, nullptr);
  xTaskCreate(Task::readFromUart1 , "readFromUart1" , 2048, nullptr , 2, nullptr);
#if INPUTS_COUNT || OUTPUTS_COUNT
  xTaskCreate(Task::writeToUart , "writeToUart" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
  xTaskCreate(Task::writeStatusCommand , "writeStatus" , configMINIMAL_STACK_SIZE, nullptr , 2, nullptr);
#endif
#if TEMPERATURE_COUNT
  xTaskCreate(Task::temperature, "temperature", 2048, nullptr, 3, nullptr);
#endif



  vTaskStartScheduler();

  while (true)     {}
}