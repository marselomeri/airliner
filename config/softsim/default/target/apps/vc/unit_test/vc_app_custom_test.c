#include "vc_app_custom_test.h"
#include "vc_custom_transmit_test_utils.h"
#include "vc_custom_device_test_utils.h"
#include "vc_platform_stubs.h"
#include <errno.h>
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

void Test_VC_Custom_Ioctl_Error(void)
{
    int32 result = 0;
    int32 expected = -1;
    
    /* Set a return value for the wrapped ioctl */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return = -1;
    
    /* A test argument to pass to VC_Ioctl value is random 
     * the wrapped ioctl will not use the arguments and will return a
     * value */
    int test = 1;
    
    
    result = VC_Ioctl(test, test, &test);

    UtAssert_True(result == expected, "VC_Ioctl did not return an error");
}

void Test_VC_Custom_Ioctl_Interrupted(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint32 i = 0;
    
    /* Set a return value for the wrapped ioctl */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return = -1;
    
    /* Set return error number to true */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno = 1;
    
    /* Set error number to interrupted */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value = EINTR;
    
    /* A test argument to pass to VC_Ioctl value is random 
     * the wrapped ioctl will not use the arguments and will return a
     * value */
    int test = 1;
    
    /* Call VC_Ioctl with errno set to EINTR max retry attempts*/
    result = VC_Ioctl(test, test, &test);
    
    UtAssert_True(result == expected, "VC_Ioctl did not return an error");
}

/**************************************************************************
 * Tests for VC_Init_CustomDevices()
 **************************************************************************/

/**************************************************************************
 * Tests for VC_InitDevice()
 **************************************************************************/

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_VC_Custom_Ioctl_Error, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_Ioctl_Error");
    UtTest_Add(Test_VC_Custom_Ioctl_Interrupted, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_Ioctl_Interrupted");
}
