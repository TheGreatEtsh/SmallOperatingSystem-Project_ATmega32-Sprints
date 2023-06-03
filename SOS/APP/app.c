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


enu_app_init_status_t_ app_init(void)
{
	/* Initialize LEDs */
	enu_led_error_t_ lo_enu_led_status = 0;
	lo_enu_led_status = led_init(APP_LED_0_PORT, APP_LED_0_PIN);
	
	if(lo_enu_led_status != LED_OK) {return APP_INIT_FAILED;}
		
	lo_enu_led_status = led_init(APP_LED_1_PORT, APP_LED_1_PIN);
	
	if(lo_enu_led_status != LED_OK) {return APP_INIT_FAILED;}
	
	/* Start Button Initialization */ 
	gl_str_start_btn.enu_btn_port	    = APP_START_ENU_BTN_PORT	;
	gl_str_start_btn.enu_btn_pin	    = APP_START_ENU_BTN_PIN 	;
	gl_str_start_btn.enu_btn_read_mode  = BTN_MODE_INTERRUPT		;
	gl_str_start_btn.enu_btn_pull_type  = BTN_EXTERNAL_PULL_DOWN	;
	gl_str_start_btn.enu_btn_activation = BTN_ACTIVATED				;
	
	/* Stop Button Initialization */ 
	gl_str_stop_btn.enu_btn_port	   = APP_STOP_ENU_BTN_PORT		;
	gl_str_stop_btn.enu_btn_pin		   = APP_STOP_ENU_BTN_PIN 		;
	gl_str_stop_btn.enu_btn_read_mode  = BTN_MODE_INTERRUPT			;
	gl_str_stop_btn.enu_btn_pull_type  = BTN_EXTERNAL_PULL_DOWN		;
	gl_str_stop_btn.enu_btn_activation = BTN_ACTIVATED				;
	
	enu_btn_status_code_t_ lo_enu_btn_status;
	
	lo_enu_btn_status = btn_init(&gl_str_start_btn);
	
	if(lo_enu_btn_status != BTN_STATUS_OK) {return APP_INIT_FAILED;}
		
	lo_enu_btn_status = btn_set_notification(&gl_str_start_btn, app_start_btn);
	
	if(lo_enu_btn_status != BTN_STATUS_OK) {return APP_INIT_FAILED;}
	
	lo_enu_btn_status = btn_init(&gl_str_stop_btn);
	
	if(lo_enu_btn_status != BTN_STATUS_OK) {return APP_INIT_FAILED;}
	
	/* Initialize the SOS */
	enu_sos_status_t_ lo_enu_sos_status = sos_init();
	
	if(lo_enu_sos_status != SOS_STATUS_SUCCESS) {return APP_INIT_FAILED;}
	
	/* LED 0 Task Initialization */
	gl_str_led0_task.uint8_task_id			 = NULL		 ;
	gl_str_led0_task.uint8_task_priority	 = 1		 ;
	gl_str_led0_task.uint16_task_periodicity = 15		 ;
	gl_str_led0_task.ptr_func_task			 = app_led0	 ;
	
	/* LED 1 Task Initialization */
	gl_str_led1_task.uint8_task_id			 = NULL		 ;
	gl_str_led1_task.uint8_task_priority	 = 1		 ;
	gl_str_led1_task.uint16_task_periodicity = 25		 ;
	gl_str_led1_task.ptr_func_task			 = app_led1	 ;

	/* Stop Button Task Initialization */
	gl_str_stop_btn_task.uint8_task_id			 = NULL			 ;
	gl_str_stop_btn_task.uint8_task_priority	 = 0			 ;
	gl_str_stop_btn_task.uint16_task_periodicity = 1			 ;
	gl_str_stop_btn_task.ptr_func_task			 = app_stop_btn	 ;

	/* Create Tasks */ 
	lo_enu_sos_status = sos_create_task(&gl_str_led0_task);
	
	if(lo_enu_sos_status != SOS_STATUS_SUCCESS) {return APP_INIT_FAILED;}
	
	lo_enu_sos_status = sos_create_task(&gl_str_led1_task);
	
	if(lo_enu_sos_status != SOS_STATUS_SUCCESS) {return APP_INIT_FAILED;}
	
	lo_enu_sos_status = sos_create_task(&gl_str_stop_btn_task);
	
	if(lo_enu_sos_status != SOS_STATUS_SUCCESS) {return APP_INIT_FAILED;}
	
	/* Enable global interrupt */
	sei();
	
	return APP_INIT_SUCCESS;
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
	if(LED_OK != led_toggle(APP_LED_0_PORT, APP_LED_0_PIN))
	{
		/*HANDLING ERROR CODE*/
	}
	else
	{
		/*SUCCESS*/
	}
}

static void app_led1(void)
{
	if(LED_OK != led_toggle(APP_LED_1_PORT, APP_LED_1_PIN))
	{
		/*HANDLING ERROR CODE*/
	}
	else
	{
		/*SUCCESS*/
	}
}

static void app_stop_btn(void)
{
	if(BTN_STATUS_OK != btn_read(&gl_str_stop_btn, &gl_enu_stop_btn_state) )
	{
		/*HANDLING ERROR CODE*/
	}
	else
	{
		/*SUCCESS*/
	}
	
	if(gl_enu_stop_btn_state == BTN_STATE_PRESSED)
	{
		sos_disable();
	}
}

static void app_start_btn(void)
{
	gl_enu_start_btn_state = BTN_STATE_PRESSED;
}