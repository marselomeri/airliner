#include "vc_cmds.h"
#include "vc_app.h"


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
                         "No-op command");
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


void VC_HelloWorldCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof(VC_NoArgsCmd_t);

    /* Verify command packet length */
    if (VC_VerifyCmdLength(msg, ExpectedLength))
    {
        CFE_EVS_SendEvent(VC_PROCCESS_INF_EID,CFE_EVS_INFORMATION, "Hello World!");
    }

    return;

} /* End of VC_HelloWorldCmd() */


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


