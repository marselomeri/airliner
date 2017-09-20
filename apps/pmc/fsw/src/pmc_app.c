
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

#include "cfe.h"

#include "pmc_app.h"
#include "pmc_msg.h"
#include "pmc_version.h"
#include <math.h>

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
PMC_AppData_t  PMC_AppData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 PMC_InitMixer(const char *Filename);
void PMC_SendOutputs(const uint16 *PWM);
uint32 PMC_Freq2tick(uint16 FreqHz);
int32 PMC_InitDevice(const char *Device);
void PMC_DeinitDevice(void);
void PMC_UpdateMotors(void);
void PMC_StopMotors(void);
int32 PMC_ControlCallback(uint32 *Handle,
        uint8 ControlGroup,
        uint8 ControlIndex,
        float *Control);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    int32  ind = 0;

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset((void*)PMC_AppData.EventTbl, 0x00, sizeof(PMC_AppData.EventTbl));

    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    PMC_AppData.EventTbl[  ind].EventID = PMC_RESERVED_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_INF_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_CONFIG_TABLE_ERR_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_CDS_ERR_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_PIPE_ERR_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_MSGID_ERR_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PMC_AppData.EventTbl[  ind].EventID = PMC_MSGLEN_ERR_EID;
    PMC_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(PMC_AppData.EventTbl,
                               PMC_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PMC - Failed to register with EVS (0x%08X)\n", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&PMC_AppData.SchPipeId,
                                 PMC_SCH_PIPE_DEPTH,
                                 PMC_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(PMC_WAKEUP_MID, PMC_AppData.SchPipeId, CFE_SB_Default_Qos, PMC_SCH_PIPE_WAKEUP_RESERVED);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "Sch Pipe failed to subscribe to PMC_WAKEUP_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PMC_SEND_HK_MID, PMC_AppData.SchPipeId, CFE_SB_Default_Qos, PMC_SCH_PIPE_SEND_HK_RESERVED);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PMC_SEND_HK_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_ARMED_MID, PMC_AppData.SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_ARMED_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_CONTROLS_MID, PMC_AppData.SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_CONTROLS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_RC_CHANNELS_MID, PMC_AppData.SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_RC_CHANNELS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }

    }
    else
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create SCH pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&PMC_AppData.CmdPipeId,
                                 PMC_CMD_PIPE_DEPTH,
                                 PMC_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(PMC_CMD_MID, PMC_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PMC_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PMC_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CMD pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitPipe_Exit_Tag;
    }

    /* Init data pipe and subscribe to messages on the data pipe */
    iStatus = CFE_SB_CreatePipe(&PMC_AppData.DataPipeId,
                                 PMC_DATA_PIPE_DEPTH,
                                 PMC_DATA_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, PMC_AppData.DataPipeId);
        */
    }
    else
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create Data pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitPipe_Exit_Tag;
    }

