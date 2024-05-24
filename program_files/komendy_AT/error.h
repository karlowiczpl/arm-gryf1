#ifndef PLCSPECIAL_ERROR_H
#define PLCSPECIAL_ERROR_H

#include <iostream>
#include <vector>
#include "pico/stdlib.h"

#include "../../setup/komendy_AT/functions.h"

struct
{
  enum
  {
    other = 0,
    setOut = 1,
    setRol = 2,
    setLamp = 3,
    output = 4,
    input = 5,
    lamp = 6,
    pressShort = 7,
    pressLong = 8,
  };
}enumFunctions;


class error {

public:
    static bool checkCommand(Functions::STATE_T states, uint8_t function , uint8_t sizeOfStates , uint8_t functionRange);
};


#endif //PLCSPECIAL_ERROR_H
