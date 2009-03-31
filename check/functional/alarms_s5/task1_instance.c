/*Instance of task t1*/

#include "embUnit.h"
#include "tpl_os.h"

DeclareAlarm(Alarm1);
DeclareTask(t2);

void WaitActivationOneShotAlarm(AlarmType Alarm);

/*test case:test the reaction of the system called with 
an activation of a task*/
static void test_t1_instance(void)
{
	
	StatusType result_inst_1, result_inst_3, result_inst_4;
	TaskStateType result_inst_2;
	
	result_inst_1 = SetRelAlarm(Alarm1, 2, 0);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_1);
	
	WaitActivationOneShotAlarm(Alarm1);

	result_inst_3 = GetTaskState(t2, &result_inst_2);
	TEST_ASSERT_EQUAL_INT(READY, result_inst_2);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_3);
	
	result_inst_4 = TerminateTask();
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_4);
}

/*create the test suite with all the test cases*/
TestRef AlarmsTest_seq5_t1_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t1_instance",test_t1_instance)
	};
	EMB_UNIT_TESTCALLER(AlarmsTest,"AlarmsTest_sequence5",NULL,NULL,fixtures);

	return (TestRef)&AlarmsTest;
}
