#include "vc_app.h"
#include "vc_dev_io.h"
#include "vc_custom_device_stubs.h"

VC_Device_Returns_t VC_Device_Test_Returns = { TRUE,
                                               TRUE,
                                               TRUE, 
                                               TRUE };

boolean VC_Devices_Start(void)
{
    return VC_Device_Test_Returns.VC_Devices_Start_Return;
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
