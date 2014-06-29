
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj;

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];

static RAW_U8 buffer[1024];

static RAW_BYTE_POOL_STRUCT byte_pool;

static RAW_U8 count = 0;

static void test_task1(void * pParam)
{
	RAW_U8* addr;

        while(1) {
		
		if(RAW_SUCCESS == raw_byte_allocate(&byte_pool, (void**)&addr, 16)) {
		
			count ++;

			__put_char("ok1 ", 4);
		}else {

			__put_char("error1 ", 7);
		}

		raw_sleep(20);
 
		if(RAW_SUCCESS == raw_byte_allocate(&byte_pool, (void**)&addr, 30)) {
		
			count ++;

			__put_char("ok2 ", 4);
		}else {

			__put_char("error2 ", 7);
		}

		raw_sleep(20);
               }
}

extern int test_switch;

void test_byte()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;


	if (RAW_SUCCESS != raw_byte_pool_create(&byte_pool, 
					"pool_byte1", 
					buffer, 
					1024)) {

		__put_char("error ", 6);
		return;
	}

        raw_task_create(&test_task_obj, (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);
}




