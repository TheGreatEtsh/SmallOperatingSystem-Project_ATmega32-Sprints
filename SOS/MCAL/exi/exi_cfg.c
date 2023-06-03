/*
 * exi_config.c
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

/************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "exi_interface.h"
#include "exi_cfg.h"

/************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/

/**
 * Options:
 * 			.EXI_NUM =    EXI_ID_0
 * 			              EXI_ID_1
 * 			              EXI_ID_2
 *
 * 			.SENSE_MODE = EXI_MODE_LOW_LEVEL			[for EXTI0 & EXTI1 only]
 * 			              EXI_MODE_ON_CHANGE			[for EXTI0 & EXTI1 only]
 * 			              EXI_MODE_FALLING_EDGE
 * 			              EXI_MODE_RISING_EDGE	
 *
 * 			.EXI_EN	=	  EXI_STATE_ENABLE
 * 						  EXI_STATE_DISABLE
 */


const str_exi_config_t_ arr_g_exiConfigs[EXI_ID_TOTAL] =
{
		{
				.EXI_NUM    = EXI_ID_0			   ,
				.SENSE_MODE = EXI_MODE_RISING_EDGE ,
				.EXI_EN     = EXI_STATE_DISABLE
		},

		{
				.EXI_NUM	= EXI_ID_1				 ,
				.SENSE_MODE = EXI_MODE_FALLING_EDGE  ,
				.EXI_EN		= EXI_STATE_DISABLE
		},

		{
				.EXI_NUM	= EXI_ID_2				,
				.SENSE_MODE = EXI_MODE_RISING_EDGE  ,
				.EXI_EN		= EXI_STATE_DISABLE
		}
};
