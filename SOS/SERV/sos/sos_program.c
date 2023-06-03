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
enu_sos_scheduler_state_t_	gl_enu_sos_scheduler_state = SOS_SCHEDULER_UNINITIALIZED;
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
{
    if (timer_init(  )==TIMER_NOK)
    {
		return SOS_STATUS_FAILED;
    }
    else
    {
		//SUCCESS
    }

    if (timer_set_time(TIMER_0, SOS_SYS_TICK_TIME_MS)==TIMER_NOK)
    {
        return SOS_STATUS_FAILED;
    }
    else
    {
		//SUCCESS
    }

    if (timer_enable_interrupt(TIMER_0)==TIMER_NOK)
    {
		return SOS_STATUS_FAILED;
    }
    else
    {
		//SUCCESS
    }
	
    if (timer_set_callback(TIMER_0,sos_sys_tick_task)== TIMER_NOK)
    {
		return SOS_STATUS_FAILED;
    }
    else
    {
		//SUCCESS
    }

    gl_enu_sos_scheduler_state = SOS_SCHEDULER_INITIALIZED;

    return SOS_STATUS_SUCCESS;
}

/**
 *
 *	@description		:	deinitializes the sos module
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *
 *
 */
enu_sos_status_t_ sos_deinit(void)
{
    if (
            (timer_pause(TIMER_0) == TIMER_NOK) ||
            (timer_disable_interrupt(TIMER_0) == TIMER_NOK)
        )
    {
        return SOS_STATUS_FAILED;
    }

    else if(0 != gl_uint8_number_of_tasks_added)
    {
        for (int i = 0; i < gl_uint8_number_of_tasks_added; ++i) {
            gl_arr_ptr_str_task[i] = NULL_PTR;
        }
    }
    gl_enu_sos_scheduler_state = SOS_SCHEDULER_UNINITIALIZED;

    return SOS_STATUS_SUCCESS;

}

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
        if(SOS_NUMBER_OF_TASKS == gl_uint8_number_of_tasks_added)
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
                uint8_t_ uint8_new_task_db_index = gl_uint8_number_of_tasks_added;
                gl_arr_ptr_str_task[uint8_new_task_db_index] = ptr_str_task;
                gl_uint8_number_of_tasks_added++;
                // sort DB tasks according to task priority
                sos_sort_database(uint8_new_task_db_index);

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
        uint8_t_ uint8_task_index_in_db = 0;
        enu_sos_status_retval = sos_find_task(uint8_task_id, &ptr_str_sos_task_to_delete, &uint8_task_index_in_db);

        if(
                SOS_STATUS_SUCCESS == enu_sos_status_retval      &&
                NULL_PTR != ptr_str_sos_task_to_delete
        ) // task found
        {
            /* Task Found - Delete it */
            //ptr_str_sos_task_to_delete = NULL_PTR;
			gl_arr_ptr_str_task[uint8_task_index_in_db] = NULL_PTR;
            sos_sort_database(uint8_task_index_in_db);
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
 *  @param[in,out]  uint8_task_id 	        :   Task ID to delete from DB
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task deleted successfully
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_ARGS     :   Failed,     Invalid Arguments Given
 *              SOS_STATUS_INVALID_TASK_ID  :   Failed,     Task ID not found in DB
 */
enu_sos_status_t_ sos_modify_task(uint8_t_ uint8_task_id)
{
    enu_sos_status_t_ enu_sos_status_retval = SOS_STATUS_SUCCESS;

    // SOS System State Check
    if(gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED)
    {
        enu_sos_status_retval = SOS_STATUS_INVALID_STATE;
    }
    else
    {
        // search for task ID in DB
        str_sos_task_t_ * ptr_str_sos_task_to_modify = NULL;
        uint8_t_ uint8_task_index_in_db = 0;
        enu_sos_status_retval = sos_find_task(uint8_task_id, &ptr_str_sos_task_to_modify, &uint8_task_index_in_db);

        if(SOS_STATUS_SUCCESS == enu_sos_status_retval) // task found
        {
            sos_sort_database(uint8_task_index_in_db); // sort modified task
            enu_sos_status_retval = SOS_STATUS_SUCCESS;
        }
        else
        {
            /* Task not found */
            enu_sos_status_retval = SOS_STATUS_INVALID_TASK_ID;
        }
    }

    return enu_sos_status_retval;
}

/**
 *	@author				                    :	Hossam Elwahsh - https://github.com/HossamElwahsh
 *
 *	@brief		                            :	Finds a task in DB using it's ID
 *  @param[in]      uint8_task_id 	        :   Task ID to search for
 *  @param[out]     ptr_ptr_str_sos_task 	:   Pointer to pointer store found task address
 *  @param[out]     uint8_task_index_in_db 	:   (optional) Pointer to store found task index in DB
 *
 *  @Return     SOS_STATUS_SUCCESS		    :	Success,    Task found
 *              SOS_STATUS_INVALID_STATE    :   Failed,     SOS Invalid State (uninitialized)
 *              SOS_STATUS_INVALID_TASK_ID  :   Failed,     Task ID not found in DB
 */
static enu_sos_status_t_	sos_find_task		(uint8_t_ uint8_task_id, str_sos_task_t_ ** ptr_ptr_str_sos_task, uint8_t_ * ptr_uint8_task_index_in_db)
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

        for (uint8_t_ i = 0; i < gl_uint8_number_of_tasks_added; ++i) {
            if(uint8_task_id == gl_arr_ptr_str_task[i]->uint8_task_id)
            {
                bool_found = TRUE;
                *ptr_ptr_str_sos_task = gl_arr_ptr_str_task[i]; // save found task pointer
                if(NULL_PTR != ptr_uint8_task_index_in_db)
                {
                    // store DB index
                    *ptr_uint8_task_index_in_db = i;
                }
                else
                {
                    /* Do Nothing */
                }
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
}


/**
 * @brief a private function to sort the task data base according to task
 *		  priority after each modification to the Data base 
 *
 * @param uint8_task_db_index : the index of the add/deleted/modified task
 *								in the task DB
 *
 * @return
 */
static void	sos_sort_database (uint8_t_ uint8_task_db_index)
{
	str_sos_task_t_* lo_ptr_str_temp_task;

	/* Check if a task was deleted */
	if(NULL_PTR == gl_arr_ptr_str_task[uint8_task_db_index])
	{
		/* swap the deleted task with the last active task */
		while(uint8_task_db_index < gl_uint8_number_of_tasks_added-1)
		{
			gl_arr_ptr_str_task[uint8_task_db_index] = gl_arr_ptr_str_task[uint8_task_db_index+1];
			gl_arr_ptr_str_task[uint8_task_db_index+1] = NULL_PTR;
			uint8_task_db_index++;
		}
	}
	/* Check if a task was added (any new task is added after the last task in the array) */
	else if(gl_uint8_number_of_tasks_added-1 == uint8_task_db_index)
	{
		/* return if in case this is the first task in the DB */
		if (!uint8_task_db_index) return;
		
		/* loop on previous tasks to insert new task in the right index according to priority */
		while(gl_arr_ptr_str_task[uint8_task_db_index]->uint8_task_priority 
			< gl_arr_ptr_str_task[uint8_task_db_index-1]->uint8_task_priority)
			{
				/* Swap the tasks */
				lo_ptr_str_temp_task = gl_arr_ptr_str_task[uint8_task_db_index];
				gl_arr_ptr_str_task[uint8_task_db_index] = gl_arr_ptr_str_task[uint8_task_db_index-1];
				gl_arr_ptr_str_task[uint8_task_db_index-1] = lo_ptr_str_temp_task;
				uint8_task_db_index --;
				
				/* Break out of loop if we reach the first index in DB */
				if(0 == uint8_task_db_index) break;
			}
	}
	else /* A task was modified */
	{
		uint8_t_ lo_uint8_temp_index = uint8_task_db_index;
		
		/* Check that the modified task is not the first in the DB */
		if(uint8_task_db_index)
		{
			/* 
			Check whether the priority of the task of the given index is smaller than
			that of the task at the previous index, if so, loop on the previous tasks
			to insert the modified task at the right index according to task priority
			*/
			
			while(gl_arr_ptr_str_task[lo_uint8_temp_index]->uint8_task_priority
			< gl_arr_ptr_str_task[lo_uint8_temp_index-1]->uint8_task_priority)
			{
				/* Swap the tasks */
				lo_ptr_str_temp_task = gl_arr_ptr_str_task[lo_uint8_temp_index];
				gl_arr_ptr_str_task[lo_uint8_temp_index] = gl_arr_ptr_str_task[lo_uint8_temp_index-1];
				gl_arr_ptr_str_task[lo_uint8_temp_index-1] = lo_ptr_str_temp_task;
				lo_uint8_temp_index --;
				if(0 == lo_uint8_temp_index) break;
			}
		}		
		
		/* 
		Check whether the priority of the task of the given index is bigger than
		that of the task at the next index, if so, loop on the previous tasks
		to insert the modified task at the right index according to task priority
		*/
		while(gl_arr_ptr_str_task[uint8_task_db_index]->uint8_task_priority
		> gl_arr_ptr_str_task[uint8_task_db_index+1]->uint8_task_priority)
		{
			/* Break out of loop if we reach the last task index */
			if(uint8_task_db_index == gl_uint8_number_of_tasks_added-1) break;
			
			/* Swap the tasks */
			lo_ptr_str_temp_task = gl_arr_ptr_str_task[uint8_task_db_index];
			gl_arr_ptr_str_task[uint8_task_db_index] = gl_arr_ptr_str_task[uint8_task_db_index+1];
			gl_arr_ptr_str_task[uint8_task_db_index+1] = lo_ptr_str_temp_task;
			uint8_task_db_index ++;			
		}
	}
}

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
void sos_run(void)
{
    if(
            (gl_enu_sos_scheduler_state != SOS_SCHEDULER_INITIALIZED) ||
            (TIMER_NOK == timer_resume(TIMER_0))
    )
    {
        return;
    }
    else
    {
        gl_enu_sos_scheduler_state = SOS_SCHEDULER_BLOCKED;
        while((gl_enu_sos_scheduler_state == SOS_SCHEDULER_BLOCKED)
              || (gl_enu_sos_scheduler_state == SOS_SCHEDULER_READY))
        {
            if (SOS_SCHEDULER_READY == gl_enu_sos_scheduler_state)
            {
                sos_system_scheduler();
            }
        }
    }


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
void sos_disable(void)
{
    if(
            (gl_enu_sos_scheduler_state == SOS_SCHEDULER_UNINITIALIZED) ||
            (TIMER_NOK == timer_pause(TIMER_0))
    )
    {
        return;
    }
    else
    {
        /* Success */
		gl_enu_sos_scheduler_state = SOS_SCHEDULER_INITIALIZED;
    }

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
		
		if(SOS_SCHEDULER_READY == gl_enu_sos_scheduler_state)
		{
			gl_enu_sos_scheduler_state = SOS_SCHEDULER_BLOCKED;
		}

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
        for (uint8_t_ i = 0; i < gl_uint8_number_of_tasks_added; ++i) {
            uint8_ids_map[gl_arr_ptr_str_task[i]->uint8_task_id] = TRUE;
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
    // Declare and initialize a uint32_t variable named uint32_gcd_value to 0.
    uint32_t_ uint32_gcd_value = 0;
    // Declare a uint32_t variable named uint32_temp.
    uint32_t_ uint32_temp;

    // Start a while loop that continues until uint32_second_variable is not equal to 0.
    while (uint32_second_variable != 0)
    {
        // Store the value of uint32_second_variable in uint32_temp.
        uint32_temp = uint32_second_variable;
        // Calculate the remainder of uint32_first_var
        //  divided by uint32_second_variable and assign it to uint32_second_variable.
        uint32_second_variable = uint32_first_var % uint32_second_variable;
        // Assign the value of uint32_temp to uint32_first_var.
        uint32_first_var = uint32_temp;
    }

    // Assign the value of uint32_first_var to uint32_gcd_value.
    uint32_gcd_value = uint32_first_var;

    // Return the calculated gcd value.
    return uint32_gcd_value;
}


static uint32_t_ lcm(uint32_t_ uint32_first_var, uint32_t_ uint32_second_variable)
{
    // Declare and initialize a uint32_t variable named uint32_lcm_return_value to 0.
    uint32_t_ uint32_lcm_return_value = 0;

    // Declare and initialize an uint32_t variable named uint32_gcd_value to 0.
    uint32_t_ uint32_gcd_value = 0;

    // Call the gcd (Greatest Common Divisor) function
    //  with uint32_first_var and uint32_second_variable as arguments
    //  and assign the returned value to uint32_gcd_value.
    uint32_gcd_value = gcd(uint32_first_var, uint32_second_variable);

    // Calculate the least common multiple (lcm)
    // by multiplying uint32_first_var and uint32_second_variable
    // and then dividing the result by uint32_gcd_value.
    // Assign the calculated value to uint32_lcm_return_value.
    uint32_lcm_return_value = (uint32_first_var * uint32_second_variable) / uint32_gcd_value;

    // Return the calculated lcm value.
    return uint32_lcm_return_value;
}


static void calculate_hyper_period(uint32_t_* ptr_uint32_hyper_period)
{
    // Declare and initialize an uint8_t variable named uint8_looping_variable to 0.
    uint8_t_ uint8_looping_variable = 0;

    // Assign the value of uint16_task_periodicity from the first element of the
    // gl_arr_ptr_str_task array to the memory location pointed to by ptr_uint32_hyper_period.
    *ptr_uint32_hyper_period = gl_arr_ptr_str_task[0]->uint16_task_periodicity;

    // Start a for loop that iterates until uint8_looping_variable
    // is less than gl_uint8_number_of_tasks_added,
    // incrementing uint8_looping_variable after each iteration.
    for (; uint8_looping_variable < gl_uint8_number_of_tasks_added; uint8_looping_variable++)
    {
        // Update the value of *ptr_uint32_hyper_period
        // by finding the least common multiple (lcm)
        // between the current value of *ptr_uint32_hyper_period
        // and the uint16_task_periodicity of the task
        // pointed to by the gl_arr_ptr_str_task[uint8_looping_variable].
        // This basically calculates the hyper period of the first two tasks periodicity,
        // then incrementally re-calculate the hyper period for the last result with the next task periodicity
        // until all the tasks have been processed we get the final total least hyper-period for all tasks
        *ptr_uint32_hyper_period = lcm(*ptr_uint32_hyper_period, gl_arr_ptr_str_task[uint8_looping_variable]->uint16_task_periodicity);
    }
}
