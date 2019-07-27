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

#include "prm_ids.h"
#include "prmlib_msgids.h"
#include "prm_lib.h"


#define CPPLIB_UNEXPECTED_MSG_ID          (-10)
#define CPPLIB_UNEXPECTED_COMMAND_CODE    (-11)



ParamsConsumer::ParamsConsumer()
{
	CFE_PSP_MemSet(&ParamRegistration, 0, sizeof(ParamRegistration));
}



ParamsConsumer::~ParamsConsumer()
{
}



int32 ParamsConsumer::InitParams(PRMLIB_ParamRegistrations_t &Params)
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



void ParamsConsumer::onParamsChange(PRMLIB_ParamRegistration_t *ParamsData, uint32 ParamsCount)
{
	OS_printf("%s %u\n", __FUNCTION__, __LINE__);
}



int32 ParamsConsumer::CheckParams(void)
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



PRMLIB_ParamRegistration_t* ParamsConsumer::GetParamRegistration(const char *Name)
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
