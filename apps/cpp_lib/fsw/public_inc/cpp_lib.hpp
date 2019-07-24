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

#ifndef CPP_LIB_H
#define CPP_LIB_H

#include "cfe.h"
#include "prm_lib.h"



#define PRMLIB_MAX_REGISTRATIONS     (50)

#define CPPLIB_MAX_POLL_PIPES        (10)
#define CPPLIB_MAX_MESSAGES_PER_PIPE (CFE_SB_MAX_PIPE_DEPTH)



extern "C" int32 CPPLIB_LibInit(void);


typedef struct
{
	char         	   Name[PRMLIB_MSG_PARAM_NAME_LEN];
    void*              Value;
    PRMLIB_ParamType_t Type;
} PRMLIB_ParamRegistration_t;

typedef struct
{
	const char                 PipeName[OS_MAX_API_NAME];
	uint32                     PipeDepth;
	PRMLIB_ParamRegistration_t Registrations[PRMLIB_MAX_REGISTRATIONS];
} PRMLIB_ParamRegistrations_t;



/* Return values for MD_SearchCmdHndlrTbl routine used to process commands */
#define CPPLIB_BAD_CMD_CODE (-1)
#define CPPLIB_BAD_MSG_ID   (-2)

typedef enum
{
	CPPLIB_TLM_MSGTYPE         = 0, /**< \brief Message Type (requires Message ID match) */
	CPPLIB_CMD_MSGTYPE         = 1, /**< \brief Command Type (requires Message ID and Command Code match) */
	CPPLIB_MSG_VARIABLE_LENGTH = 2  /**< \brief Message is variable length.  CPPLIB will not automatically validate message lengths of variable length messages. */
} CPPLIB_MsgFlags_t;

/*
** Data structure of a single record in CPPLIB_MsgHandlerTbl which defines a single message handler.
*/
typedef struct
{
	CFE_SB_MsgId_t             MsgID;             /**< \brief Message ID */
    uint32                     MsgLimit;          /**< \brief Message limit for contained pipe */
    uint16                     CmdCode;           /**< \brief Command Code */
    uint32                     Length;            /**< \brief Message Length (in bytes) including message header */
    uint32                     MsgFlags;          /**< \brief Message Flags (i.e. - is message variable length)   */
} CPPLIB_MsgHandlerRegistration_t;

/*
** Data structure of a single record in CPPLIB_PipeTblRec_t which defines a single message pipe.
*/
typedef struct
{
    char                            PipeName[OS_MAX_API_NAME]; /**< \brief Pipe Name.  Maximum length is #OS_MAX_API_NAME characters. */
    uint32                          TimeOut;  /**< \brief The number of milliseconds to wait for a new message if the
                                                    pipe is empty at the time of the call.  This can also be set
                                                    to #CFE_SB_PEND_FOREVER to wait forever for a message to arrive. */
    CPPLIB_MsgHandlerRegistration_t MsgHandler[CFE_SB_MAX_PIPE_DEPTH]; /**< \brief Message handlers array.  Maximum size is #CFE_SB_MAX_PIPE_DEPTH messages. */
    CFE_SB_PipeId_t                 PipeHandle; /**< \brief Pipe Handle.  This is set by CPP LIB when the pipes are initialized. */
    uint32                          PipeDepth;
} CPPLIB_PendPipeRegistration_t;

/*
** Data structure of a single record in CPPLIB_PipeTblRec_t which defines a single message pipe.
*/
typedef struct
{
    char                            PipeName[OS_MAX_API_NAME]; /**< \brief Pipe Name.  Maximum length is #OS_MAX_API_NAME characters. */
    CPPLIB_MsgHandlerRegistration_t MsgHandler[CFE_SB_MAX_PIPE_DEPTH]; /**< \brief Message handlers array.  Maximum size is #CFE_SB_MAX_PIPE_DEPTH messages. */
    CFE_SB_PipeId_t                 PipeHandle; /**< \brief Pipe Handle.  This is set by CPP LIB when the pipes are initialized. */
    uint32                          PipeDepth;
    uint32                          MsgCount;
} CPPLIB_PollPipeRegistration_t;

/*
** Data structure of a single record in CPPLIB_PipeRegistrations_t which defines a single message pipe.
*/
typedef struct
{
	CPPLIB_PendPipeRegistration_t PendPipe;
	CPPLIB_PollPipeRegistration_t PollPipe[CPPLIB_MAX_POLL_PIPES];
	uint32                        PollPipeCount;
} CPPLIB_PipeRegistrations_t;



class CPPApp
{
    public:
	    CPPApp();
	    ~CPPApp();

        PRMLIB_ParamRegistration_t* GetParamRegistration(const char *Name);
	    int32 InitParams(PRMLIB_ParamRegistrations_t &Params);
	    int32 CheckParams(void);
        virtual void onParamsChange(PRMLIB_ParamRegistration_t *ParamsData, uint32 ParamsCount);

	    int32 InitPipes(CPPLIB_PipeRegistrations_t &Pipe);
	    int32 ProcessPollPipes(void);
	    int32 ProcessPollPipe(const char *PipeName);
	    int32 PendOnPendPipe(CFE_SB_MsgId_t &MsgId, CFE_SB_MsgPtr_t MsgPtr);
	    int32 IsCommandMsg(CFE_SB_MsgPtr_t MsgPtr, osalbool *isCommand);
        virtual void onReceivedUnexpectedMessageID(const char *ErrorText, CFE_SB_MsgId_t MsgId);
        virtual void onReceivedTelemetryWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint32 Length, uint32 ActualLength);
        virtual void onReceivedCommandWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint16 CmdCode, uint32 Length, uint32 ActualLength);
        virtual void onReceivedUnexpectedCommand(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint16 CmdCode);
        virtual void onReceivedCommand(CFE_SB_MsgId_t MsgID, uint16 CmdCode, CFE_SB_MsgPtr_t MsgPtr);
        virtual void onReceivedTelemetry(CFE_SB_MsgId_t MsgId, CFE_SB_MsgPtr_t MsgPtr);
        virtual void onPendPipeTimeout(void);
        virtual void onPollPipeEmpty(CPPLIB_PollPipeRegistration_t *Pipe);

    private:
	    int32 InitPollPipes(CPPLIB_PollPipeRegistration_t *Pipes);
	    int32 InitPendPipe(CPPLIB_PendPipeRegistration_t *Pipe);
	    int32 ProcessPollPipe(CPPLIB_PollPipeRegistration_t *Pipe);
	    int32 GetPollMessageRegistration(CFE_SB_MsgPtr_t MsgPtr, CPPLIB_PollPipeRegistration_t *Pipe, CPPLIB_MsgHandlerRegistration_t **MessageRegistration);
        osalbool IsMsgVariableLength(CPPLIB_MsgHandlerRegistration_t *MessageRegistration);
        osalbool IsCommandMsg(CPPLIB_MsgHandlerRegistration_t *MessageRegistration);

        /** \brief Param Pipe ID */
        CFE_SB_PipeId_t            ParamPipeId;
        PRMLIB_ParamRegistration_t ParamRegistration[PRMLIB_MAX_REGISTRATIONS];

        CPPLIB_PipeRegistrations_t PipeRegistrations;

    protected:
};



#endif /* CPP_LIB_H */

/************************/
/*  End of File Comment */
/************************/
