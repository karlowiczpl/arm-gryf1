
#ustawienie minimalnej wersji cmake
cmake_minimum_required(VERSION 3.12)

SET(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)


#SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
#include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

#ustawienie nazwy projektu, języków i ich wersji
project(plcSpecial C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#inicjalizacja bibliotek pico-sdk
pico_sdk_init()

#find_package(mbedTLS)

#dodanie plików projektu
add_executable(${PROJECT_NAME}
        komendy_AT/komendyAT.cpp
        komendy_AT/komendyAT.h
        eeprom/eprom.cpp
        eeprom/eprom.h
        setup/setup.hpp
        setup/setup.cpp
        main.cpp
        communication/communication.cpp
        communication/communication.h
)

#Utworzenie plików binarnych
pico_add_extra_outputs(${PROJECT_NAME})


add_subdirectory(pico-onewire)

#dodanie funkcji do pico-sdk
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_pwm
        pico_multicore
        hardware_pio
        pico_one_wire
#        FreeRTOS-Kernel-Heap4
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)