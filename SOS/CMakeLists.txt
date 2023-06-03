cmake_minimum_required(VERSION 3.25)
project(SOS C)

set(CMAKE_C_STANDARD 11)

include_directories(ECUAL/led)
include_directories(ECUAL/button)
include_directories(LIB)
include_directories(MCAL/dio)
include_directories(MCAL/exi)
include_directories(MCAL/timer)
include_directories(SERV)
include_directories(SERV/sos)

add_executable(SOS
        LIB/bit_math.h
        LIB/interrupts.h
        LIB/std.h

        MCAL/dio/dio_interface.h
        MCAL/dio/dio_private.h
        MCAL/dio/dio_program.c

        MCAL/exi/exi_cfg.c
        MCAL/exi/exi_cfg.h
        MCAL/exi/exi_interface.h
        MCAL/exi/exi_private.h
        MCAL/exi/exi_program.c

        MCAL/timer/timer_program.c
        MCAL/timer/timer_interface.h
        MCAL/timer/timer_private.h
        MCAL/timer/timer_cfg.c
        MCAL/timer/timer_cfg.h

        ECUAL/led/led_interface.h
        ECUAL/led/led_program.c

        ECUAL/button/btn_program.c
        ECUAL/button/btn_interface.h


        SERV/sos/sos_interface.h
        SERV/sos/sos_preconfig.h
        SERV/sos/sos_private.h
        SERV/sos/sos_program.c

        LIB/bit_math.h
        LIB/interrupts.h
        LIB/std.h

        main.c

        APP/app.c
        APP/app.h
        )
