/*Instance of task t1*/

#include "embUnit.h"
#include "tpl_os.h"

DeclareAlarm(Alarm1);

void WaitActivationPeriodicAlarm(AlarmType Alarm);
void WaitActivationOneShotAlarm(AlarmType Alarm);

/*test case:test the reaction of the system called with 
an activation of a task*/
static void test_t1_instance(void)
{
	
	StatusType result_inst_1, result_inst_2, result_inst_3, result_inst_4, result_inst_5, result_inst_6, result_inst_7, result_inst_9, result_inst_10;
	TickType result_inst_8;

	result_inst_1 = SetAbsAlarm(Alarm1, 2, 2);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_1);
	
	result_inst_2 = SetAbsAlarm(Alarm1, 3, 0);
	TEST_ASSERT_EQUAL_INT(E_OS_STATE, result_inst_2);
	
	WaitActivationPeriodicAlarm(Alarm1);
	
	result_inst_3 = Schedule();
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_3);	

	WaitActivationPeriodicAlarm(Alarm1);
	
	result_inst_4 = Schedule();
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_4);	
	
	result_inst_5 = CancelAlarm(Alarm1);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_5);
	
	result_inst_6 = SetRelAlarm(Alarm1, 2, 0);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_6);
	
	result_inst_7 = SetRelAlarm(Alarm1, 3, 0);
	TEST_ASSERT_EQUAL_INT(E_OS_STATE, result_inst_7);
	
	result_inst_9 = GetAlarm(Alarm1, &result_inst_8);
	TEST_ASSERT_EQUAL_INT(2, result_inst_8);
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_9);
	
	WaitActivationOneShotAlarm(Alarm1);

	result_inst_10 = Schedule();
	TEST_ASSERT_EQUAL_INT(E_OK, result_inst_10);
	
}

/*create the test suite with all the test cases*/
TestRef AlarmsTest_seq3_t1_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t1_instance",test_t1_instance)
	};
	EMB_UNIT_TESTCALLER(AlarmsTest,"AlarmsTest_sequence3",NULL,NULL,fixtures);

	return (TestRef)&AlarmsTest;
}
