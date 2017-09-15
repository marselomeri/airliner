#include "ea_perfmon_test.h"
#include "ea_test_utils.h"
#include "ea_app.h"
#include "ea_custom.h"
#include "ea_msg.h"

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

char PERFMON_APP_PATH[OS_MAX_PATH_LEN] = "/usr/bin/python";
char PERFMON_TEST_ARG_FIB[OS_MAX_PATH_LEN] = "fib.py";
char PERFMON_TEST_ARG_SLP[OS_MAX_PATH_LEN] = "sleep.py";
int PERFMON_SAMPLES = 5;

/**
 * Test EA_PerfmonCustom(), Nominal
 */
void Test_EA_PerfmonCustom_Nominal(void)
{
	/*
	** Create child process to execute test app
	*/
	pid_t pid = fork();
	/*
	** Child process
	*/
	if (pid == 0)
	{
		char *argv[] = {PERFMON_APP_PATH, PERFMON_TEST_ARG_FIB, NULL};
		if(execvp(PERFMON_APP_PATH, argv) == -1)
		{
			printf("Unable to execute new process\n");
		}
		exit(0);
	}
	/*
	** Failed Fork
	*/
	else if (pid == -1)
	{
		printf("Unable to execute fork\n");
	}
	/*
	** Parent process
	*/
	else
	{
		int high_util_flag = 0;
		int low_util_flag = 0;
		int util = 0;
		int count = 0;
		while(count < PERFMON_SAMPLES)
		{
			/* Get current util */
			EA_PerfmonCustom(pid);
			util = EA_AppData.HkTlm.ActiveAppUtil;

			/* Test if util in expected ranges */
			if(util >= 0 && util <= 100)
			{
				low_util_flag = 1;
			}
			if(util > 50 && util <= 100)
			{
				high_util_flag = 1;
			}
			count += 1;
			sleep(1);
		}

		/* Verify results */
		UtAssert_True(low_util_flag==1, "Hit low util threshold");
		UtAssert_True(high_util_flag==1, "Hit high util threshold");
	}
}

/**
 * Test EA_PerfmonCustom(), Idle
 */
void Test_EA_PerfmonCustom_Idle(void)
{
	/*
	** Create child process to execute test app
	*/
	pid_t pid = fork();
	/*
	** Child process
	*/
	if (pid == 0)
	{
		char *argv[] = {PERFMON_APP_PATH, PERFMON_TEST_ARG_SLP, NULL};
		if(execvp(PERFMON_APP_PATH, argv) == -1)
		{
			printf("Unable to execute new process\n");
		}
		exit(0);
	}
	/*
	** Failed Fork
	*/
	else if (pid == -1)
	{
		printf("Unable to execute fork\n");
	}
	/*
	** Parent process
	*/
	else
	{
		int high_util_flag = 0;
		int low_util_flag = 0;
		int util = 0;
		int count = 0;
		while(count < PERFMON_SAMPLES)
		{
			/* Get current util */
			EA_PerfmonCustom(pid);
			util = EA_AppData.HkTlm.ActiveAppUtil;

			/* Test if util in expected ranges */
			if(util >= 0 && util <= 100)
			{
				low_util_flag = 1;
			}
			if(util > 50 && util <= 100)
			{
				high_util_flag = 1;
			}
			count += 1;
			sleep(1);
		}

		/* Verify results */
		UtAssert_True(low_util_flag==1, "Hit low util threshold");
		UtAssert_True(high_util_flag==0, "Hit high util threshold");
	}
}



/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void EA_Perfmon_Test_AddTestCases(void)
{
	UtTest_Add(Test_EA_PerfmonCustom_Nominal, EA_Test_Setup, EA_Test_TearDown, "Test_EA_PerfmonCustom_Nominal");
	UtTest_Add(Test_EA_PerfmonCustom_Idle, EA_Test_Setup, EA_Test_TearDown, "Test_EA_PerfmonCustom_Idle");
}

