cmake_minimum_required(VERSION 3.12)


#Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(adxl343 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#Initial SDK
pico_sdk_init()

add_executable(adxl343
        adxl343.c
	adxl343.h
        )


target_link_libraries(adxl343 pico_stdlib hardware_i2c)
	
#enable USB(by adding 1) and diable UART(by adding 0)
pico_enable_stdio_usb(adxl343 1)

pico_enable_stdio_uart(adxl343 0)

pico_add_extra_outputs(adxl343)


