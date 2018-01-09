
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"
#include "mavlink.h"
#include "params_app.h"
#include "params_msg.h"
#include "params_version.h"

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
PARAMS_AppData_t  PARAMS_AppData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    int32  ind = 0;

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset((void*)PARAMS_AppData.EventTbl, 0x00, sizeof(PARAMS_AppData.EventTbl));

    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_RESERVED_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_INF_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_CONFIG_TABLE_ERR_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_CDS_ERR_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_PIPE_ERR_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_MSGID_ERR_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    PARAMS_AppData.EventTbl[  ind].EventID = PARAMS_MSGLEN_ERR_EID;
    PARAMS_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(PARAMS_AppData.EventTbl,
                               PARAMS_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PARAMS - Failed to register with EVS (0x%08X)\n", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&PARAMS_AppData.SchPipeId,
                                 PARAMS_SCH_PIPE_DEPTH,
                                 PARAMS_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(PARAMS_WAKEUP_MID, PARAMS_AppData.SchPipeId, CFE_SB_Default_Qos, PARAMS_SCH_PIPE_WAKEUP_RESERVED);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "Sch Pipe failed to subscribe to PARAMS_WAKEUP_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PARAMS_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PARAMS_SEND_HK_MID, PARAMS_AppData.SchPipeId, CFE_SB_Default_Qos, PARAMS_SCH_PIPE_SEND_HK_RESERVED);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PARAMS_SEND_HK_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PARAMS_InitPipe_Exit_Tag;
        }

    }
    else
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create SCH pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&PARAMS_AppData.CmdPipeId,
                                 PARAMS_CMD_PIPE_DEPTH,
                                 PARAMS_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(PARAMS_CMD_MID, PARAMS_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PARAMS_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PARAMS_InitPipe_Exit_Tag;
        }

        /* Subscribe to mavlink commands */
        iStatus = CFE_SB_Subscribe(MAVLINK_REQUEST_PARAMS_MID, PARAMS_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PARAMS_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto PARAMS_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CMD pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitPipe_Exit_Tag;
    }

    /* Init data pipe and subscribe to messages on the data pipe */
    iStatus = CFE_SB_CreatePipe(&PARAMS_AppData.DataPipeId,
                                 PARAMS_DATA_PIPE_DEPTH,
                                 PARAMS_DATA_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, PARAMS_AppData.DataPipeId);
        */
    }
    else
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create Data pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitPipe_Exit_Tag;
    }

PARAMS_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&PARAMS_AppData.InData, 0x00, sizeof(PARAMS_AppData.InData));

    /* Init output data */
    memset((void*)&PARAMS_AppData.OutData, 0x00, sizeof(PARAMS_AppData.OutData));
    CFE_SB_InitMsg(&PARAMS_AppData.OutData,
                   PARAMS_OUT_DATA_MID, sizeof(PARAMS_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&PARAMS_AppData.HkTlm, 0x00, sizeof(PARAMS_AppData.HkTlm));
    CFE_SB_InitMsg(&PARAMS_AppData.HkTlm,
                   PARAMS_HK_TLM_MID, sizeof(PARAMS_AppData.HkTlm), TRUE);

    PARAMS_AppData.HkTlm.ParamsInitialized = TRUE;

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* PARAMS initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = PARAMS_InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PARAMS - Failed to init events (0x%08X)\n", (unsigned int)iStatus);
        goto PARAMS_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = PARAMS_InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init pipes (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitApp_Exit_Tag;
    }

    iStatus = PARAMS_InitData();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init data (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitApp_Exit_Tag;
    }

    iStatus = PARAMS_InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init config tables (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitApp_Exit_Tag;
    }

    iStatus = PARAMS_InitCdsTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init CDS table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitApp_Exit_Tag;
    }

