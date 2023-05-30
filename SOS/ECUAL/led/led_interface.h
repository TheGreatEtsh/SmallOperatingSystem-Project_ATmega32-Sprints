/**
 * @file    :   led_interface.h
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   Header File contains all LED typedefs and functions' prototypes
 * @version :   2.0
 * @date    :   2023-05-29
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LED_H_
#define LED_H_

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"

typedef enum EN_LED_ERROR_t
{
    LED_OK              = 0 ,
    LED_ERROR               ,
}enu_led_error_t_;

/**
 * @brief                       :   Initializes LED on given port & pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_init(enu_dio_port_t_ enu_led_port, enu_dio_pin_t_ enu_led_pin);   // initialize LED

/**
 * @brief                       :   Turns on LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_on(enu_dio_port_t_ enu_led_port, enu_dio_pin_t_ enu_led_pin);     // turn LED on

/**
 * @brief                       :   Turns off LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_off(enu_dio_port_t_ enu_led_port, enu_dio_pin_t_ enu_led_pin);    // turn LED off


/**
 * @brief                       :   Toggles LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_toggle(enu_dio_port_t_ enu_led_port, enu_dio_pin_t_ enu_led_pin); // toggle LED

#endif /* LED_H_ */