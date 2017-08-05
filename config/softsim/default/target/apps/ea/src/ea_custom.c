#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ea_custom.h"
#include "ea_platform_cfg.h"
#include "ea_app.h"
#include "ea_msg.h"

int32 EA_StartAppCustom(CFE_SB_Msg_t* MsgPtr)
{
	int32 iStatus = CFE_ES_APP_ERROR;
	EA_StartCmd_t  *CmdPtr = 0;
	uint16 ExpectedLength = sizeof(EA_StartCmd_t);

	/*
	** Verify command packet length
	*/
	if(EA_VerifyCmdLength(MsgPtr, ExpectedLength))
	{
		if(EA_AppData.HkTlm.ActiveAppPID == 0)
		{
			CmdPtr = ((EA_StartCmd_t *) MsgPtr);

			/*
			** NUL terminate the very end of the filename string as a
			** safety measure
			*/
			CmdPtr->interpreter[OS_MAX_PATH_LEN - 1] = '\0';
			CmdPtr->script[OS_MAX_PATH_LEN - 1] = '\0';

			/*
			** Check if the filename string is a nul string
			*/
			if(strlen(CmdPtr->interpreter) == 0 || strlen(CmdPtr->script) == 0)
			{
				EA_AppData.HkTlm.usCmdErrCnt++;
				CFE_EVS_SendEvent(EA_MSGLEN_ERR_EID, CFE_EVS_ERROR,
					"NUL (empty) string specified as file name");
			}
			else
			{
				/*
				** Check if specified interpreter exists
				*/
				if(access(CmdPtr->interpreter, F_OK ) != -1)
				{
					/*
					** Check if specified script exists
					*/
					if(access(CmdPtr->script, F_OK ) != -1)
					{
						/*
						** Create child process to execute app
						*/
						pid_t pid = fork();
						//int ret = -1;

						/*
						** Child process
						*/
						if (pid == 0)
						{
							char *argv[] = {CmdPtr->interpreter, CmdPtr->script, NULL};
							if(execvp(CmdPtr->interpreter, argv) == -1)
							{
								CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
													"Error starting external application");
							}
						}
						else if (pid == -1)
						{
							CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
												"Error starting new process");
						}
						/*
						** Parent process
						*/
						else
						{
							iStatus = CFE_SUCCESS;
							EA_AppData.HkTlm.usCmdCnt++;
							CFE_EVS_SendEvent(EA_INF_APP_START, CFE_EVS_INFORMATION,
												"External application started");
							strncpy(EA_AppData.HkTlm.ActiveApp, CmdPtr->script, OS_MAX_PATH_LEN);
							EA_AppData.HkTlm.ActiveAppPID = pid;
							waitpid(pid, &EA_AppData.HkTlm.LastAppStatus, 0); // Check this to be correct
							strncpy(EA_AppData.HkTlm.LastAppRun, EA_AppData.HkTlm.ActiveApp, OS_MAX_PATH_LEN);
							//EA_AppData.HkTlm.LastAppStatus = ret; // Check this to be correct
							//printf("Return code: %d\n", ret>>8); /* wait for child to exit */
						}
					}
					else
					{
						EA_AppData.HkTlm.usCmdErrCnt++;
						CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
							"Specified script does not exist");
					}
				}
				else
				{
					EA_AppData.HkTlm.usCmdErrCnt++;
					CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
						"Specified interpreter does not exist");
				}
			}
		}
		else
		{
			EA_AppData.HkTlm.usCmdErrCnt++;
			CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
				"Attempted to send start command while app already running");
		}
	}
	else
	{
		EA_AppData.HkTlm.usCmdErrCnt++;
		CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
			"Invalid command length");
	}

	return(iStatus);
}

int32 EA_TermAppCustom(CFE_SB_Msg_t* MsgPtr)
{
	char kill_cmd[80];
	uint16 ExpectedLength = sizeof(EA_NoArgCmd_t);
	int32 iStatus = CFE_ES_APP_ERROR;

	/*
	** Verify command packet length
	*/
	if(EA_VerifyCmdLength(MsgPtr, ExpectedLength))
	{
		if(EA_AppData.HkTlm.ActiveAppPID != 0)
		{
			snprintf(kill_cmd, sizeof(kill_cmd), "kill -9 %i", EA_AppData.HkTlm.ActiveAppPID);
			system(kill_cmd);

			if(EA_GetPidUtil(EA_AppData.HkTlm.ActiveAppPID) == 0)
			{
				EA_AppData.HkTlm.usCmdCnt++;
				EA_AppData.HkTlm.ActiveAppPID = 0;
				strncpy(EA_AppData.HkTlm.LastAppRun, EA_AppData.HkTlm.ActiveApp, OS_MAX_PATH_LEN);
				EA_AppData.HkTlm.LastAppStatus = -1; // TODO: Add meaningful number to this
				iStatus = CFE_SUCCESS;
			}
			else
			{
				EA_AppData.HkTlm.usCmdErrCnt++;
				CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
								"Unable to terminate application");
			}
		}
		else
		{
			EA_AppData.HkTlm.usCmdErrCnt++;
			CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
							"Attempted to terminate app while none executing");
		}
	}

	return(iStatus);
}

int32 EA_PerfmonCustom(CFE_SB_Msg_t* MsgPtr)
{
	return 0;
}

uint8 EA_GetPidUtil(int pid)
{
	return 0;
}





