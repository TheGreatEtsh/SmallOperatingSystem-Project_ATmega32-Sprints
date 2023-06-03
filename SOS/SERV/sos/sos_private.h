/**
 * @fileName	:	sos_private.h
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Hamsters
 * @brief		: 	Private file for Simple Operating System 
 */ 


#ifndef SOS_PRIVATE_H_
#define SOS_PRIVATE_H_
#include "sos_interface.h"
#include "sos_preconfig.h"
#include "timer_interface.h"

typedef enum
{
    SOS_SCHEDULER_UNINITIALIZED		= 0 ,
    SOS_SCHEDULER_INITIALIZED		    ,
    SOS_SCHEDULER_BLOCKED		        ,
    SOS_SCHEDULER_READY
}enu_sos_scheduler_state_t_;


static enu_sos_status_t_	sos_find_task		(uint8_t_ uint8_task_id, str_sos_task_t_ ** ptr_ptr_str_sos_task, uint8_t_ * uint8_task_index_in_db);
static void					sos_sort_database	(uint8_t_ uint8_task_db_index);
static void					sos_system_scheduler(void);
static void					sos_sys_tick_task	(void);
static enu_sos_status_t_    sos_generate_task_id(uint8_t_ * uint8_new_task_id);

/* Hyper-period Calculations */
static uint32_t_			gcd						(uint32_t_ uint32_first_var, uint32_t_ uint32_second_variable);
static uint32_t_			lcm						(uint32_t_ uint32_first_var, uint32_t_ uint32_second_variable);
static void					calculate_hyper_period	(uint32_t_* ptr_uint32_hyper_period);

#endif /* SOS_PRIVATE_H_ */