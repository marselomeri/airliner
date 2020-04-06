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
#include "uttest.h"
#include "utassert.h"
#include "ut_osarte_test_utils.h"
#include "osarte.h"
#include "ut_osarte_platform_stubs.h"
#include "ccsds.h"
#include "common_types.h"
#include "osapi.h"


/**************************************************************************
 * Tests for OS_ArteInitData
 **************************************************************************/
/**
 * Test OS_ArteInitData nominal.
 */
void Test_OSAL_ARTE_InitData_Nominal(void)
{
    /* Call the function under test */
    OS_ArteInitData();
    
    /* Verify results */
    UtAssert_StrCmp(Arte_Handle.ArteIP, OS_ARTE_SERVER_IP, "IP set");
    UtAssert_True(Arte_Handle.ArtePort == OS_ARTE_SERVER_PORT,"Port set");
    UtAssert_True(CCSDS_RD_LEN(Arte_Handle.ready_notification.PriHdr) == 
            sizeof(Arte_Handle.ready_notification), "Ready length set");
    UtAssert_True(CCSDS_RD_SHDR(Arte_Handle.ready_notification.PriHdr) == 
            1, "SecHdrFlag set");
    UtAssert_True(CCSDS_RD_LEN(Arte_Handle.shutdown_notification.PriHdr) == 
            sizeof(Arte_Handle.ready_notification), "Ready length set");
    UtAssert_True(CCSDS_RD_SHDR(Arte_Handle.shutdown_notification.PriHdr) == 
            1, "SecHdrFlag set");
}


/**************************************************************************
 * Tests for OS_ArteInit
 **************************************************************************/
/**
 * Test OS_ArteInit fail socket creation.
 */
void Test_OSAL_ARTE_Init_SocketFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    
    /* Set socket create to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Return = -1;
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Errno = 1;
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Errno_Return = 1;
    
    /* Call the function under test */
    returnCode = OS_ArteInit();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteInit fail setsockopts.
 * Note: test for coverage, failing setsockopt doesn't return failure.
 */
