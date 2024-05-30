#ifndef PLCSPECIAL_SETUP_KOMENDY_AT_COMMANDS_H_
#define PLCSPECIAL_SETUP_KOMENDY_AT_COMMANDS_H_

#include "functions.h"
#include "../../program_files/komendy_AT/komendyAT.h"
#include "../../program_files/eeprom/eprom.h"

#include "FreeRTOS.h"
#include "task.h"

enum funEnum
{
  setOut = 1,
  mDelay = 2,
  equal = 3,
  elseFun = 4,
  equalTrue = 5,
  equalFalse = 6,
};
enum pinsType
{
  input = 0,
  output = 1,
};

class Commands {
public:
  static void inputInit(Functions::STATE_T states);
  static void setOut(Functions::STATE_T  states);
  static void stop(Functions::STATE_T states);
  static void delay(Functions::STATE_T states);
  static void equal(Functions::STATE_T states);
  static void reset(Functions::STATE_T states);
  static void elseFun(Functions::STATE_T states);
  static void equalTrue(Functions::STATE_T states);
  static void equalFalse(Functions::STATE_T states);


  static void newFunction(void *pvParameters);
};
#endif // PLCSPECIAL_SETUP_KOMENDY_AT_COMMANDS_H_
