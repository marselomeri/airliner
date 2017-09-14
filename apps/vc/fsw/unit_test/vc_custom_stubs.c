#include "vc_custom_stubs.h"

VC_Custom_Returns_t VC_Custom_Test_Returns;

void VC_ProcessNewCustomCmds(CFE_SB_Msg_t* MsgPtr)
{

}


void VC_StartStreamingCmd(CFE_SB_Msg_t* MsgPtr)
{
    
}


void VC_StopStreamingCmd(CFE_SB_Msg_t* MsgPtr)
{
    
}


int32 VC_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    return VC_Custom_Test_Returns.VC_Custom_Init_EventFilters_Return;
}
