/****************************************************************************
 *
 *   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Windhover Labs nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#include "cpp_lib.hpp"
#include "cpp_lib_version.h"
#include "prm_ids.h"
#include "prmlib_msgids.h"
#include "prm_lib.h"


#define CPPLIB_UNEXPECTED_MSG_ID          (-10)
#define CPPLIB_UNEXPECTED_COMMAND_CODE    (-11)



extern "C" int32 CPPLIB_LibInit()
{
    OS_printf ("CPP Lib Initialized.  Version %d.%d.%d.%d\n",
    		CPP_LIB_MAJOR_VERSION,
			CPP_LIB_MINOR_VERSION,
			CPP_LIB_REVISION,
			CPP_LIB_MISSION_REV);

    return OS_SUCCESS;
}



CPPApp::CPPApp()
{
	CFE_PSP_MemSet(&ParamRegistration, 0, sizeof(ParamRegistration));
}



CPPApp::~CPPApp()
{
}



int32 CPPApp::InitParams(PRMLIB_ParamRegistrations_t &Params)
{
    int32 iStatus;

    /* Init param pipe and subscribe to param messages */
    iStatus = CFE_SB_CreatePipe(&ParamPipeId,
    		Params.PipeDepth,
			Params.PipeName);
    if (iStatus != CFE_SUCCESS)
    {
        /* We failed to create the pipe for param messages.  Immediately jump
         * to the end of the function to abort initialization and return
         * the error code.
         */
        goto InitParams_Exit_Tag;
    }

    /* Subscribe to the PRMLIB_PARAM_UPDATED_MID message to receive
     * parameter requests. */
    iStatus = CFE_SB_SubscribeEx(PRMLIB_PARAM_UPDATED_MID, ParamPipeId,
            CFE_SB_Default_Qos, 1);
    if (iStatus != CFE_SUCCESS)
    {
        /* We failed to create the pipe for param messages.  Immediately jump
         * to the end of the function to abort initialization and return the
         * error code.
         */
        goto InitParams_Exit_Tag;
    }

    /* Loop through all parameters just passed to the function. */
    for(uint32 i = 0; i < PRMLIB_MAX_REGISTRATIONS; ++i)
    {
    	/* Check to see if the name is blank.  If the name is blank, we will
    	 * assume we've reached the end of the list and just terminate the
    	 * loop.
    	 */
    	if(Params.Registrations[i].Name[0] == 0)
    	{
    		/* The name is blank.  Terminate the loop. */
    		break;
    	}

        iStatus = PRMLIB_ParamRegister(Params.Registrations[i].Name,
                Params.Registrations[i].Value, Params.Registrations[i].Type);
        if(iStatus != CFE_SUCCESS)
        {
    		break;
        }

        CFE_PSP_MemCpy((void*)ParamRegistration[i].Name, (void*)Params.Registrations[i].Name, sizeof(ParamRegistration[i].Name));
        CFE_PSP_MemCpy(&ParamRegistration[i].Type, &Params.Registrations[i].Type, sizeof(ParamRegistration[i].Type));
        CFE_PSP_MemCpy(&ParamRegistration[i].Value, &Params.Registrations[i].Value, sizeof(ParamRegistration[i].Value));
    }

InitParams_Exit_Tag:

    return iStatus;
}



void CPPApp::onParamsChange(PRMLIB_ParamRegistration_t *ParamsData, uint32 ParamsCount)
{
	OS_printf("%s %u\n", __FUNCTION__, __LINE__);
}



