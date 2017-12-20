
#include "params_cmds_test.h"
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

int32 PARAMS_Cmds_Test_UT_CFE_SB_SubscribeHook1(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 5;
}


int32 PARAMS_Cmds_Test_UT_CFE_SB_SubscribeHook2(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 6;
}


void PARAMS_Function2_Test_Case1(void)
{
/*    int32 Result;

    PARAMS_AppData.Variable3 = 3;

    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_SUBSCRIBE_INDEX, &PARAMS_Cmds_Test_UT_CFE_SB_SubscribeHook1);
*/
    /* Execute the function being tested */
/*    Result = PARAMS_Function2();*/
    
    /* Verify results */
/*    UtAssert_True (PARAMS_AppData.Variable4 == 4, "PARAMS_AppData.Variable4 == 4");
    UtAssert_True (Result == 25, "Result == 25");

    UtAssert_True (Ut_CFE_EVS_GetEventQueueDepth() == 0, "Ut_CFE_EVS_GetEventQueueDepth() == 0");
*/
} /* end PARAMS_Function2_Test_Case1 */


void PARAMS_Cmds_Test_AddTestCases(void)
{
    UtTest_Add(PARAMS_Function2_Test_Case1, PARAMS_Test_Setup, PARAMS_Test_TearDown, "PARAMS_Function2_Test_Case1");
} /* end PARAMS_Cmds_Test_AddTestCases */


