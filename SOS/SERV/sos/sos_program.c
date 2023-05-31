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
 *  @param[in,out]  ptr_str_task 	        :   Pointer to task structure
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
        str_sos_task_t_ ** str_sos_task_to_delete;
        enu_sos_status_retval = sos_find_task(uint8_task_id, str_sos_task_to_delete);

        if(SOS_STATUS_SUCCESS == enu_sos_status_retval) // task found
        {
            /* Task Found - Delete it */
            *str_sos_task_to_delete = NULL_PTR;
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
 *	@syntax				:	sos_modify(str_sos_task_t_ str_task);
 *	@description		:	Modifies tasks and updates the  database
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
        uint8_t_ uint8_ids_map[SOS_MAX_ID_NUMBER+1] = {FALSE};

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
        for (uint8_t_ id = 0; id <= SOS_MAX_ID_NUMBER; ++id) {
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