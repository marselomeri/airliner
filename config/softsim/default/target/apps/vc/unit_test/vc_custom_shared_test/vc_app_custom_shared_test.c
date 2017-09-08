#include "vc_app_custom_shared_test.h"
#include "vc_custom_shared_test_utils.h"
#include "vc_platform_cfg.h"
#include <errno.h>
#include <stdio.h>
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

/**
 * Test VC_ProcessNewCustomCmds(), - InvalidMsgID
 */
void Test_VC_Custom_ProcessNewCustomCmds_InvalidMsgID(void)
{
    VC_StartStreamCmd_t InMsg;

    CFE_SB_InitMsg (&InMsg, 0x0000, sizeof(VC_StartStreamCmd_t), TRUE);
    
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InMsg, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);

    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InMsg);

    /* Verify results */
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt == 1,"CmdErrCnt not incremented");
    UtAssert_EventSent(VC_MSGID_ERR_EID, CFE_EVS_ERROR, "", 
            "VC_ProcessNewCustomCmds() failed to raise an event");
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_Custom_App_Shared_Test_AddTestCases(void)
{
/**************************************************************************
 * Tests for Custom Shared Layer
 **************************************************************************/
    UtTest_Add(Test_VC_Custom_ProcessNewCustomCmds_InvalidMsgID, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_Custom_ProcessNewCustomCmds_InvalidMsgID");

}
