#include "vc_app_custom_shared_test.h"
#include "vc_custom_shared_test_utils.h"
#include "vc_platform_cfg.h"
#include "vc_transmit_udp.h"
#include "vc_msgids.h"
#include "vc_platform_stubs.h"

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
 * Test VC_ProcessNewCustomCmds() - InvalidMsgID
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


/**
 * Test VC_ProcessNewCustomCmds() - Invalid Command Code
 */
void Test_VC_Custom_ProcessNewCustomCmds_InvalidCommand(void)
{
    /* Create an invalid command code */
    uint8 InvalidCommandCode = 100;
    
    VC_StartStreamCmd_t InMsg;
    
    CFE_SB_InitMsg (&InMsg, VC_STARTSTREAMING_CC, sizeof(VC_StartStreamCmd_t), TRUE);
    
    /* Set invalid command code */
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InMsg, InvalidCommandCode);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InMsg);

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");
    UtAssert_EventSent(VC_MSGID_ERR_EID, CFE_EVS_ERROR, "", 
            "Cmd with Invalid Cmd Code Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, Invalid Size
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidSize(void)
{
    /* Command with the wrong type (size) */
    VC_NoArgCmd_t InMsg;
    
    CFE_SB_InitMsg (&InMsg, VC_CMD_MID, sizeof(InMsg), TRUE);
    
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InMsg, VC_STARTSTREAMING_CC);

    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InMsg);

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");
    UtAssert_EventSent(VC_MSGLEN_ERR_EID, CFE_EVS_ERROR, "", 
            "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, Invalid State
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidState(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;

    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);

    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to streaming */
    VC_AppData.AppState = VC_STREAMING;
    
    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");
    UtAssert_EventSent(VC_CMD_ERR_EID, CFE_EVS_ERROR, "VC is already streaming", "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, Invalid (Null) Address
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidNullAddress(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;
    
    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");
    UtAssert_EventSent(VC_ADDR_NUL_ERR_EID, CFE_EVS_ERROR, 
            "NUL (empty) string specified for address", "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, Invalid Address
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidAddress(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;
    
    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    /* Start streaming needs an address to pass null check */
    strcpy(InStartStreamingCmd.Address, "NOT_NULL");

    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");
    UtAssert_EventSent(VC_ADDR_ERR_EID, CFE_EVS_ERROR, 
            "Invalid string specified for address", "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, destination
 * update failure
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_UpdateDestinationFail(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;

    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    /* Start streaming needs an address to pass null check */
    strcpy(InStartStreamingCmd.Address, "1.1.1.1");

    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");    
    UtAssert_EventSent(VC_INIT_ERR_EID, CFE_EVS_ERROR, "Destination update failed", "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, transmit
 * uninit failure
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitUninitFail(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;

    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    /* Start streaming needs an address to pass null check */
    strcpy(InStartStreamingCmd.Address, "1.1.1.1");
    
    /* Set a channel to enabled to pass VC_Update_Destination */
    VC_AppCustomData.Channel[0].Mode = VC_CHANNEL_ENABLED;
    
    /* Set close to fail */
    VC_Platform_Stubs_Returns.VC_Wrap_Close_Return = -1;

    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==4,"Event Count = 4");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");    
    UtAssert_EventSent(VC_UNINIT_ERR_EID, CFE_EVS_ERROR, "", "Start Streaming Cmd Event Sent");
}


/**
 * Test VC_ProcessNewCustomCmds(), StartStreaming command, transmit
 * init failure
 */
void Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitInitFail(void)
{
    VC_StartStreamCmd_t InStartStreamingCmd;

    CFE_SB_InitMsg (&InStartStreamingCmd, VC_CMD_MID, sizeof(InStartStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStartStreamingCmd, VC_STARTSTREAMING_CC);
    
    /* Set get command code function hook */
    Ut_CFE_SB_SetFunctionHook(UT_CFE_SB_GETCMDCODE_INDEX, &Ut_CFE_SB_GetCmdCodeHook);
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    /* Start streaming needs an address to pass null check */
    strcpy(InStartStreamingCmd.Address, "1.1.1.1");
    
    /* Set a channel to enabled to pass VC_Update_Destination */
    VC_AppCustomData.Channel[0].Mode = VC_CHANNEL_ENABLED;
    
    /* Set open to fail */
    VC_Platform_Stubs_Returns.VC_Wrap_Open_Return = -1;

    /* Call the function under test */
    VC_ProcessNewCustomCmds(&InStartStreamingCmd);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==4,"Event Count = 4");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt = 1,"Command error counter != 1");    
    UtAssert_EventSent(VC_INIT_ERR_EID, CFE_EVS_ERROR, 
            "VC_Transmit_Init failed in cmd start streaming", "Transmit init failure did not raise event");
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
    UtTest_Add(Test_VC_Custom_ProcessNewCustomCmds_InvalidCommand, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_Custom_ProcessNewCustomCmds_InvalidCommand");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidSize, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidSize");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidState, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidState");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidNullAddress, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidNullAddress");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidAddress, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_InvalidAddress");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_UpdateDestinationFail, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_UpdateDestinationFail");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitUninitFail, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitUninitFail");
    UtTest_Add(Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitInitFail, 
            VC_Custom_Shared_Test_Setup, VC_Custom_Shared_Test_TearDown,
            "Test_VC_ProcessNewCustomCmds_StartStreaming_TransmitInitFail");

}
