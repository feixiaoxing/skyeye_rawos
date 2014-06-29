
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj[2];

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];
static PORT_STACK test_task_stack2[TEST_TASK_STK_SIZE];

static RAW_SEMAPHORE s1;

static void test_task1(void * pParam)
{

        while(1) {	

		raw_semaphore_get(&s1, RAW_WAIT_FOREVER);
		__put_char("give ", 5);

		raw_sleep(2);
        }
}

static void test_task2(void * pParam)
{

        while(1) {
		raw_semaphore_put(&s1);
		__put_char("get ", 4);

		raw_sleep(100);
        }
}


extern int test_switch;

void test_sem()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	raw_semaphore_create(&s1, "sem1", 0);

        raw_task_create(&test_task_obj[0], (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);


        raw_task_create(&test_task_obj[1], (RAW_U8  *)"task2", 0,
                                 5, 10,   test_task_stack2,
                                 TEST_TASK_STK_SIZE ,  test_task2, 1);



}




