/*Instance 4 of com error*/

#include "embUnit.h"
#include "tpl_os.h"
#include "tpl_com_error.h" /*for COMErrorGetServiceId()*/

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_comerror_instance4(void)
{
	StatusType result_inst_1, result_inst_2, result_inst_3;
	
	result_inst_1 = COMErrorGetServiceId();
	TEST_ASSERT_EQUAL_INT(COMServiceId_ReceiveMessage , result_inst_1);
	
	result_inst_2 = (StatusType)(*COMError_ReceiveMessage_DataRef());
	TEST_ASSERT_EQUAL_INT((StatusType)('3') , result_inst_2);
	
	result_inst_3 = (StatusType)COMError_ReceiveMessage_Message();
	TEST_ASSERT_EQUAL_INT(SEND_MESSAGE_COUNT , result_inst_3);
}

/*create the test suite with all the test cases*/
TestRef COMInternalTest_seq2_comerror_instance4(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_comerror_instance4",test_comerror_instance4)
	};
	EMB_UNIT_TESTCALLER(COMInternalTest,"COMInternalTest_sequence2",NULL,NULL,fixtures);
	
	return (TestRef)&COMInternalTest;
}
