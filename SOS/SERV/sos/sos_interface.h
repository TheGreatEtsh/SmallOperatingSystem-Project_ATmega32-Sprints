/**
 * @fileName	:	sos_interface.h
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Hamsters
 * @brief		: 	Interface file for Simple Operating System 
 */ 


#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

#include "std.h"
#include "sos_preconfig.h"
#include "timer_interface.h"

typedef void(*ptr_func_task_t_)(void);

typedef enum
{
	SOS_SCHEDULER_UNINITIALIZED		= 0 ,
	SOS_SCHEDULER_INITIALIZED		    ,
	SOS_SCHEDULER_BLOCKED		        ,
	SOS_SCHEDULER_READY
}enu_sos_scheduler_state_t_;

typedef enum
{
	SOS_STATUS_SUCCESS				= 0	,
	SOS_STATUS_FAILED					,
	SOS_STATUS_INVALID_STATE			,
	SOS_STATUS_INVALID_ARGS             ,
	SOS_STATUS_INVALID_TASK_ID			,
	SOS_STATUS_DATABASE_FULL			,
	SOS_STATUS_TOTAL
}enu_sos_status_t_;


typedef struct
{
	uint8_t_ 			uint8_task_id;
	uint8_t_ 			uint8_task_priority;
	uint16_t_  			uint16_task_periodicity;
	ptr_func_task_t_	ptr_func_task;
}str_sos_task_t_;


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
enu_sos_status_t_ sos_init(void);

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
enu_sos_status_t_ sos_deinit(void);

/**
 *	@syntax				:	sos_create_task(str_sos_task_t_* ptr_str_task);
 *	@description		:	Creates tasks and add them to the database
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	*ptr_str_task
 *  @Parameters (out)	:	*ptr_str_task
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_DATABASE_FULL in case of Database is full
 */
enu_sos_status_t_ sos_create_task(str_sos_task_t_* ptr_str_task);

/**
 *	@syntax				:	sos_delete_task(uint8_t_ uint8_task_id);
 *	@description		:	delete tasks from Database
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_sos_status_t_ sos_delete_task(uint8_t_ uint8_task_id);

/**
 *	@syntax				:	sos_modify_task(str_sos_task_t_ str_task);
 *	@description		:	Modifies tasks and updates the  database
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	str_task
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_sos_status_t_ sos_modify_task(str_sos_task_t_ str_task);

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
enu_sos_status_t_ sos_run(void);

/**
 *	@syntax				:	sos_modify_task(str_sos_taskCreate_t_ str_task);
 *	@description		:	Stops the timer
 *	@Sync\Async      	:	Synchronous
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */
enu_sos_status_t_ sos_disable(void);



#endif


