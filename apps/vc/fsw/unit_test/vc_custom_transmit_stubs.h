#ifndef VC_CUSTOM_TRANSMIT_STUBS_H
#define VC_CUSTOM_TRANSMIT_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    boolean VC_Transmit_Init_Return;
    boolean VC_Transmit_Uninit_Return;
    boolean VC_Address_Verification_Return;
    boolean VC_Update_Destination_Return;
    int32 VC_SendData_Return;
    uint8   VC_Transmit_Init_Return_Values;
    uint8   VC_Transmit_Uninit_Return_Values;
    uint8   VC_Address_Verification_Return_Values;
    uint8   VC_Update_Destination_Return_Values;
    uint8   VC_SendData_Return_Values;
    uint8   VC_Transmit_Init_CallCount;
    int32   VC_Transmit_InitData_Return;
} VC_Transmit_Returns_t;


extern VC_Transmit_Returns_t VC_Transmit_Test_Returns;


#ifdef __cplusplus
}
#endif

#endif /* VC_CUSTOM_TRANSMIT_STUBS_H */
