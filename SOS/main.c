/*
 * SOS.c
 *
 * Created: 5/30/2023 2:18:36 PM
 * Author : 
 */ 

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
		/* Do Nothing */
	}
}

