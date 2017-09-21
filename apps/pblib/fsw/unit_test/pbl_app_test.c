
#include "pbl_app_test.h"
#include "pb_lib.h"
#include "pbl_test_utils.h"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_sb_hooks.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"

char 				*TEST_MSG_NAME = "TestMsg";
char 				*BAD_TEST_MSG_NAME = "BadTestMsg";
CFE_SB_MsgId_t 		TEST_MSG_ID = 1;
uint16 				TEST_CC = 1;

/**
 * Test PBLIB_LibInit(), Fail Create Mutex
 */
void Test_PBLIB_LibInit_Fail_Mutex(void)
{
	int32 retCode = 0;

	/* Set to cause to fail */
	Ut_OSAPI_SetReturnCode(UT_OSAPI_MUTSEMCREATE_INDEX, -1, 1);

	/* Execute the function being tested */
	retCode = PBLIB_LibInit();

	/* Verify results */
	UtAssert_True(retCode==-1,"Return = -1");
}

/**
 * Test PBLIB_LibInit(), Nominal
 */
void Test_PBLIB_LibInit_Nominal(void)
{
	int32 retCode = -1;

	/* Execute the function being tested */
	retCode = PBLIB_LibInit();

	/* Verify results */
	UtAssert_True(retCode==CFE_SUCCESS,"Return = CFE_SUCCESS");
}

/**
 * Test PBLIB_RegisterMessage(), Invalid MsgID
 */
void Test_PBLIB_RegisterMessage_Inv_MsgID(void)
{
	int32 retCode = 0;

	/* Execute the function being tested */
	retCode = PBLIB_RegisterMessage(0, TEST_CC, TEST_MSG_NAME);

	/* Verify results */
	UtAssert_True(retCode==-1,"Invalid MsgId");
}

/**
 * Test PBLIB_RegisterMessage(), Full array
 */
void Test_PBLIB_RegisterMessage_Full(void)
{
	int32 retCode = -1;

	for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
	{
		PBLIB_RegisterMessage(TEST_MSG_ID + i, TEST_CC, TEST_MSG_NAME);
	}

	/* Execute the function being tested */
	retCode = PBLIB_RegisterMessage(TEST_MSG_ID, TEST_CC, TEST_MSG_NAME);

	/* Verify results */
	UtAssert_True(retCode==-2,"Full registration array");
}

/**
 * Test PBLIB_RegisterMessage(), Nominal
 */
void Test_PBLIB_RegisterMessage_Nominal(void)
{
	int32 retCode = -1;

	/* Execute the function being tested */
	retCode = PBLIB_RegisterMessage(TEST_MSG_ID, TEST_CC, TEST_MSG_NAME);

	/* Verify results */
	UtAssert_True(retCode==CFE_SUCCESS,"Return = CFE_SUCCESS");
}

/**
 * Test PBLIB_DeregisterMessage(), Invalid MsgID
 */
void Test_PBLIB_DeregisterMessage_Inv_MsgID(void)
{
	int32 retCode = 0;

	/* Execute the function being tested */
	retCode = PBLIB_DeregisterMessage(0, TEST_CC);

	/* Verify results */
	UtAssert_True(retCode==-1,"Invalid MsgId");
}

/**
 * Test PBLIB_DeregisterMessage(), Not found
 */
