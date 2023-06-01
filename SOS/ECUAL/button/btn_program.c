/*
* CFile1.c
*
* Created: 5/30/2023 2:24:25 PM
*  Author: Alaa
*/

#include "exi_interface.h"

#include "btn_interface.h"


static enu_btn_status_code_t_ btn_map_to_exi(enu_dio_port_t_ enu_btn_port, enu_dio_pin_t_ enu_btn_pin, enu_exi_id_t_* ptr_enu_btn_exi_id);
/************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

/**
* @brief Function to initialize a given button instance
*
* @param ptr_str_btn_config            : pointer to the desired button structure
*
* @return BTN_STATUS_OK 	            : When the operation is successful
*         BTN_STATUS_INVALID_STATE		: Button structure pointer is a NULL_PTR
*         BTN_STATUS_INVALID_PULL_TYPE : If the pull type field in button structure is set to invalid value
*/
enu_btn_status_code_t_ btn_init(str_btn_config_t_* ptr_str_btn_config)
{
	enu_btn_status_code_t_ lo_enu_btn_status = BTN_STATUS_OK;
	
	if (NULL_PTR != ptr_str_btn_config)
	{
		lo_enu_btn_status =
		dio_init
		(
		ptr_str_btn_config->enu_btn_port,
		ptr_str_btn_config->enu_btn_pin	,
		DIO_IN
		);
		
		if(lo_enu_btn_status == BTN_STATUS_OK)
		{
			switch (ptr_str_btn_config->enu_btn_pull_type)
			{
				case BTN_INTERNAL_PULL_UP:
				{
					lo_enu_btn_status =
					dio_write
					(
					ptr_str_btn_config->enu_btn_port,
					ptr_str_btn_config->enu_btn_pin	,
					DIO_PIN_HIGH
					);
					break;
				}
				case BTN_EXTERNAL_PULL_UP: break;
				case BTN_EXTERNAL_PULL_DOWN: break;
				default : lo_enu_btn_status = BTN_STATUS_INVALID_PULL_TYPE;
			}
			/* Set the button state */
			ptr_str_btn_config->enu_btn_activation = BTN_ACTIVATED;
		}
		else
		{
			lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
		}
	}
	else
	{
		lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
	}
	
	return lo_enu_btn_status;
}

enu_btn_status_code_t_ btn_disable(str_btn_config_t_* ptr_str_btn_config)
{
	enu_btn_status_code_t_ lo_enu_btn_status = BTN_STATUS_OK;
	
	if (NULL_PTR != ptr_str_btn_config)
	{
		if(ptr_str_btn_config->enu_btn_activation == BTN_ACTIVATED)
		{
			switch(ptr_str_btn_config->enu_btn_read_mode)
			{
				case BTN_MODE_INTERRUPT:
				{
					enu_exi_id_t_ enu_exi_id;
					btn_map_to_exi(ptr_str_btn_config->enu_btn_port, ptr_str_btn_config->enu_btn_pin, &enu_exi_id);
					exi_set_state(enu_exi_id, EXI_STATE_DISABLE);
				}
				case BTN_MODE_POLLING:
				{
					ptr_str_btn_config->enu_btn_activation == BTN_DEACTIVATED;
				}
				default: lo_enu_btn_status = BTN_STATUS_INVALID_READ_MODE;
			}

		}
	}
	else
	{
		lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
	}
	
	return lo_enu_btn_status;
}

/**
* @brief Function to read the current button state
*
* @param ptr_str_btn_config            : pointer to the desired button structure
* @param ptr_enu_btn_state             : pointer to variable to store the button state
*
* @return BTN_STATUS_OK                : When the operation is successful
*         BTN_STATUS_INVALID_STATE     : Button structure and/or button state pointers are NULL_PTRs
*         BTN_STATUS_INVALID_PULL_TYPE : If the pull type field in button structure is set to invalid value
*		  BTN_STATUS_DEACTIVATED	   : If we are trying to read from a deactivated button
*/
enu_btn_status_code_t_ btn_read(str_btn_config_t_* ptr_str_btn_config, enu_btn_state_t_* ptr_enu_btn_state)
{
	enu_btn_status_code_t_ lo_enu_btn_status = BTN_STATUS_OK;
	enu_dio_pin_val_t_ lo_enu_btn_val;

	if((ptr_str_btn_config != NULL_PTR) && (ptr_enu_btn_state != NULL_PTR))
	{
		if(BTN_ACTIVATED == ptr_str_btn_config->enu_btn_activation)
		{
			dio_read(ptr_str_btn_config->enu_btn_port, ptr_str_btn_config->enu_btn_pin, &lo_enu_btn_val);

			switch (ptr_str_btn_config->enu_btn_pull_type)
			{
				case BTN_INTERNAL_PULL_UP:
				case BTN_EXTERNAL_PULL_UP:
				{
					*ptr_enu_btn_state = !lo_enu_btn_val;
					break;
				}
				case BTN_EXTERNAL_PULL_DOWN:
				{
					*ptr_enu_btn_state = lo_enu_btn_val;
					break;
				}
				
				default : lo_enu_btn_status = BTN_STATUS_INVALID_PULL_TYPE;
			}
		}
		else
		{
			lo_enu_btn_status = BTN_STATUS_DEACTIVATED;
		}
	}
	else
	{
		lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
	}

	return lo_enu_btn_status;
}

