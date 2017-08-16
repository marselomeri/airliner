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
char PERFMON_TEST_ARG[OS_MAX_PATH_LEN] = "/home/vagrant/airliner/apps/ea/fsw/unit_test/fib.py";

int PERFMON_SAMPLES = 50;

/**
 * Test EA_PerfmonCustom(), Nominal
 */
void Test_EA_PerfmonCustom_Nominal(void)
{

	printf("Begin perfmon test\n");
	/*
	** Create child process to execute test app
	*/
	pid_t pid = fork();
	/*
	** Child process
	*/
	if (pid == 0)
	{
		char *argv[] = {PERFMON_APP_PATH, PERFMON_TEST_ARG, NULL};
		if(execvp(PERFMON_APP_PATH, argv) == -1)
		{
			printf("Unable to execute new process");
		}
		exit(0);
	}
	/*
	** Failed Fork
	*/
	else if (pid == -1)
	{
		printf("Unable to execute fork");
	}
	/*
	** Parent process
	*/
	else
	{
		printf("PID: %i\n", pid);
		int count = 0;
		int util = 0;
		int app_util = 0;
		int top_idx = EA_CalibrateTop(pid);
		while(count < PERFMON_SAMPLES)
		{
			util = EA_GetPidUtil(pid, top_idx);
			EA_PerfmonCustom(pid);
			app_util = (int)EA_AppData.HkTlm.ActiveAppUtil;
			printf("Top util: %i\n", util);
			printf("App util: %i\n\n", app_util);
		}
	}

	/* Execute the function being tested */

	/* Verify results */

	//UtAssert_True(EA_AppData.HkTlm.LastAppStatus==-1,"LastAppStatus = -1");
	printf("End perfmon test");
}

int EA_CalibrateTop(int pid)
{
	FILE *fp;
	char output[1024];
	char top_cmd_calibrate[80];
	char *cpu_perc = "%CPU";

	/* Generate top calibration command for PID */
	snprintf(top_cmd_calibrate, sizeof(top_cmd_calibrate), "/usr/bin/top -b -n 1 -p %i | grep %%CPU", pid);

	fp = popen(top_cmd_calibrate, "r");
	if (fp == NULL) {
		OS_printf("Failed to run command top\n" );
		//exit(1);
	}

	int util_ndx = -1;
	int count_ndx = 0;
	/* Read the CPU% column header and get it's index in top output */
	if (fgets(output, sizeof(output)-1, fp) != NULL)
	{
		for (char *tok = strtok(output," "); tok != NULL; tok = strtok(NULL, " "))
		{
			if (strcmp(tok, "%CPU") == 0)
			{
				util_ndx = count_ndx;
				break;
			}
			count_ndx++;
		}
	}
	else
	{
		// Calibration failed
		OS_printf("Calibration faild\n");
	}
	pclose(fp);

	return(util_ndx);
}

int EA_GetPidUtil(int pid, int util_ndx)
{
	FILE *fp;
	char output[1024];
	char top_cmd[80];
	int util = -1;
	int TOP_READ_LINE = 1;
	/* Generate top command for PID */
	snprintf(top_cmd, sizeof(top_cmd), "/usr/bin/top -p %i -d 1 -b -n 2 | grep %i", pid, pid);

	fp = popen(top_cmd, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	int output_line = 0;
	int count_ndx = 0;
	/* Read the outputput a line at a time - output it. */
	while (fgets(output, sizeof(output)-1, fp) != NULL) {
		if (output_line == TOP_READ_LINE)
		{
			for (char *tok = strtok(output," "); tok != NULL; tok = strtok(NULL, " "))
			{
				if (count_ndx == util_ndx)
				{
					util = atoi(tok);
				}
				count_ndx++;
			}
		}
		output_line++;
	}

	//OS_printf("Util: %i\n", util);

	/* close */
	pclose(fp);

	return util;
}



/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void EA_Perfmon_Test_AddTestCases(void)
{
	UtTest_Add(Test_EA_PerfmonCustom_Nominal, EA_Test_Setup, EA_Test_TearDown, "Test_EA_PerfmonCustom_Nominal");
	//UtTest_Add(, EA_Test_Setup, EA_Test_TearDown, "");
}

