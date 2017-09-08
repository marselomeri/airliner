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

/*************************************************************************
** Private Function Prototypes
*************************************************************************/


typedef struct
{
	CFE_SB_MsgId_t 	msgId;
	char			msgName[CFE_SB_MAX_SB_MSG_SIZE]; // TODO: Should use smaller?
    uint16	 		cmdCode;
} PBLIB_RegData_t;

//
PBLIB_RegData_t PBLIB_RegisteredFuncs[PBLIB_REG_MAX_ENTRY];

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_LibInit(void);


int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode, char *msgName);


int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode);


uint32 *PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);


uint32 *PBLIB_GetDeserializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);

/************************/
/*  End of File Comment */
/************************/
#endif
