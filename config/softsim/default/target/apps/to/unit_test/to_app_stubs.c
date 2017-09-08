
#include "to_app_stubs.h"

TO_App_Returns_t TO_App_Return = {0};

int32 TO_Channel_OpenChannel(uint32 index, char *ChannelName,
        char *ConfigTableName, char *ConfigTableFileName,
        char *DumpTableName)
{
    return TO_App_Return.TO_Channel_OpenChannel_Return;
}


void  TO_Channel_LockByIndex(uint32 index)
{
    
}


void  TO_Channel_UnlockByIndex(uint32 index)
{
    
}


uint8 TO_Channel_State(uint32 index)
{
    uint8 returnCode = 0;

    if(0 == TO_App_Return.TO_Channel_State_CallCount) 
    {
        returnCode = TO_App_Return.TO_Channel_State_Return;
    }
    else
    {
        TO_AppCustomData.Channel[0].Mode = TO_CHANNEL_DISABLED;
        returnCode = TO_App_Return.TO_Channel_State_Return1;
    }
    TO_App_Return.TO_Channel_State_CallCount++;
    return returnCode;
}
