#include <iostream>
#include <string>
#include <vector>
#include "pico/stdlib.h"
//#include <cstdlib>
//#include <cstring>
//#include <cstdint>

#include "komendyAT.h"
#include "../setup/setup.hpp"

void KomendyAT::parseMessage(std::string message)
{
    std::string function, bar;
    size_t position = message.find('=');
    if (position != std::string::npos)
    {
        function = message.substr(0, position);
        bar = message.substr(position + 1);

        std::vector<uint8_t> states;
        size_t start = 0, end = 0;
        while ((end = bar.find(',', start)) != std::string::npos) {
            std::string token = bar.substr(start, end - start);
            states.push_back(std::stoi(token));
            start = end + 1;
        }
        std::string lastToken = bar.substr(start);
        states.push_back(std::stoi(lastToken));
        KomendyAT k1;
        Eeprom e1;
        if(states[0] == 1) //pobierz id
        {
            if(function == "AT+SetOut")
            {
                k1.setOut(states);
            }
            else if(function == "AT+SetLED")
            {
                k1.setPwm(states);
            }
            else if(function == "AT+key")
            {
                k1.setKey(states);
            }
            else if(function == "AT+RST")
            {
                k1.reset(states);
            }
            else if(function == "PING")
            {
                k1.ping(states);
            }
            else
            {
                std::cout<<"UNOWN FUNCTION"<<std::endl;
            }
        }
        else
        {
            if(function == "AT+Search")
            {
                std::cout<<"Licznik: "<<states[0]<<" Szukane id: "<<states[1]<<std::endl;
                k1.setId(states);
            }
            else
            {
                Eeprom e1;
//                std::cout<<"UNOWN ID"<<" myId: "<<e1.getId()<<std::endl;
            }
        }
    }
}
void KomendyAT::setOut(std::vector<uint8_t> states)
{
    Setup setup;
    uint8_t size = states.size();
    for(uint8_t i = 0; i < size ; i++)
    {
        gpio_put(setup.HardwareInfo.outputs[i] , states[i]);
    }
}
void KomendyAT::setPwm(std::vector<uint8_t> states)
{
    std::cout<<"Pwm o numerze "<<states[1]<<", Zostal ustawiont na "<<states[2]<<"%"<<std::endl;
}
void KomendyAT::setId(std::vector<uint8_t> states)
{
    if(states[0] == states[1])
    {
        Eeprom e1;
        //zmień id
        std::cout<<"Ustawiono id na: "<<states[1]<<std::endl;
    }
    else
    {
        //inkrementuj + przesli na przeciwny port
    }
}
void KomendyAT::setKey(std::vector<uint8_t> states)
{

}

void KomendyAT::reset(std::vector<uint8_t> states)
{

}
void KomendyAT::ping(std::vector<uint8_t> states)
{

}



