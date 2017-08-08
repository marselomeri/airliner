
#include "vc_app_test.h"
#include "vc_app.h"
#include "vc_test_utils.h"

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


int32 hookCalledCount = 0;

/**************************************************************************
 * Tests for VC_InitEvent()
 **************************************************************************/

/**
 * Test VC_InitEvent() with failed CFE_EVS_Register
 */
void Test_VC_InitEvent_Fail_Register(void)
{
    /* Set a fail result for EVS */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EVENTS_SERVICE | CFE_EVS_NOT_IMPLEMENTED;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitEvent();

    /* Verify results */
    UtAssert_True (result == expected, "InitEvent, failed EVS Register");
}


/**************************************************************************
 * Tests for VC_InitPipe()
 **************************************************************************/
/**
 * Test VC_InitPipe(), fail SCH CFE_SB_CreatePipe
 */
void Test_VC_InitPipe_Fail_CreateSCHPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create SCH pipe");
}


/**
 * Test VC_InitPipe(), fail CFE_SB_SubscribeEx for wakeup
 */
void Test_VC_InitPipe_Fail_SubscribeWakeup(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for wakeup");
}


/**
 * Test VC_InitPipe(), fail CFE_SB_SubscribeEx for sendhk
 */
void Test_VC_InitPipe_Fail_SubscribeSendHK(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 2);

    /* Execute the function being tested */
    result = VC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for sendhk");
}


/**
 * Test VC_InitPipe(), fail CMD CFE_SB_CreatePipe
 */
void Test_VC_InitPipe_Fail_CreateCMDPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 2);

    /* Execute the function being tested */
    result = VC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create CMD pipe");
}


/**
 * Test VC_InitPipe(), fail CFE_SB_Subscribe for CMD msg
 */
void Test_VC_InitPipe_Fail_SubscribeCMD(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_Subscribe for CMD");
}


/**************************************************************************
 * Tests for VC_InitData()
 **************************************************************************/
/**
 * Test VC_InitData()
 */
void Test_VC_InitData(void)
{
    /* Set a fail result */
    int32 result = -1;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = VC_InitData();

    /* Verify results */
    UtAssert_True (result == expected, "InitData");
}


/**************************************************************************
 * Tests for VC_InitApp()
 **************************************************************************/
/**
 * Test VC_InitApp(), fail init event
 */
void Test_VC_InitApp_Fail_InitEvent(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init event");
}


/**
 * Test VC_InitApp(), fail init pipe
 */
void Test_VC_InitApp_Fail_InitPipe(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init pipe");
}


/**
 * Test VC_InitApp(), fail init data.
 * NOTE: no current way to fail VC_InitData() in default
 */
void Test_VC_InitApp_Fail_InitData(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init data");
}


/* TODO */
/**
 * Test VC_InitApp(), fail init transmit.
 */
void Test_VC_InitApp_Fail_InitTransmit(void)
{
    //int32 result = CFE_SUCCESS;
    //int32 expected = CFE_TBL_ERR_INVALID_NAME;

    //Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init transmit");
}


/* TODO */
/**
 * Test VC_InitApp(), fail init devices
 */
void Test_VC_InitApp_Fail_InitDevices(void)
{
    //int32 result = CFE_SUCCESS;
    //int32 expected = CFE_ES_CDS_INVALID_NAME;

    //Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERCDS_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init devices");
}


/**
 * Test VC_InitApp(), fail OS_TaskInstallDeleteHandler.
 */
void Test_VC_InitApp_FailTaskInstallDeleteHandler(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_ES_BAD_ARGUMENT;

    Ut_OSAPI_SetReturnCode(UT_OSAPI_TASKINSTALLDELETEHANDLER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail OS_TaskInstallDeleteHandler");
}


/**
 * Test VC_InitApp(), Nominal
 */
void Test_VC_InitApp_Nominal(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EXECUTIVE_SERVICE | CFE_ES_ERR_APP_REGISTER;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = VC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, nominal");
}


/**************************************************************************
 * Tests for VC_CleanupCallback()
 **************************************************************************/
/**
 * Test VC_CleanupCallback()
 * NOTE: empty function, so nothing to assert
 */
void Test_VC_CleanupCallback(void)
{
    /* Execute the function being tested */
    VC_CleanupCallback();
}


/**************************************************************************
 * Tests for VC_AppMain()
 **************************************************************************/
/**
 * Test VC_AppMain(), Fail RegisterApp
 */
void Test_VC_AppMain_Fail_RegisterApp(void)
{
    /* fail the register app */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERAPP_INDEX, CFE_ES_ERR_APP_REGISTER, 1);

    /* Execute the function being tested */
    VC_AppMain();
}