int32 CPPApp::CheckParams(void)
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t* MsgPtr=NULL;
    CFE_SB_MsgId_t MsgId;
    bool contProcessing = true;
    PRMLIB_ParamRegistration_t paramDataOut[PRMLIB_MAX_REGISTRATIONS];
    uint32 paramsOut = 0;

    /* Process param messages until the pipe is empty */
    while (contProcessing)
    {
        iStatus = CFE_SB_RcvMsg(&MsgPtr, ParamPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            /* We did receive a message.  Process it. */
            MsgId = CFE_SB_GetMsgId(MsgPtr);
            switch (MsgId)
            {
                case PRMLIB_PARAM_UPDATED_MID:
                {
                    /* We did receive a parameter request.  Process it. */
                	PRMLIB_UpdatedParamMsg_t *paramMsg = (PRMLIB_UpdatedParamMsg_t*)MsgPtr;

                	PRMLIB_ParamRegistration_t *paramRegistration = GetParamRegistration(paramMsg->name);
                	if(paramRegistration != 0)
                	{
                		//OS_printf("Was %u\n", *((uint32*)paramRegistration->Value));
                        iStatus = PRMLIB_GetParamValueById(paramMsg->name, (cpuaddr*)paramRegistration->Value);

                        //CFE_PSP_MemSet(ParamRegistration[i].Value, 1, sizeof(ParamRegistration[i].Type));

                		//OS_printf("Is %u\n", *((uint32*)paramRegistration->Value));
                        if(iStatus != CFE_SUCCESS)
                        {
                        	contProcessing = FALSE;
                        }

                    	OS_printf("%s %u\n", __FUNCTION__, __LINE__);
                    	//CFE_PSP_MemCpy(paramData->Value, &paramData->Value, paramData->Type);
                    	CFE_PSP_MemCpy(&paramDataOut[paramsOut], paramRegistration, sizeof(paramDataOut[paramsOut]));
                    	paramsOut++;
                	}
                    break;
                }

                default:
                {
                    contProcessing = false;
                    iStatus = -1;
                    break;
                }
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            /* The pipe is empty.  Break the loop and continue on. */
            contProcessing = false;
        }
        else
        {
            /* Something failed.  Quit the loop. */
            iStatus = -2;
            contProcessing = false;
        }
    }

    if(paramsOut > 0)
    {
    	onParamsChange(paramDataOut, paramsOut);
    }

    return iStatus;
}



PRMLIB_ParamRegistration_t* CPPApp::GetParamRegistration(const char *Name)
{
	PRMLIB_ParamRegistration_t *result = 0;

    for(uint32 i = 0; i < PRMLIB_MAX_REGISTRATIONS; ++i)
    {
    	if(strncmp(ParamRegistration[i].Name, Name, sizeof(ParamRegistration[i].Name)) == 0)
    	{
    		/* The name is the same.  Return this object. */
    		result = &ParamRegistration[i];
    	}
    }

    return result;
}



void CPPApp::onReceivedUnexpectedMessageID(const char *ErrorText, CFE_SB_MsgId_t MsgID)
{
	OS_printf("CPPApp:  %s\n", ErrorText);
}



void CPPApp::onReceivedTelemetryWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgID, uint32 Length, uint32 ActualLength)
{
	OS_printf("CPPApp:  %s\n", ErrorText);
}



void CPPApp::onReceivedCommandWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgID, uint16 CmdCode, uint32 Length, uint32 ActualLength)
{
	OS_printf("CPPApp:  %s\n", ErrorText);
}



void CPPApp::onReceivedUnexpectedCommand(const char *ErrorText, CFE_SB_MsgId_t MsgID, uint16 CmdCode)
{
	OS_printf("CPPApp:  %s\n", ErrorText);
}



void CPPApp::onReceivedCommand(CFE_SB_MsgId_t MsgID, uint16 CmdCode, CFE_SB_MsgPtr_t MsgPtr)
{
	OS_printf("CPPApp:  Received command but handler is not defined.  MsgID=0x%04x  CC=%u\n", MsgID, CmdCode);
}



void CPPApp::onReceivedTelemetry(CFE_SB_MsgId_t MsgID, CFE_SB_MsgPtr_t MsgPtr)
{
	OS_printf("CPPApp:  Received telemetry but handler is not defined.  MsgID=0x%04x\n", MsgID);
}



void CPPApp::onPendPipeTimeout(void)
{
	OS_printf("CPPApp:  Pend Pipe Timeout\n");
}



void CPPApp::onPollPipeEmpty(CPPLIB_PollPipeRegistration_t *Pipe)
{
}



osalbool CPPApp::IsMsgVariableLength(CPPLIB_MsgHandlerRegistration_t *MessageRegistration)
{
	osalbool result;

	if((MessageRegistration->MsgFlags & CPPLIB_MSG_VARIABLE_LENGTH) > 0)
	{
        result = TRUE;
	}
	else
	{
        result = FALSE;
	}

	return result;
}



osalbool CPPApp::IsCommandMsg(CPPLIB_MsgHandlerRegistration_t *MessageRegistration)
{
	osalbool result;

	if((MessageRegistration->MsgFlags & CPPLIB_CMD_MSGTYPE) > 0)
	{
        result = TRUE;
	}
	else
	{
        result = FALSE;
	}

	return result;
}



int32 CPPApp::InitPipes(CPPLIB_PipeRegistrations_t &Pipe)
{
	int32 iStatus = CFE_SUCCESS;

	iStatus = InitPollPipes(Pipe.PollPipe);
	if(iStatus != CFE_SUCCESS)
	{
		return iStatus;
	}

	iStatus = InitPendPipe(&Pipe.PendPipe);

	return iStatus;
}



