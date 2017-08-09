#include "vc_app.h"
#include "vc_transmit.h"

boolean VC_Transmit_Init(void)
{
    return TRUE;
}


boolean VC_Transmit_Uninit(void)
{
    return TRUE;
}


boolean VC_Address_Verification(const char *Address)
{
    return TRUE;
}


boolean VC_Update_Destination(const char *Address, uint16 Port)
{
    return TRUE;
}


int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size)
{
    return 1;
}