/**
 * Test VC_AppMain(), Fail InitApp
 */
void Test_VC_AppMain_Fail_InitApp(void)
{
    /* fail the register app */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_APP_NOT_REGISTERED, 1);

    /* Execute the function being tested */
    VC_AppMain();
}


/**
 * Test VC_AppMain(), Invalid Schedule Message
 */
void Test_VC_AppMain_InvalidSchMessage(void)
{
    /* The following will emulate behavior of receiving a SCH message to send HK */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, 0, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

}

/* TODO */
/**
 * Hook to support: VC_AppMain(), Nominal - SendHK
 */
int32 Test_VC_AppMain_Nominal_SendHK_SendMsgHook(CFE_SB_Msg_t *MsgPtr)
{
    /* TODO:  Test the contents of your HK message here. */

    hookCalledCount++;

    return CFE_SUCCESS;
}


/**
 * Test VC_AppMain(), Nominal - SendHK
 */
void Test_VC_AppMain_Nominal_SendHK(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, VC_SEND_HK_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Used to verify HK was transmitted correctly. */
    hookCalledCount = 0;
    Ut_CFE_ES_SetFunctionHook(UT_CFE_SB_SENDMSG_INDEX, &Test_VC_AppMain_Nominal_SendHK_SendMsgHook);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True (hookCalledCount == 1, "AppMain_Nominal_SendHK");

}


/**
 * Test VC_AppMain(), Nominal - Wakeup
 */
void Test_VC_AppMain_Nominal_Wakeup(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, VC_WAKEUP_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

}


/**
 * Test VC_AppMain(), ProcessNewData - InvalidMsgID
 */
void Test_VC_AppMain_ProcessNewData_InvalidMsgID(void)
{
    VC_InData_t  InMsg;
    int32 DataPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it data to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_DATA_PIPE");
    CFE_SB_InitMsg (&InMsg, 0x0000, sizeof(VC_InData_t), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InMsg, DataPipe);

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, VC_WAKEUP_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==3,"Event Count = 3");
    UtAssert_EventSent(VC_MSGID_ERR_EID, CFE_EVS_ERROR, "", "Error Event Sent");
}


/**
 * Test VC_ProcessNewAppCmds(), Invalid Command Code
 */
void Test_VC_ProcessNewAppCmds_InvalidCommand(void)
{
    VC_NoArgCmd_t InSchMsg;
    VC_NoArgCmd_t InInvalidCmd;
    int32         DataPipe;
    int32         CmdPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it a command to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_SCH_PIPE");
    CFE_SB_InitMsg (&InSchMsg, VC_SEND_TLM_MID, sizeof(InSchMsg), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InSchMsg, DataPipe);

    CmdPipe = Ut_CFE_SB_CreatePipe("VC_CMD_PIPE");
    CFE_SB_InitMsg ((CFE_SB_MsgPtr_t)&InInvalidCmd, VC_CMD_MID, sizeof(InInvalidCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InInvalidCmd, 100);
    Ut_CFE_SB_AddMsgToPipe(&InInvalidCmd, CmdPipe);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_MSGID_ERR_EID, CFE_EVS_ERROR, "", "Cmd with Invalid Cmd Code Sent");
}


/**
 * Test VC_ProcessNewAppCmds(), NOOP command, Invalid Size
 */
void Test_VC_ProcessNewAppCmds_Noop_InvalidSize(void)
{
    VC_NoArgCmd_t InSchMsg;
    VC_AddMessageFlowCmd_t InNoopCmd;
    int32         DataPipe;
    int32         CmdPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it a command to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_SCH_PIPE");
    CFE_SB_InitMsg (&InSchMsg, VC_SEND_TLM_MID, sizeof(InSchMsg), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InSchMsg, DataPipe);

    CmdPipe = Ut_CFE_SB_CreatePipe("VC_CMD_PIPE");
    CFE_SB_InitMsg (&InNoopCmd, VC_CMD_MID, sizeof(InNoopCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InNoopCmd, VC_NOOP_CC);
    Ut_CFE_SB_AddMsgToPipe(&InNoopCmd, CmdPipe);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_MSGLEN_ERR_EID, CFE_EVS_ERROR, "", "NOOP Cmd Event Sent");
}


