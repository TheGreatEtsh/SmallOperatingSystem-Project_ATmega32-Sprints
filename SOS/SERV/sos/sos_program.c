/**
 * @fileName	:	sos_program.c
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Hamsters
 * @brief		: 	Program file for Simple Operating System 
 */ 
#include "sos_interface.h"
#include "sos_private.h"
static str_sos_task_t_*	ptr_str_arr_task[SOS_NUMBER_OF_TASKS] = {NULL_PTR};
uint32_t_ gl_uint32_tick_counter = 0; uint8_t_ gl_uint8_number_of_tasks_added = 0;
enu_sos_scheduler_state_t_	gl_enu_sos_scheduler_state = SOS_SCHEDULER_BLOCKED;
	/**
 *	@syntax				:	sos_init(void);
 *	@description		:	Initializes the sos module
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case timers doesn't return an error
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */ 
enu_sos_status_t_ sos_init(void)
{//Line23
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}//Line 125

/**
 *	@syntax				:	sos_deinit(void);
 *	@description		:	deinitializes the sos module
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case timers doesn't return an error
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */ 
enu_sos_status_t_ sos_deinit(void)
{//Line138
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}// Line 251

/**
 *	@syntax				:	sos_createTask(str_sos_task_t_* ptr_str_task);
 *	@description		:	Creates tasks and add them to the data base
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	*ptr_str_task
 *  @Parameters (out)	:	*ptr_str_task
 *  @Return value		:	sos_STATUS_SUCCESS in case of SUCCESS
 *							sos_STATUS_DATABASE_FULL in case of Database is full
 */
enu_sos_status_t_ sos_createTask(str_sos_task_t_* ptr_str_task)
{//Line 264
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}//Line 365

/**
 *	@syntax				:	sos_deleteTask(uint8_t_ uint8_task_id);
 *	@description		:	delete tasks from Database
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_sos_status_t_ sos_deleteTask(uint8_t_ uint8_task_id)
{//Line 378

























































































































}//Line 500

/**
 *	@syntax				:	sos_modify(str_sos_task_t_ str_task);
 *	@description		:	Modifies tasks and updates the  data base
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	str_task
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_sos_status_t_ sos_modify(str_sos_task_t_ str_task)
{//Line513






































































































}//Line 616

static enu_sos_status_t_	sos_search_task		(uint8_t_ uint8_task_id,str_sos_task_t_* ptr_str_sos_task)
{//line 619









































































































}//Line 725

static void					sos_sort_database	(void)
{//Line728






































































































}//line 831

/**
 *	@syntax				:	sos_run(void);
 *	@description		:	Starts timer
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */
enu_sos_status_t_ sos_run(void)
{
	enu_sos_status_t_ enu_return_value = SOS_STATUS_SUCCESS;

	if(TIMER_NOK == TIMER_resume(TIMER_0))
	{
		enu_return_value = SOS_STATUS_FAILED;
	}
	else
	{
		/*SOS_STATUS_SUCCESS*/
	}
	if (SOS_STATUS_SUCCESS == enu_return_value)
	{
		while(1)
		{
			if (SOS_SCHEDULER_READY == gl_enu_sos_scheduler_state)
			{
				sos_system_scheduler();
			}
		}
	}
	return enu_return_value;
}

/**
 *	@syntax				:	sos_disable(void);
 *	@description		:	Stops the timer
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */
enu_sos_status_t_ sos_disable(void)
{
	enu_sos_status_t_ enu_return_value = SOS_STATUS_SUCCESS;

	if(TIMER_NOK == TIMER_pause(TIMER_0))
	{
		enu_return_value = SOS_STATUS_FAILED;
	}
	else
	{
		/*SOS_STATUS_SUCCESS*/
	}
	return enu_return_value;
}

static void	sos_system_scheduler(void)
{
	if (0 != gl_uint8_number_of_tasks_added)	
	{	
		uint8_t_ uint8_looping_variable;
		for (uint8_looping_variable = 0; uint8_looping_variable < gl_uint8_number_of_tasks_added; uint8_looping_variable++)
		{
			if (0 == (gl_uint32_tick_counter % ptr_str_arr_task[uint8_looping_variable]->uint16_task_periodicity))
			{
				if (NULL_PTR != ptr_str_arr_task[uint8_looping_variable]->ptr_func_task)
				{
					ptr_str_arr_task[uint8_looping_variable]->ptr_func_task();
				}
				else
				{
					/*FUNCTION DOES NOT EXIST*/
				}
			}
			else
			{
				/*TASK IS NOT READY*/
			}
		}
		gl_enu_sos_scheduler_state = SOS_SCHEDULER_BLOCKED;
	}
	else
	{
		/*DATA BASE IS EMPTY*/
	}
}

static void	sos_sys_tick_task	(void)
{
	gl_uint32_tick_counter++;
	gl_enu_sos_scheduler_state = SOS_SCHEDULER_READY;
}
