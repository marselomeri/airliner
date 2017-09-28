#include "mac_app_test.h"
#include "mac_app.h"
#include "mac_test_utils.h"

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
 * Tests for MAC_InitEvent()
 **************************************************************************/

/**
 * Test MAC_InitEvent() with failed CFE_EVS_Register
 */
void Test_MAC_InitEvent_Fail_Register(void)
{
    /* Set a fail result for EVS */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EVENTS_SERVICE | CFE_EVS_NOT_IMPLEMENTED;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitEvent();

    /* Verify results */
    UtAssert_True (result == expected, "InitEvent, failed EVS Register");
}


/**************************************************************************
 * Tests for MAC_InitPipe()
 **************************************************************************/
/**
 * Test MAC_InitPipe(), fail SCH CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateSCHPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create SCH pipe");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_SubscribeEx for wakeup
 */
void Test_MAC_InitPipe_Fail_SubscribeWakeup(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for wakeup");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_SubscribeEx for sendhk
 */
void Test_MAC_InitPipe_Fail_SubscribeSendHK(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 2);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for sendhk");
}


/**
 * Test MAC_InitPipe(), fail CMD CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateCMDPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 2);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create CMD pipe");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_Subscribe for CMD msg
 */
void Test_MAC_InitPipe_Fail_SubscribeCMD(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_Subscribe for CMD");
}


/**
 * Test MAC_InitPipe(), fail DATA CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateDATAPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 3);

    /* Execute the function being tested */
    result = MAC_InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create DATA pipe");
}


/**************************************************************************
 * Tests for MAC_InitData()
 **************************************************************************/
/**
 * Test MAC_InitData()
 */
void Test_MAC_InitData(void)
{
    /* Set a fail result */
    int32 result = -1;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = MAC_InitData();

    /* Verify results */
    UtAssert_True (result == expected, "InitData");
}


/**************************************************************************
 * Tests for MAC_InitApp()
 **************************************************************************/
/**
 * Test MAC_InitApp(), fail init event
 */
void Test_MAC_InitApp_Fail_InitEvent(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init event");
}


/**
 * Test MAC_InitApp(), fail init pipe
 */
void Test_MAC_InitApp_Fail_InitPipe(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init pipe");
}


/**
 * Test MAC_InitApp(), fail init data.
 * NOTE: no current way to fail MAC_InitData() in default
 */
void Test_MAC_InitApp_Fail_InitData(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init data");
}


/**
 * Test MAC_InitApp(), fail init config table
 */
void Test_MAC_InitApp_Fail_InitConfigTbl(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_TBL_ERR_INVALID_NAME;

    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init config table");
}


/**
 * Test MAC_InitApp(), fail init CDS table
 */
void Test_MAC_InitApp_Fail_InitCDSTbl(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_ES_CDS_INVALID_NAME;

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERCDS_INDEX, expected, 1);

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init CDS table");
}


/**
 * Test MAC_InitApp(), Nominal
 */
void Test_MAC_InitApp_Nominal(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EXECUTIVE_SERVICE | CFE_ES_ERR_APP_REGISTER;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = MAC_InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, nominal");
}

/**************************************************************************
 * Tests for MAC_AppMain()
 **************************************************************************/
/**
 * Test MAC_AppMain(), Fail RegisterApp
 */
void Test_MAC_AppMain_Fail_RegisterApp(void)
{
    /* fail the register app */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERAPP_INDEX, CFE_ES_ERR_APP_REGISTER, 1);

    /* Execute the function being tested */
    MAC_AppMain();
}


/**
 * Test MAC_AppMain(), Fail InitApp
 */
void Test_MAC_AppMain_Fail_InitApp(void)
{
    /* fail the register app */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_APP_NOT_REGISTERED, 1);

    /* Execute the function being tested */
    MAC_AppMain();
}


/**
 * Test MAC_AppMain(), Fail AcquireConfigPtrs
 */
void Test_MAC_AppMain_Fail_AcquireConfigPtrs(void)
{
    /* fail the register app */
    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_GETADDRESS_INDEX, CFE_TBL_ERR_INVALID_HANDLE, 2);

    /* Execute the function being tested */
    MAC_AppMain();
}


