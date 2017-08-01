
#include "to_app.h"
#include "to_custom.h"
#include "to_platform_cfg.h"
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include "to_events.h"
#include <strings.h>
#include <string.h>
#include <unistd.h>

extern TO_AppData_t TO_AppData;

#define TO_CUSTOM_RETURN_CODE_NULL_POINTER      (-1)
#define TO_CUSTOM_RETURN_CODE_MESSAGE_TOO_BIG   (-2)

#define TO_CUSTOM_MAX_MESSAGE_SIZE              (1024)

/* The following macro defines the soak time, in milliseconds.  The write
 * function will pend for that amount of time to ensure we don't try to write
 * faster than the FPGA can send the data out.
 */
#define TO_CUSTOM_WRITE_SOAK_TIME               (100) 

/* The follow macro enables the loopback test mode.  Use this to verify 
 * data is sent out the port correctly by physically connecting the outgoing
 * port to an incoming port.  For example, when using the debug RS-422 port,
 * physically cross-wire the TX and RX, like a null modem cable.  Then set the
 * TO_CUSTOM_DEV_PATH and TO_CUSTOM_LOOPABACK_DEV_PATH to the correct paths.
 * Finally, disable any applications that will open the device with the
 * loopback path.  For Build 0.1, this means disabling CI to prevent
 * collisions.
 */
//#define TO_CUSTOM_LOOPBACK_ENABLE
#define TO_CUSTOM_LOOPBACK_ERRNO_OFFSET		(-256)
#define TO_CUSTOM_LOOPBACK_SIZE_MISCOMPARE	(-2000)
#define TO_CUSTOM_LOOPBACK_CONTENT_MISCOMPARE	(-2001)

/* TODO:  Add Doxygen markup. */
#define TO_ENABLE_CHANNEL_CC                 (10)
#define TO_DISABLE_CHANNEL_CC                (11)

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8  ChannelID;
    char   DestinationAddress[INET_ADDRSTRLEN];
    uint16 DestinationPort;
} TO_EnableChannelCmd_t;

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8  ChannelID;
} TO_DisableChannelCmd_t;

typedef enum {
	/* TODO:  Add Doxygen markup. */
	TO_TLMOUTSOCKET_ERR_EID = TO_EVT_CNT,
	TO_TLMOUTENA_INF_EID,
	TO_TLMOUTENA_ERR_EID,
	TO_SOCKET_SEND_PERF_ID,
	TO_TLMOUTSTOP_ERR_EID,
    TO_CUSTOM_EVT_CNT
} TO_CustomEventIds_t;

typedef enum
{
	TO_CHANNEL_UNUSED 		= 0,
	TO_CHANNEL_DISABLED 	= 1,
	TO_CHANNEL_ENABLED 		= 2
} TO_TLM_ChannelMode_t;

typedef struct
{
	TO_TLM_ChannelMode_t	Mode;
	char					IP[INET_ADDRSTRLEN];
	uint16					DstPort;
	uint8  					Priority;
	CFE_ES_ChildTaskMainFuncPtr_t   ListenerTask;
	int  					Socket;
	uint32  				ChildTaskID;
} TO_TlmChannels_t;

typedef struct
{
	TO_TlmChannels_t		Channel[TO_MAX_OUTPUT_CHANNELS];
} TO_AppCustomData_t;


int32 TO_EnableChannel(uint8 ChannelID, const char *DestinationAddress, uint16 DestinationPort);
int32 TO_DisableChannel(uint8 ChannelID);
void TO_ListenerTask(void);



TO_AppCustomData_t TO_AppCustomData = {
	{
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 50, TO_ListenerTask, 0, 0}
	}
};



int32 TO_InitCustom(void)
{
    uint32 i = 0;

	for (i=0; i < TO_MAX_OUTPUT_CHANNELS; i++)
	{
		if(TO_AppCustomData.Channel[i].Mode == TO_CHANNEL_ENABLED)
		{
			if(TO_EnableChannel(i, TO_AppCustomData.Channel[i].IP, TO_AppCustomData.Channel[i].DstPort))
			{
				TO_AppCustomData.Channel[i].Mode = TO_CHANNEL_DISABLED;
			}
			else
			{
				CFE_EVS_SendEvent(TO_TLMOUTENA_INF_EID, CFE_EVS_INFORMATION,
						"UDP telemetry output enabled channel %u to %s:%u",
						(unsigned int)i, TO_AppCustomData.Channel[i].IP,
						(unsigned int)TO_AppCustomData.Channel[i].DstPort);
			}
		}
	}

    return 0;
}


