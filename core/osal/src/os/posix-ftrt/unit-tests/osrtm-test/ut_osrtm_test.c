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
#include "ut_osrtm_test_utils.h"
#include "osrtm.h"
#include "ut_osrtm_platform_stubs.h"

/**************************************************************************
 * Tests for OS_RtmInit
 **************************************************************************/
/**
 * Test OS_RtmInit fail pthread_cond_init
 */
void Test_OSAL_RTM_Init_CondInitFail(void)
{
    int32 returnCode = 0;
    int32 expectedReturn = OS_ERROR;
    OS_RunTimeModeEnum_t RunMode = OS_RTM_STATE_REALTIME;
    
    /* Set pthread_cond_init to fail */
    OS_RTM_Platform_Stubs_Returns.OS_RTM_Pthread_Cond_Init_Return = 1;
    OS_RTM_Platform_Stubs_Returns.OS_RTM_Pthread_Cond_Init_Errno = 1;
    OS_RTM_Platform_Stubs_Returns.OS_RTM_Pthread_Cond_Init_Errno_Return = 1;
    
    /* Call the function under test */
    returnCode = OS_RtmInit(RunMode);
    
    /* Verify results */
    UtAssert_True(returnCode==expectedReturn,"Return code not expected");
}

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void Osrtm_Osal_Test_AddTestCases(void)
{
    UtTest_Add(Test_OSAL_RTM_Init_CondInitFail, OSAL_RTM_Test_Setup, OSAL_RTM_Test_TearDown,
               "Test_OSAL_RTM_Init_CondInitFail");
}