int32 CPPApp::InitPollPipes(CPPLIB_PollPipeRegistration_t *Pipe)
{
    int32 iStatus = CFE_SUCCESS;

    /* Clear the Pipe registry */
    CFE_PSP_MemSet(PipeRegistrations.PollPipe, 0, sizeof(PipeRegistrations.PollPipe));
    PipeRegistrations.PollPipeCount = 0;

    /* First, find out how many pipes are defined. */
    for(uint32 iPipe = 0; iPipe < CPPLIB_MAX_POLL_PIPES; ++iPipe)
    {
    	CPPLIB_PollPipeRegistration_t *pipe = &Pipe[iPipe];

        if(strncmp(pipe->PipeName, "", sizeof(pipe->PipeName)) == 0)
        {
        	/* This is the end of the pipe definition.  Break from the loop. */
        	break;
        }
        OS_printf("%s\n", pipe->PipeName);
        PipeRegistrations.PollPipeCount++;
    };

    /* Create the pipes and subscribe to messages.
     */
    for(uint32 iPipe = 0; iPipe < PipeRegistrations.PollPipeCount; ++iPipe)
    {
    	CPPLIB_PollPipeRegistration_t *pipe = &Pipe[iPipe];
    	pipe->MsgCount = 0;
    	pipe->PipeDepth = 0;

        /* Before we create the pipe, determine the pipe depth needed to
         * contain the message limits defined.
         */
        for(uint32 iMsg = 0; iMsg < CFE_SB_MAX_PIPE_DEPTH; ++iMsg)
        {
        	CPPLIB_MsgHandlerRegistration_t *msgHandler = &pipe->MsgHandler[iMsg];

        	if(msgHandler->MsgID == 0)
        	{
        		/* This is the end of the message list.  Stop looping. */
        	    break;
        	}

        	pipe->PipeDepth += msgHandler->MsgLimit;
        	pipe->MsgCount++;
        }

        /* Now that we know the minimum message depth, create the pipe. */
        iStatus = CFE_SB_CreatePipe(&pipe->PipeHandle, pipe->PipeDepth, pipe->PipeName);
        if(iStatus != CFE_SUCCESS)
        {
        	return iStatus;
        }

        /* Next, lets subscribe to all the messages. */
        for(uint32 iMsg = 0; iMsg < pipe->MsgCount; ++iMsg)
        {
        	CPPLIB_MsgHandlerRegistration_t *msgHandler = &pipe->MsgHandler[iMsg];

            iStatus = CFE_SB_SubscribeEx(msgHandler->MsgID, pipe->PipeHandle, CFE_SB_Default_Qos, msgHandler->MsgLimit);
            //if(iStatus != CFE_SUCCESS)
            //{
            //	return iStatus;
            //}

    		OS_printf("0x%04x\n", msgHandler->MsgID);
        }

        /* Lastly, lets copy the pipe definition list to a private structure. */
        CFE_PSP_MemCpy(&PipeRegistrations.PollPipe[iPipe], pipe, sizeof(PipeRegistrations.PollPipe[iPipe]));
    };

    return iStatus;
}



int32 CPPApp::InitPendPipe(CPPLIB_PendPipeRegistration_t *Pipe)
{
    int32 iStatus = CFE_SUCCESS;
    uint32 msgCount = 0;

    /* Clear the Pend Pipe registry */
    CFE_PSP_MemSet(&PipeRegistrations.PendPipe, 0, sizeof(PipeRegistrations.PendPipe));

    /* Create the pipe and subscribe to messages, but before we create the pipe,
     * determine the pipe depth needed to contain the message limits defined. */
    Pipe->PipeDepth = 0;
	for(uint32 iMsg = 0; iMsg < CFE_SB_MAX_PIPE_DEPTH; ++iMsg)
	{
		CPPLIB_MsgHandlerRegistration_t *msgHandler = &Pipe->MsgHandler[iMsg];

		if(msgHandler->MsgID == 0)
		{
			/* This is the end of the message list.  Stop looping. */
			break;
		}

		Pipe->PipeDepth += msgHandler->MsgLimit;
		msgCount++;
	}

    /* Now that we know the minimum message depth, create the pipe. */
    iStatus = CFE_SB_CreatePipe(&Pipe->PipeHandle, Pipe->PipeDepth, Pipe->PipeName);
    if(iStatus != CFE_SUCCESS)
    {
        return iStatus;
    }

	/* Next, lets subscribe to all the messages. */
	for(uint32 iMsg = 0; iMsg < msgCount; ++iMsg)
	{
		CPPLIB_MsgHandlerRegistration_t *msgHandler = &Pipe->MsgHandler[iMsg];

		iStatus = CFE_SB_SubscribeEx(msgHandler->MsgID, Pipe->PipeHandle, CFE_SB_Default_Qos, msgHandler->MsgLimit);
		if(iStatus != CFE_SUCCESS)
		{
			return iStatus;
		}
	}

    /* Lastly, lets copy the pipe definition list to a private structure. */
    CFE_PSP_MemCpy(&PipeRegistrations.PendPipe, Pipe, sizeof(PipeRegistrations.PendPipe));

    return iStatus;
}