void Test_PBLIB_RegisterMessage_No_Match(void)
{
	int32 retCode = -1;

	/* Execute the function being tested */
	retCode = PBLIB_DeregisterMessage(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(retCode==-2,"No matching registration");
}

/**
 * Test PBLIB_DeregisterMessage(), Nominal
 */
void Test_PBLIB_DeregisterMessage_Nominal(void)
{
	int32 retCode = -1;

	/* Register the MsgId and cmd code */
	retCode = PBLIB_RegisterMessage(TEST_MSG_ID, TEST_CC, TEST_MSG_NAME);

	/* Execute the function being tested */
	retCode = PBLIB_DeregisterMessage(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(retCode==CFE_SUCCESS,"Return = CFE_SUCCESS");
}

/**
 * Test OS_SymbolLookupHook()
 */
int32 OS_SymbolLookupHook( uint32 *SymbolAddress, const char *SymbolName )
{
	*SymbolAddress = 1;
}

/**
 * Test PBLIB_GetSerializationFunc(), Not found
 */
void Test_PBLIB_GetSerializationFunc_No_Match(void)
{
	uint32 funcAddr = -1;

	/* Execute the function being tested */
	funcAddr = (uint32)PBLIB_GetSerializationFunc(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(funcAddr==0,"Serialization function not found");
}

/**
 * Test PBLIB_GetSerializationFunc(), Nominal
 */
void Test_PBLIB_GetSerializationFunc_Nominal(void)
{
	uint32 funcAddr = 0;

	/* Register the MsgId and cmd code */
	PBLIB_RegisterMessage(TEST_MSG_ID, TEST_CC, TEST_MSG_NAME);

	/* Set symbol lookup return */
	Ut_OSAPI_SetFunctionHook(UT_OSAPI_SYMBOLLOOKUP_INDEX, OS_SymbolLookupHook);

	/* Execute the function being tested */
	funcAddr = (uint32)PBLIB_GetSerializationFunc(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(funcAddr==1,"Serialization function found");
}

/**
 * Test PBLIB_GetDeserializationFunc(), Not found
 */
void Test_PBLIB_GetDeserializationFunc_No_Match(void)
{
	uint32 funcAddr = -1;

	/* Set symbol lookup return */
	Ut_OSAPI_SetReturnCode(UT_OSAPI_SYMBOLLOOKUP_INDEX, 0, 1);

	/* Execute the function being tested */
	funcAddr = (uint32)PBLIB_GetDeserializationFunc(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(funcAddr==0,"Serialization function not found");
}

/**
 * Test PBLIB_GetDeserializationFunc(), Nominal
 */
void Test_PBLIB_GetDeserializationFunc_Nominal(void)
{
	uint32 funcAddr = 0;

	/* Register the MsgId and cmd code */
	PBLIB_RegisterMessage(TEST_MSG_ID, TEST_CC, TEST_MSG_NAME);

	/* Set symbol lookup return */
	Ut_OSAPI_SetFunctionHook(UT_OSAPI_SYMBOLLOOKUP_INDEX, OS_SymbolLookupHook);

	/* Execute the function being tested */
	funcAddr = (uint32)PBLIB_GetDeserializationFunc(TEST_MSG_ID, TEST_CC);

	/* Verify results */
	UtAssert_True(funcAddr==1,"Serialization function found");
}

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void PBLIB_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_PBLIB_LibInit_Fail_Mutex, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_LibInit_Fail_Mutex");
    UtTest_Add(Test_PBLIB_LibInit_Nominal, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_LibInit_Nominal");
    UtTest_Add(Test_PBLIB_RegisterMessage_Inv_MsgID, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_RegisterMessage_Inv_MsgID");
    UtTest_Add(Test_PBLIB_RegisterMessage_Full, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_RegisterMessage_Full");
	UtTest_Add(Test_PBLIB_RegisterMessage_Nominal, PBLIB_Test_Setup, PBLIB_Test_TearDown,
			   "Test_PBLIB_RegisterMessage_Nominal");
    UtTest_Add(Test_PBLIB_DeregisterMessage_Inv_MsgID, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_DeregisterMessage_Inv_MsgID");
    UtTest_Add(Test_PBLIB_RegisterMessage_No_Match, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_RegisterMessage_No_Match");
    UtTest_Add(Test_PBLIB_DeregisterMessage_Nominal, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_DeregisterMessage_Nominal");
    UtTest_Add(Test_PBLIB_GetSerializationFunc_No_Match, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_GetSerializationFunc_No_Match");
    UtTest_Add(Test_PBLIB_GetSerializationFunc_Nominal, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_GetSerializationFunc_Nominal");
    UtTest_Add(Test_PBLIB_GetDeserializationFunc_No_Match, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_GetDeserializationFunc_No_Match");
    UtTest_Add(Test_PBLIB_GetDeserializationFunc_Nominal, PBLIB_Test_Setup, PBLIB_Test_TearDown,
               "Test_PBLIB_GetDeserializationFunc_Nominal");


}