/**
* @brief Function to set a notification function when the given button is pressed
*
* @param ptr_str_btn_config            : pointer to the desired button structure
* @param pv_btn_cbf                    : pointer to the notification function
*
* @return BTN_STATUS_OK                : When the operation is successful
*         BTN_STATUS_INVALID_STATE     : Button structure and/or function pointers are NULL_PTRs
*                                        or if the button is not connected to and EXI pin
*         BTN_STATUS_INVALID_PULL_TYPE : If the pull type field in button structure is set to invalid value
*/
enu_btn_status_code_t_ btn_set_notification(str_btn_config_t_* ptr_str_btn_config, void (*pv_btn_cbf)(void))
{
	enu_btn_status_code_t_ lo_enu_btn_status = BTN_STATUS_OK;
	enu_exi_id_t_ lo_enu_btn_exi_id;
	
	if ((NULL_PTR != ptr_str_btn_config) && (NULL_PTR != pv_btn_cbf))
	{
		lo_enu_btn_status = btn_map_to_exi(ptr_str_btn_config->enu_btn_port, ptr_str_btn_config->enu_btn_pin, &lo_enu_btn_exi_id);
		
		if(BTN_STATUS_OK == lo_enu_btn_status)
		{
			switch (ptr_str_btn_config->enu_btn_pull_type)
			{
				case BTN_INTERNAL_PULL_UP:
				case BTN_EXTERNAL_PULL_UP:
				{
					exi_set_sense(lo_enu_btn_exi_id, EXI_MODE_FALLING_EDGE);
					break;
				}
				
				case BTN_EXTERNAL_PULL_DOWN:
				{
					exi_set_sense(lo_enu_btn_exi_id, EXI_MODE_RISING_EDGE);
					break;
				}
				default : lo_enu_btn_status = BTN_STATUS_INVALID_PULL_TYPE;
			}
			
			if(BTN_STATUS_OK == lo_enu_btn_status)
			{
				exi_set_callback(lo_enu_btn_exi_id, pv_btn_cbf);
				exi_set_state(lo_enu_btn_exi_id, EXI_STATE_ENABLE);
			}
		}
		else
		{
			lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
		}
	}
	else
	{
		lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
	}
	
	return lo_enu_btn_status;
}

/**
* @brief a private function for the button module to map a given button to a certain external interrupt
*
* @param enu_btn_port              : the port the button is connected on
* @param enu_btn_pin               : the pin the button is connected to
* @param ptr_enu_btn_exi_id        : pointer to EXI ID to return the ID that the button maps to
*
* @return BTN_STATUS_OK            : When the button maps to an EXI pin
*         BTN_STATUS_INVALID_STATE : When the button does not map to any EXI
*/
static enu_btn_status_code_t_ btn_map_to_exi(enu_dio_port_t_ enu_btn_port, enu_dio_pin_t_ enu_btn_pin, enu_exi_id_t_* ptr_enu_btn_exi_id)
{
	enu_btn_status_code_t_ lo_enu_btn_status = BTN_STATUS_OK;
	
	if(DIO_PORT_D == enu_btn_port)
	{
		switch(enu_btn_pin)
		{
			case DIO_PIN_2: {*ptr_enu_btn_exi_id = EXI_ID_0; break;}
			case DIO_PIN_3: {*ptr_enu_btn_exi_id = EXI_ID_1; break;}
			default		  : lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
		}
	}
	else if(DIO_PORT_B == enu_btn_port)
	{
		if(DIO_PIN_2 == enu_btn_pin)
		{
			*ptr_enu_btn_exi_id = EXI_ID_2;
		}
		else
		{
			lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
		}
	}
	else
	{
		lo_enu_btn_status = BTN_STATUS_INVALID_STATE;
	}
	
	return lo_enu_btn_status;
}