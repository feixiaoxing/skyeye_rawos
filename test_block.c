
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj;

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];

static RAW_U8 buffer[1024];

static RAW_U8* p_block;

static MEM_POOL mem_pool;

static RAW_U8 count = 0;

static void test_task1(void * pParam)
{
	RAW_U8* addr;

        while(1) {
		
		if(RAW_SUCCESS == raw_block_allocate(&mem_pool, (void**)&addr)) {
		
			count ++;

			__put_char("ok ", 3);
		}else {

			__put_char("error ", 6);
		}

		raw_sleep(20);
        }
}

extern int test_switch;

void test_block()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;


	if (RAW_SUCCESS != raw_block_pool_create(&mem_pool, 
					"pool_block1", 
					32, 
					buffer, 
					1024)) {

		__put_char("error ", 6);
		return;
	}

        raw_task_create(&test_task_obj, (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);
}




