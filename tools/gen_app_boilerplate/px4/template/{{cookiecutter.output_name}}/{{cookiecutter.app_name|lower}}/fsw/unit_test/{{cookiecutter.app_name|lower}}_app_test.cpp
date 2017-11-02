/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#include "cfe.h"
#include "{{cookiecutter.app_name|lower}}_app.h"
#include "{{cookiecutter.app_name|lower}}_test_utils.h"
#include "{{cookiecutter.app_name|lower}}_app_test.h"
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
 * Tests for {{cookiecutter.app_name}}_InitEvent()
 **************************************************************************/

/**
 * Test {{cookiecutter.app_name}}_InitEvent() with failed CFE_EVS_Register
 */
void Test_{{cookiecutter.app_name}}_InitEvent_Fail_Register(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for EVS */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EVENTS_SERVICE | CFE_EVS_NOT_IMPLEMENTED;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitEvent();

    /* Verify results */
    UtAssert_True (result == expected, "InitEvent, failed EVS Register");
}


/**************************************************************************
 * Tests for {{cookiecutter.app_name}}_InitPipe()
 **************************************************************************/
/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail SCH CFE_SB_CreatePipe
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateSCHPipe(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create SCH pipe");
}


/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail CFE_SB_SubscribeEx for wakeup
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeWakeup(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for wakeup");
}


/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail CFE_SB_SubscribeEx for sendhk
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeSendHK(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 2);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for sendhk");
}


/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail CMD CFE_SB_CreatePipe
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateCMDPipe(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 2);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create CMD pipe");
}


/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail CFE_SB_Subscribe for CMD msg
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeCMD(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_Subscribe for CMD");
}


/**
 * Test {{cookiecutter.app_name}}_InitPipe(), fail DATA CFE_SB_CreatePipe
 */
void Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateDATAPipe(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 2);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create DATA pipe");
}


/**************************************************************************
 * Tests for {{cookiecutter.app_name}}_InitData()
 **************************************************************************/
/**
 * Test {{cookiecutter.app_name}}_InitData()
 */
void Test_{{cookiecutter.app_name}}_InitData(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result */
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.InitData();

    /* Verify results */
    //UtAssert_True (result == expected, "InitData");
}


/**************************************************************************
 * Tests for {{cookiecutter.app_name}}_InitApp()
 **************************************************************************/
/**
 * Test {{cookiecutter.app_name}}_InitApp(), fail init event
 */
void Test_{{cookiecutter.app_name}}_InitApp_Fail_InitEvent(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    int32 result = CFE_SUCCESS;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init event");
}


/**
 * Test {{cookiecutter.app_name}}_InitApp(), fail init pipe
 */
void Test_{{cookiecutter.app_name}}_InitApp_Fail_InitPipe(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init pipe");
}


/**
 * Test {{cookiecutter.app_name}}_InitApp(), fail init data.
 * NOTE: no current way to fail {{cookiecutter.app_name}}_InitData() in default
 */
void Test_{{cookiecutter.app_name}}_InitApp_Fail_InitData(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init data");
}


/**
 * Test {{cookiecutter.app_name}}_InitApp(), fail init config table
 */
void Test_{{cookiecutter.app_name}}_InitApp_Fail_InitConfigTbl(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    int32 result = CFE_SUCCESS;
    int32 expected = CFE_TBL_ERR_INVALID_NAME;

    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init config table");
}


/**
 * Test {{cookiecutter.app_name}}_InitApp(), Nominal
 */
void Test_{{cookiecutter.app_name}}_InitApp_Nominal(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EXECUTIVE_SERVICE | CFE_ES_ERR_APP_REGISTER;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = o{{cookiecutter.app_name}}.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, nominal");
}

/**************************************************************************
 * Tests for {{cookiecutter.app_name}}_AppMain()
 **************************************************************************/
/**
 * Test {{cookiecutter.app_name}}_AppMain(), Fail RegisterApp
 */
void Test_{{cookiecutter.app_name}}_AppMain_Fail_RegisterApp(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* fail the register app */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERAPP_INDEX, CFE_ES_ERR_APP_REGISTER, 1);

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.AppMain();
}


