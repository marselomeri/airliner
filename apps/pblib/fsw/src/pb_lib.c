
/*************************************************************************
** Includes
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pb_version.h"
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
	char*			msgName;
} PBLIB_RegData_t;

PBLIB_RegData_t PBLIB_RegisteredFuncs[PBLIB_REG_MAX_ENTRY];

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_LibInit(void)
{
    OS_printf ("PBLIB Initialized.  Version %d.%d.%d.%d\n",
    		PBLIB_MAJOR_VERSION,
			PBLIB_MINOR_VERSION,
			PBLIB_REVISION,
			PBLIB_MISSION_REV);

    //PBLIB_RegisteredFuncs = PBLIB_RegData_t[]

    return OS_SUCCESS;
 
}/* End PBLIB_LibInit */

// TODO: Look into hashmaps

int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, char *msgName)
{
    int32 		status = -2;

    if(msgId == 0)
    {
    	OS_printf("MsgId 0. Stop");
    	status = -1;
    	goto PBLIB_RegisterMessage_Exit_Tag;
    }

    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_RegisteredFuncs[i].msgId == 0)
    	{
    		OS_printf("Found empty idx");
    		PBLIB_RegisteredFuncs[i].msgId = msgId;
    		PBLIB_RegisteredFuncs[i].msgName = msgName;
    		status = 0;
    		break;
    	}
    }

PBLIB_RegisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_RegisterMessage */

int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId)
{
    int32 		status = -2;

    if(msgId == 0)
    {
    	OS_printf("MsgId 0. Stop");
    	status = -1;
    	goto PBLIB_DeregisterMessage_Exit_Tag;
    }

    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_RegisteredFuncs[i].msgId == msgId)
    	{
    		OS_printf("Found msg idx");
    		PBLIB_RegisteredFuncs[i].msgId = 0;
    		PBLIB_RegisteredFuncs[i].msgName = "\0";
    		status = 0;
    		break;
    	}
    }

PBLIB_DeregisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_DeregisterMessage */

void *PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId)
{
	void (*funcAddr());// = NULL;
	//funcAddr = NULL;

    if(msgId == 0)
    {
    	OS_printf("MsgId 0. Stop");
    	goto PBLIB_DeregisterMessage_Exit_Tag;
    }

    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_RegisteredFuncs[i].msgId == msgId)
    	{
    		OS_printf("Found msg idx");
    		OS_SymbolLookup(funcAddr, PBLIB_RegisteredFuncs[i].msgName);
    		break;
    	}
    }

PBLIB_DeregisterMessage_Exit_Tag:
    return funcAddr;
}/* End PBLIB_GetSerializationFunc */




/************************/
/*  End of File Comment */
/************************/

