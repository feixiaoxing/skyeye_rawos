

#include    <raw_api.h>

void _trace_init()
{


}

void _trace_task_switch(RAW_TASK_OBJ *from, RAW_TASK_OBJ *to)
{


}

void _trace_int_task_switch(RAW_TASK_OBJ *from, RAW_TASK_OBJ *to)
{
	
}


void _trace_task_create(RAW_TASK_OBJ *task)
{

}


void _trace_task_priority_change(RAW_TASK_OBJ *task, RAW_U8 priority)
{


}


void _trace_task_suspend(RAW_TASK_OBJ *task_obj, RAW_TASK_OBJ *task)
{
}


void _trace_task_resume(RAW_TASK_OBJ *task_obj, RAW_TASK_OBJ *task_resumed)
{

	
}


void _trace_task_delete(RAW_TASK_OBJ *task)
{


}


void _trace_task_abort(RAW_TASK_OBJ *task)
{


}


void _trace_task_0_overflow(EVENT_HANLDER *p, TASK_0_EVENT_TYPE ev, void *event_data)
{


}

void _trace_int_msg_exhausted()
{



}


void _trace_int_msg_post(RAW_U8 type, void *p_obj, void *p_void, RAW_U32 msg_size, RAW_U32 flags, RAW_U8 opt)
{


}

void _trace_semaphore_create(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj)
{


}



void _trace_semaphore_overflow(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj)
{


}

void _trace_semaphore_delete(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj)
{


}


void _trace_semaphore_get_success(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj)
{


}


void _trace_semaphore_get_block(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj, RAW_TICK_TYPE wait_option)
{


}

void _trace_sem_wake_task(RAW_TASK_OBJ *task, RAW_TASK_OBJ *task_waked_up, RAW_U8 opt_wake_all)
{

}


void _trace_semaphore_count_increase(RAW_TASK_OBJ *task, RAW_SEMAPHORE *semaphore_obj)
{


}


void _trace_queue_create(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj)
{

}


void _trace_queue_msg_post(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj, void *msg, RAW_U8 opt_send_method)

{

}

void _trace_queue_wake_task(RAW_TASK_OBJ *task, RAW_TASK_OBJ *task_waked_up, void *msg, RAW_U8 opt_wake_all)
{
}



void  _trace_queue_get_msg(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj, RAW_TICK_TYPE wait_option, void *msg)
{

}


void _trace_queue_msg_max(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj, void *msg, RAW_U8 opt_send_method)
{

}


void _trace_queue_get_block(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj, RAW_TICK_TYPE wait_option)
{



}


void _trace_queue_flush(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj)
{



}


void _trace_queue_delete(RAW_TASK_OBJ *task, RAW_QUEUE *queue_obj)
{


}


void _trace_mutex_create(RAW_TASK_OBJ *task,RAW_MUTEX *mutex_ptr, RAW_U8 *name_ptr, RAW_U8 policy, RAW_U8 ceiling_prio)
{

}


void _trace_mutex_release(RAW_TASK_OBJ *task, RAW_TASK_OBJ *tcb, RAW_U8 newpri)
{

}


void _trace_mutex_ex_ce_pri(RAW_TASK_OBJ *task, RAW_MUTEX *mutex_obj, RAW_TICK_TYPE wait_option)
{
}


void _trace_mutex_get(RAW_TASK_OBJ *task, RAW_MUTEX *mutex_obj, RAW_TICK_TYPE wait_option)
{

}

void _trace_task_pri_inv(RAW_TASK_OBJ *task, RAW_TASK_OBJ *mtxtsk)
{

}



void _trace_mutex_get_block(RAW_TASK_OBJ *task, RAW_MUTEX *mutex_obj, RAW_TICK_TYPE wait_option)
{


}

void _trace_mutex_release_success(RAW_TASK_OBJ *task, RAW_MUTEX *mutex_obj)
{
}

void _trace_mutex_wake_task(RAW_TASK_OBJ *task, RAW_TASK_OBJ *task_waked_up)
{
}


void _trace_mutex_delete(RAW_TASK_OBJ *task, RAW_MUTEX *mutex_obj)
{

}

void _trace_task_stack_space(RAW_TASK_OBJ *task_obj)
{


}


void _trace_block_no_memory(RAW_TASK_OBJ *task_obj, MEM_POOL *pool_obj)
{

	
}


void _trace_block_pool_create(RAW_TASK_OBJ *task_obj, MEM_POOL *pool_obj)
{

}


void _trace_byte_no_memory(RAW_TASK_OBJ *task_obj, RAW_BYTE_POOL_STRUCT *pool_obj)
{

	task_obj = task_obj;
	pool_obj = pool_obj;

}


void _trace_event_create(RAW_TASK_OBJ *task_obj, RAW_EVENT *event_obj, RAW_U8 *name, RAW_U32 flags_init)
{

}


void _trace_event_get(RAW_TASK_OBJ *task_obj, RAW_EVENT *event_obj)
{

}


void _trace_event_get_block(RAW_TASK_OBJ *task_obj, RAW_EVENT *event_obj, RAW_TICK_TYPE wait_option)
{

	
}


void _trace_event_wake(RAW_TASK_OBJ *task_obj, RAW_TASK_OBJ *task)
{


}


void _trace_event_delete(RAW_TASK_OBJ *task_obj, RAW_EVENT *event_obj)
{


}


void _trace_queue_size_create(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj)
{


}


void _trace_queue_size_msg_max(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj, void *msg, MSG_SIZE_TYPE msg_size, RAW_U8 opt_send_method)
{


}

void _trace_queue_size_msg_post(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj, void *msg, MSG_SIZE_TYPE msg_size, RAW_U8 opt_send_method)
{

	
}


void _trace_queue_size_wake_task(RAW_TASK_OBJ *task_obj, RAW_TASK_OBJ *task_waked_up, void *msg, MSG_SIZE_TYPE msg_size, RAW_U8 opt_wake_all)
{
}


void _trace_queue_size_get_msg(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj, RAW_TICK_TYPE wait_option, void *msg, RAW_U32 msg_size)
{

}

void _trace_queue_size_get_block(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj, RAW_TICK_TYPE wait_option)
{

}

void _trace_queue_size_flush(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj)
{


}

void _trace_queue_size_delete(RAW_TASK_OBJ *task_obj, RAW_QUEUE_SIZE *queue_size_obj)
{


}


void _trace_queue_buffer_create(RAW_TASK_OBJ *task_obj, RAW_QUEUE_BUFFER *queue_buffer_obj)
{


}


void _trace_buffer_max(RAW_TASK_OBJ *task_obj, RAW_QUEUE_BUFFER *queue_buffer_obj, RAW_VOID *p_void, MSG_SIZE_TYPE msg_size, RAW_U8 opt_send_method)
{
	
}

void _trace_buffer_post(RAW_TASK_OBJ *task_obj, RAW_QUEUE_BUFFER *queue_buffer_obj, RAW_VOID *p_void, MSG_SIZE_TYPE msg_size, RAW_U8 opt_send_method)
{


}


void _trace_queue_buffer_wake_task(RAW_TASK_OBJ *task_obj, RAW_TASK_OBJ *task_waked_up, RAW_VOID *p_void, MSG_SIZE_TYPE msg_size, RAW_U8 opt_send_method)
{

	
}


void _trace_queue_buffer_get_block(RAW_TASK_OBJ *task_obj, RAW_QUEUE_BUFFER *queue_buffer_obj, RAW_TICK_TYPE wait_option)
{

}




