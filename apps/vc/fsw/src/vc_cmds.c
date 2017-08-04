#include "vc_cmds.h"
#include "vc_app.h"
#include <string.h>


void VC_HousekeepingCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof(VC_NoArgsCmd_t); 
    uint16 i;
    
    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
       /* Get command execution counters */
        VC_AppData.HkPacket.CmdCounter = VC_AppData.CmdCounter;
        VC_AppData.HkPacket.ErrCounter = VC_AppData.ErrCounter;
        
        /* Send housekeeping telemetry packet */
        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &VC_AppData.HkPacket);
        CFE_SB_SendMsg((CFE_SB_Msg_t *) &VC_AppData.HkPacket);

        /* This command does not affect the command execution counter */
    }

    return;

} /* End of VC_HousekeepingCmd() */


void VC_NoopCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof(VC_NoArgsCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
        VC_AppData.CmdCounter++;

        CFE_EVS_SendEvent(VC_NOOP_INF_EID, CFE_EVS_INFORMATION, \
                        "No-op command. Version %d.%d.%d.%d", \
                        VC_MAJOR_VERSION, \
                        VC_MINOR_VERSION, \
                        VC_REVISION, \
                        VC_MISSION_REV); \
    }

    return;

} /* End of VC_NoopCmd() */


void VC_ResetCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof(VC_NoArgsCmd_t); 

    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
        VC_AppData.CmdCounter = 0;
        VC_AppData.ErrCounter = 0;

        CFE_EVS_SendEvent(VC_RESET_INF_EID, CFE_EVS_INFORMATION, \
                         "Reset Counters command received");
    }

    return;

} /* End of VC_ResetCmd() */


void VC_StartStreamingCmd(CFE_SB_MsgPtr_t msg)
{
    VC_StartStreamCmd_t *CmdPtr = 0;
    
    uint16 ExpectedLength = sizeof(VC_StartStreamCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
        CmdPtr = ((VC_StartStreamCmd_t *) msg);
        
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
            VC_AppData.ErrCounter++;
            CFE_EVS_SendEvent(VC_ADDR_NUL_ERR_EID, CFE_EVS_ERROR,
                            "NUL (empty) string specified for address");
        }
        else
        {   
            /* If address is not an empty string */
            
            /* Check streaming state */
            
            /* Verify the address */
            
            /* Update the configuration */
            
            VC_AppData.CmdCounter++;

        }
        
        CFE_EVS_SendEvent(VC_PROCCESS_INF_EID,CFE_EVS_INFORMATION, "Start Streaming command received");
    }

    return;

} /* End of VC_StartStreamingCmd() */


void VC_StopStreamingCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof(VC_NoArgsCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
        CFE_EVS_SendEvent(VC_PROCCESS_INF_EID,CFE_EVS_INFORMATION, "Stop Streaming command received");
    }

    return;

} /* End of VC_StopStreamingCmd() */


boolean VC_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{
    boolean result = TRUE;
    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /* Verify the command packet length */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID = CFE_SB_GetMsgId(msg);
        uint16 CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(VC_LEN_ERR_EID, CFE_EVS_ERROR, \
           "Invalid cmd pkt: ID = 0x%X,  CC = %d, Len = %d", \
                          MessageID, CommandCode, ActualLength);
        result = FALSE;
        VC_AppData.ErrCounter++;
    }

    return(result);

} /* End of VC_VerifyCmdLength() */


