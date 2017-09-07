
/*************************************************************************
** Includes
*************************************************************************/

#include "pb_lib.h"
#include "pb_version.h"

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

int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode, char *msgName)
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
    		PBLIB_RegisteredFuncs[i].cmdCode = cmdCode;
    		strcpy(PBLIB_RegisteredFuncs[i].msgName, msgName);
    		status = 0;
    		break;
    	}
    }

PBLIB_RegisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_RegisterMessage */

int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode)
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
    	if(PBLIB_RegisteredFuncs[i].msgId == msgId && PBLIB_RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		OS_printf("Found msg idx");
    		PBLIB_RegisteredFuncs[i].msgId = 0;
    		PBLIB_RegisteredFuncs[i].cmdCode = 0;
    		strcpy(PBLIB_RegisteredFuncs[i].msgName, "\0");
    		status = 0;
    		break;
    	}
    }

PBLIB_DeregisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_DeregisterMessage */

uint32 *PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode)
{
	//void (*funcAddr)(const void *, char *, uint32) = NULL;
	uint32 *funcAddr = 0;

    if(msgId == 0)
    {
    	OS_printf("MsgId 0. Stop");
    	goto PBLIB_GetSerializationFunc_Exit_Tag;
    }

    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_RegisteredFuncs[i].msgId == msgId && PBLIB_RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		OS_printf("Found msg idx");
    		OS_SymbolLookup(funcAddr, strcat(PBLIB_RegisteredFuncs[i].msgName, "_Enc"));
    		break;
    	}
    }

PBLIB_GetSerializationFunc_Exit_Tag:
    return funcAddr;
}/* End PBLIB_GetSerializationFunc */

int32 OS_SymbolLookupTest( uint32 *SymbolAddress, const char *SymbolName )
{
   OS_printf("Looking up SYMBOL %s\n", SymbolName);

   return(OS_SUCCESS);

}/* end OS_SymbolLookup */

uint32 *PBLIB_GetDeserializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode)
{
	//void (*funcAddr)(const void *, char *, uint32) = NULL;
	uint32 *funcAddr = 0;
	char decFuncName[64];


    if(msgId == 0)
    {
    	OS_printf("MsgId 0. Stop");
    	goto PBLIB_GetDeserializationFunc_Exit_Tag;
    }

    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_RegisteredFuncs[i].msgId == msgId && PBLIB_RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		strcpy(decFuncName, PBLIB_RegisteredFuncs[i].msgName);
			strcat(decFuncName, "_Dec");
    		OS_printf("Found msg idx\n");
    		OS_printf("Looking up %s\n", decFuncName);
    		OS_SymbolLookupTest(funcAddr, &decFuncName);
    		break;
    	}
    }

PBLIB_GetDeserializationFunc_Exit_Tag:
    return funcAddr;
}/* End PBLIB_GetSerializationFunc */





/************************/
/*  End of File Comment */
/************************/