PMC_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&PMC_AppData.InData, 0x00, sizeof(PMC_AppData.InData));

    /* Init output data */
    memset((void*)&PMC_AppData.OutData, 0x00, sizeof(PMC_AppData.OutData));
    CFE_SB_InitMsg(&PMC_AppData.OutData,
            PX4_ACTUATOR_OUTPUTS_MID, sizeof(PMC_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&PMC_AppData.HkTlm, 0x00, sizeof(PMC_AppData.HkTlm));
    CFE_SB_InitMsg(&PMC_AppData.HkTlm,
                   PMC_HK_TLM_MID, sizeof(PMC_AppData.HkTlm), TRUE);

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* PMC initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC_InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = PMC_InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PMC - Failed to init events (0x%08X)\n", (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = PMC_InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init pipes (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

    iStatus = PMC_InitData();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init data (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

    iStatus = PMC_InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init config tables (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

    iStatus = PMC_InitCdsTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init CDS table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

    MIXER_Rotor RotorConfig[] = {
        { -0.382683,  0.923880, -1.000000,  1.000000 },
        {  0.382683, -0.923880, -1.000000,  1.000000 },
        { -0.923880,  0.382683,  1.000000,  1.000000 },
        { -0.382683, -0.923880,  1.000000,  1.000000 },
        {  0.382683,  0.923880,  1.000000,  1.000000 },
        {  0.923880, -0.382683,  1.000000,  1.000000 },
        {  0.923880,  0.382683, -1.000000,  1.000000 },
        { -0.923880, -0.382683, -1.000000,  1.000000 },
    };

    iStatus = MIXER_MixerInit(
            PMC_ControlCallback,
            &PMC_AppData.CVT.ActuatorControls,
            &PMC_AppData.MixerData,
            10000.0/10000.0f,
            10000.0/10000.0f,
            10000.0/10000.0f,
            1600.0/10000.0f,
            8,
            RotorConfig);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init mixer (0x%08x)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

    PwmLimit_Init(&PMC_AppData.PwmLimit);

    iStatus = PMC_InitDevice(PMC_DEVICE_PATH);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init device (0x%08x)",
                                 (unsigned int)iStatus);
        goto PMC_InitApp_Exit_Tag;
    }

PMC_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PMC_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
                                 PMC_MAJOR_VERSION,
                                 PMC_MINOR_VERSION,
                                 PMC_REVISION,
                                 PMC_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR, "Application failed to initialize");
        }
        else
        {
            (void) CFE_ES_WriteToSysLog("PMC - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PMC_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, PMC_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PMC_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case PMC_WAKEUP_MID:
                PMC_ProcessNewCmds();
                PMC_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                 * automatically publish new output. */
                PMC_SendOutData();
                break;

            case PMC_SEND_HK_MID:
                PMC_ReportHousekeeping();
                break;

            case PX4_ACTUATOR_ARMED_MID:
                memcpy(&PMC_AppData.CVT.ActuatorArmed, MsgPtr, sizeof(PMC_AppData.CVT.ActuatorArmed));
                PMC_UpdateMotors();
                break;

            case PX4_ACTUATOR_CONTROLS_MID:
                memcpy(&PMC_AppData.CVT.ActuatorControls, MsgPtr, sizeof(PMC_AppData.CVT.ActuatorControls));
                if(PMC_AppData.CVT.ActuatorArmed.InEscCalibrationMode == FALSE)
                {
                    PMC_UpdateMotors();
                }
                break;

            case PX4_RC_CHANNELS_MID:
                memcpy(&PMC_AppData.CVT.RcChannels, MsgPtr, sizeof(PMC_AppData.CVT.RcChannels));
                if(PMC_AppData.CVT.ActuatorArmed.InEscCalibrationMode == TRUE)
                {
                    PMC_UpdateMotors();
                }
                break;

            default:
                (void) CFE_EVS_SendEvent(PMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid SCH msgId (0x%04X)", (unsigned short)MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else
    {
        /* TODO: This is an example of exiting on an error (either CFE_SB_BAD_ARGUMENT, or
         * CFE_SB_PIPE_RD_ERROR).
         */
        (void) CFE_EVS_SendEvent(PMC_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "SB pipe read error (0x%08X), app will exit", (unsigned int)iStatus);
        PMC_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Data                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   DataMsgPtr=NULL;
    CFE_SB_MsgId_t  DataMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&DataMsgPtr, PMC_AppData.DataPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            DataMsgId = CFE_SB_GetMsgId(DataMsgPtr);
            switch (DataMsgId)
            {
                /* TODO:  Add code to process all subscribed data here
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         PMC_ProcessNavData(DataMsgPtr);
                **         break;
                */

                default:
                    (void) CFE_EVS_SendEvent(PMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid data msgId (0x%04X)", (unsigned short)DataMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(PMC_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "Data pipe read error (0x%08X)", (unsigned int)iStatus);
            PMC_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, PMC_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case PMC_CMD_MID:
                    PMC_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         PMC_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    PMC_AppData.HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(PMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(PMC_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08X)", (unsigned int)iStatus);
            PMC_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process PMC Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case PMC_NOOP_CC:
                PMC_AppData.HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(PMC_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd NOOP cmd (%u), Version %d.%d.%d.%d",
                                  (unsigned int)uiCmdCode,
                                  PMC_MAJOR_VERSION,
                                  PMC_MINOR_VERSION,
                                  PMC_REVISION,
                                  PMC_MISSION_REV);
                break;

            case PMC_RESET_CC:
                PMC_AppData.HkTlm.usCmdCnt = 0;
                PMC_AppData.HkTlm.usCmdErrCnt = 0;
                (void) CFE_EVS_SendEvent(PMC_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd RESET cmd (%u)", (unsigned int)uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the PMC commands here */

            default:
                PMC_AppData.HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(PMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send PMC Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PMC_AppData.HkTlm);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&PMC_AppData.HkTlm);
    if (iStatus != CFE_SUCCESS)
    {
        /* TODO: Decide what to do if the send message fails. */
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PMC_AppData.OutData);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&PMC_AppData.OutData);
    if (iStatus != CFE_SUCCESS)
    {
        /* TODO: Decide what to do if the send message fails. */
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

boolean PMC_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(PMC_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            PMC_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* PMC application entry point and main process loop               */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC_AppMain()
{
    /* Register the application with Executive Services */
    PMC_AppData.uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PMC - Failed to register the app (0x%08X)\n", (unsigned int)iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PMC_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = PMC_InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(PMC_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(PMC_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(PMC_MAIN_TASK_PERF_ID);
    }
    else
    {
        PMC_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&PMC_AppData.uiRunStatus) == TRUE)
    {
        int32 iStatus = PMC_RcvMsg(PMC_SCH_PIPE_PEND_TIME);
        if (iStatus != CFE_SUCCESS)
        {
            /* TODO: Decide what to do for other return values in PMC_RcvMsg(). */
        }
        /* TODO: This is only a suggestion for when to update and save CDS table.
        ** Depends on the nature of the application, the frequency of update
        ** and save can be more or less independently.
        */
        PMC_UpdateCdsTbl();
        PMC_SaveCdsTbl();

        iStatus = PMC_AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            PMC_AppData.uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PMC_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(PMC_AppData.uiRunStatus);
}



int32 PMC_InitMixer(const char *Filename)
{
	/* TODO:  Complete this */
	return 0;
}

void PMC_SendOutputs(const uint16 *PWM)
{
    uint32 i = 0;

    /* Convert this to duty_cycle in ns */
    for (i = 0; i < PMC_MAX_ZYNQ_PWMS; ++i) {
        PMC_AppData.SharedMemCmd->PeriodHi[i].Hi = PMC_TICK_PER_US * PWM[i];
    }
}


void PMC_StopMotors(void)
{
    uint16 disarmed_pwm[PMC_MAX_ZYNQ_PWMS];

    for (unsigned int i = 0; i < PMC_MAX_ZYNQ_PWMS; i++) {
        disarmed_pwm[i] = PMC_AppData.ConfigTblPtr->PwmDisarmed;
    }

    PMC_SendOutputs(disarmed_pwm);
}


void PMC_UpdateMotors(void)
{
    const uint16 reverse_mask = 0;
    uint16 disarmed_pwm[PMC_MAX_ZYNQ_PWMS];
    uint16 min_pwm[PMC_MAX_ZYNQ_PWMS];
    uint16 max_pwm[PMC_MAX_ZYNQ_PWMS];
    uint16 pwm[PMC_MAX_ZYNQ_PWMS];
    PX4_ActuatorOutputsMsg_t outputs;

    //_outputs.timestamp = _controls.timestamp;

    /* Do mixing */
    PMC_AppData.OutData.Count = MIXER_Mix(&PMC_AppData.MixerData, PMC_AppData.OutData.Output, 0, 0);

    /* Disable unused ports by setting their output to NaN */
    for (size_t i = PMC_AppData.OutData.Count;
         i < sizeof(PMC_AppData.OutData.Output) / sizeof(PMC_AppData.OutData.Output[0]);
         i++) {
        PMC_AppData.OutData.Output[i] = NAN;
    }

    for (unsigned int i = 0; i < PMC_MAX_ZYNQ_PWMS; i++) {
        disarmed_pwm[i] = PMC_AppData.ConfigTblPtr->PwmDisarmed;
        min_pwm[i] = PMC_AppData.ConfigTblPtr->PwmMin;
        max_pwm[i] = PMC_AppData.ConfigTblPtr->PwmMax;
    }

    /* TODO */
    PwmLimit_Calc(PMC_AppData.CVT.ActuatorArmed.Armed,
            FALSE/*_armed.prearmed*/,
            PMC_AppData.OutData.Count,
            reverse_mask,
            disarmed_pwm,
            min_pwm,
            max_pwm,
            PMC_AppData.OutData.Output,
            pwm,
            &PMC_AppData.PwmLimit);

    if (PMC_AppData.CVT.ActuatorArmed.Lockdown)
    {
        OS_printf("PMC_AppData.CVT.ActuatorArmed.Lockdown\n");
        PMC_SendOutputs(disarmed_pwm);
    }
    else if (PMC_AppData.CVT.ActuatorArmed.InEscCalibrationMode)
    {
        OS_printf("PMC_AppData.CVT.ActuatorArmed.InEscCalibrationMode\n");
        if (PMC_AppData.CVT.ActuatorControls.Control[3] * 1000 > 0.5f) {
            pwm[0] = PMC_AppData.ConfigTblPtr->PwmMax;
            pwm[1] = PMC_AppData.ConfigTblPtr->PwmMax;
            pwm[2] = PMC_AppData.ConfigTblPtr->PwmMax;
            pwm[3] = PMC_AppData.ConfigTblPtr->PwmMax;
        } else {
            pwm[0] = PMC_AppData.ConfigTblPtr->PwmMin;
            pwm[1] = PMC_AppData.ConfigTblPtr->PwmMin;
            pwm[2] = PMC_AppData.ConfigTblPtr->PwmMin;
            pwm[3] = PMC_AppData.ConfigTblPtr->PwmMin;
        }

        PMC_SendOutputs(pwm);
        CFE_EVS_SendEvent(PMC_PWM_CALIB_INFO_EID, CFE_EVS_INFORMATION, "Calib pwm %d:%d:%d:%d.", pwm[0], pwm[1], pwm[2], pwm[3]);

    }
    else
    {
        OS_printf("******************\n");
        for(uint32 i = 0; i < 8; ++i)
        {
            OS_printf("%u %04x\n", i, pwm[i]);
        }
        PMC_SendOutputs(pwm);
    }

    OS_printf("  \n");
    for(uint32 i = 0; i < PMC_AppData.OutData.Count; ++i)
    {
        OS_printf("%u %f\n", i, PMC_AppData.OutData.Output[i]);
    }
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PMC_AppData.OutData);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&PMC_AppData.OutData);
}


int32 PMC_InitDevice(const char *device)
{
    uint32 i;
    int mem_fd;

    /* Initialize just in case we were reloaded and the ctor wasn't called. */
    PMC_AppData.SharedMemCmd = 0;

    //signal(SIGBUS,catch_sigbus);
    mem_fd = open(device, O_RDWR | O_SYNC);
    PMC_AppData.SharedMemCmd = (PMC_SharedMemCmd_t *) mmap(0, 0x1000, PROT_READ | PROT_WRITE,
                        MAP_SHARED, mem_fd, PMC_RCOUT_ZYNQ_PWM_BASE);
    close(mem_fd);

    if (PMC_AppData.SharedMemCmd == 0) {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init device.  errno = %u.",
                                 errno);
        return -1;
    }

    for (i = 0; i < PMC_MAX_ZYNQ_PWMS; ++i) {
        PMC_AppData.SharedMemCmd->PeriodHi[i].Period = PMC_Freq2tick(PMC_FREQUENCY_PWM);
        PMC_AppData.SharedMemCmd->PeriodHi[i].Hi     = PMC_Freq2tick(PMC_FREQUENCY_PWM) / 2; // i prefer it is zero at the beginning
        //PX4_ERR("initialize pwm pointer failed.%d, %d", sharedMem_cmd->periodhi[i].period, sharedMem_cmd->periodhi[i].hi);
    }

    OS_TaskDelay(100);
    PMC_StopMotors();

    return 0;
}

void PMC_Deinitialize(void)
{
    uint32 i = 0;

    for (i = 0; i < PMC_MAX_ZYNQ_PWMS; ++i) {
        PMC_AppData.SharedMemCmd = 0;
    }
}


unsigned long PMC_Freq2tick(uint16 FreqHz)
{
    unsigned long duty = PMC_TICK_PER_S / (unsigned long)FreqHz;
    return duty;
}


int32 PMC_ControlCallback(uint32 *Handle,
        uint8 ControlGroup,
        uint8 ControlIndex,
        float *Control)
{
    const PX4_ActuatorControlsMsg_t *controls = (PX4_ActuatorControlsMsg_t*)Handle;

    *Control = controls[ControlGroup].Control[ControlIndex];

    return 0;
}

/************************/
/*  End of File Comment */
/************************/
