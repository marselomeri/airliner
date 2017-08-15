#include "vc_app.h"
#include "vc_transmit.h"
#include "vc_custom_transmit_stubs.h"

VC_Transmit_Returns_t VC_Transmit_Test_Returns = { TRUE,
                                                   TRUE,
                                                   TRUE, 
                                                   TRUE, 
                                                   1,
                                                   0b11111111,
                                                   0b11111111,
                                                   0b11111111,
                                                   0b11111111,
                                                   0b11111111,
                                                   0 };


boolean VC_Transmit_Init(void)
{
    boolean returnCode = FALSE;

    /* Bitshift 1 to the left the value of call count AND with 
     * return values */
    if(VC_Transmit_Test_Returns.VC_Transmit_Init_Return_Values &
        (1<<VC_Transmit_Test_Returns.VC_Transmit_Init_CallCount))
    {
        returnCode = VC_Transmit_Test_Returns.VC_Transmit_Init_Return;
    }
    else
    {
        returnCode = !VC_Transmit_Test_Returns.VC_Transmit_Init_Return;
    }

    VC_Transmit_Test_Returns.VC_Transmit_Init_CallCount++;
    return returnCode;
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
