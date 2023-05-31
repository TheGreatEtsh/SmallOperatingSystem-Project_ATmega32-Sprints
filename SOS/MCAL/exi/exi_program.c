/*
* exi_program.c
*
*  Created on: May 16, 2023
*      Author: Alaa
*/

/************************************************************************************************************
* 													Includes
************************************************************************************************************/

#include "exi_private.h"
#include "exi_interface.h"
#include "exi_cfg.h"

/************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
extern const str_exi_config_t_ gl_arr_str_exi_config[EXI_ID_TOTAL];

void (*arr_g_exiCBF[EXI_ID_TOTAL])(void) = {NULL};

/************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
/**
* @brief Check the parameters and configurations
*
* This static function checks the validity of the input EXI number,
* the configured EXI state and the configured EXI sense mode
* parameters in the configuration source file
*
* @param[in] en_a_intNumber the interrupt to be initialized
*
* @return enu_exi_error_t_ value that indicates operation success/failure
*		   (EXI_STATUS_OK in case of success or EXI_ERROR in case of failure)
*/
static enu_exi_error_t_ ParameterCheck(enu_exi_id_t_ en_a_intNumber)
{
	/* Check whether the ext. int. number is valid */
	if((en_a_intNumber < EXI_ID_0) || (en_a_intNumber > EXI_ID_2))
	return EXI_STATUS_INVALID_INTERRUPT;
	
	/* Check whether the interrupt state is valid */
	if((gl_arr_str_exi_config[en_a_intNumber].EXI_EN != EXI_STATE_DISABLE)
	&& (gl_arr_str_exi_config[en_a_intNumber].EXI_EN != EXI_STATE_ENABLE))
	return EXI_INVALID_FUNCTIONAL_STATE;
	
	/* Check whether the interrupt sense mode is valid */
	if(((gl_arr_str_exi_config[en_a_intNumber].SENSE_MODE)<EXI_MODE_LOW_LEVEL)
	|| ((gl_arr_str_exi_config[en_a_intNumber].SENSE_MODE)>EXI_MODE_RISING_EDGE))
	return EXI_STATUS_INVALID_SENSE_MODE;
	
	return EXI_STATUS_OK;
}

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
enu_exi_error_t_ exi_init(enu_exi_id_t_ enu_a_exi_id)
{
	enu_exi_error_t_ en_l_errorState = EXI_STATUS_OK;

	/* Input and configuration check */
	en_l_errorState = ParameterCheck(enu_a_exi_id);
	
	if(en_l_errorState == EXI_STATUS_OK)
	{
		exi_set_sense(enu_a_exi_id, gl_arr_str_exi_config[enu_a_exi_id].SENSE_MODE);
		exi_set_state(enu_a_exi_id, gl_arr_str_exi_config[enu_a_exi_id].EXI_EN);
	}
	else
	{
		/* Do Nothing */
	}

	return en_l_errorState;
}

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
enu_exi_error_t_ exi_set_sense(enu_exi_id_t_ enu_a_exi_id, enu_exi_sense_mode_t_ enu_a_sense_mode)
{
	enu_exi_error_t_ en_l_errorState = EXI_STATUS_OK;

	if((enu_a_sense_mode>=EXI_MODE_LOW_LEVEL && enu_a_sense_mode<EXI_MODE_TOTAL) && !(enu_a_sense_mode<EXI_MODE_FALLING_EDGE && enu_a_exi_id==EXI_ID_2))
	{
		switch(enu_a_exi_id)
		{
			case EXI_ID_0:
			{
				MCUCR &= EXI0_SENSE_MODE_MASK;
				MCUCR |= enu_a_sense_mode;
				break;
			}
			
			case EXI_ID_1:
			{
				MCUCR &= EXI1_SENSE_MODE_MASK;
				MCUCR |= enu_a_sense_mode<<MCUCR_ISC10;
				break;
			}			

			case EXI_ID_2:
			{
				if (EXI_MODE_RISING_EDGE == enu_a_sense_mode) {SET_BIT(MCUCSR, MCUCSR_ISC2);}
				else	/* Falling Edge */					  {CLR_BIT(MCUCSR, MCUCSR_ISC2);}
				
				break;
			}
			
			default: en_l_errorState = EXI_STATUS_INVALID_INTERRUPT;
		}
	}
	else
	{
		en_l_errorState = EXI_STATUS_INVALID_SENSE_MODE;
	}

	return en_l_errorState;
}

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
enu_exi_error_t_ exi_set_state(enu_exi_id_t_ en_a_intNumber, enu_exi_state_t_ enu_a_int_state)
{
	enu_exi_error_t_ en_l_errorState = EXI_STATUS_OK;

	/* Set Specific Interrupt Enable bit as configured */
	if((EXI_STATE_ENABLE == enu_a_int_state) || (EXI_STATE_DISABLE == enu_a_int_state))
	{
		switch(en_a_intNumber)
		{
			case EXI_ID_0:
			CLR_BIT(GICR, GICR_INT0);
			GICR |= (enu_a_int_state << GICR_INT0);
			break;

			case EXI_ID_1:
			CLR_BIT(GICR, GICR_INT1);
			GICR |= (enu_a_int_state << GICR_INT1);
			break;

			case EXI_ID_2:
			CLR_BIT(GICR, GICR_INT2);
			GICR |= (enu_a_int_state << GICR_INT2);
			break;

			default: en_l_errorState = EXI_STATUS_INVALID_INTERRUPT;
		}
	}
	else
	{
		en_l_errorState = EXI_INVALID_FUNCTIONAL_STATE;
	}

	return en_l_errorState;
}


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
enu_exi_error_t_ exi_set_callback(enu_exi_id_t_ enu_a_exi_id, void (*pv_a_Function)(void))
{
	enu_exi_error_t_ en_l_errorState = EXI_STATUS_OK;

	if(pv_a_Function != NULL_PTR)
	{
		if((enu_a_exi_id >= EXI_ID_0) && (enu_a_exi_id < EXI_ID_TOTAL))
		{
			arr_g_exiCBF[enu_a_exi_id] = pv_a_Function;
		}
		else
		{
			en_l_errorState = EXI_STATUS_INVALID_INTERRUPT;
		}
	}
	else
	{
		en_l_errorState = EXI_STATUS_INVALID_CBF;
	}

	return en_l_errorState;
}

/*************************************************************************************************************
* 													ISRs
************************************************************************************************************/
ISR(EXT_INT_0)
{
	if(arr_g_exiCBF[EXI_ID_0] != NULL)
	{
		arr_g_exiCBF[EXI_ID_0]();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(EXT_INT_1)
{
	if(arr_g_exiCBF[EXI_ID_1] != NULL)
	{
		arr_g_exiCBF[EXI_ID_1]();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(EXT_INT_2)
{
	if(arr_g_exiCBF[EXI_ID_2] != NULL)
	{
		arr_g_exiCBF[EXI_ID_2]();
	}
	else
	{
		/* Do Nothing */
	}
}
