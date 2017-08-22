
#include "to_app_custom_test.h"
#include "to_custom_test_utils.h"
#include "to_platform_stubs.h"

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
 * Tests for TO_Custom_Init()
 **************************************************************************/
/**
 * Test TO_Custom_Init() fail TO_Channel_OpenChannel
 */
void TO_Custom_Init_OpenChannelFail(void)
{
    int32 result = 0;
    int32 expected = 1;
    
    TO_App_Return.TO_Channel_OpenChannel_Return = 1;
    
    /* Execute the function being tested */
    result = TO_Custom_Init();
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_Custom_Init() did not fail");
}


/**************************************************************************
 * Tests for TO_OutputChannel_CustomBuildupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomBuildupAll() nominal
 * NOTE: Function is not currently implemented.
 */
void Test_TO_OutputChannel_CustomBuildupAll_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint32 index = 0;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_CustomBuildupAll(index);
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_OutputChannel_CustomBuildupAll() failed nominal");
}


/**************************************************************************
 * Tests for TO_OutputChannel_Enable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Enable() null destination address
 */
void Test_TO_OutputChannel_Enable_NullDestinationAddress(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    /* Null destination address */
    char *DestinationAddress = 0;
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "Destination address for channel %u is null.", 0);
    
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() invalid channel id
 */
void Test_TO_OutputChannel_Enable_InvalidID(void)
{
    int32 result = 0;
    int32 expected = -1;
    /* Set invalid channel ID */
    uint8 ChannelID = (TO_MAX_CHANNELS);
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "ChannelID (%u) invalid.", (TO_MAX_CHANNELS));
    
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail socket creation
 */
void Test_TO_OutputChannel_Enable_SocketFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    int32 expectedErrno = 5;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "TLM socket errno: %i on channel %u", expectedErrno, ChannelID);
    
    /* Set socket call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = -1;
    
    /* Set errno for socket call */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno = 1;
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno_Value = expectedErrno;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Socket == -1,
                        "TO_OutputChannel_Enable() failed to return an error");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                         "TO_OutputChannel_Enable() did not set correct mode");
    UtAssert_EventSent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail bind
 */
void Test_TO_OutputChannel_Enable_BindFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    int32 expectedErrno = 5;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "TLM bind errno: %i on channel %u", expectedErrno, ChannelID);
    
    /* Set socket call to pass */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = 1;
    
    /* Set bind call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Return = -1;
    
    /* Set errno for bind call */
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno = 1;
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno_Value = expectedErrno;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                         "TO_OutputChannel_Enable() did not set correct mode");
    UtAssert_EventSent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail create child task
 */
void Test_TO_OutputChannel_Enable_CreateChildTaskFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    /* Set create child task to fail */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_CREATECHILDTASK_INDEX, -1, 1);
    
    /* Set socket call to pass */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = 1;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==0,"Event Count = 0");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_ENABLED, 
                         "TO_OutputChannel_Enable() did not set correct mode");
}


/**************************************************************************
 * Tests for TO_OutputChannel_Send()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Send()
 */
 
 
 /**************************************************************************
 * Tests for TO_OutputChannel_ChannelHandler()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ChannelHandler()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_ProcessNewCustomCmds()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ProcessNewCustomCmds()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_OnboardChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_OnboardChannelTask()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_GroundChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_GroundChannelTask()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_CustomTeardownAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomTeardownAll() nominal
 * NOTE: Function is not currently implemented.
 */
 void Test_TO_OutputChannel_CustomTeardownAll_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint32 index = 0;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_CustomTeardownAll(index);
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_OutputChannel_CustomBuildupAll() failed nominal");
}
 /**************************************************************************
 * Tests for TO_OutputChannel_CustomCleanupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomCleanupAll()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_Disable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Disable()
 */

void TO_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(TO_Custom_Init_OpenChannelFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_Custom_Init_OpenChannelFail");
    UtTest_Add(Test_TO_OutputChannel_CustomBuildupAll_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_CustomBuildupAll_Nominal");
    UtTest_Add(Test_TO_OutputChannel_Enable_NullDestinationAddress, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_NullDestinationAddress");
    UtTest_Add(Test_TO_OutputChannel_Enable_InvalidID, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_InvalidID");
    UtTest_Add(Test_TO_OutputChannel_Enable_SocketFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_SocketFail");
    UtTest_Add(Test_TO_OutputChannel_Enable_BindFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_BindFail");
    UtTest_Add(Test_TO_OutputChannel_Enable_CreateChildTaskFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_CreateChildTaskFail");


    UtTest_Add(Test_TO_OutputChannel_CustomTeardownAll_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_CustomTeardownAll_Nominal");
}