int32 TO_SendToChannel(uint32 ChannelID, const char* Buffer, uint32 Size)
{
	static struct sockaddr_in s_addr;
    int						  status = 0;
    int32	returnCode = 0;

    bzero((char *) &s_addr, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;

    if(ChannelID < TO_MAX_OUTPUT_CHANNELS)
    {
    	TO_TlmChannels_t *channel = &TO_AppCustomData.Channel[ChannelID];

    	if(channel->Mode == TO_CHANNEL_ENABLED)
    	{
			CFE_ES_PerfLogEntry(TO_SOCKET_SEND_PERF_ID);
			/* Send message via UDP socket */
			s_addr.sin_addr.s_addr = inet_addr(channel->IP);
			s_addr.sin_port        = htons(channel->DstPort);
			status = sendto(channel->Socket, (char *)Buffer, Size, 0,
									(struct sockaddr *) &s_addr,
									 sizeof(s_addr));
			if (status < 0)
			{
				if(errno == 90)
				{
					CFE_EVS_SendEvent(TO_TLMOUTSTOP_ERR_EID,CFE_EVS_ERROR,
								   "L%d TO sendto errno %d.  Message too long.  Size=%u", __LINE__, errno, (unsigned int)Size);
				}
				else
				{
					CFE_EVS_SendEvent(TO_TLMOUTSTOP_ERR_EID,CFE_EVS_ERROR,
							   "L%d TO sendto errno %d.", __LINE__, errno);
					channel->Mode = TO_CHANNEL_DISABLED;
				}
				returnCode = -1;
			}
			CFE_ES_PerfLogExit(TO_SOCKET_SEND_PERF_ID);
    	}
    }

    return returnCode;
}



void TO_CleanupCustom(void)
{
	uint32 i = 0;

	for(i=0; i < TO_MAX_OUTPUT_CHANNELS; i++)
	{
		if(TO_AppCustomData.Channel[i].Mode == TO_CHANNEL_ENABLED)
		{

			TO_DisableChannel(i);
		}
	}
}



void TO_ProcessNewCustomCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
    	uint16 inSize = CFE_SB_GetTotalMsgLength(MsgPtr);
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);

        switch (uiCmdCode)
        {
            case TO_ENABLE_CHANNEL_CC:
            {
            	TO_EnableChannelCmd_t *cmd = (TO_EnableChannelCmd_t*) MsgPtr;
            	/* Validate arguments. */
            	if(inSize != sizeof(TO_EnableChannelCmd_t))
            	{
                    TO_AppData.HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(TO_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                                      "Invalid message length.  Received %u.  Expected %u.",
									  (unsigned int)inSize, sizeof(TO_EnableChannelCmd_t));
                    break;
            	}

            	if(TO_EnableChannel(cmd->ChannelID, cmd->DestinationAddress, cmd->DestinationPort))
            	{
                    TO_AppData.HkTlm.usCmdErrCnt++;
                    break;
            	}

                TO_AppData.HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(TO_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Enabled channel %u to %s:%u.",
								  cmd->ChannelID,
								  cmd->DestinationAddress,
								  cmd->DestinationPort);
                break;
            }

            case TO_DISABLE_CHANNEL_CC:
            {
            	TO_DisableChannelCmd_t *cmd = (TO_DisableChannelCmd_t*) MsgPtr;
            	/* Validate arguments. */
            	if(inSize != sizeof(TO_DisableChannelCmd_t))
            	{
                    TO_AppData.HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(TO_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                                      "Invalid message length.  Received %u.  Expected %u.",
									  (unsigned int)inSize, sizeof(TO_DisableChannelCmd_t));
                    break;
            	}

            	if(TO_DisableChannel(cmd->ChannelID))
            	{
                    TO_AppData.HkTlm.usCmdErrCnt++;
                    break;
            	}

                TO_AppData.HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(TO_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Disabled channel %u.",
								  cmd->ChannelID);
                break;
            }

            default:
                TO_AppData.HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(TO_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}



int32 TO_EnableChannel(uint8 ChannelID, const char *DestinationAddress, uint16 DestinationPort)
{
    int32 returnCode = 0;
    uint32 i = 0;
	struct sockaddr_in servaddr;
	int status;
	int reuseaddr=1;

	if((TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_ENABLED) &
	   (TO_AppCustomData.Channel[ChannelID].Socket != 0))
	{
		CFE_EVS_SendEvent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR,
						  "UDP telemetry for channel %u already enabled.", (unsigned int)i);
		returnCode = -1;
		goto end_of_function;
	}

	if(DestinationAddress == 0)
	{
		CFE_EVS_SendEvent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR,
						  "Destination address for channel %u is null.", (unsigned int)i);
		returnCode = -1;
		goto end_of_function;
	}

	if(ChannelID >= TO_MAX_OUTPUT_CHANNELS)
	{
		CFE_EVS_SendEvent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR,
						  "ChannelID (%u) invalid.", (unsigned int)ChannelID);
		returnCode = -1;
		goto end_of_function;
	}

	memcpy(TO_AppCustomData.Channel[ChannelID].IP, DestinationAddress, sizeof(TO_AppCustomData.Channel[ChannelID].IP));
	TO_AppCustomData.Channel[ChannelID].DstPort = DestinationPort;

    if((TO_AppCustomData.Channel[ChannelID].Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_DISABLED;
		CFE_EVS_SendEvent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR,
				   "TLM socket errno: %i on channel %u", errno, (unsigned int)i);
		returnCode = -1;
		goto end_of_function;
	}

    /* Set the Reuse Address flag.  If we don't set this flag, the socket will
     * lock the port on termination and the kernel won't unlock it until it
     * times out after a minute or so.
     */
	setsockopt(TO_AppCustomData.Channel[ChannelID].Socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

	/* Set the input arguments to the socket bind.
	 */
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port=0;
	status = bind(TO_AppCustomData.Channel[ChannelID].Socket,
			(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(status < 0)
	{
		CFE_EVS_SendEvent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR,
				   "TLM bind errno: %i on channel %u", errno, (unsigned int)i);
		TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_DISABLED;
		returnCode = -1;
		goto end_of_function;
	}

	/* Create the child listener task. */
	char TaskName[OS_MAX_API_NAME];
	snprintf(TaskName, OS_MAX_API_NAME, "TO_OUTCH_%u", ChannelID);
	returnCode = CFE_ES_CreateChildTask(
			&TO_AppCustomData.Channel[ChannelID].ChildTaskID,
	        (const char *)TaskName,
			TO_AppCustomData.Channel[ChannelID].ListenerTask,
			0,
			CFE_ES_DEFAULT_STACK_SIZE,
			TO_AppCustomData.Channel[ChannelID].Priority,
			0);

end_of_function:
	return returnCode;
}



int32 TO_DisableChannel(uint8 ChannelID)
{
    int32 returnCode = 0;
    uint32 i = 0;
	struct sockaddr_in servaddr;
	int status;
	int reuseaddr=1;

	if(TO_AppCustomData.Channel[ChannelID].Mode != TO_CHANNEL_ENABLED)
	{
		CFE_EVS_SendEvent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR,
						  "UDP telemetry for channel %u is not enabled.", (unsigned int)i);
		returnCode = -1;
		goto end_of_function;
	}

	close(TO_AppCustomData.Channel[ChannelID].Socket);

end_of_function:
	return returnCode;
}


