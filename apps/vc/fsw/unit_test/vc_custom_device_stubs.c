#include "vc_app.h"
#include "vc_dev_io.h"
#include "vc_custom_device_stubs.h"

VC_Device_Returns_t VC_Device_Test_Returns = { TRUE,
                                               TRUE,
                                               TRUE, 
                                               TRUE,
                                               0b11111111,
                                               0b11111111,
                                               0b11111111,
                                               0b11111111,
                                               0 };

boolean VC_Devices_Start(void)
{
    boolean returnCode = FALSE;
    
    /* Bitshift 1 to the left the value of call count AND with 
     * return values */
    if(VC_Device_Test_Returns.VC_Devices_Start_Return_Values &
        (1<<VC_Device_Test_Returns.VC_Devices_Start_CallCount))
    {
        returnCode = VC_Device_Test_Returns.VC_Devices_Start_Return;
    }
    else
    {
        returnCode = !VC_Device_Test_Returns.VC_Devices_Start_Return;
    }
    VC_Device_Test_Returns.VC_Devices_Start_CallCount++;
    return returnCode;
}


boolean VC_Devices_Stop(void)
{
    return VC_Device_Test_Returns.VC_Devices_Stop_Return;
}


boolean VC_Devices_Init(void)
{
    return VC_Device_Test_Returns.VC_Devices_Init_Return;
}


boolean VC_Devices_Uninit(void)
{
    return VC_Device_Test_Returns.VC_Devices_Uninit_Return;
}


int32 VC_Devices_InitData(void)
{
    return VC_Device_Test_Returns.VC_Devices_InitData_Return;
}
