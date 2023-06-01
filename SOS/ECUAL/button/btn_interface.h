/*
 * btn_interface.h
 *
 * Created: 5/31/2023 1:35:19 PM
 *  Author: Alaa
 */ 


#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

#include "dio_interface.h"

typedef enum
{
	BTN_STATE_PRESSED		,
	BTN_STATE_NOT_PRESSED	,
	BTN_STATE_TOTAL
}enu_btn_state_t_;

typedef enum
{
	BTN_INTERNAL_PULL_UP = 0	,
	BTN_EXTERNAL_PULL_UP		,
	BTN_EXTERNAL_PULL_DOWN
}enu_btn_pull_t_;


typedef enum
{
	BTN_STATUS_OK = 0			 ,
	BTN_STATUS_INVALID_PULL_TYPE ,
	BTN_STATUS_INVALID_STATE	 ,
}enu_btn_status_code_t_;

typedef struct
{
	enu_dio_port_t_ BTN_PORT 	  ;
	enu_dio_pin_t_ 	BTN_PIN 	  ;
	enu_btn_pull_t_ BTN_PULL_TYPE ;
}str_btn_config_t_;


/**
 * @brief Function to initialize a given button instance
 * 
 * @param ptr_str_btn_config            : pointer to the desired button structure
 * 
 * @return BTN_STATUS_OK 	            : When the operation is successful
 *         BTN_STATUS_INVALID_STATE		: Button structure pointer is a NULL_PTR
 *         BTN_STATUS_INVALID_PULL_TYPE : If the pull type field in button structure is set to invalid value
 */
enu_btn_status_code_t_ btn_init(str_btn_config_t_* ptr_str_btn_config);

/**
 * @brief Function to read the current button state 
 * 
 * @param ptr_str_btn_config            : pointer to the desired button structure
 * @param ptr_enu_btn_state             : pointer to variable to store the button state
 * 
 * @return BTN_STATUS_OK                : When the operation is successful
 *         BTN_STATUS_INVALID_STATE     : Button structure and/or button state pointers are NULL_PTRs
 *         BTN_STATUS_INVALID_PULL_TYPE : If the pull type field in button structure is set to invalid value
 */
enu_btn_status_code_t_ btn_read(str_btn_config_t_* ptr_str_btn_config, enu_btn_state_t_* ptr_enu_btn_state);

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
enu_btn_status_code_t_ btn_set_notification(str_btn_config_t_* ptr_str_btn_config, void (*pv_btn_cbf)(void));

#endif /* BTN_INTERFACE_H_ */