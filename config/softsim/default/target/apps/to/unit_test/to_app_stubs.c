
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
    return 0;
}


void  TO_Channel_UnlockByIndex(uint32 index)
{
    return 0;
}
