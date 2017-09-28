#include "mac_cmds_test.h"
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

int32 MAC_Cmds_Test_UT_CFE_SB_SubscribeHook1(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 5;
}


int32 MAC_Cmds_Test_UT_CFE_SB_SubscribeHook2(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 6;
}


void MAC_Function2_Test_Case1(void)
{
/*    int32 Result;

    Variable3 = 3;

    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_SUBSCRIBE_INDEX, &MAC_Cmds_Test_UT_CFE_SB_SubscribeHook1);
*/
    /* Execute the function being tested */
/*    Result = MAC_Function2();*/
    
    /* Verify results */
/*    UtAssert_True (Variable4 == 4, "Variable4 == 4");
    UtAssert_True (Result == 25, "Result == 25");

    UtAssert_True (Ut_CFE_EVS_GetEventQueueDepth() == 0, "Ut_CFE_EVS_GetEventQueueDepth() == 0");
*/
} /* end MAC_Function2_Test_Case1 */


void MAC_Cmds_Test_AddTestCases(void)
{
    UtTest_Add(MAC_Function2_Test_Case1, MAC_Test_Setup, MAC_Test_TearDown, "MAC_Function2_Test_Case1");
} /* end MAC_Cmds_Test_AddTestCases */