/**
 * Test VC_ProcessNewAppCmds(), NOOP command, Nominal
 */
void Test_VC_ProcessNewAppCmds_Noop_Nominal(void)
{
    VC_NoArgCmd_t InSchMsg;
    VC_NoArgCmd_t InNoopCmd;
    int32         DataPipe;
    int32         CmdPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it a command to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_SCH_PIPE");
    CFE_SB_InitMsg (&InSchMsg, VC_SEND_TLM_MID, sizeof(InSchMsg), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InSchMsg, DataPipe);

    CmdPipe = Ut_CFE_SB_CreatePipe("VC_CMD_PIPE");
    CFE_SB_InitMsg (&InNoopCmd, VC_CMD_MID, sizeof(InNoopCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InNoopCmd, VC_NOOP_CC);
    Ut_CFE_SB_AddMsgToPipe(&InNoopCmd, CmdPipe);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_CMD_NOOP_EID, CFE_EVS_INFORMATION, "", "NOOP Cmd Event Sent");
}


/**
 * Test VC_ProcessNewAppCmds(), Reset command, Nominal
 */
void Test_VC_ProcessNewAppCmds_Reset_Nominal(void)
{
    VC_NoArgCmd_t InSchMsg;
    VC_NoArgCmd_t InResetCmd;
    int32         DataPipe;
    int32         CmdPipe;
    uint32        i = 0;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it a command to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_SCH_PIPE");
    CFE_SB_InitMsg (&InSchMsg, VC_SEND_TLM_MID, sizeof(InSchMsg), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InSchMsg, DataPipe);

    CmdPipe = Ut_CFE_SB_CreatePipe("VC_CMD_PIPE");
    CFE_SB_InitMsg (&InResetCmd, VC_CMD_MID, sizeof(InResetCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InResetCmd, VC_RESET_CC);
    Ut_CFE_SB_AddMsgToPipe(&InResetCmd, CmdPipe);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Now give all the counters we're going to clear a value to ensure that
     * the reset command actually clears them.
     */
    VC_AppData.HkTlm.usCmdCnt = 1;
    VC_AppData.HkTlm.usCmdErrCnt = 2;

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_CMD_RESET_EID, CFE_EVS_INFORMATION, "", "RESET Cmd Event Sent");

    UtAssert_True(VC_AppData.HkTlm.usCmdCnt == 0, "VC_AppData.HkTlm.usCmdCnt == 0");
    UtAssert_True(VC_AppData.HkTlm.usCmdErrCnt == 0, "VC_AppData.HkTlm.usCmdErrCnt == 0");
}

/* TODO */
/**
 * Test VC_ProcessNewAppCmds(), StartStreaming command, Invalid Size
 */
void Test_VC_ProcessNewAppCmds_StartStreaming_InvalidSize(void)
{

}

/* TODO */
/**
 * Test VC_ProcessNewAppCmds(), StartStreaming command, Invalid Address
 */
void Test_VC_ProcessNewAppCmds_StartStreaming_InvalidAddress(void)
{

}

/* TODO */
/**
 * Test VC_ProcessNewAppCmds(), StartStreaming command, Invalid (Null Address
 */
void Test_VC_ProcessNewAppCmds_StartStreaming_InvalidNullAddress(void)
{

}

/* TODO */
/**
 * Test VC_ProcessNewAppCmds(), Start Streaming command, Nominal
 */
void Test_VC_ProcessNewAppCmds_StartStreaming_Nominal(void)
{

}

/**
 * Test VC_ProcessNewAppCmds(), StopStreaming command, Invalid Size
 */
