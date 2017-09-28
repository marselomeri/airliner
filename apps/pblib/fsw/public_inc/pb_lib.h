/****************************************************************************
 *
 *   Copyright (c) 2016 Windhover Labs, L.L.C. All rights reserved.
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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 ****************************************************************************/

#ifndef PC_LIB_H
#define PC_LIB_H

/*************************************************************************
** Includes
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfe.h"

/*************************************************************************
** Macro Definitions
*************************************************************************/
#define PBLIB_REG_MAX_ENTRY  (100)
#define PBLIB_REGTBL_MUTEX_NAME ("PBLIB_REGTBL_MUTEX")

/************************************************************************
** Local Structure Definitions
*************************************************************************/

typedef struct
{
	CFE_SB_MsgId_t 	msgId;
	char			msgName[CFE_SB_MAX_SB_MSG_SIZE]; // TODO: Should use smaller?
    uint16	 		cmdCode;
} PBLIB_RegData_t;

typedef struct
{
	/** \brief registration table for serialization functions */
	PBLIB_RegData_t RegisteredFuncs[PBLIB_REG_MAX_ENTRY];

	/** \brief Mutex for registration table */
	uint32          RegTblMutex;
}PBLIB_AppData_t;

typedef uint32 (*PBLib_DecodeFuncPtr_t)(char *, uint32, const void *);
typedef uint32 (*PBLib_EncodeFuncPtr_t)(const void *, char *, uint32);

/*************************************************************************
** Local Function Prototypes
*************************************************************************/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_LibInit(void);


int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode, char *msgName);


int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode);


PBLib_EncodeFuncPtr_t PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);


PBLib_DecodeFuncPtr_t PBLIB_GetDeserializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);

/************************/
/*  End of File Comment */
/************************/
#endif
