#ifndef PLCSPECIAL_ERROR_H
#define PLCSPECIAL_ERROR_H

#include <iostream>
#include <vector>
#include "pico/stdlib.h"

class error {


public:
    bool checkCommand(std::string message , uint8_t size , bool letters);
    uint8_t getFunctionNumber(std::string function);
};


#endif //PLCSPECIAL_ERROR_H
