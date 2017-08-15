#include "vc_app_custom_test.h"
#include "vc_custom_transmit_test_utils.h"
#include "vc_custom_device_test_utils.h"
#include "vc_platform_stubs.h"
#include "vc_platform_cfg.h"
#include <errno.h>
#include <stdio.h>
//#include "vc_msgids.h"
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
 * Tests for VC_Ioctl()
 **************************************************************************/
/**
 * Test VC_Ioctl() ioctl returns -1 error
 */
void Test_VC_Custom_Ioctl_Error(void)
{
    int32 result = 0;
    int32 expected = -1;
    
    /* Set a return value for the wrapped ioctl */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return = -1;
    
    /* A test argument to pass to VC_Ioctl value is random 
     * the wrapped ioctl will not use the arguments and will return a
     * value */
    int test = 1;
    
    
    result = VC_Ioctl(test, test, &test);

    UtAssert_True(result == expected, "VC_Ioctl did not return an error");
}
/**
 * Test VC_Ioctl() ioctl returns -1 error and errno interrupted
 */
void Test_VC_Custom_Ioctl_Interrupted(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint32 i = 0;
    
    /* Set a return value for the wrapped ioctl (always fail) */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return = -1;
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return1 = -1;
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return2 = -1;
    
    /* Set return error number to true */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno = 1;
    
    /* Set error number to interrupted */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value = EINTR;
    
    /* A test argument to pass to VC_Ioctl value is random 
     * the wrapped ioctl will not use the arguments and will return a
     * value */
    int test = 777;
    
    /* Call VC_Ioctl with errno set to EINTR max retry attempts*/
    result = VC_Ioctl(test, test, &test);
    
    UtAssert_True(result == expected, "VC_Ioctl did not return an error");
}

/**************************************************************************
 * Tests for VC_InitDevice()
 **************************************************************************/

/**
 * Test VC_InitDevice() through VC_Init_CustomDevices already initialized error
 */
void Test_VC_Custom_InitDevice_AlreadyInitialized(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;
    /* Set the first device file descriptor to a non-zero value */
    VC_AppCustomDevice.Channel[0].DeviceFd = 1;

    result = VC_Init_CustomDevices();
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(result == expected,"VC_InitDevice() did not return an error");
    
    UtAssert_True(VC_AppCustomDevice.Channel[0].Mode == VC_DEVICE_DISABLED, 
                         "VC_InitCustomDevices() did not mode to disabled");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, "VC Device test for channel 0 already initialized.", 
                        "VC_InitDevice() failed to raise an event");
}

/**
 * Test VC_InitDevice() null device name
 */
void Test_VC_Custom_InitDevice_NullName(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char *DeviceName = 0;
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;


    result = VC_InitDevice(DeviceID, DeviceName);
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(result == expected,"VC_InitDevice() did not return an error");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, "VC Device name for channel 0 is null.", 
                        "VC_InitDevice() failed to raise an event");
}


/**
 * Test VC_InitDevice() invalid device ID
 */
void Test_VC_Custom_InitDevice_InvalidID(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = VC_MAX_DEVICES;
    char returnString[32];
    snprintf(returnString, 32, "VC DeviceID (%u) invalid.", VC_MAX_DEVICES);
    char DeviceName[] = "test";
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;

    result = VC_InitDevice(DeviceID, DeviceName);
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(result == expected,"VC_InitDevice() did not return an error");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_InitDevice() failed to raise an event");
}


/**
 * Test VC_InitDevice() through VC_InitCustomDevices() open error
 */
void Test_VC_Custom_InitDevice_OpenError(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[32];
    snprintf(returnString, 32, "VC Device open errno: %i on channel %u", 5, 0);
    //char DeviceName[] = "test";
    
    /* Set a return value for the wrapped open */
    VC_Platform_Stubs_Returns.VC_Wrap_Open_Return = -1;
    
    /* Set return error number to true */
    VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno = 1;
    
    /* Set error number to interrupted */
    VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno_Value = 5;
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;

    //result = VC_InitDevice(DeviceID, DeviceName);
    result = VC_Init_CustomDevices();
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(VC_AppCustomDevice.Channel[0].Mode == VC_DEVICE_DISABLED, 
                         "VC_InitCustomDevices() did not mode to disabled");
    UtAssert_True(result == expected,"VC_InitDevice() did not return an error");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_InitDevice() failed to raise an event");
}

/**
 * Test VC_InitDevice() through VC_InitCustomDevices() nominal
 */
void Test_VC_Custom_InitDevice_Nominal(void)
{
    int32 result = 0;
    int32 expected = 0;
    uint8 DeviceID = 0;
    char DeviceName[] = "test";
    
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;

    result = VC_InitDevice(DeviceID, DeviceName);
    
    UtAssert_True(result == expected,"VC_InitDevice() did not return success");
}


/**************************************************************************
 * Tests for VC_InitCustomDevices()
 **************************************************************************/

/**
 * Test VC_InitCustomDevices() pass init but fail configure
 * ConfigureDevice will fail on the first v4L struct verification
 */
void Test_VC_Custom_InitCustomDevices_HalfNominal(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VC Device initialized channel %u from %s", 0, "test");
    
    /* Set the first device to enabled */
    VC_AppCustomDevice.Channel[0].Mode = VC_DEVICE_ENABLED;

    /* Set a test device path */
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");
    
    result = VC_Init_CustomDevices();
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==2,"Event Count = 2");
    UtAssert_EventSent(VC_DEV_INF_EID, CFE_EVS_INFORMATION, returnString, 
                        "VC_InitCustomDevices() failed to raise an event");
    UtAssert_True(VC_AppCustomDevice.Channel[0].Status == VC_DEVICE_UNINITIALIZED, 
                         "VC_InitCustomDevices() did not set status to uninitialized");
    UtAssert_True(result == expected,"VC_InitDevice() did not return failure");
}


