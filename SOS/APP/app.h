/*
 * app.h
 *
 * Created: 6/1/2023 7:26:28 AM
 *  Author: Alaa
 */ 


#ifndef APP_H_
#define APP_H_

#define APP_LED_0_PORT				LED_PORT_B
#define APP_LED_0_PIN				LED_PIN_4
									
#define APP_LED_1_PORT				LED_PORT_B
#define APP_LED_1_PIN				LED_PIN_5
									
#define APP_START_ENU_BTN_PORT		BTN_PORT_B
#define APP_START_ENU_BTN_PIN		BTN_PIN_2
									
#define APP_STOP_ENU_BTN_PORT		BTN_PORT_C
#define APP_STOP_ENU_BTN_PIN		BTN_PIN_4


typedef enum
{
	APP_INIT_SUCCESS,
	APP_INIT_FAILED
}enu_app_init_status_t_;


enu_app_init_status_t_ app_init(void);
void app_start(void);

#endif /* APP_H_ */