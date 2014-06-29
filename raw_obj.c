/*
     raw os - Copyright (C)  Lingjun Chen(jorya_txj).

    This file is part of raw os.

    raw os is free software; you can redistribute it it under the terms of the 
    GNU General Public License as published by the Free Software Foundation; 
    either version 3 of the License, or  (at your option) any later version.

    raw os is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
    See the GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. if not, write email to jorya.txj@gmail.com
                                      ---

    A special exception to the LGPL can be applied should you wish to distribute
    a combined work that includes raw os, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/


/* 	2012-4  Created by jorya_txj
  *	xxxxxx   please added here
  */

#include <raw_api.h>

RAW_U8                    raw_os_active;
RAW_U8                    idle_task_exit;

RAW_RUN_QUEUE             raw_ready_queue;

/*System  lock*/
RAW_U8                    raw_sched_lock;
RAW_U8                    raw_int_nesting;

/*highest ready task object*/
RAW_TASK_OBJ              *high_ready_obj;

/*current active task*/
RAW_TASK_OBJ              *raw_task_active;

/*idle attribute*/
RAW_TASK_OBJ              raw_idle_obj;
PORT_STACK                idle_stack[IDLE_STACK_SIZE];

/*tick attribute*/
RAW_TICK_TYPE             raw_tick_count;
LIST                      tick_head[TICK_HEAD_ARRAY];

#if (CONFIG_RAW_TIMER > 0)

LIST                      timer_head[TIMER_HEAD_NUMBERS];
RAW_TICK_TYPE             raw_timer_count;
RAW_U32                   raw_timer_ctrl;
RAW_TASK_OBJ              raw_timer_obj;
PORT_STACK                timer_task_stack[TIMER_STACK_SIZE];
RAW_SEMAPHORE             timer_sem;

#endif


#if (RAW_SYSTEM_CHECK > 0)

RAW_SYSTEM_DEBUG          system_debug;

#endif


#if (CONFIG_RAW_TASK_0 > 0)

RAW_U16                    task_0_event_head;
RAW_U16                    task_0_event_end;
RAW_U16                    task_0_events;
RAW_U16                    peak_events;

EVENT_STRUCT               task_0_events_queue[MAX_TASK_EVENT];
RAW_TASK_OBJ               raw_task_0_obj;

PORT_STACK                 task_0_stack[TASK_0_STACK_SIZE];
EVENT_HANLDER              task_0_event_handler;
RAW_U8                     task_0_exit;


#if (CONFIG_RAW_ZERO_INTERRUPT > 0)

OBJECT_INT_MSG             object_int_msg[OBJECT_INT_MSG_SIZE];
OBJECT_INT_MSG             *free_object_int_msg;
RAW_U32                    int_msg_full;
EVENT_HANLDER              msg_event_handler;

#endif

#endif

#if (CONFIG_RAW_TICK_TASK > 0)

RAW_TASK_OBJ               tick_task_obj;
PORT_STACK                 tick_task_stack[TICK_TASK_STACK_SIZE];
RAW_SEMAPHORE              tick_semaphore_obj;

#endif


#if (CONFIG_RAW_IDLE_EVENT > 0)

/*public global event*/
STATE_EVENT STM_GLOBAL_EVENT[4] = {
    { STM_EMPTY_SIG, 	0, 0 },
    { STM_ENTRY_SIG,    0, 0 },
    { STM_EXIT_SIG,     0, 0 },
    { STM_INIT_SIG,     0, 0 }
};

RAW_U8           raw_idle_rdy_grp;                     
RAW_U8           raw_rdy_tbl[RAW_IDLE_RDY_TBL_SIZE];
LIST             raw_idle_tick_head;

const RAW_U8     raw_idle_map_table[256] = {
    0u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x00 to 0x0F                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x10 to 0x1F                   */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x20 to 0x2F                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x30 to 0x3F                   */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x40 to 0x4F                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x50 to 0x5F                   */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x60 to 0x6F                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x70 to 0x7F                   */
    7u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x80 to 0x8F                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x90 to 0x9F                   */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xA0 to 0xAF                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xB0 to 0xBF                   */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xC0 to 0xCF                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xD0 to 0xDF                   */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xE0 to 0xEF                   */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u  /* 0xF0 to 0xFF                   */
};

#endif