/**
 * Test MAC_AppMain(), Invalid Schedule Message
 */
void Test_MAC_AppMain_InvalidSchMessage(void)
{
    /* The following will emulate behavior of receiving a SCH message to send HK */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, 0, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    MAC_AppMain();

}


/**
 * Hook to support: MAC_AppMain(), Nominal - SendHK
 */
int32 Test_MAC_AppMain_Nominal_SendHK_SendMsgHook(CFE_SB_Msg_t *MsgPtr)
{
    /* TODO:  Test the contents of your HK message here. */

    hookCalledCount++;

    return CFE_SUCCESS;
}

/**
 * Test MAC_AppMain(), Nominal - SendHK
 */
void Test_MAC_AppMain_Nominal_SendHK(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_SEND_HK_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Used to verify HK was transmitted correctly. */
    hookCalledCount = 0;
    Ut_CFE_ES_SetFunctionHook(UT_CFE_SB_SENDMSG_INDEX, &Test_MAC_AppMain_Nominal_SendHK_SendMsgHook);

    /* Execute the function being tested */
    MAC_AppMain();

    /* Verify results */
    UtAssert_True (hookCalledCount == 1, "AppMain_Nominal_SendHK");

}


/**
 * Test MAC_AppMain(), Nominal - Wakeup
 */
void Test_MAC_AppMain_Nominal_Wakeup(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_WAKEUP_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    MAC_AppMain();

}


/**
 * Test MAC_AppMain(), ProcessNewData - InvalidMsgID
 */
void Test_MAC_AppMain_ProcessNewData_InvalidMsgID(void)
{
    MAC_InData_t  InMsg;
    int32 DataPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it data to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("MAC_DATA_PIPE");
    CFE_SB_InitMsg (&InMsg, 0x0000, sizeof(MAC_InData_t), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InMsg, DataPipe);

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_WAKEUP_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    MAC_AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==3,"Event Count = 3");
    UtAssert_EventSent(MAC_MSGID_ERR_EID, CFE_EVS_ERROR, "", "Error Event Sent");
}



/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void MAC_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_MAC_InitEvent_Fail_Register, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitEvent_Fail_Register");

    UtTest_Add(Test_MAC_InitPipe_Fail_CreateSCHPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateSCHPipe");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeWakeup, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeWakeup");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeSendHK, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeSendHK");
    UtTest_Add(Test_MAC_InitPipe_Fail_CreateCMDPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateCMDPipe");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeCMD, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeCMD");
    UtTest_Add(Test_MAC_InitPipe_Fail_CreateDATAPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateDATAPipe");

    UtTest_Add(Test_MAC_InitData, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitData");

    UtTest_Add(Test_MAC_InitApp_Fail_InitEvent, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitEvent");
    UtTest_Add(Test_MAC_InitApp_Fail_InitPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitPipe");
    UtTest_Add(Test_MAC_InitApp_Fail_InitData, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitData");
    UtTest_Add(Test_MAC_InitApp_Fail_InitConfigTbl, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitConfigTbl");
    UtTest_Add(Test_MAC_InitApp_Fail_InitCDSTbl, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitCDSTbl");
    UtTest_Add(Test_MAC_InitApp_Nominal, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Nominal");

    UtTest_Add(Test_MAC_AppMain_Fail_RegisterApp, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_RegisterApp");
    UtTest_Add(Test_MAC_AppMain_Fail_InitApp, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_InitApp");
    UtTest_Add(Test_MAC_AppMain_Fail_AcquireConfigPtrs, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_AcquireConfigPtrs");
    UtTest_Add(Test_MAC_AppMain_InvalidSchMessage, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_InvalidSchMessage");
    UtTest_Add(Test_MAC_AppMain_Nominal_SendHK, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Nominal_SendHK");
    UtTest_Add(Test_MAC_AppMain_Nominal_Wakeup, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Nominal_Wakeup");
    UtTest_Add(Test_MAC_AppMain_ProcessNewData_InvalidMsgID, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_ProcessNewData_InvalidMsgID");

}


