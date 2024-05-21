#include "error.h"
#include "../setup/setup.hpp"
#include "komendyAT.h"

bool error::checkCommand(std::string message, uint8_t size, bool letters) {


    return false;
}

uint8_t error::getFunctionNumber(std::string function) {
    if(function == "AT+SetOut")     return 1;
    else if(function == "AT+SetRol")     return 2;
    else if(function == "AT+SetLamp")     return 3;
    else if(function == "O")     return 4;
    else if(function == "I")     return 5;
    else if(function == "L")     return 6;
    else if(function == "PS")     return 7;
    else if(function == "PL")     return 8;
    else return 0;
}
