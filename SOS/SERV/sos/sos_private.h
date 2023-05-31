/**
 * @fileName	:	sos_private.h
 * @Created		: 	2:08 AM Tuesday, May 30, 2023
 * @Author		: 	Hamsters
 * @brief		: 	Private file for Simple Operating System 
 */ 


#ifndef SOS_PRIVATE_H_
#define SOS_PRIVATE_H_
#include "sos_interface.h"

static enu_sos_status_t_	sos_find_task		(uint8_t_ uint8_task_id, str_sos_task_t_ ** ptr_ptr_str_sos_task);
static void					sos_sort_database	(void);
static void					sos_system_scheduler(void);
static void					sos_sys_tick_task	(void);
static enu_sos_status_t_    sos_generate_task_id(uint8_t_ * uint8_new_task_id);

#endif /* SOS_PRIVATE_H_ */