int32 CPPApp::ProcessPollPipes(void)
{
	int32 iStatus;

	for(uint32 i = 0; i < PipeRegistrations.PollPipeCount; ++i)
	{
		CPPLIB_PollPipeRegistration_t *pipe = &PipeRegistrations.PollPipe[i];
		iStatus = ProcessPollPipe(pipe);
		if(iStatus != CFE_SUCCESS)
		{
			return iStatus;
		}
	}

	return iStatus;
}



int32 CPPApp::ProcessPollPipe(const char *PipeName)
{
	int32 iStatus = -1;

	for(uint32 i = 0; i < PipeRegistrations.PollPipeCount; ++i)
	{
		CPPLIB_PollPipeRegistration_t *pipe = &PipeRegistrations.PollPipe[i];
		if(strncmp(pipe->PipeName, PipeName, sizeof(pipe->PipeName)) == 0)
		{
			iStatus = ProcessPollPipe(pipe);
		}
	}

	return iStatus;
}



int32 CPPApp::IsCommandMsg(CFE_SB_MsgPtr_t MsgPtr, osalbool *isCommand)
{
    if((CCSDS_RD_TYPE(MsgPtr->Hdr) == CCSDS_TLM)||(CCSDS_RD_SHDR(MsgPtr->Hdr) == 0))
    {
        *isCommand = FALSE;
    }
    else
    {
    	*isCommand = TRUE;
    }

    return CFE_SUCCESS;
}



int32 CPPApp::ProcessPollPipe(CPPLIB_PollPipeRegistration_t *Pipe)
{
    int32           iStatus = CFE_SUCCESS;
    CFE_SB_MsgPtr_t MsgPtr = NULL;
    CFE_SB_MsgId_t  MsgID;
    uint32          msgCount = 0;

    for(uint32 i = 0; i < Pipe->PipeDepth; ++i)
    {
        iStatus = CFE_SB_RcvMsg(&MsgPtr, Pipe->PipeHandle, CFE_SB_POLL);

        if(iStatus == CFE_SUCCESS)
        {
    	    CFE_SB_MsgId_t msgID = CFE_SB_GetMsgId(MsgPtr);
        	CPPLIB_MsgHandlerRegistration_t *msgReg;

        	iStatus = GetPollMessageRegistration(MsgPtr, Pipe, &msgReg);
        	switch(iStatus)
        	{
        	    case CPPLIB_UNEXPECTED_MSG_ID:
        	    {
            		char errorText[CFE_EVS_MAX_MESSAGE_LENGTH];
            		sprintf(errorText, "Received unexpected message ID 0x%04x", msgID);
                    onReceivedUnexpectedMessageID((const char*)errorText, msgID);
                    break;
        	    }

        	    case CPPLIB_UNEXPECTED_COMMAND_CODE:
        	    {
            		char errorText[CFE_EVS_MAX_MESSAGE_LENGTH];
    		        uint16 cmdCode = CFE_SB_GetCmdCode(MsgPtr);
            		sprintf(errorText, "Received unexpected command.  MsgID=0x%04x  CC=%u\n", msgID, cmdCode);
            		onReceivedUnexpectedCommand(errorText, msgID, cmdCode);
                    break;
        	    }

        	    default:
        	    {
        	    	osalbool acceptMessage = FALSE;
        	    	osalbool isCommand = IsCommandMsg(msgReg);

        	    	/* This is one of the messages we registered for.  Is the message variable
        	    	 * length?
        	    	 */
        	    	if(IsMsgVariableLength(msgReg) == TRUE)
        	    	{
        	    		/* This is variable length, just send it unchecked. */
        	    		acceptMessage = TRUE;
        	    		OS_printf("%s %u\n", __FUNCTION__, __LINE__);
        	    	}
        	    	else
        	    	{
        	    		/* This is fixed length.  Validate the message length. */
            	    	uint16 length = CFE_SB_GetTotalMsgLength(MsgPtr);

            	    	if(length != msgReg->Length)
            	    	{
            	    		/* This is the incorrect length. */
                    		char errorText[CFE_EVS_MAX_MESSAGE_LENGTH];

            	    		if(isCommand == TRUE)
            	    		{
            	    			onReceivedCommandWithIncorrectLength(errorText, msgID, msgReg->CmdCode, msgReg->Length, length);
            	    		}
            	    		else
            	    		{
            	    			onReceivedTelemetryWithIncorrectLength(errorText, msgID, msgReg->Length, length);
            	    		}
            	    	}
            	    	else
            	    	{
            	    		/* The length is correct. */
            	    		acceptMessage = TRUE;
            	    	}
        	    	}

                    /* Is it ok to forward the message to the super class? */
        	    	if(acceptMessage == TRUE)
    	    		{
        	    		if(isCommand == TRUE)
    					{
        	    			OS_printf("%s %u\n", __FUNCTION__, __LINE__);
    						onReceivedCommand(msgID, msgReg->CmdCode, MsgPtr);
    					}
    					else
    					{
    						onReceivedTelemetry(msgID, MsgPtr);
        	    		}
    	    		}
        	    }
        	}

        	msgCount++;
		}
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
        	iStatus = CFE_SUCCESS;
        	/* Pipe is empty.  Stop looping. */
        	if(msgCount == 0)
        	{
        		onPollPipeEmpty(Pipe);
        	}
        	break;
		}
        else
        {
            /* TODO */
        }
    }

    return iStatus;
}



