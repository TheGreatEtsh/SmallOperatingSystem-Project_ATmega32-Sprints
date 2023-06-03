/*
* SOS.c
*
* Created: 5/30/2023 2:18:36 PM
* Author :
*/

#include "led_interface.h"

#include "app.h"

int main(void)
{
	enu_app_init_status_t_ enu_init_status;
	
	enu_init_status = app_init();
	
	if(APP_INIT_SUCCESS == enu_init_status)
	{
		app_start();
	}
	else
	{
		/* Turn on error indication LED */
		while(LED_OK != led_init(LED_PORT_A, LED_PIN_0));
		while(LED_OK != led_on(LED_PORT_A, LED_PIN_0));
		
		while(1);
	}
}