void TO_ListenerTask(void)
{
	CFE_ES_RegisterChildTask();
    boolean continueListening = TRUE;
    int32 iStatus = CFE_SUCCESS;

	TO_TlmOutputChannelQueue_t *channel = &TO_AppData.Config.OutputChannel[0];
	CFE_SB_MsgPtr_t  msgPtr = 0;
	uint32 msgSize = 0;
	while(continueListening)
	{
		iStatus =  OS_QueueGet(
				channel->OSALQueueID,
				&msgPtr, sizeof(msgPtr), &msgSize, 1000);
		if(iStatus == OS_SUCCESS)
		{
			static struct sockaddr_in s_addr;
		    int						  status = 0;
		    int32	returnCode = 0;
		    uint16  actualMessageSize = CFE_SB_GetUserDataLength(msgPtr);

		    bzero((char *) &s_addr, sizeof(s_addr));
		    s_addr.sin_family      = AF_INET;

			CFE_ES_PerfLogEntry(TO_SOCKET_SEND_PERF_ID);
			/* Send message via UDP socket */
			s_addr.sin_addr.s_addr = inet_addr(TO_AppCustomData.Channel[0].IP);
			s_addr.sin_port        = htons(TO_AppCustomData.Channel[0].DstPort);
			status = sendto(TO_AppCustomData.Channel[0].Socket, (char *)msgPtr, actualMessageSize, 0,
									(struct sockaddr *) &s_addr,
									 sizeof(s_addr));
			if (status < 0)
			{
				if(errno == 90)
				{
					CFE_EVS_SendEvent(TO_TLMOUTSTOP_ERR_EID,CFE_EVS_ERROR,
								   "L%d TO sendto errno %d.  Message too long.  Size=%u", __LINE__, errno, (unsigned int)msgSize);
				}
				else
				{
					CFE_EVS_SendEvent(TO_TLMOUTSTOP_ERR_EID,CFE_EVS_ERROR,
							   "L%d TO sendto errno %d.", __LINE__, errno);
				}
				returnCode = -1;
			}
			CFE_ES_PerfLogExit(TO_SOCKET_SEND_PERF_ID);

			iStatus = CFE_ES_PutPoolBuf(TO_AppData.HkTlm.MemPoolHandle, (uint32 *)msgPtr);
		    if(iStatus < msgSize)
	    	{
	        	(void) CFE_EVS_SendEvent(TO_GET_POOL_ERR_EID, CFE_EVS_ERROR,
	                             "PutPoolBuf: error=%i",
	                             (int)iStatus);
	    	}

			channel->QueuedCount--;
		}
		else if(iStatus == OS_QUEUE_TIMEOUT)
		{
			/* Don't do anything.  We include a timeout so we check to see if
			 * the parent task wants us to terminate.
			 */
		}
		else
		{
			CFE_EVS_SendEvent(TO_TLM_LISTEN_ERR_EID, CFE_EVS_ERROR,
							  "Listener failed to pop message from queue. (%i).", (unsigned int)iStatus);
		}
	}

}
