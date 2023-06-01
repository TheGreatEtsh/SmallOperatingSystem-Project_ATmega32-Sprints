/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
 *
 *         @Date:  	5:34 PM Monday, May 15, 2023
 *		   @File:  	timer_cfg.c         
 *		 @Module:  	Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Program file for Timer module     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "timer_interface.h"
#include "timer_cfg.h"
#include "timer_private.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const str_timer_config_t str_timer_config [NUMBER_OF_TIMERS_USED];

void (*timer_0_callback) (void) = NULL_PTR;

void (*timer_1_callback) (void) = NULL_PTR;

void (*timer_2_callback) (void) = NULL_PTR;

void (*TIMER_0_pwmOnCallBack) (void) = NULL_PTR;

void (*TIMER_0_pwmOffCallBack) (void) = NULL_PTR;


uint32_t_ gl_uint32_timer0NumberOfOVFs	=	0;

uint8_t_  gl_uint8_timer0RemTicks		=	0;

volatile uint32_t_ gl_uint32_timer0OVFCounter	=	0;

uint32_t_ gl_uint32_timer1NumberOfOVFs	=	0;

uint16_t_ gl_uint16_timer1RemTicks		=	0;

volatile uint32_t_ gl_uint32_timer1OVFCounter	=	0;

uint32_t_ gl_uint32_timer2NumberOfOVFs	=	0;

uint32_t_ gl_uint8_timer2RemTicks		=	0;

volatile uint32_t_ gl_uint32_timer2OVFCounter	=	0;

uint8_t_ gl_uint8_normalToPwm		=	0;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
/******************************************************************************
* @Syntax          : enu_timer_error_t timer_init( void )
* @Description     : Initialize Timer according to preprocessed configured definitions
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_init( void )
{
	enu_timer_error_t returnValue = TIMER_OK;
	
	for (uint8_t_ counter = 0; counter < NUMBER_OF_TIMERS_USED; counter++)
	{
		switch(str_timer_config[counter].timerUsed)
		{
			case TIMER_0:
			switch(str_timer_config[counter].waveformUsed)
			{
				case TIMER_OV:
				/*Choosing Normal Mode*/
				CLR_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
				/*Enabling OVF Interrupt 0*/
				SET_BIT(TIMSK,TOIE0);
				//SET_BIT(TIMSK,TOIE0);
				break;
				
				case TIMER_CTC:
				/*Choosing CTC Mode*/
				SET_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
				/*Enabling CTC Interrupt 0*/
				SET_BIT(TIMSK,OCIE0);
				break;
				
				case TIMER_PWM:
				/*TO BE IMPLEMENTED*/
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			
			case TIMER_1:
			switch(str_timer_config[counter].waveformUsed)
			{
				case TIMER_OV:
				CLR_BIT(TCCR1A,COM1A1);
				CLR_BIT(TCCR1A,COM1A0);
				
				CLR_BIT(TCCR1B,WGM13);
				CLR_BIT(TCCR1B,WGM12);
				CLR_BIT(TCCR1A,WGM11);
				CLR_BIT(TCCR1A,WGM10);
				
				//SET_BIT(TIMSK, TOIE1);
				break;
				
				case TIMER_CTC:
				break;
				
				case TIMER_PWM:
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			
			case TIMER_2:
			switch(str_timer_config[counter].waveformUsed)
			{
				case TIMER_OV:
				/*Choosing Normal Mode*/
				CLR_BIT(TCCR2,WGM21); CLR_BIT(TCCR2,WGM20);
				/*Enabling OVF Interrupt 0*/
				SET_BIT(TIMSK,TOIE2);
				break;
				
				case TIMER_CTC:
				/*Choosing CTC Mode*/
				SET_BIT(TCCR0,WGM21); CLR_BIT(TCCR0,WGM20);
				/*Enabling CTC Interrupt 0*/
				SET_BIT(TIMSK,OCIE2);
				break;
				
				case TIMER_PWM:
				/*TO BE IMPLEMENTED*/
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			default:
			returnValue =  TIMER_WRONG_TIMER_USED;
			break;
		}
		if (returnValue)
		{
			break;
		}
	}
	/*Enabling Global Interrupt*/
	SET_BIT(SREG, Ibit);
	
	return returnValue;
}