void Test_OSAL_ARTE_Init_SetsockoptFail(void)
{
    int32 returnCode = -1;
    int32 expectedReturn = 0;
    
    /* Set setsockopt to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Setsockopt_Return = -1;
    
    /* Set inet_aton to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_InetAton_Return = 1;
    
    
    /* Call the function under test */
    returnCode = OS_ArteInit();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteInit fail inet_aton.
 */
void Test_OSAL_ARTE_Init_InetAtonFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    
    /* Set inet_aton to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_InetAton_Return = 0;
    
    /* Call the function under test */
    returnCode = OS_ArteInit();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteInit fail connect.
 */
void Test_OSAL_ARTE_Init_ConnectFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    
    /* Set inet_aton to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_InetAton_Return = 1;
    
    /* Set connect to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Connect_Return = -1;
    
    /* Call the function under test */
    returnCode = OS_ArteInit();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteInit Nominal.
 */
void Test_OSAL_ARTE_Init_Nominal(void)
{
    int32 returnCode = -1;
    int32 expectedReturn = 0;
    
    /* Set inet_aton to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_InetAton_Return = 1;
    
    /* Call the function under test */
    returnCode = OS_ArteInit();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**************************************************************************
 * Tests for OS_ArteSendReady
 **************************************************************************/
/**
 * Test OS_ArteSendReady fail send.
 */
void Test_OSAL_ARTE_SendReady_SendFail(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;
    
    /* Set send to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return = -1;
    
    /* Call the function under test */
    returnBool = OS_ArteSendReady();
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/**
 * Test OS_ArteSendReady fail send.
 */
void Test_OSAL_ARTE_SendReady_SendCompleteFail(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;
    
    /* Set send to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return 
            = sizeof(Arte_Handle.ready_notification) - 1;
    
    /* Call the function under test */
    returnBool = OS_ArteSendReady();
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/**
 * Test OS_ArteSendReady Nominal.
 */
void Test_OSAL_ARTE_SendReady_Nominal(void)
{
    boolean returnBool = FALSE;
    boolean expectedReturn = TRUE;
    
    /* Set send to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return = sizeof(Arte_Handle.ready_notification);
    
    /* Call the function under test */
    returnBool = OS_ArteSendReady();
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/**************************************************************************
 * Tests for OS_ArteSendShutdown
 **************************************************************************/
/**
 * Test OS_ArteSendShutdown fail send.
 */
void Test_OSAL_ARTE_SendShutdown_SendFail(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;
    
    /* Set send to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return = -1;
    
    /* Call the function under test */
    returnBool = OS_ArteSendShutdown(TRUE);
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
    UtAssert_True(CCSDS_RD_APID(Arte_Handle.shutdown_notification.PriHdr) 
            == 1,"PriHdr APID set");
}


/**
 * Test OS_ArteSendShutdown fail send.
 */
void Test_OSAL_ARTE_SendShutdown_SendCompleteFail(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;
    
    /* Set send to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return 
            = sizeof(Arte_Handle.shutdown_notification) - 1;
    
    /* Call the function under test */
    returnBool = OS_ArteSendShutdown(FALSE);
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
    UtAssert_True(CCSDS_RD_APID(Arte_Handle.shutdown_notification.PriHdr) 
            == 2,"PriHdr APID set");
}


/**
 * Test OS_ArteSendShutdown Nominal.
 */
void Test_OSAL_ARTE_SendShutdown_Nominal(void)
{
    boolean returnBool = FALSE;
    boolean expectedReturn = TRUE;
    
    /* Set send to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return 
            = sizeof(Arte_Handle.shutdown_notification);
    
    /* Call the function under test */
    returnBool = OS_ArteSendShutdown(TRUE);
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/**************************************************************************
 * Tests for OS_ArteVerifyCommand 
 **************************************************************************/
/**
 * Test OS_ArteVerifyCommand null pointer.
 */
void Test_OSAL_ARTE_VerifyCommand_NullPointer(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;

    /* Call the function under test */
    returnBool = OS_ArteVerifyCommand(0);

    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/* TODO */
/**
 * Test OS_ArteVerifyCommand fail.
 */


/**
 * Test OS_ArteVerifyCommand nominal.
 */


/**************************************************************************
 * Tests for OS_ArteRecvNextStep
 **************************************************************************/
/**
 * Test OS_ArteRecvNextStep recv fail.
 */
void Test_OSAL_ARTE_RecvNextStep_RecvFail(void)
{
    boolean returnBool = TRUE;
    boolean expectedReturn = FALSE;
    
    /* Set recv to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Return = -1;
    
    /* Call the function under test */
    returnBool = OS_ArteRecvNextStep();
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
}


/**
 * Test OS_ArteRecvNextStep recv nominal.
 */
void Test_OSAL_ARTE_RecvNextStep_Nominal(void)
{
    boolean returnBool = FALSE;
    boolean expectedReturn = TRUE;
    
    /* Set recv to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Return = 0;
    
    /* Set the buffer to a CCSDS command packet with a sequence count */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Nominal = 1;
    
    /* Call the function under test */
    returnBool = OS_ArteRecvNextStep();
    
    /* Verify results */
    UtAssert_True(returnBool == expectedReturn,"Return bool expected");
    UtAssert_True(Arte_Handle.SequenceCount == 100,"Sequence count correct");
}


/**************************************************************************
 * Tests for OS_ArteStepNext
 **************************************************************************/
/**
 * Test OS_ArteStepNext null pointer.
 */
void Test_OSAL_ARTE_StepNext_NullPointer(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    
    /* Call the function under test */
    returnCode = OS_ArteStepNext(0,0);
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteStepNext send fail.
 */
void Test_OSAL_ARTE_StepNext_SendFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    uint32 sequence = 0;
    uint32 frame = 0;
    
    /* Set send to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return = -1;
    /* Call the function under test */
    returnCode = OS_ArteStepNext(&sequence, &frame);
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteStepNext recv fail.
 */
void Test_OSAL_ARTE_StepNext_RecvFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    uint32 sequence = 0;
    uint32 frame = 0;
    
    /* Set recv to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Return = -1;
    /* Call the function under test */
    returnCode = OS_ArteStepNext(&sequence, &frame);
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteStepNext nominal.
 */
void Test_OSAL_ARTE_StepNext_Nominal(void)
{
    int32 returnCode = -1;
    int32 expectedReturn = 0;
    uint32 sequence = 0;
    uint32 frame = 0;
    
    /* Set send to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return 
            = sizeof(Arte_Handle.shutdown_notification);
    /* Set recv to pass */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Return = 0;
    
    /* Call the function under test */
    returnCode = OS_ArteStepNext(&sequence, &frame);
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
    UtAssert_True(Arte_Handle.SequenceCount  == 0,"Sequence count expected");
}

/**************************************************************************
 * Tests for OS_ArteCleanup
 **************************************************************************/
/**
 * Test OS_ArteCleanup fail.
 */
void Test_OSAL_ARTE_Cleanup_Fail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = -1;
    
    /* Set close to fail */
    OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Close_Return = -1;
    
    /* Call the function under test */
    returnCode = OS_ArteCleanup();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**
 * Test OS_ArteCleanup nominal.
 */
void Test_OSAL_ARTE_Cleanup_Nominal(void)
{
    int32 returnCode = -1;
    int32 expectedReturn = OS_SUCCESS;

    /* Call the function under test */
    returnCode = OS_ArteCleanup();
    
    /* Verify results */
    UtAssert_True(returnCode == expectedReturn,"Return code expected");
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void Arte_Osal_Test_AddTestCases(void)
{
    UtTest_Add(Test_OSAL_ARTE_InitData_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_InitData_Nominal");
    UtTest_Add(Test_OSAL_ARTE_Init_SocketFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Init_SocketFail");
    UtTest_Add(Test_OSAL_ARTE_Init_SetsockoptFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Init_SetsockoptFail");
    UtTest_Add(Test_OSAL_ARTE_Init_InetAtonFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Init_InetAtonFail");
    UtTest_Add(Test_OSAL_ARTE_Init_ConnectFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Init_ConnectFail");
    UtTest_Add(Test_OSAL_ARTE_Init_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Init_Nominal");
    UtTest_Add(Test_OSAL_ARTE_SendReady_SendCompleteFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_SendReady_SendCompleteFail");
    UtTest_Add(Test_OSAL_ARTE_SendReady_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_SendReady_Nominal");
    UtTest_Add(Test_OSAL_ARTE_SendShutdown_SendFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_SendShutdown_SendFail");
    UtTest_Add(Test_OSAL_ARTE_SendShutdown_SendCompleteFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_SendShutdown_SendCompleteFail");
    UtTest_Add(Test_OSAL_ARTE_SendShutdown_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_SendShutdown_Nominal");
    UtTest_Add(Test_OSAL_ARTE_VerifyCommand_NullPointer, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_VerifyCommand_NullPointer");
    UtTest_Add(Test_OSAL_ARTE_RecvNextStep_RecvFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_RecvNextStep_RecvFail");
    UtTest_Add(Test_OSAL_ARTE_RecvNextStep_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_RecvNextStep_Nominal");
    UtTest_Add(Test_OSAL_ARTE_StepNext_NullPointer, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_StepNext_NullPointer");
    UtTest_Add(Test_OSAL_ARTE_StepNext_SendFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_StepNext_SendFail");
    UtTest_Add(Test_OSAL_ARTE_StepNext_RecvFail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_StepNext_RecvFail");
    UtTest_Add(Test_OSAL_ARTE_StepNext_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_StepNext_Nominal");
    UtTest_Add(Test_OSAL_ARTE_Cleanup_Fail, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Cleanup_Fail");
    UtTest_Add(Test_OSAL_ARTE_Cleanup_Nominal, OSAL_ARTE_Test_Setup, OSAL_ARTE_Test_TearDown,
               "Test_OSAL_ARTE_Cleanup_Nominal");
}
