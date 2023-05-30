/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *
 *		   @Date:  	5:34 PM Monday, May 15, 2023
 *		   @File:  	timer_interface.h         
 *		 @Module:  	Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Interfacing file for Timer module     
 *  
 *********************************************************************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "interrupts.h"
#include "bit_math.h"
#include "std.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
/**************************************_CLOCK_FREQUENCY_USED_************************************/
#define XTAL_FREQ								(F_CPU / 1000000UL)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum timerError{
	TIMER_OK = 0,
	TIMER_WRONG_TIMER_USED,
	TIMER_WRONG_DESIRED_TIME,
	TIMER_NOK
}enu_TIMER_error_t;
	
typedef enum
{
	TIMER_0 = 0,
	TIMER_1,
    TIMER_2
}enu_TIMER_number_t;

typedef enum
{
	TIMER_OV = 0,
	TIMER_PWM,
    TIMER_CTC
}enu_TIMER_waveformUsed_t;

typedef enum
{	
	TIMER_NO_CLK		= 0,
	TIMER_PRESCLNG_1	= 1,
	TIMER_PRESCLNG_8	= 8,
	TIMER_PRESCLNG_64	= 64,
	TIMER_PRESCLNG_256	= 256,
	TIMER_PRESCLNG_1024	= 1024,
	TIMER_XCK_FLNG_EDGE	= 10,
	TIMER_XCK_RSNG_EDGE	= 15
}enu_TIMER_prescalerUsed_t;


typedef struct
{
	enu_TIMER_number_t			timerUsed;
	enu_TIMER_waveformUsed_t		waveformUsed;
	enu_TIMER_prescalerUsed_t	prescalerUsed;
}st_TIMER_config_t;


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_init( void )
* @Description     : Initialize Timer according to preprocessed configured definitions
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None		
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_TIMER_error_t TIMER_init( void );

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_setTime
*					 (enu_TIMER_number_t enu_a_timerUsed, f32_t_ f32_desiredTime)
* @Description     : set the time at which the timer interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
*					 f32					f32_a_desiredTime
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_TIMER_error_t TIMER_setTime(enu_TIMER_number_t enu_a_timerUsed, f32_t_ f32_a_desiredTime);

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_resume(enu_TIMER_number_t enu_a_timerUsed)
* @Description     : makes the timer to start/resume counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_TIMER_error_t TIMER_resume(enu_TIMER_number_t enu_a_timerUsed);

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_pause(enu_TIMER_number_t enu_a_timerUsed)
* @Description     : makes the timer to pause counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_TIMER_error_t TIMER_pause(enu_TIMER_number_t enu_a_timerUsed);

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_disableInterrupt(enu_TIMER_number_t enu_a_timerUsed)
* @Description     : Disables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_TIMER_error_t TIMER_disableInterrupt(enu_TIMER_number_t enu_a_timerUsed);

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_enableInterrupt(enu_TIMER_number_t enu_a_timerUsed)
* @Description     : Enables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/				 
enu_TIMER_error_t TIMER_enableInterrupt(enu_TIMER_number_t enu_a_timerUsed);

/******************************************************************************
* @Syntax          : enu_TIMER_error_t TIMER_setCallBack
*					 (enu_TIMER_number_t enu_a_timerUsed, void (*funPtr)(void))
* @Description     : sets the call back function for a specific timer
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_TIMER_number_t		enu_a_timerUsed
*					 void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : enu_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/				 
enu_TIMER_error_t TIMER_setCallBack(enu_TIMER_number_t enu_a_timerUsed, void (*funPtr)(void));


#endif /* TIMER_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: timer_interface.h
 *********************************************************************************************************************/
