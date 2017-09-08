#include "vc_custom_shared.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Custom Commands.  Raise an error event if the       */
/* command is unknown.                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void VC_ProcessNewCustomCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uint16 inSize = CFE_SB_GetTotalMsgLength(MsgPtr);
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);

        switch (uiCmdCode)
        {
            case VC_STARTSTREAMING_CC: 
            {
                VC_StartStreamingCmd(MsgPtr); 
                break;
            }
            case VC_STOPSTREAMING_CC:
            {
                VC_StopStreamingCmd(MsgPtr);
                break;
            }
            default:
                VC_AppData.HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(VC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}


void VC_StartStreamingCmd(CFE_SB_Msg_t* MsgPtr)
{
    VC_StartStreamCmd_t *CmdPtr = 0;
    
    uint16 ExpectedLength = sizeof(VC_StartStreamCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(MsgPtr, ExpectedLength))
    {
        CFE_EVS_SendEvent(VC_CMD_INF_EID, CFE_EVS_INFORMATION, "Start Streaming command received");

        if (VC_AppData.AppState == VC_INITIALIZED)
        {
            CmdPtr = ((VC_StartStreamCmd_t *) MsgPtr);
        
            /* 
            ** NUL terminate the very end of the address string as a
            ** safety measure
            */
            CmdPtr->Address[VC_ADDRESS_LENGTH - 1] = '\0';

            /* 
            ** Check if the address string is a nul string
            */ 
            if(strlen(CmdPtr->Address) == 0)
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_ADDR_NUL_ERR_EID, CFE_EVS_ERROR,
                                "NUL (empty) string specified for address");
            }
            /* Check if the address is valid */
            else if (FALSE == VC_Address_Verification(CmdPtr->Address))
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_ADDR_ERR_EID, CFE_EVS_ERROR,
                                "Invalid string specified for address");
            }
            /* Update the configuration */
            else if (FALSE == VC_Update_Destination(CmdPtr->Address, CmdPtr->Port))
            {   
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_INIT_ERR_EID, CFE_EVS_ERROR,
                                "Destination update failed in cmd start streaming");
            }
            /* Call VC_Transmit_Uninit() */
            else if (FALSE == VC_Transmit_Uninit())
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_UNINIT_ERR_EID, CFE_EVS_ERROR,
                                "VC_Transmit_Uninit failed in cmd start streaming");
            }
            /* Call VC_Transmit_Init() */
            else if (FALSE == VC_Transmit_Init())
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_INIT_ERR_EID, CFE_EVS_ERROR,
                                "VC_Transmit_Init failed in cmd start streaming");
            }
            /* Call VC_Devices_Start() */
            else if (FALSE == VC_Devices_Start())
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_INIT_ERR_EID, CFE_EVS_ERROR,
                                "VC_Devices_Start failed in cmd start streaming");
            }
            /* Success! */
            else
            {
                VC_AppData.AppState = VC_STREAMING;
                VC_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(VC_CMD_INF_EID, CFE_EVS_INFORMATION, 
                    "VC started streaming to %s:%u", CmdPtr->Address, CmdPtr->Port);
            }
        }
        else
        {
            VC_AppData.HkTlm.usCmdErrCnt++;
            CFE_EVS_SendEvent(VC_CMD_ERR_EID, CFE_EVS_ERROR, "VC is already streaming");
        }
    }
    return;
} /* End of VC_StartStreamingCmd() */


void VC_StopStreamingCmd(CFE_SB_Msg_t* MsgPtr)
{
    uint16 ExpectedLength = sizeof(VC_NoArgCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(MsgPtr, ExpectedLength))
    {
        CFE_EVS_SendEvent(VC_CMD_INF_EID, CFE_EVS_INFORMATION, "Stop Streaming command received");

        if (VC_AppData.AppState == VC_STREAMING)
        {
            if(FALSE == VC_Devices_Stop())
            {
                VC_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(VC_UNINIT_ERR_EID, CFE_EVS_ERROR,
                                "VC_Devices_Stop() failed");
            }
            else
            {
                VC_AppData.AppState = VC_INITIALIZED;
                VC_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(VC_CMD_INF_EID ,CFE_EVS_INFORMATION, 
                    "VC stopped streaming");
            }
        }
        else
        {
            VC_AppData.HkTlm.usCmdErrCnt++;
            CFE_EVS_SendEvent(VC_CMD_ERR_EID, CFE_EVS_ERROR, "VC is already not streaming");
        }
    }
    return;
} /* End of VC_StopStreamingCmd() */


void VC_Custom_Init_EventFilters(int32 ind)
{
    VC_AppData.EventTbl[  ind].EventID = VC_MSGLEN_ERR_EID;
    VC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
    
    VC_AppData.EventTbl[  ind].EventID = VC_SOCKET_ERR_EID;
    VC_AppData.EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;
    
    VC_AppData.EventTbl[  ind].EventID = VC_DEVICE_ERR_EID;
    VC_AppData.EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;

    VC_AppData.EventTbl[  ind].EventID = VC_ADDR_ERR_EID;
    VC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
    
    VC_AppData.EventTbl[  ind].EventID = VC_ADDR_NUL_ERR_EID;
    VC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
}
