#ifndef _pc_lib_h_
#define _pc_lib_h_

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
