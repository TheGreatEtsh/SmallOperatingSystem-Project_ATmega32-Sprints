/*
 * exi_interface.h
 *
 * Created: 5/15/2023 5:15:06 PM
 *  Author: Alaa Hisham
 */ 


#ifndef EXI_INTERFACE_H_
#define EXI_INTERFACE_H_

/************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/

#include "std.h"
#include "bit_math.h"
#include "interrupts.h"

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/

typedef enum
{
	EXI_ID_0 = 0	,
	EXI_ID_1		,
	EXI_ID_2		,
	EXI_ID_TOTAL
}enu_exi_id_t_;

typedef enum
{
	EXI_STATE_DISABLE = 0	 ,
	EXI_STATE_ENABLE		
}enu_exi_state_t_;

typedef enum
{
	EXI_MODE_LOW_LEVEL =0	  ,
	EXI_MODE_ON_CHANGE		  ,
	EXI_MODE_FALLING_EDGE	  ,
	EXI_MODE_RISING_EDGE	  ,
	EXI_MODE_TOTAL
}enu_exi_sense_mode_t_;

typedef enum
{
	EXI_STATUS_OK = 0			   ,				/* Successful EXI operation */
	EXI_STATUS_INVALID_INTERRUPT   ,				/* Means that EXI num passed as an argument was out of range */
	EXI_STATUS_INVALID_SENSE_MODE  ,				/* Means that EXI sense mode passed as an argument was not supported */
	EXI_STATUS_INVALID_CBF		   ,				/* When CBF passed as argument is invalid (null ptr) */
	EXI_INVALID_FUNCTIONAL_STATE   ,
	EXI_STATUS_TOTAL
}enu_exi_error_t_;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * @brief Initialize given EXI as configured
 *
 * This function initializes the passed interrupt with the configured
 * parameters in the configuration source file
 *
 * @param[in] enu_a_exi_id				:	the interrupt to be initialized
 *
 * @return EXi_STATUS_OK				:	When the given EXI is initialized successfully
 *		   EXI_STATUS_INVALID_INTERRUPT	:	EXI number is out of available bounds
 */
enu_exi_error_t_ exi_init(enu_exi_id_t_ enu_a_exi_id);

/**
 * @brief  Function to choose the trigger event for given EXI 
 *
 * This function sets the given EXI to be triggered whenever 
 * an event that matches the given sense mode occurs
 *
 * @param[in] enu_a_exi_id					:	The interrupt to be configured
 * @param[in] enu_a_sense_mode				:	The event to trigger the EXI
 *
 * @return EXi_STATUS_OK					:	When the triggering event is set successfully
 *		   EXI_STATUS_INVALID_INTERRUPT		:	EXI number is out of available bounds
 *		   EXI_STATUS_INVALID_SENSE_MODE	:	When sense mode is not within the specified options
 */
enu_exi_error_t_ exi_set_sense(enu_exi_id_t_ enu_a_exi_id, enu_exi_sense_mode_t_ enu_a_sense_mode);

/**
 * @brief Function to enable/disable given EXI
 *
 * This function sets or clears the specific interrupt enable bit
 * for the given interrupt to enable or disable it
 *
 * @param[in] enu_a_exi_id				:	The interrupt to be configured
 * @param[in] enu_a_int_state			:	EXI state (EXI_ENABLE/EXI_DISABLE)
 *
 * @return EXi_STATUS_OK				:	When the state of the EXI is set successfully
 *		   EXI_STATUS_INVALID_INTERRUPT	:	EXI number is out of available bounds
 *		   EXI_INVALID_FUNCTIONAL_STATE	:	When passed state is neither (EXI_ENABLE) nor (EXI_DISABLE)
 */
enu_exi_error_t_ exi_set_state(enu_exi_id_t_ enu_a_exi_id, enu_exi_state_t_ enu_a_int_state);

/**
 * @brief Function to set a function to call when EXI is triggered
 *
 * This function sets a callback function to be called whenever 
 * the given interrupt is triggered 
 *
 * @param[in] enu_a_exi_id				:	The desired EXI number
 * @param[in] pv_a_function				:	The function to call
 *
 * @return EXi_STATUS_OK				:	CBF is set successfully for given interrupt
 *		   EXI_STATUS_INVALID_INTERRUPT	:	EXI number is out of available bounds
 *		   EXI_STATUS_INVALID_CBF		:	When passed function pointer is a NULL_PTR
 */
enu_exi_error_t_ exi_set_callback(enu_exi_id_t_ enu_a_exi_id, void (*pv_a_function)(void));


#endif /* EXI_INTERFACE_H_ */