PARAMS_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(PARAMS_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
                                 PARAMS_MAJOR_VERSION,
                                 PARAMS_MINOR_VERSION,
                                 PARAMS_REVISION,
                                 PARAMS_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR, "Application failed to initialize");
        }
        else
        {
            (void) CFE_ES_WriteToSysLog("PARAMS - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


void PARAMS_AddParam(PARAMS_ParamData_t param)
{
	/* Iterate over table to find first empty index */
	for(int i = 0; i < PARAMS_PARAM_TABLE_MAX_ENTRIES; ++i)
	{
		if (PARAMS_AppData.ParamTblPtr->params[i].enabled == 0)
		{
			/* Update parameter message with current table index values */
			PARAMS_AppData.ParamTblPtr->params[i].enabled = 1;
			PARAMS_AppData.ParamTblPtr->params[i].param_data.value = param.value;
			memcpy(PARAMS_AppData.ParamTblPtr->params[i].param_data.name, param.name,
					sizeof(param.name)); //need to clear string?
			PARAMS_AppData.ParamTblPtr->params[i].param_data.type = param.type;
			PARAMS_AppData.ParamTblPtr->params[i].param_data.vehicle_id = param.vehicle_id;
			PARAMS_AppData.ParamTblPtr->params[i].param_data.component_id = param.component_id;
		}
	}
}

boolean PARAMS_ParamsEqual(PARAMS_ParamData_t param1, PARAMS_ParamData_t param2)
{
	boolean equal = TRUE;

	if (param1.vehicle_id != param2.vehicle_id)
	{
		equal = FALSE;
		goto PARAMS_ParamsEqual_Exit_Tag;
	}

	if (param1.component_id != param2.component_id)
	{
		equal = FALSE;
		goto PARAMS_ParamsEqual_Exit_Tag;
	}

	if (strcmp(param1.name, param2.name) != 0)
	{
		equal = FALSE;
		goto PARAMS_ParamsEqual_Exit_Tag;
	}

PARAMS_ParamsEqual_Exit_Tag:
	return equal;
}

void PARAMS_PrintParam(PARAMS_ParamData_t param_data)
{
	OS_printf("name: %s \n", param_data.name);
	OS_printf("val: %u \n", param_data.value);
	OS_printf("type: %u \n", param_data.type);
	OS_printf("vehicle_id: %u \n", param_data.vehicle_id);
	OS_printf("component_id: %u \n", param_data.component_id);
}



void PARAMS_SetParam(PARAMS_SendParamDataCmd_t* SetParamMsg)
{
	int32 Status;
	CFE_SB_MsgPtr_t 	CmdMsgPtr;
	boolean paramExists = FALSE;

	/* Iterate over table to find parameter */
	for(int i = 0; i < PARAMS_PARAM_TABLE_MAX_ENTRIES; ++i)
	{
		/* Only check enabled parameters */
		if (PARAMS_AppData.ParamTblPtr->params[i].enabled == 1)
		{
			if (PARAMS_ParamsEqual(SetParamMsg->param_data, PARAMS_AppData.ParamTblPtr->params[i].param_data))
			{
				/* Update parameter message with current table index values */
				paramExists = TRUE;
				PARAMS_AppData.ParamTblPtr->params[i].param_data.value = SetParamMsg->param_data.value;
				PARAMS_AppData.ParamTblPtr->params[i].param_data.type = SetParamMsg->param_data.type;
			}
		}
	}

	// TODO: Verify this is expected
	if (!paramExists)
	{
		PARAMS_AddParam(SetParamMsg->param_data);
	}
	//PARAMS_PrintParam(SetParamMsg->param_data);

	/* Init Airliner message */
	CFE_SB_InitMsg(&SetParamMsg, PARAMS_PARAM_MID, sizeof(PARAMS_SendParamDataCmd_t), FALSE);
	CmdMsgPtr = (CFE_SB_MsgPtr_t)&SetParamMsg;
	CFE_SB_SetCmdCode(CmdMsgPtr, PARAMS_PARAM_DATA_CC);

	/* Send to SB */
	Status = CFE_SB_SendMsg(CmdMsgPtr);
	if (Status != CFE_SUCCESS)
	{
		OS_printf("Error sending param to SB\n");
		/* TODO: Decide what to do if the send message fails. */
	}
}

// For QGC when requesting vehicle params
void PARAMS_SendAllParamsToSB()
{
	int32 Status;
	uint16 msg_size 		= 0;
	PARAMS_SendParamDataCmd_t ParamDataMsg = {0};
	CFE_SB_MsgPtr_t 	CmdMsgPtr;
	uint16 param_index = 0;

	/* Ensure param count is up to date */
	PARAMS_UpdateParamCount();
	OS_printf("sending params to SB\n");
	/* Iterate over table and send each parameter */
	for(int i = 0; i < PARAMS_PARAM_TABLE_MAX_ENTRIES; ++i)
	{
		if (PARAMS_AppData.ParamTblPtr->params[i].enabled == 1)
		{
			/* Init Airliner message */
			CFE_SB_InitMsg(&ParamDataMsg, PARAMS_PARAM_MID, sizeof(PARAMS_SendParamDataCmd_t), FALSE);
			CmdMsgPtr = (CFE_SB_MsgPtr_t)&ParamDataMsg;
			CFE_SB_SetCmdCode(CmdMsgPtr, PARAMS_PARAM_DATA_CC);

			/* Update parameter message with current table index values */
			ParamDataMsg.param_data.value = PARAMS_AppData.ParamTblPtr->params[i].param_data.value;
			memcpy(ParamDataMsg.param_data.name, PARAMS_AppData.ParamTblPtr->params[i].param_data.name,
					sizeof(PARAMS_AppData.ParamTblPtr->params[i].param_data.name));
			ParamDataMsg.param_data.type = PARAMS_AppData.ParamTblPtr->params[i].param_data.type;
			ParamDataMsg.param_count = PARAMS_AppData.ParamCount;
			ParamDataMsg.param_index = param_index;

			/* Send to SB */
			Status = CFE_SB_SendMsg(CmdMsgPtr);
			if (Status != CFE_SUCCESS)
			{
				OS_printf("Error sending param to SB\n");
				/* TODO: Decide what to do if the send message fails. */
			}

			/* Increment the param index. Can't use loop index since not all entries are enabled */
			param_index++;
		}
	}
}

// For QGC when requesting an individual parameter
void PARAMS_RequestSingleParam(PARAMS_RequestParamDataCmd_t* requestCmd)
{
	int32 Status;
	uint16 msg_size 		= 0;
	PARAMS_SendParamDataCmd_t ParamDataMsg = {0};
	CFE_SB_MsgPtr_t 	CmdMsgPtr;
	uint16 param_index = 0;

	/* Iterate over table to reach enabled index */
	for(int i = 0; i < PARAMS_PARAM_TABLE_MAX_ENTRIES; ++i)
	{
		if (PARAMS_AppData.ParamTblPtr->params[i].enabled == 1)
		{
			if (requestCmd->param_index == param_index ||
				strcmp(requestCmd->name, PARAMS_AppData.ParamTblPtr->params[i].param_data.name) == 0)
			{
				/* Init Airliner message */
				CFE_SB_InitMsg(&ParamDataMsg, PARAMS_PARAM_MID, sizeof(PARAMS_SendParamDataCmd_t), FALSE);
				CmdMsgPtr = (CFE_SB_MsgPtr_t)&ParamDataMsg;
				CFE_SB_SetCmdCode(CmdMsgPtr, PARAMS_PARAM_DATA_CC);

				/* Update parameter message with current table index values */
				ParamDataMsg.param_data.value = PARAMS_AppData.ParamTblPtr->params[i].param_data.value;
				memcpy(ParamDataMsg.param_data.name, PARAMS_AppData.ParamTblPtr->params[i].param_data.name,
						sizeof(PARAMS_AppData.ParamTblPtr->params[i].param_data.name));
				ParamDataMsg.param_data.type = PARAMS_AppData.ParamTblPtr->params[i].param_data.type;
				ParamDataMsg.param_count = PARAMS_AppData.ParamCount;
				ParamDataMsg.param_index = param_index;

				/* Send to SB */
				Status = CFE_SB_SendMsg(CmdMsgPtr);
				if (Status != CFE_SUCCESS)
				{
					OS_printf("Error sending param to SB\n");
					/* TODO: Decide what to do if the send message fails. */
				}

				break;
			}

			/* Increment the param index. Can't use loop index since not all entries are enabled */
			param_index++;
		}
	}
}

void PARAMS_UpdateParamCount()
{
	uint16 count =0;

	/* Iterate over table and count enabled entries */
	for(int i = 0; i < PARAMS_PARAM_TABLE_MAX_ENTRIES; ++i)
	{
		if (PARAMS_AppData.ParamTblPtr->params[i].enabled == 1)
		{
			count++;
		}
	}

	PARAMS_AppData.ParamCount = count;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PARAMS_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, PARAMS_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PARAMS_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case PARAMS_WAKEUP_MID:
                PARAMS_ProcessNewCmds();
                PARAMS_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                 * automatically publish new output. */
                PARAMS_SendOutData();
                break;

            case PARAMS_SEND_HK_MID:
                PARAMS_ReportHousekeeping();
                break;

            default:
                (void) CFE_EVS_SendEvent(PARAMS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid SCH msgId (0x%04X)", (unsigned short)MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
        OS_printf("Params no msg\n");
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
        OS_printf("Params timeout\n");
    }
    else
    {
        /* TODO: This is an example of exiting on an error (either CFE_SB_BAD_ARGUMENT, or
         * CFE_SB_PIPE_RD_ERROR).
         */
        (void) CFE_EVS_SendEvent(PARAMS_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "SB pipe read error (0x%08X), app will exit", (unsigned int)iStatus);
        PARAMS_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Data                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   DataMsgPtr=NULL;
    CFE_SB_MsgId_t  DataMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&DataMsgPtr, PARAMS_AppData.DataPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            DataMsgId = CFE_SB_GetMsgId(DataMsgPtr);
            switch (DataMsgId)
            {
                /* TODO:  Add code to process all subscribed data here
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         PARAMS_ProcessNavData(DataMsgPtr);
                **         break;
                */

                default:
                    (void) CFE_EVS_SendEvent(PARAMS_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(PARAMS_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "Data pipe read error (0x%08X)", (unsigned int)iStatus);
            PARAMS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, PARAMS_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case PARAMS_CMD_MID:
                    PARAMS_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    PARAMS_AppData.HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(PARAMS_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(PARAMS_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08X)", (unsigned int)iStatus);
            PARAMS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process PARAMS Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case PARAMS_NOOP_CC:
                PARAMS_AppData.HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(PARAMS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd NOOP cmd (%u), Version %d.%d.%d.%d",
                                  (unsigned int)uiCmdCode,
                                  PARAMS_MAJOR_VERSION,
                                  PARAMS_MINOR_VERSION,
                                  PARAMS_REVISION,
                                  PARAMS_MISSION_REV);
                break;

            case PARAMS_REQUEST_ALL_CC:
                PARAMS_AppData.HkTlm.usCmdCnt++;
                PARAMS_SendAllParamsToSB();
                (void) CFE_EVS_SendEvent(PARAMS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd request all cmd (%u)", (unsigned int)uiCmdCode);
                break;

            case PARAMS_REQUEST_PARAM_CC:
                PARAMS_AppData.HkTlm.usCmdCnt++;
                PARAMS_RequestSingleParam((PARAMS_RequestParamDataCmd_t *)MsgPtr);
                (void) CFE_EVS_SendEvent(PARAMS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd request specified cmd (%u)", (unsigned int)uiCmdCode);
                break;

            case PARAMS_SET_PARAM_CC:
            	PARAMS_AppData.HkTlm.usCmdCnt++;
            	PARAMS_SetParam((PARAMS_SendParamDataCmd_t *) MsgPtr);
                (void) CFE_EVS_SendEvent(PARAMS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd set param cmd (%u)", (unsigned int)uiCmdCode);
                break;

            default:
                PARAMS_AppData.HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(PARAMS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send PARAMS Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PARAMS_AppData.HkTlm);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&PARAMS_AppData.HkTlm);
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

void PARAMS_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PARAMS_AppData.OutData);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&PARAMS_AppData.OutData);
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

boolean PARAMS_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(PARAMS_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            PARAMS_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* PARAMS application entry point and main process loop               */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_AppMain()
{
    /* Register the application with Executive Services */
    PARAMS_AppData.uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("PARAMS - Failed to register the app (0x%08X)\n", (unsigned int)iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PARAMS_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = PARAMS_InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(PARAMS_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(PARAMS_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(PARAMS_MAIN_TASK_PERF_ID);
    }
    else
    {
        PARAMS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&PARAMS_AppData.uiRunStatus) == TRUE)
    {
        int32 iStatus = PARAMS_RcvMsg(PARAMS_SCH_PIPE_PEND_TIME);
        if (iStatus != CFE_SUCCESS)
        {
            /* TODO: Decide what to do for other return values in PARAMS_RcvMsg(). */
        }
        /* TODO: This is only a suggestion for when to update and save CDS table.
        ** Depends on the nature of the application, the frequency of update
        ** and save can be more or less independently.
        */
        PARAMS_UpdateCdsTbl();
        PARAMS_SaveCdsTbl();
        //PARAMS_SendAllParamsToSB();

        iStatus = PARAMS_AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            PARAMS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PARAMS_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(PARAMS_AppData.uiRunStatus);
}

/************************/
/*  End of File Comment */
/************************/
