/*
* app.c
*
* Created: 5/30/2023 2:25:22 PM
*  Author: Alaa
*/

#include "interrupts.h"

#include "led_interface.h"
#include "btn_interface.h"
#include "sos_interface.h"

#include "app.h"

static void app_led0(void);
static void app_led1(void);
static void app_start_btn(void);
static void app_stop_btn(void);

static str_btn_config_t_ gl_str_start_btn;
static str_btn_config_t_ gl_str_stop_btn;

static str_sos_task_t_ gl_str_led0_task;
static str_sos_task_t_ gl_str_led1_task;
static str_sos_task_t_ gl_str_stop_btn_task;

static enu_btn_state_t_ gl_enu_start_btn_state = BTN_STATE_NOT_PRESSED;
static enu_btn_state_t_ gl_enu_stop_btn_state = BTN_STATE_NOT_PRESSED;


void app_init(void)
{
	
	/* Initialize LEDs */
	enu_led_error_t_ lo_enu_led_status = 0;
	lo_enu_led_status = led_init(APP_LED_0_PORT, APP_LED_0_PIN);
	lo_enu_led_status += led_init(APP_LED_1_PORT, APP_LED_1_PIN);
	
	if(lo_enu_led_status != LED_OK) {return;}
	
	/* Initialize push buttons */
	gl_str_start_btn = (str_btn_config_t_)
	{
		.enu_btn_port	    = APP_START_ENU_BTN_PORT		,
		.enu_btn_pin	    = APP_START_ENU_BTN_PIN 		,
		.enu_btn_read_mode  = BTN_MODE_INTERRUPT			,
		.enu_btn_pull_type  = BTN_EXTERNAL_PULL_DOWN		,
		.enu_btn_activation = BTN_ACTIVATED
	};
	
	gl_str_stop_btn = (str_btn_config_t_)
	{
		.enu_btn_port	    = APP_STOP_ENU_BTN_PORT			,
		.enu_btn_pin	    = APP_STOP_ENU_BTN_PIN 			,
		.enu_btn_read_mode  = BTN_MODE_INTERRUPT			,
		.enu_btn_pull_type  = BTN_EXTERNAL_PULL_DOWN		,
		.enu_btn_activation = BTN_ACTIVATED
	};
	
	enu_btn_status_code_t_ lo_enu_btn_status;
	
	lo_enu_btn_status = btn_init(&gl_str_start_btn);
	lo_enu_btn_status += btn_set_notification(&gl_str_start_btn, app_start_btn);
	lo_enu_btn_status += btn_init(&gl_str_stop_btn);
	
	if(lo_enu_btn_status != BTN_STATUS_OK) {return;}
	
	/* Initialize the SOS */
	enu_sos_status_t_ lo_enu_sos_status = sos_init();
	
	if(lo_enu_sos_status != SOS_STATUS_SUCCESS) {return;}
	
	/* Create Tasks */
	gl_str_led0_task = (str_sos_task_t_)
	{
		.uint8_task_id			 = NULL		 ,
		.uint8_task_priority	 = 1		 ,
		.uint16_task_periodicity = 15		 ,
		.ptr_func_task			 = app_led0
	};
	
	gl_str_led1_task = (str_sos_task_t_)
	{
		.uint8_task_id			 = NULL		 ,
		.uint8_task_priority	 = 1		 ,
		.uint16_task_periodicity = 25		 ,
		.ptr_func_task			 = app_led1
	};
	
	gl_str_stop_btn_task = (str_sos_task_t_)
	{
		.uint8_task_id			 = NULL			 ,
		.uint8_task_priority	 = 0			 ,
		.uint16_task_periodicity = 1			 ,
		.ptr_func_task			 = app_stop_btn
	};
	
	sos_create_task(&gl_str_led0_task);
	sos_create_task(&gl_str_led1_task);
	sos_create_task(&gl_str_stop_btn_task);
	
	/* Enable global interrupt */
	sei();
}


void app_start(void)
{
	while(1)
	{
		/* Check if start button is pressed */
		if(gl_enu_start_btn_state == BTN_STATE_PRESSED)
		{
			/* Reset button state */
			gl_enu_start_btn_state = BTN_STATE_NOT_PRESSED;
			
			/* Run the operating system */
			sos_run();
		}	
		else
		{
			/* Do Nothing */
		}
	}
}


static void app_led0(void)
{
	led_toggle(APP_LED_0_PORT, APP_LED_0_PIN);
}

static void app_led1(void)
{
	led_toggle(APP_LED_1_PORT, APP_LED_1_PIN);
}

static void app_stop_btn(void)
{
	btn_read(&gl_str_stop_btn, &gl_enu_stop_btn_state);
	
	if(gl_enu_stop_btn_state == BTN_STATE_PRESSED)
	{
		sos_disable();
	}
}

static void app_start_btn(void)
{
	gl_enu_start_btn_state = BTN_STATE_PRESSED;
}