int32 CPPApp::GetPollMessageRegistration(CFE_SB_MsgPtr_t MsgPtr, CPPLIB_PollPipeRegistration_t *Pipe, CPPLIB_MsgHandlerRegistration_t **MessageRegistration)
{
	int32 iStatus = CPPLIB_UNEXPECTED_MSG_ID;
    CFE_SB_MsgId_t  MsgID;
    osalbool isCommand = FALSE;
    osalbool msgIDFound = FALSE;

    /* Set the MessageRegistration to zero in case we don't find the registration. */
    *MessageRegistration = 0;

    MsgID = CFE_SB_GetMsgId(MsgPtr);

    IsCommandMsg(MsgPtr, &isCommand);

    if((CCSDS_RD_TYPE(MsgPtr->Hdr) == CCSDS_TLM)||(CCSDS_RD_SHDR(MsgPtr->Hdr) == 0))
    {
        isCommand = FALSE;
    }
    else
    {
    	isCommand = TRUE;
    }

	for(uint32 i = 0; i < Pipe->MsgCount; ++i)
	{
		if(Pipe->MsgHandler[i].MsgID == MsgID)
		{
			/* This is the same message ID. */
			msgIDFound = TRUE;

			/* Is this a command? */
			if(isCommand == TRUE)
			{
				/* This is a command.  Is this the right command code? */
		        uint16 cmdCode = CFE_SB_GetCmdCode(MsgPtr);

		        if(cmdCode == Pipe->MsgHandler[i].CmdCode)
		        {
		        	/* This is the right command code.  Return this object. */
		        	*MessageRegistration = &Pipe->MsgHandler[i];
		        	iStatus = CFE_SUCCESS;
		        }
			}
	        else
	        {
				/* This is telemetry.  Return this object. */
	        	*MessageRegistration = &Pipe->MsgHandler[i];
	        	iStatus = CFE_SUCCESS;
	        }
		}
	}

	if(msgIDFound == TRUE)
	{
		if(iStatus != CFE_SUCCESS)
		{
			/* We found the Message ID, but this must have been a command and
			 * we didn't find the command code.
			 */
			iStatus = CPPLIB_UNEXPECTED_COMMAND_CODE;
		}
	}

	return iStatus;
}



int32 CPPApp::PendOnPendPipe(CFE_SB_MsgId_t &MsgID, CFE_SB_MsgPtr_t MsgPtr)
{
    int32 iStatus;

    /* Wait for pended messages */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, PipeRegistrations.PendPipe.PipeHandle, PipeRegistrations.PendPipe.TimeOut);
    if(iStatus == CFE_SUCCESS)
    {
        MsgID = CFE_SB_GetMsgId(MsgPtr);
    }
    else
    {
    	if(iStatus == CFE_SB_TIME_OUT)
    	{
    		onPendPipeTimeout();
        }

    	MsgID = 0;
    }

    return iStatus;
}


