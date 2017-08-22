

#include "to_app_custom_test.h"

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
 * Tests for TO_Custom_Init()
 **************************************************************************/
/**
 * Test TO_Custom_Init()
 */
 
/**************************************************************************
 * Tests for TO_OutputChannel_CustomBuildupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomBuildupAll() nominal
 * NOTE: Function is not currently implemented.
 */
void Test_TO_OutputChannel_CustomBuildupAll_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint32 index = 0;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_CustomBuildupAll(index);
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_OutputChannel_CustomBuildupAll() failed nominal");
}

/**************************************************************************
 * Tests for TO_OutputChannel_Enable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Enable()
 */
 
/**************************************************************************
 * Tests for TO_OutputChannel_Send()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Send()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_ChannelHandler()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ChannelHandler()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_ProcessNewCustomCmds()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ProcessNewCustomCmds()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_OnboardChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_OnboardChannelTask()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_GroundChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_GroundChannelTask()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_CustomTeardownAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomTeardownAll()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_CustomCleanupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomCleanupAll()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_Disable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Disable()
 */

void TO_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_TO_OutputChannel_CustomBuildupAll_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_CustomBuildupAll_Nominal");
        
}
