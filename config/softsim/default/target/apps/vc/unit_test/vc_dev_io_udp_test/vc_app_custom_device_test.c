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

#include "vc_app_custom_device_test.h"
#include "vc_custom_device_test_utils.h"
#include "vc_transmit_udp.h"
#include "vc_platform_stubs.h"
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

/**************************************************************************
 * Tests for VC_InitCustomDevices()
 **************************************************************************/
/**
 * Test VC_InitCustomDevices() fail socket creation
 */
void Test_VC_Custom_InitCustomDevices_FailSocket(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "Socket errno: %i on channel %u", 13, 0);
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;
    
    /* Set socket creation to fail */
    VC_Platform_Stubs_Returns.VC_Wrap_Socket_Return = -1;
    VC_Platform_Stubs_Returns.VC_Wrap_Socket_Errno = 1;
    VC_Platform_Stubs_Returns.VC_Wrap_Socket_Errno_Value = 13;
    
    result = VC_Init_CustomDevices();
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_InitCustomDevices() failed to raise an event");
    UtAssert_True(VC_AppCustomDevice.Channel[0].Status == VC_DEVICE_UNINITIALIZED, 
                         "VC_InitCustomDevices() status NOT uninitialized");
    UtAssert_True(result == expected,"VC_InitDevice() did not return failure");
}

/**
 * Test VC_InitCustomDevices() fail bind
 */
void Test_VC_Custom_InitCustomDevices_FailBind(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "Bind errno: %i on channel %u", 13, 0);
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;
    
    /* Set socket creation to pass */
    VC_Platform_Stubs_Returns.VC_Wrap_Socket_Return = 1;
    
    /* Set bind to fail */
    VC_Platform_Stubs_Returns.VC_Wrap_Bind_Return = -1;
    VC_Platform_Stubs_Returns.VC_Wrap_Bind_Errno = 1;
    VC_Platform_Stubs_Returns.VC_Wrap_Bind_Errno_Value = 13;
    
    result = VC_Init_CustomDevices();
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_InitCustomDevices() failed to raise an event");
    UtAssert_True(VC_AppCustomDevice.Channel[0].Status == VC_DEVICE_UNINITIALIZED, 
                         "VC_InitCustomDevices() status NOT uninitialized");
    UtAssert_True(result == expected,"VC_InitDevice() did not return failure");
}

/**
 * Test VC_InitCustomDevices() nominal 
 */
void Test_VC_Custom_InitCustomDevices_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VC Device initialized channel %u", 0);
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;
    
    /* Set socket creation to pass */
    VC_Platform_Stubs_Returns.VC_Wrap_Socket_Return = 1;
    
    /* Set bind to pass */
    VC_Platform_Stubs_Returns.VC_Wrap_Bind_Return = 1;
    
    result = VC_Init_CustomDevices();
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEV_INF_EID, CFE_EVS_INFORMATION, returnString, 
                        "VC_InitCustomDevices() failed to raise an event");
    UtAssert_True(VC_AppCustomDevice.Channel[0].Status == VC_DEVICE_INITIALIZED, 
                         "VC_InitCustomDevices() status NOT initialized");
    UtAssert_True(result == expected,"VC_InitDevice() did not return failure");
}

/**************************************************************************
 * Tests for VC_Stream_Task()
 **************************************************************************/

/**
 * Test VC_Stream_Task() fail register child task
 */
void Test_VC_Custom_StreamTask_RegisterChildTaskFail(void)
{
    /* Set register child task to fail */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERCHILDTASK_INDEX, -1, 1);

    /* Call the function under test */
    VC_Stream_Task();
    
    /* Verfity results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(VC_AppData.AppState == VC_INITIALIZED,
                        "VC_Stream_Task() did not set app state");
    UtAssert_EventSent(VC_DEV_INF_EID, CFE_EVS_INFORMATION, 
                        "VC streaming task exited with return code 0 task status (0xFFFFFFFF)", 
                        "VC_Stream_Task() failed to raise an event");
}

/**************************************************************************
 * Tests for VC_Devices_Start()
 **************************************************************************/
 

/**************************************************************************
 * Tests for VC_Devices_Stop()
 **************************************************************************/


/**************************************************************************
 * Tests for VC_CleanupDevices()
 **************************************************************************/


/**************************************************************************
 * Tests for VC_Devices_Init()
 **************************************************************************/
 
 
/**************************************************************************
 * Tests for VC_Devices_Uninit()
 **************************************************************************/


/**************************************************************************
 * Tests for VC_Send_Buffer()
 **************************************************************************/


/**************************************************************************
 * Tests for VC_Devices_InitData()
 **************************************************************************/

/**
 * Test VC_Devices_InitData() nominal
 * Note: currently no way to fail this function
 */
void Test_VC_Devices_InitData_Nominal(void)
{
    int32 result = -1;
    int32 expected = CFE_SUCCESS;
    
    /* Call the function under test */
    result = VC_Devices_InitData();
    
    /* Verify the results */
    UtAssert_True(result == expected,"VC_Custom_InitData() did not succeed");
}

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_Custom_App_Device_Test_AddTestCases(void)
{
/**************************************************************************
 * Tests for Custom Device Layer
 **************************************************************************/
    UtTest_Add(Test_VC_Custom_InitCustomDevices_FailSocket, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitCustomDevices_FailSocket");
    UtTest_Add(Test_VC_Custom_InitCustomDevices_FailBind, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitCustomDevices_FailBind");
    UtTest_Add(Test_VC_Custom_InitCustomDevices_Nominal, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitCustomDevices_Nominal");
    UtTest_Add(Test_VC_Custom_StreamTask_RegisterChildTaskFail, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_StreamTask_RegisterChildTaskFail");
    UtTest_Add(Test_VC_Devices_InitData_Nominal, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Devices_InitData_Nominal");
}
