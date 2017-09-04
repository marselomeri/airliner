#ifndef VC_CUSTOM_DEVICE_STUBS_H
#define VC_CUSTOM_DEVICE_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    boolean VC_Devices_Start_Return;
    boolean VC_Devices_Stop_Return;
    boolean VC_Devices_Init_Return;
    boolean VC_Devices_Uninit_Return;
    uint8   VC_Devices_Start_Return_Values;
    uint8   VC_Devices_Stop_Return_Values;
    uint8   VC_Devices_Init_Return_Values;
    uint8   VC_Devices_Uninit_Return_Values;
    uint8   VC_Devices_Start_CallCount;
    int32   VC_Devices_InitData_Return;
} VC_Device_Returns_t;


extern VC_Device_Returns_t VC_Device_Test_Returns;


#ifdef __cplusplus
}
#endif

#endif /* VC_CUSTOM_DEVICE_STUBS_H */
