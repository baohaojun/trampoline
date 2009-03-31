/*Instance of task t6*/

#include "embUnit.h"
#include "tpl_os.h"

/*test case:test the reaction of the system called with 
an activation of a task*/
static void test_t6_instance(void)
{
	StatusType result_inst;
	
	result_inst = TerminateTask();
	TEST_ASSERT_EQUAL_INT(E_OK , result_inst); 
}

/*create the test suite with all the test cases*/
TestRef TaskManagementTest_seq13_t6_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t6_instance",test_t6_instance)
	};
	EMB_UNIT_TESTCALLER(TaskManagementTest,"TaskManagementTest_sequence13",NULL,NULL,fixtures);

	return (TestRef)&TaskManagementTest;
}
