
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj[3];

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];
static PORT_STACK test_task_stack2[TEST_TASK_STK_SIZE];
static PORT_STACK test_task_stack3[TEST_TASK_STK_SIZE];

static void test_task1(void * pParam)
{

        while(1) {
		__put_char("hi ", 3);
		raw_sleep(10);	
        }
}

static void test_task2(void * pParam)
{

        while(1) {
		__put_char("bye ", 4);
		raw_sleep(5);
        }
}


static void test_task3(void * pParam)
{

        while(1) {
		__put_char("go ", 3);
		raw_sleep(5);
        }
}

extern int test_switch;

void test_task()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

        raw_task_create(&test_task_obj[0], (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);


        raw_task_create(&test_task_obj[1], (RAW_U8  *)"task2", 0,
                                 15, 10,   test_task_stack2,
                                 TEST_TASK_STK_SIZE ,  test_task2, 1);

	raw_task_create(&test_task_obj[2], (RAW_U8  *)"task3", 0,
                                 20, 10,   test_task_stack3,
                                 TEST_TASK_STK_SIZE ,  test_task3, 1);


}




