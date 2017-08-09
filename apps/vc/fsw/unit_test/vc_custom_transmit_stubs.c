#include "vc_app.h"
#include "vc_transmit.h"
#include "vc_custom_transmit_stubs.h"

VC_Transmit_Returns_t VC_Transmit_Test_Returns = { TRUE,
                                                   TRUE,
                                                   TRUE, 
                                                   TRUE, 
                                                   1 };


boolean VC_Transmit_Init(void)
{
    return VC_Transmit_Test_Returns.VC_Transmit_Init_Return;
}


boolean VC_Transmit_Uninit(void)
{
    return VC_Transmit_Test_Returns.VC_Transmit_Uninit_Return;
}


boolean VC_Address_Verification(const char *Address)
{
    return VC_Transmit_Test_Returns.VC_Address_Verification_Return;
}


boolean VC_Update_Destination(const char *Address, uint16 Port)
{
    return VC_Transmit_Test_Returns.VC_Update_Destination_Return;
}


int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size)
{
    return VC_Transmit_Test_Returns.VC_SendData_Return;
}
