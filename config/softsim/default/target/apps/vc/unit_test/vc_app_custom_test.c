#include "vc_app_custom_test.h"
#include "vc_custom_transmit_test_utils.h"
#include "vc_custom_device_test_utils.h"
//#include "vc_msgids.h"
#include <string.h>

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

/**************************************************************************
 * Tests for VC_Ioctl()
 **************************************************************************/

void Test_VC_Custom_Test_True(void)
{
    int testing = 1;
    VC_Ioctl(testing, testing, &testing);
    UtAssert_True(TRUE == TRUE, "True != True");
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_VC_Custom_Test_True, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_Test_True");
    UtTest_Add(Test_VC_Custom_Test_True, VC_Custom_Transmit_Test_Setup, 
            VC_Custom_Transmit_Test_TearDown, "Test_VC_Custom_Test_True");
}
