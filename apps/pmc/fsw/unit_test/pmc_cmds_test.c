
#include "pmc_cmds_test.h"
#include "pmc_test_utils.h"

#include "pmc_msg.h"

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

int32 PMC_Cmds_Test_UT_CFE_SB_SubscribeHook1(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 5;
}


int32 PMC_Cmds_Test_UT_CFE_SB_SubscribeHook2(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 6;
}


void PMC_Function2_Test_Case1(void)
{
/*    int32 Result;

    PMC_AppData.Variable3 = 3;

    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_SUBSCRIBE_INDEX, &PMC_Cmds_Test_UT_CFE_SB_SubscribeHook1);
*/
    /* Execute the function being tested */
/*    Result = PMC_Function2();*/
    
    /* Verify results */
/*    UtAssert_True (PMC_AppData.Variable4 == 4, "PMC_AppData.Variable4 == 4");
    UtAssert_True (Result == 25, "Result == 25");

    UtAssert_True (Ut_CFE_EVS_GetEventQueueDepth() == 0, "Ut_CFE_EVS_GetEventQueueDepth() == 0");
*/
} /* end PMC_Function2_Test_Case1 */


void PMC_Cmds_Test_AddTestCases(void)
{
    UtTest_Add(PMC_Function2_Test_Case1, PMC_Test_Setup, PMC_Test_TearDown, "PMC_Function2_Test_Case1");
} /* end PMC_Cmds_Test_AddTestCases */