void Test_VC_ProcessNewAppCmds_StopStreaming_InvalidSize(void)
{
    VC_NoArgCmd_t InSchMsg;
    VC_AddMessageFlowCmd_t InStopStreamingCmd;
    int32         DataPipe;
    int32         CmdPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it a command to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("VC_SCH_PIPE");
    CFE_SB_InitMsg (&InSchMsg, VC_SEND_TLM_MID, sizeof(InSchMsg), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InSchMsg, DataPipe);

    CmdPipe = Ut_CFE_SB_CreatePipe("VC_CMD_PIPE");
    CFE_SB_InitMsg (&InStopStreamingCmd, VC_CMD_MID, sizeof(InStopStreamingCmd), TRUE);
    CFE_SB_SetCmdCode((CFE_SB_MsgPtr_t)&InStopStreamingCmd, VC_STARTSTREAMING_CC);
    Ut_CFE_SB_AddMsgToPipe(&InStopStreamingCmd, CmdPipe);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    VC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_MSGLEN_ERR_EID, CFE_EVS_ERROR, "", "StartStreaming Cmd Event Sent");
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_VC_InitEvent_Fail_Register, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitEvent_Fail_Register");
    UtTest_Add(Test_VC_InitPipe_Fail_CreateSCHPipe, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitPipe_Fail_CreateSCHPipe");
    UtTest_Add(Test_VC_InitPipe_Fail_SubscribeWakeup, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitPipe_Fail_SubscribeWakeup");
    UtTest_Add(Test_VC_InitPipe_Fail_SubscribeSendHK, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitPipe_Fail_SubscribeSendHK");
    UtTest_Add(Test_VC_InitPipe_Fail_CreateCMDPipe, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitPipe_Fail_CreateCMDPipe");
    UtTest_Add(Test_VC_InitPipe_Fail_SubscribeCMD, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitPipe_Fail_SubscribeCMD");
    UtTest_Add(Test_VC_InitData, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitData");
    UtTest_Add(Test_VC_InitApp_Fail_InitEvent, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Fail_InitEvent");
    UtTest_Add(Test_VC_InitApp_Fail_InitPipe, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Fail_InitPipe");
    UtTest_Add(Test_VC_InitApp_Fail_InitData, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Fail_InitData");
    UtTest_Add(Test_VC_InitApp_Fail_InitTransmit, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Fail_InitTransmit");
    UtTest_Add(Test_VC_InitApp_Fail_InitDevices, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Fail_InitDevices");
    UtTest_Add(Test_VC_InitApp_FailTaskInstallDeleteHandler, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_FailTaskInstallDeleteHandler");               
    UtTest_Add(Test_VC_InitApp_Nominal, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_InitApp_Nominal");
    UtTest_Add(Test_VC_CleanupCallback, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_CleanupCallback");
    UtTest_Add(Test_VC_AppMain_Fail_RegisterApp, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_Fail_RegisterApp");
    UtTest_Add(Test_VC_AppMain_Fail_InitApp, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_Fail_InitApp");
    UtTest_Add(Test_VC_AppMain_InvalidSchMessage, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_InvalidSchMessage");
    UtTest_Add(Test_VC_AppMain_Nominal_SendHK, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_Nominal_SendHK");
    UtTest_Add(Test_VC_AppMain_Nominal_Wakeup, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_Nominal_Wakeup");
    UtTest_Add(Test_VC_AppMain_ProcessNewData_InvalidMsgID, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_AppMain_ProcessNewData_InvalidMsgID");
    UtTest_Add(Test_VC_ProcessNewAppCmds_InvalidCommand, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_InvalidCommand"); 
    UtTest_Add(Test_VC_ProcessNewAppCmds_Noop_InvalidSize, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_Noop_InvalidSize");  
    UtTest_Add(Test_VC_ProcessNewAppCmds_Noop_Nominal, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_Noop_Nominal");                 
    UtTest_Add(Test_VC_ProcessNewAppCmds_Reset_Nominal, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_Reset_Nominal");   
    UtTest_Add(Test_VC_ProcessNewAppCmds_StartStreaming_InvalidSize, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_StartStreaming_InvalidSize");             
    UtTest_Add(Test_VC_ProcessNewAppCmds_StartStreaming_InvalidAddress, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_StartStreaming_InvalidAddress");            
    UtTest_Add(Test_VC_ProcessNewAppCmds_StartStreaming_InvalidNullAddress, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_StartStreaming_InvalidNullAddress");            
    UtTest_Add(Test_VC_ProcessNewAppCmds_StartStreaming_Nominal, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_StartStreaming_Nominal");           
    UtTest_Add(Test_VC_ProcessNewAppCmds_StopStreaming_InvalidSize, VC_Test_Setup, VC_Test_TearDown,
               "Test_VC_ProcessNewAppCmds_StopStreaming_InvalidSize");
}


