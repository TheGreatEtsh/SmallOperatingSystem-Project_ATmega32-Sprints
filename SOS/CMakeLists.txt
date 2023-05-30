cmake_minimum_required(VERSION 3.25)
project(SOS C)

set(CMAKE_C_STANDARD 11)

include_directories(ECUAL/led)
include_directories(LIB)
include_directories(MCAL/dio)
include_directories(SERV)
include_directories(SERV/sos)

add_executable(SOS
        APP/CFile1.c
        ECUAL/button/CFile1.c
        ECUAL/led/led_interface.h
        ECUAL/led/led_program.c
        LIB/bit_math.h
        LIB/interrupts.h
        LIB/std.h
        MCAL/dio/dio_interface.h
        MCAL/dio/dio_private.h
        MCAL/dio/dio_program.c
        MCAL/exi/CFile1.c
        SERV/sos/sos_interface.h
        main.c)