/******************************************************************************
* @Syntax          : enu_timer_error_t timer_set_time
*					 (enu_timer_number_t enu_a_timerUsed, f32 f32_desiredTime)
* @Description     : set the time at which the timer interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
*					 f32					f32_a_desiredTime
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_set_time(enu_timer_number_t enu_a_timerUsed, f32_t_ f32_desiredTime)
{
	enu_timer_error_t returnValue = TIMER_OK;
	uint32_t_ uint32_tickTime = 0;
	uint32_t_ uint32_numberOfTicks = 0;
	uint16_t_ uint16_TCNTValue = 0;
	
	switch(enu_a_timerUsed)
	{
		case TIMER_0:
		switch(str_timer_config[enu_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			uint32_tickTime = str_timer_config[enu_a_timerUsed].prescalerUsed / XTAL_FREQ;
			uint32_numberOfTicks = ((f32_desiredTime*1000)/uint32_tickTime);
			
			gl_uint32_timer0NumberOfOVFs = uint32_numberOfTicks / 256;
			gl_uint8_timer0RemTicks = uint32_numberOfTicks % 256;
			
			if (gl_uint8_timer0RemTicks)
			{
				TCNT0 = 256 - gl_uint8_timer0RemTicks;
				gl_uint32_timer0NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		case TIMER_1:
		switch(str_timer_config[enu_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			uint32_tickTime = str_timer_config[enu_a_timerUsed].prescalerUsed / XTAL_FREQ;
			uint32_numberOfTicks = ((f32_desiredTime*1000)/uint32_tickTime);
			
			gl_uint32_timer1NumberOfOVFs = uint32_numberOfTicks / 65536;
			gl_uint16_timer1RemTicks = uint32_numberOfTicks % 65536;
			
			if (gl_uint16_timer1RemTicks)
			{
				uint16_TCNTValue = 65536 - gl_uint16_timer1RemTicks;
				
				TCNT1L |= uint16_TCNTValue;
				TCNT1H |= (uint16_TCNTValue>>8);
				
				gl_uint32_timer2NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		case TIMER_2:
		switch(str_timer_config[enu_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			uint32_tickTime = str_timer_config[enu_a_timerUsed].prescalerUsed / XTAL_FREQ;
			uint32_numberOfTicks = ((f32_desiredTime*1000)/uint32_tickTime);
			
			gl_uint32_timer2NumberOfOVFs = uint32_numberOfTicks / 256;
			gl_uint8_timer2RemTicks = uint32_numberOfTicks % 256;
			
			if (gl_uint8_timer2RemTicks)
			{
				TCNT2 = 256 - gl_uint8_timer2RemTicks;
				gl_uint32_timer2NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	return returnValue;
}


/******************************************************************************
* @Syntax          : enu_timer_error_t timer_resume(enu_timer_number_t enu_a_timerUsed)
* @Description     : makes the timer to start/resume counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_resume(enu_timer_number_t enu_a_timerUsed)
{
	enu_timer_error_t returnValue = TIMER_OK;
	switch(enu_a_timerUsed)
	{
		case TIMER_0:
		switch(str_timer_config[TIMER_0].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_64:
			CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		
		case TIMER_1:
		switch(str_timer_config[TIMER_1].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR1B, CS12);	SET_BIT(TCCR1B, CS11);	CLR_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_64:
			CLR_BIT(TCCR1B, CS12);	SET_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	CLR_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		
		case TIMER_2:
		switch(str_timer_config[TIMER_1].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_64:
			SET_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		default:
		returnValue =  TIMER_NOK;
		break;
		
	}
	return returnValue;
}


/******************************************************************************
* @Syntax          : enu_timer_error_t timer_pause(enu_timer_number_t enu_a_timerUsed)
* @Description     : makes the timer to pause counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_pause(enu_timer_number_t enu_a_timerUsed)
{
	enu_timer_error_t returnValue = TIMER_OK;
	switch(enu_a_timerUsed)
	{
		case TIMER_0:
		CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);	break;
		
		case TIMER_1:
		CLR_BIT(TCCR1B,CS12);	CLR_BIT(TCCR1B,CS11);	CLR_BIT(TCCR1B,CS10);	break;
		
		case TIMER_2:
		CLR_BIT(TCCR2, CS22);	CLR_BIT(TCCR2, CS21);	CLR_BIT(TCCR2, CS20);	break;
		
		default:	
		returnValue =			TIMER_WRONG_TIMER_USED;							break;
		
	}
	return returnValue;
}

/******************************************************************************
* @Syntax          : enu_timer_error_t timer_disable_interrupt(enu_timer_number_t enu_a_timerUsed)
* @Description     : Disables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_disable_interrupt(enu_timer_number_t enu_a_timerUsed)
{
	enu_timer_error_t returnValue = TIMER_OK;
	switch(enu_a_timerUsed)
	{
		case TIMER_0:	CLR_BIT(TIMSK,TOIE0);				break;
		
		case TIMER_1:	CLR_BIT(TIMSK,TOIE1);				break;
		
		case TIMER_2:	CLR_BIT(TIMSK,TOIE2);				break;
		
		default:	returnValue =  TIMER_WRONG_TIMER_USED;	break;
		
	}
	return returnValue;
}

/******************************************************************************
* @Syntax          : enu_timer_error_t timer_enable_interrupt(enu_timer_number_t enu_a_timerUsed)
* @Description     : Enables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_enable_interrupt(enu_timer_number_t enu_a_timerUsed)
{
	enu_timer_error_t returnValue = TIMER_OK;
	switch(enu_a_timerUsed)
	{
		case TIMER_0:	SET_BIT(TIMSK,TOIE0);				break;
		
		case TIMER_1:	SET_BIT(TIMSK,TOIE1);				break;
		
		case TIMER_2:	SET_BIT(TIMSK,TOIE2);				break;
		
		default:	returnValue =  TIMER_WRONG_TIMER_USED;	break;
		
	}
	return returnValue;
}

/******************************************************************************
* @Syntax          : enu_timer_error_t timer_set_callback
*					 (enu_timer_number_t enu_a_timerUsed, void (*funPtr)(void))
* @Description     : sets the call back function for a specific timer
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : enu_timer_number_t		enu_a_timerUsed
*					 void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : enu_timer_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
enu_timer_error_t timer_set_callback(enu_timer_number_t enu_a_timerUsed, void (*funPtr)(void))
{
	enu_timer_error_t returnValue = TIMER_OK;
	
	if(funPtr != NULL_PTR)	
	{	
		switch(enu_a_timerUsed)
		{
			case TIMER_0:	timer_0_callback = funPtr;			break;
			
			case TIMER_1:	timer_1_callback = funPtr;			break;
			
			case TIMER_2:	timer_2_callback = funPtr;			break;
			
			default:	returnValue = TIMER_WRONG_TIMER_USED;	break;
		}
	}
	else
	{
		returnValue = TIMER_NOK;
	}
	return returnValue;
}

ISR(TIM0_OVF_INT)
{
	if (gl_uint8_normalToPwm == 0	)
	{
		gl_uint32_timer0OVFCounter ++;
		if (gl_uint32_timer0OVFCounter == gl_uint32_timer0NumberOfOVFs)
		{
			if(timer_0_callback != NULL_PTR)
			{
				timer_0_callback();
			}
			gl_uint32_timer0OVFCounter   =	0;
			TCNT0 = 256 - gl_uint8_timer0RemTicks;
		}
	}
	else
	{
		/*TO BE IMPLEMENT*/
	}
}

ISR(TIM1_OVF_INT)
{
	gl_uint32_timer1OVFCounter ++;
	if (gl_uint32_timer1OVFCounter  == gl_uint32_timer1NumberOfOVFs)
	{
		if(timer_1_callback != NULL_PTR)
		{
			timer_1_callback();
		}
		gl_uint32_timer1OVFCounter  =	0;
		TCNT1 = 65536 - gl_uint16_timer1RemTicks;
		
	}

}

ISR(TIM2_OVF_INT)
{
	gl_uint32_timer2OVFCounter ++;
	if (gl_uint32_timer2OVFCounter  == gl_uint32_timer2NumberOfOVFs)
	{
		if(timer_2_callback != NULL_PTR)
		{
			timer_2_callback();
		}
		gl_uint32_timer2OVFCounter  =	0;
		TCNT2 = 256 - gl_uint8_timer2RemTicks;
		
	}

}
/**********************************************************************************************************************
 *  END OF FILE: timer_program.c
 *********************************************************************************************************************/
