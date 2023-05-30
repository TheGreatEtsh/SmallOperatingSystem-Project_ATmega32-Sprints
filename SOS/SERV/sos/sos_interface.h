/**
 * @fileName	:	sos_interface.h
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Ahmed Hesham
 * @brief		: 	Interface file for Simple Operating System 
 */ 


#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

typedef void(*SOS_task_t_)(void);

typedef enum
{
	SOS_STATUS_SUCCESS = 0,
	SOS_STATUS_INVALID_STATE,
	SOS_STATUS_DATABASE_FULL,
	SOS_STATUS_TASK_NFOUND
}enu_SOS_status_t_;

typedef enum
{
	SOS_TASK_AVAILABLE = 0,
	SOS_TASK_DELETED
}enu_SOS_taskState_t_

typedef struct
{
	uint8_t_ 	uint8_taskID;
	uint8_t_ 	uint8_taskPriority;
	uint16_t_  	uint16_taskPeriodicity;
	SOS_task_t_	ptr_task;
}str_SOS_taskCreate_t_;

typedef struct
{
	enu_SOS_taskState_t_ 	enu_taskState;
	str_SOS_taskCreate_t_*	ptrstr_task;
}str_SOS_taskDataBase_t_;

/**
 *	@syntax				:	SOS_init(void);
 *	@description		:	Initializes the SOS module
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case timers doesn't return an error
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */ 
enu_SOS_statust_ SOS_init(void);

/**
 *	@syntax				:	SOS_deinit(void);
 *	@description		:	deinitializes the SOS module
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case timers doesn't return an error
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */ 
enu_SOS_status_t_ SOS_deinit(void);

/**
 *	@syntax				:	SOS_createTask(str_SOS_taskCreate_t_* ptr_str_task);
 *	@description		:	Creates tasks and add them to the data base
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	*ptr_str_task
 *  @Parameters (out)	:	*ptr_str_task
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_DATABASE_FULL in case of Database is full
 */
enu_SOS_status_t_ SOS_createTask(str_SOS_taskCreate_t_* ptr_str_task);

/**
 *	@syntax				:	SOS_deleteTask(uint8_t_ uint8_taskID);
 *	@description		:	delete tasks from Database
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_SOS_status_t_ SOS_deleteTask(uint8_t_ uint8_taskID);

/**
 *	@syntax				:	SOS_modify(str_SOS_taskCreate_t_ str_task);
 *	@description		:	Modifies tasks and updates the  data base
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	str_task
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_TASK_NFOUND in case task is not found
 */
enu_SOS_status_t_ SOS_modify(str_SOS_taskCreate_t_ str_task);

/**
 *	@syntax				:	SOS_run(void);
 *	@description		:	Starts timer
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	None
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */
enu_SOS_status_t_ SOS_run(void);

/**
 *	@syntax				:	SOS_modify(str_SOS_taskCreate_t_ str_task);
 *	@description		:	Stops the timer
 *	@Sync\Async      	:	Synchronus
 *  @Reentrancy      	:	Reentrant
 *  @Parameters (in) 	:	uint8_taskID
 *  @Parameters (out)	:	None
 *  @Return value		:	SOS_STATUS_SUCCESS in case of SUCCESS
 *							SOS_STATUS_INVALID_STATE in case timers return an error
 */
enu_SOS_status_t_ SOS_disable(void);

#endif


