
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

#include "vc_cmds.h"
#include "vc_app.h"
#include <string.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

void VC_NoopCmd(CFE_SB_Msg_t* MsgPtr)
{
    uint16 ExpectedLength = sizeof(VC_NoArgCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(MsgPtr, ExpectedLength))
    {
        VC_AppData.HkTlm.usCmdCnt++;

        (void) CFE_EVS_SendEvent(VC_NOOP_INF_EID, CFE_EVS_INFORMATION,
                            "Recvd NOOP cmd, Version %d.%d.%d.%d",
                            VC_MAJOR_VERSION,
                            VC_MINOR_VERSION,
                            VC_REVISION,
                            VC_MISSION_REV);
    }

    return;

} /* End of VC_NoopCmd() */


void VC_ResetCmd(CFE_SB_Msg_t* MsgPtr)
{
    uint16 ExpectedLength = sizeof(VC_NoArgCmd_t); 

    /* Verify command packet length */
    if (VC_VerifyCmdLength(MsgPtr, ExpectedLength))
    {
        VC_AppData.HkTlm.usCmdCnt = 0;
        VC_AppData.HkTlm.usCmdErrCnt = 0;
        (void) CFE_EVS_SendEvent(VC_RESET_INF_EID, CFE_EVS_INFORMATION,
                            "Recvd RESET cmd");
                
    }

    return;

} /* End of VC_ResetCmd() */


void VC_ReportHousekeeping(CFE_SB_Msg_t* MsgPtr)
{
    uint16 ExpectedLength = sizeof(VC_NoArgCmd_t); 
    uint16 i;
    
    /* Verify command packet length */
    if (VC_VerifyCmdLength(MsgPtr, ExpectedLength))
    {
        VC_AppData.HkTlm.State = VC_AppData.AppState; 
        
        /* Send housekeeping telemetry packet */
        CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VC_AppData.HkTlm);
        int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&VC_AppData.HkTlm);
        if (iStatus != CFE_SUCCESS)
        {
        /* TODO: Decide what to do if the send message fails. */
        }
        /* This command does not affect the command execution counter */
    }

    return;

} /* End of VC_HousekeepingCmd() */


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


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

boolean VC_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult  = TRUE;
    uint16  usMsgLen = 0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(VC_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            VC_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
} /* End of VC_VerifyCmdLength() */

/************************/
/*  End of File Comment */
/************************/


