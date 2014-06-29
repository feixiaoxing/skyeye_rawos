
#include <raw_api.h>

#define  TEST_TASK_STK_SIZE 1024

static RAW_TASK_OBJ            test_task_obj;

static PORT_STACK test_task_stack1[TEST_TASK_STK_SIZE];

static RAW_TIMER tm1;

static int count = 0;

static void timer_func(void* p_arg)
{
	count ++;

	count = count % 3;

	if(1 == count)
		__put_char("a ", 2);

	else if(2 == (count %3))

		__put_char("b ", 2);
	else
		__put_char("c ", 2);
}


static void test_task1(void * pParam)
{

	raw_timer_activate(&tm1, 0);

        while(1) {
		
		;
        }
}

extern int test_switch;

void test_timer()
{

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	raw_timer_create(&tm1, "timer1", timer_func, 0, 10, 10, 0);

        raw_task_create(&test_task_obj, (RAW_U8  *)"task1", 0,
                                 5, 10,  test_task_stack1,
                                 TEST_TASK_STK_SIZE ,  test_task1, 1);
}




