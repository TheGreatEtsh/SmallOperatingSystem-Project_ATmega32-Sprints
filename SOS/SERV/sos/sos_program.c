/**
 * @fileName	:	sos_program.c
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Hamsters
 * @brief		: 	Program file for Simple Operating System 
 */ 
#include "sos_interface.h"
#include "sos_private.h"
static str_sos_task_t_*	gl_arr_ptr_str_task[SOS_NUMBER_OF_TASKS] = {NULL_PTR};
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
	enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;
	if (TIMER_init(  )==TIMER_NOK)
	{enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	
	
	if (TIMER_setTime(TIMER_0, SOS_SYS_TICK_TIME_MS)==TIMER_NOK)
	{
		enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	
	if (TIMER_enableInterrupt(TIMER_0)==TIMER_NOK)
	{enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	if (TIMER_setCallBack(TIMER_0,sos_sys_tick_task)== TIMER_NOK)
	{enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

return enu_sos_status_retval;	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
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
	
	enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;
	
	if (TIMER_pause(TIMER_0)==TIMER_NOK)
	{
		enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	
	
	if (TIMER_disableInterrupt(TIMER_0)==TIMER_NOK)
	{ enu_sos_status_retval = SOS_STATUS_FAILED;
	} 
	else
	{//SUCCESS
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return enu_sos_status_retval;	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
}// Line 251

/**
 *	@author				                    :	Hossam Elwahsh - https://github.com/HossamElwahsh
 *
 *	@brief		                            :	Generates a new task ID, add the requested task parameters to the database
 *  @param[in,out]  ptr_str_task 	        :   Pointer to task structure
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task created successfully
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_ARGS     :   Failed,     Invalid Arguments Given
 *              SOS_STATUS_DATABASE_FULL    :   Failed,     Database is full
 */
enu_sos_status_t_ sos_create_task(str_sos_task_t_* ptr_str_task)
{//Line 264
    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    // Arguments check
    else if(
            NULL_PTR == ptr_str_task                    ||  // task ptr is null
            ptr_str_task->uint16_task_periodicity == 0  ||  // task periodicity is 0 (infinite)
            NULL_PTR == ptr_str_task->ptr_func_task         // task function ptr is null
            )
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_ARGS;
    }
    else
    {
        /* Task Creation */
        // get next empty db index
        uint8_t_ uint8_number_of_tasks_in_db = 0;
        for (uint8_t_ i = 0; i < SOS_NUMBER_OF_TASKS; ++i) {
            if (NULL_PTR == gl_arr_ptr_str_task[i])
            {
                /* Reached end of DB */
                break;
            }
            else
            {
                uint8_number_of_tasks_in_db++;
            }
        }

        if(SOS_NUMBER_OF_TASKS == uint8_number_of_tasks_in_db)
        {
            /* DB FULL */
            enu_sos_status_retval = SOS_STATUS_DATABASE_FULL;
        }
        else
        {
            // generate a new task ID
            uint8_t_ uint8_generated_task_id = 0;
            enu_sos_status_retval = sos_generate_task_id(&uint8_generated_task_id);
            if(enu_sos_status_retval == SOS_STATUS_SUCCESS)
            {
                // task ID generated successfully
                // update task structure
                ptr_str_task->uint8_task_id = uint8_generated_task_id;

                // save task in DB
                gl_arr_ptr_str_task[uint8_number_of_tasks_in_db] = ptr_str_task;

                // sort DB tasks according to task priority // todo-hossam check on alaa adding a return value for this?
                sos_sort_database();

                enu_sos_status_retval = SOS_STATUS_SUCCESS;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
	













	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	


	
    return enu_sos_status_retval;
}//Line 365

/**
 *	@author				                    :	Hossam Elwahsh - https://github.com/HossamElwahsh
 *
 *	@brief		                            :	Deletes a task from DB
 *  @param[in,out]  uint8_task_id 	        :   Task ID to delete from DB
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task deleted successfully
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_TASK_ID  :   Failed,     Task ID not found in DB
 */
enu_sos_status_t_ sos_delete_task(uint8_t_ uint8_task_id)
{//Line 378

    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    else
    {
        // search for task ID in DB
        str_sos_task_t_ *ptr_str_sos_task_to_delete = NULL;
        enu_sos_status_retval = sos_find_task(uint8_task_id, &ptr_str_sos_task_to_delete);

        if(
                SOS_STATUS_SUCCESS == enu_sos_status_retval      &&
                NULL_PTR != ptr_str_sos_task_to_delete
        ) // task found
        {
            /* Task Found - Delete it */
            ptr_str_sos_task_to_delete = NULL_PTR;
            sos_sort_database();
            enu_sos_status_retval = SOS_STATUS_SUCCESS;
        }
        else
        {
            /* Task not found */
            enu_sos_status_retval = SOS_STATUS_INVALID_TASK_ID;
        }
    }

    return enu_sos_status_retval;

























































































}//Line 500

/**
 *	@author				                    :	Hossam Elwahsh - https://github.com/HossamElwahsh
 *
 *	@brief		                            :	Modifies a task
 *  @param[in]  str_task 	                :   Task Data
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task deleted successfully
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_ARGS     :   Failed,     Invalid Arguments Given
 *              SOS_STATUS_INVALID_TASK_ID  :   Failed,     Task ID not found in DB
 */
enu_sos_status_t_ sos_modify_task(str_sos_task_t_ str_task)
{
    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    // Arguments check
    else if(
                    (NULL_PTR == str_task.ptr_func_task) ||
                    (0 == str_task.uint16_task_periodicity)
            )
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_ARGS;
    }
    else
    {
        // search for task ID in DB
        str_sos_task_t_ * ptr_str_sos_task_to_delete = NULL;
        enu_sos_status_retval = sos_find_task(str_task.uint8_task_id, &ptr_str_sos_task_to_delete);

        if(SOS_STATUS_SUCCESS == enu_sos_status_retval) // task found
        {
            /* DB Task Ptr Found - Modify it */

            ptr_str_sos_task_to_delete->uint8_task_priority     = str_task.uint8_task_priority;
            ptr_str_sos_task_to_delete->uint16_task_periodicity = str_task.uint16_task_periodicity;
            ptr_str_sos_task_to_delete->ptr_func_task           = str_task.ptr_func_task;
            sos_sort_database();
            enu_sos_status_retval = SOS_STATUS_SUCCESS;
        }
        else
        {
            /* Task not found */
            enu_sos_status_retval = SOS_STATUS_INVALID_TASK_ID;
        }
    }

    return enu_sos_status_retval;






























































}//Line 616

/**
 *	@author				                    :	Hossam Elwahsh - https://github.com/HossamElwahsh
 *
 *	@brief		                            :	Finds a task in DB using it's ID
 *  @param[in]      uint8_task_id 	        :   Task ID to search for
 *  @param[out]     ptr_ptr_str_sos_task 	:   Pointer to pointer store found task address
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task found
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_TASK_ID  :   Failed,     Task ID not found in DB
 */
static enu_sos_status_t_	sos_find_task		(uint8_t_ uint8_task_id, str_sos_task_t_ ** ptr_ptr_str_sos_task)
{
    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    // Arguments check
    else if(NULL_PTR == ptr_ptr_str_sos_task)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_ARGS;
    }
    else
    {
        /* search for task ID in DB */

        uint8_t_ bool_found = FALSE;        // task found flag

        for (uint8_t_ i = 0; i < SOS_NUMBER_OF_TASKS; ++i) {
            if(uint8_task_id == gl_arr_ptr_str_task[i]->uint8_task_id)
            {
                bool_found = TRUE;
                *ptr_ptr_str_sos_task = gl_arr_ptr_str_task[i]; // save found task pointer
                break;
            }
            else
            {
                /* Do Nothing */
            }
        }

        if(TRUE == bool_found)
        {
            /* Task Found */
            enu_sos_status_retval = SOS_STATUS_SUCCESS;
        }
        else
        {
            /* Task not found */
            enu_sos_status_retval = SOS_STATUS_INVALID_TASK_ID;
        }

    }

    return enu_sos_status_retval;





















































}//Line 725


/**
 * @brief a private function to sort the task data base according to task 
 *		  priority after each modification to the Data base
 *
 * @return 
 */
static void					sos_sort_database	(void)
{//Line771

	str_sos_task_t_* lo_ptr_str_temp_task;
	uint8_t_ lo_u8_null_found = 0;
	uint8_t_ lo_u8_iterator, lo_u8_active_tasks = 0;
	sint8_t_ lo_s8_null_task_index = -1;
	uint8_t_ lo_u8_min_id_index = 0;

	for(lo_u8_iterator = 0; lo_u8_iterator<SOS_NUMBER_OF_TASKS; lo_u8_iterator++)
	{
		if(NULL_PTR != gl_arr_ptr_str_task[lo_u8_iterator])
		{
			lo_u8_active_tasks++;
			if(lo_u8_null_found)
			{
				lo_u8_null_found = 0;
				lo_s8_null_task_index = lo_u8_iterator-1;
			}
		}
		else if(lo_u8_null_found) 
		{
			//lo_u8_active_tasks--;
			break;
		}
		else
		{
			//lo_u8_active_tasks++;
			lo_u8_null_found = 1;
		}
	}

	if(lo_s8_null_task_index != -1)
	{
		/* swap the deleted task with the last active task */
		gl_arr_ptr_str_task[lo_s8_null_task_index] = gl_arr_ptr_str_task[lo_u8_active_tasks];
		gl_arr_ptr_str_task[lo_u8_active_tasks] = NULL_PTR;
		return;		
	}

	for (lo_u8_iterator = 0; lo_u8_iterator < lo_u8_active_tasks-1; lo_u8_iterator++) 
	{
		lo_u8_min_id_index = lo_u8_iterator;
		
		for (uint8_t_ i = lo_u8_iterator+1; i < lo_u8_active_tasks; i++) 
		{
			if (gl_arr_ptr_str_task[i]->uint8_task_priority < gl_arr_ptr_str_task[lo_u8_min_id_index]->uint8_task_priority) 
			{
				lo_u8_min_id_index = i;
			}
		}
		
		lo_ptr_str_temp_task = gl_arr_ptr_str_task[lo_u8_min_id_index];
		gl_arr_ptr_str_task[lo_u8_min_id_index] = gl_arr_ptr_str_task[lo_u8_iterator];
		gl_arr_ptr_str_task[lo_u8_iterator] = lo_ptr_str_temp_task;
	}









































}//line 867

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
	uint32_t_ uint32_hyper_period = 0;
	uint8_t_ uint8_looping_variable;
	
	if (0 != gl_uint8_number_of_tasks_added)	
	{	
		calculate_hyper_period(&uint32_hyper_period);
		
		for (uint8_looping_variable = 0; uint8_looping_variable < gl_uint8_number_of_tasks_added; uint8_looping_variable++)
		{
			if (0 == (gl_uint32_tick_counter % gl_arr_ptr_str_task[uint8_looping_variable]->uint16_task_periodicity))
			{
				if (NULL_PTR != gl_arr_ptr_str_task[uint8_looping_variable]->ptr_func_task)
				{
					gl_arr_ptr_str_task[uint8_looping_variable]->ptr_func_task();
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
		
		if (uint32_hyper_period == gl_uint32_tick_counter)
		{
			gl_uint32_tick_counter = 0;
		}
		else
		{
			/*SCHEDULER HAVEN'T REACH TO HYPER PERIOD YET*/
		}
	}
	else
	{
		/*DATABASE IS EMPTY*/
	}
}

static void	sos_sys_tick_task	(void)
{
	gl_uint32_tick_counter++;
	gl_enu_sos_scheduler_state = SOS_SCHEDULER_READY;
}


/**
 * @author                              :   Hossam Elwahsh
 *
 * @brief                               :   Generates a new unique ID for SOS task
 *
 * @param[out]  uint8_new_task_id       :   Generated task ID
 *
 * @return  SOS_STATUS_SUCCESS          :   Success,    Task ID generated successfully
 *          SOS_STATUS_DATABASE_FULL    :   Failed,     DB full, all unique IDs are in-use
 *          SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 */
static enu_sos_status_t_    sos_generate_task_id(uint8_t_ * uint8_new_task_id)
{
    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    else
    {
        /* generate a new task ID */

        uint8_t_ uint8_generated = FALSE;       // generated flag

        // IDs Maps
        // 0(false): unused, 1(true): used
        uint8_t_ uint8_ids_map[SOS_NUMBER_OF_TASKS] = {FALSE};

        // Calculate ids map DB O(n)
        for (uint8_t_ i = 0; i < SOS_NUMBER_OF_TASKS; ++i) {
            if(NULL_PTR == gl_arr_ptr_str_task[i])
            {
                // reached end of tasks
                break;
            }
            else
            {
                uint8_ids_map[gl_arr_ptr_str_task[i]->uint8_task_id] = TRUE;
            }
        }

        // Get first unused ID, worst case: O(n)
        for (uint8_t_ id = 0; id < SOS_NUMBER_OF_TASKS; ++id) {
            if(FALSE == uint8_ids_map[id])
            {
                *uint8_new_task_id = id;
                uint8_generated = TRUE;
                break;
            }
        }

        if(FALSE == uint8_generated) // all possible ID numbers are in use == database is full
        {
            // DB Full
            enu_sos_status_retval = SOS_STATUS_DATABASE_FULL;
        }
        else
        {
            /* Do Nothing */
        }
    }

    return enu_sos_status_retval;
}


static uint32_t_ gcd(uint32_t_ uint32_first_var, uint32_t_ uint32_second_variable) 
{
	uint32_t_ uint32_gcd_value = 0, uint32_temp;
    while (uint32_second_variable != 0) 
	{
        uint32_temp = uint32_second_variable;
        uint32_second_variable = uint32_first_var % uint32_second_variable;
        uint32_first_var = uint32_temp;
    }
	uint32_gcd_value = uint32_first_var;
    return uint32_first_var;
}

static uint32_t_ lcm(uint32_t_ uint32_first_var, uint32_t_ uint32_second_variable) 
{
	uint32_t_ uint32_lcm_return_value = 0;
	uint32_t_ uint32_gcd_value = 0;
	uint32_gcd_value = gcd(uint32_first_var, uint32_second_variable);
    uint32_lcm_return_value = (uint32_first_var * uint32_second_variable) / uint32_gcd_value;
	return uint32_lcm_return_value;
}

static void calculate_hyper_period(uint32_t_* ptr_uint32_hyper_period) 
{
	uint8_t_ uint8_looping_variable = 0;
	*ptr_uint32_hyper_period = gl_arr_ptr_str_task[0]->uint16_task_periodicity;
	for (; uint8_looping_variable < gl_uint8_number_of_tasks_added; uint8_looping_variable++)
	{
		*ptr_uint32_hyper_period = lcm(*ptr_uint32_hyper_period, gl_arr_ptr_str_task[uint8_looping_variable]->uint16_task_periodicity);
	}
}