/**
 * Test VC_InitCustomDevices() pass init and configure
 */
void Test_VC_Custom_InitCustomDevices_Nominal(void)
{

}

/**************************************************************************
 * Tests for VC_ConfigureDevice()
 **************************************************************************/
 
/**
 * Test VC_ConfigureDevice() fail V4L capabilities query
 */
void Test_VC_Custom_ConfigureDevice_CapabilitiesFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VC VIDIOC_QUERYCAP returned %i on %s channel %u", 5, "test", 0);
    
    /* Set a return value for the wrapped ioctl */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return = -1;
    
    /* Set return error number to true */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno = 1;
    
    /* Set error number to interrupted */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value = 5;
    
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");

    result = VC_ConfigureDevice(DeviceID);
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_ConfigureDevices() failed to raise an event");
    UtAssert_True(result == expected,"VC_ConfigureDevice() did not return failure");
    
}


/**
 * Test VC_ConfigureDevice() fail V4L capabilities fail 
 * check buffer type
 */
void Test_VC_Custom_ConfigureDevice_CapabilitiesBuffer(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VC Capabilities %u on %s channel %u not found", 
    VC_V4L_BUFFER_TYPE,"test", 0);
    
    /* Set the test device path */
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");
    
    VC_AppCustomDevice.Channel[0].BufferType = VC_V4L_BUFFER_TYPE;

    /* Call the function under test */
    result = VC_ConfigureDevice(DeviceID);
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_ConfigureDevices() failed to raise an event");
    UtAssert_True(result == expected,"VC_ConfigureDevice() did not return failure");
    
}


/**
 * Test VC_ConfigureDevice() fail V4L capabilities check fail
 * check streaming capability
 */
void Test_VC_Custom_ConfigureDevice_CapabilitiesStreaming(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VC Capabilities %u on %s channel %u not found", 
    V4L2_CAP_STREAMING,"test", 0);
    
    /* Set to true to emulate ioctl setting struct values */
    /* Need to succeed once for the first capabilities check */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct = 1;
    
    /* Set the test device path */
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");
    
    /* Set the correct buffer type */
    VC_AppCustomDevice.Channel[0].BufferType = VC_V4L_BUFFER_TYPE;

    /* Call the function under test */
    result = VC_ConfigureDevice(DeviceID);
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_ConfigureDevices() failed to raise an event");
    UtAssert_True(result == expected,"VC_ConfigureDevice() did not return failure");
    
}


/**
 * Test VC_ConfigureDevice() fail V4L set format fail
 */
void Test_VC_Custom_ConfigureDevice_FormatFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 DeviceID = 0;
    char returnString[64];
    snprintf(returnString, 64, "VIDIOC_S_FMT returned %i on %s channel %u", 
    5,"test", 0);
    
    /* Set to true to emulate ioctl setting struct values */
    /* Need to succeed once for the first capabilities check */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct = 2;
    
    /* Set the test device path */
    strcpy(VC_AppCustomDevice.Channel[0].DevName, "test");
    
    /* Set the correct buffer type */
    VC_AppCustomDevice.Channel[0].BufferType = VC_V4L_BUFFER_TYPE;
    
    /* Set return error number to true */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno = 1;
    
    /* Set error number to interrupted */
    /* Note this will set errno through multiple calls */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value = 5;
    
    /* Set the second ioctl call to fail */
    VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return1 = -1;

    /* Call the function under test */
    result = VC_ConfigureDevice(DeviceID);
    
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, returnString, 
                        "VC_ConfigureDevices() failed to raise an event");
    UtAssert_True(result == expected,"VC_ConfigureDevice() did not return failure");
    
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void VC_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_VC_Custom_Ioctl_Error, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_Ioctl_Error");
    UtTest_Add(Test_VC_Custom_Ioctl_Interrupted, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_Ioctl_Interrupted");
    UtTest_Add(Test_VC_Custom_InitDevice_AlreadyInitialized, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitDevice_AlreadyInitialized");
    UtTest_Add(Test_VC_Custom_InitDevice_NullName, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitDevice_NullName");
    UtTest_Add(Test_VC_Custom_InitDevice_InvalidID, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitDevice_InvalidID");
    UtTest_Add(Test_VC_Custom_InitDevice_OpenError, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitDevice_OpenError");
    UtTest_Add(Test_VC_Custom_InitDevice_Nominal, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitDevice_Nominal");
    UtTest_Add(Test_VC_Custom_InitCustomDevices_HalfNominal, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_InitCustomDevices_HalfNominal");
    UtTest_Add(Test_VC_Custom_ConfigureDevice_CapabilitiesFail, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_ConfigureDevice_CapabilitiesFail");
    UtTest_Add(Test_VC_Custom_ConfigureDevice_CapabilitiesBuffer, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_ConfigureDevice_CapabilitiesBuffer");
    UtTest_Add(Test_VC_Custom_ConfigureDevice_CapabilitiesStreaming, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_ConfigureDevice_CapabilitiesStreaming");
    UtTest_Add(Test_VC_Custom_ConfigureDevice_FormatFail, VC_Custom_Device_Test_Setup, 
            VC_Custom_Device_Test_TearDown, "Test_VC_Custom_ConfigureDevice_FormatFail");
}
