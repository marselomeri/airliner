
#include "params_config_tbl_test.h"
#include "params_test_utils.h"

#include "params_msg.h"

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


void PARAMS_Config_Tbl_Test_Case1(void)
{

}


void PARAMS_Config_Tbl_Test_AddTestCases(void)
{
    UtTest_Add(PARAMS_Config_Tbl_Test_Case1, PARAMS_Test_Setup, PARAMS_Test_TearDown, "PARAMS_Config_Tbl_Test_Case1");
}


