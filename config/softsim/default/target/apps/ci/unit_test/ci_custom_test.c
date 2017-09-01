#include "ci_custom_test.h"
#include "ci_app.h"
#include "ci_test_utils.h"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"

int SOCK_RET_CODE;
int BIND_RET_CODE;

/**
 * Test CI_InitCustom(), Bad socket
 */
void Test_CI_InitCustom_Bad_Socket(void)
{
	int32	retCode = 0;

	/* Set to cause to fail */
	SOCK_RET_CODE = -1;

	/* Execute the function being tested */
	retCode = CI_InitCustom();

	/* Verify results */
	UtAssert_True(retCode==-1,"Return = -1");
	UtAssert_EventSent(CI_SOCKET_ERR_EID, CFE_EVS_ERROR, "", "Socket error");
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
}

/**
 * Test CI_InitCustom(), Bad bind
 */
void Test_CI_InitCustom_Bad_Bind(void)
{
	int32	retCode = 0;

	/* Set to cause to fail */
	SOCK_RET_CODE = 0;
	BIND_RET_CODE = -1;

	/* Execute the function being tested */
	retCode = CI_InitCustom();

	/* Verify results */
	UtAssert_True(retCode==-1,"Return = -1");
	UtAssert_EventSent(CI_SOCKET_ERR_EID, CFE_EVS_ERROR, "", "Bind error");
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
}

/**
 * Test CI_InitCustom(), Nominal
 */
void Test_CI_InitCustom_Nominal(void)
{
	int32	retCode = -1;

	/* Set to cause to pass */
	SOCK_RET_CODE = 0;
	BIND_RET_CODE = 0;

	/* Execute the function being tested */
	retCode = CI_InitCustom();

	/* Verify results */
	UtAssert_True(retCode==0,"Return = 0");
	UtAssert_EventSent(CI_ENA_INF_EID, CFE_EVS_INFORMATION, "", "Socket opened");
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
}

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void CI_Custom_Test_AddTestCases(void)
{
	UtTest_Add(Test_CI_InitCustom_Bad_Socket, CI_Test_Setup, CI_Test_TearDown,
			   "Test_CI_InitCustom_Bad_Socket");
	UtTest_Add(Test_CI_InitCustom_Bad_Bind, CI_Test_Setup, CI_Test_TearDown,
			   "Test_CI_InitCustom_Bad_Bind");
	UtTest_Add(Test_CI_InitCustom_Nominal, CI_Test_Setup, CI_Test_TearDown,
			   "Test_CI_InitCustom_Nominal");
}
