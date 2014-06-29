
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj[2];

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];
static PORT_STACK test_task_stack2[TEST_TASK_STK_SIZE];

static int flag = 0;

static RAW_MUTEX m1;

static void test_task1(void * pParam)
{

        while(1) {	
                
               raw_mutex_get(&m1, RAW_WAIT_FOREVER);
               
		if(0 == flag){

			flag = 1;
			__put_char("set ", 4);
		}

		raw_mutex_put(&m1);

		raw_sleep(10);
        }
}

static void test_task2(void * pParam)
{

        while(1) {
	
		raw_mutex_get(&m1, RAW_WAIT_FOREVER);

		if(1 == flag) {

			flag = 0;
			__put_char("clean ", 6);
		}

		raw_mutex_put(&m1);

        }
}


extern int test_switch;

void test_mutex()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	raw_mutex_create(&m1, "mutex1", RAW_MUTEX_INHERIT_POLICY, 0);


        raw_task_create(&test_task_obj[0], (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);


        raw_task_create(&test_task_obj[1], (RAW_U8  *)"task2", 0,
                                 15, 10,   test_task_stack2,
                                 TEST_TASK_STK_SIZE ,  test_task2, 1);



}




