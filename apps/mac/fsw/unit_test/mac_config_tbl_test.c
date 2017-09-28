#include "mac_config_tbl_test.h"
#include "mac_test_utils.h"

#include "mac_msg.h"

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


void MAC_Config_Tbl_Test_Case1(void)
{

}


void MAC_Config_Tbl_Test_AddTestCases(void)
{
    UtTest_Add(MAC_Config_Tbl_Test_Case1, MAC_Test_Setup, MAC_Test_TearDown, "MAC_Config_Tbl_Test_Case1");
}