/**
 * Test {{cookiecutter.app_name}}_AppMain(), Fail InitApp
 */
void Test_{{cookiecutter.app_name}}_AppMain_Fail_InitApp(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* fail the register app */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_APP_NOT_REGISTERED, 1);

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.AppMain();
}


/**
 * Test {{cookiecutter.app_name}}_AppMain(), Fail AcquireConfigPtrs
 */
void Test_{{cookiecutter.app_name}}_AppMain_Fail_AcquireConfigPtrs(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* fail the register app */
    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_GETADDRESS_INDEX, CFE_TBL_ERR_INVALID_HANDLE, 2);

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.AppMain();
}


/**
 * Test {{cookiecutter.app_name}}_AppMain(), Invalid Schedule Message
 */
void Test_{{cookiecutter.app_name}}_AppMain_InvalidSchMessage(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* The following will emulate behavior of receiving a SCH message to send HK */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, 0, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.AppMain();

}


/**
 * Hook to support: {{cookiecutter.app_name}}_AppMain(), Nominal - SendHK
 */
int32 Test_{{cookiecutter.app_name}}_AppMain_Nominal_SendHK_SendMsgHook(CFE_SB_Msg_t *MsgPtr)
{
    /* TODO:  Test the contents of your HK message here. */

    hookCalledCount++;

    return CFE_SUCCESS;
}

/**
 * Test {{cookiecutter.app_name}}_AppMain(), Nominal - SendHK
 */
void Test_{{cookiecutter.app_name}}_AppMain_Nominal_SendHK(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, {{cookiecutter.app_name}}_SEND_HK_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Used to verify HK was transmitted correctly. */
    hookCalledCount = 0;
    Ut_CFE_ES_SetFunctionHook(UT_CFE_SB_SENDMSG_INDEX, (void*)&Test_{{cookiecutter.app_name}}_AppMain_Nominal_SendHK_SendMsgHook);

    /* Execute the function being tested */
    o{{cookiecutter.app_name}}.AppMain();

    /* Verify results */
    UtAssert_True (hookCalledCount == 1, "AppMain_Nominal_SendHK");

}


/**
 * Test {{cookiecutter.app_name}}_AppMain(), Nominal - Wakeup
 */
void Test_{{cookiecutter.app_name}}_AppMain_Nominal_Wakeup(void)
{
    {{cookiecutter.app_name}} o{{cookiecutter.app_name}};

    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, {{cookiecutter.app_name}}_UPDATE_MOTORS_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    //o{{cookiecutter.app_name}}.AppMain();

}



/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void {{cookiecutter.app_name}}_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitEvent_Fail_Register, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitEvent_Fail_Register");

    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateSCHPipe, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateSCHPipe");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeWakeup, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeWakeup");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeSendHK, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeSendHK");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateCMDPipe, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateCMDPipe");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeCMD, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_SubscribeCMD");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateDATAPipe, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitPipe_Fail_CreateDATAPipe");

    UtTest_Add(Test_{{cookiecutter.app_name}}_InitData, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitData");

    UtTest_Add(Test_{{cookiecutter.app_name}}_InitApp_Fail_InitEvent, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitApp_Fail_InitEvent");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitApp_Fail_InitPipe, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitApp_Fail_InitPipe");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitApp_Fail_InitData, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitApp_Fail_InitData");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitApp_Fail_InitConfigTbl, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitApp_Fail_InitConfigTbl");
    UtTest_Add(Test_{{cookiecutter.app_name}}_InitApp_Nominal, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_InitApp_Nominal");

    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_Fail_RegisterApp, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_Fail_RegisterApp");
    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_Fail_InitApp, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_Fail_InitApp");
    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_Fail_AcquireConfigPtrs, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_Fail_AcquireConfigPtrs");
    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_InvalidSchMessage, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_InvalidSchMessage");
    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_Nominal_SendHK, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_Nominal_SendHK");
    UtTest_Add(Test_{{cookiecutter.app_name}}_AppMain_Nominal_Wakeup, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown,
               "Test_{{cookiecutter.app_name}}_AppMain_Nominal_Wakeup");

}


