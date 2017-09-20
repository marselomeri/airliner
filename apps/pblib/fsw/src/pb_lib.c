/*************************************************************************
** Includes
*************************************************************************/

#include "pb_lib.h"
#include "pb_version.h"

PBLIB_AppData_t PBLIB_AppData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_LibInit(void)
{
	int32 Status = CFE_SUCCESS;

	/* Create mutex for registration table */
	Status = OS_MutSemCreate(&PBLIB_AppData.RegTblMutex, PBLIB_REGTBL_MUTEX_NAME, 0);
	if (Status != CFE_SUCCESS)
	{
		goto PBLIB_LibInit_Exit_Tag;
	}

PBLIB_LibInit_Exit_Tag:
	if (Status == CFE_SUCCESS)
	{
		OS_printf ("PBLIB Initialized.  Version %d.%d.%d.%d\n",
    		PBLIB_MAJOR_VERSION,
			PBLIB_MINOR_VERSION,
			PBLIB_REVISION,
			PBLIB_MISSION_REV);
	}

    return Status;
 
}/* End PBLIB_LibInit */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Register Message		                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode, char *msgName)
{
    int32 		status = -2;

    if(msgId == 0)
    {
    	status = -1;
    	goto PBLIB_RegisterMessage_Exit_Tag;
    }

    /* Lock the mutex */
	OS_MutSemTake(PBLIB_AppData.RegTblMutex);

	/* Find an empty registration entry */
    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_AppData.RegisteredFuncs[i].msgId == 0)
    	{
    		PBLIB_AppData.RegisteredFuncs[i].msgId = msgId;
    		PBLIB_AppData.RegisteredFuncs[i].cmdCode = cmdCode;
    		strcpy(PBLIB_AppData.RegisteredFuncs[i].msgName, msgName);
    		status = 0;
    		break;
    	}
    }

    /* Unlock the mutex */
	OS_MutSemGive(PBLIB_AppData.RegTblMutex);

PBLIB_RegisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_RegisterMessage */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Deregister Message		                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode)
{
    int32 		status = -2;

    if(msgId == 0)
    {
    	status = -1;
    	goto PBLIB_DeregisterMessage_Exit_Tag;
    }

    /* Lock the mutex */
	OS_MutSemTake(PBLIB_AppData.RegTblMutex);

	/* Find the registration entry */
    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_AppData.RegisteredFuncs[i].msgId == msgId && PBLIB_AppData.RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		PBLIB_AppData.RegisteredFuncs[i].msgId = 0;
    		PBLIB_AppData.RegisteredFuncs[i].cmdCode = 0;
    		strcpy(PBLIB_AppData.RegisteredFuncs[i].msgName, "\0");
    		status = 0;
    		break;
    	}
    }

    /* Unlock the mutex */
	OS_MutSemGive(PBLIB_AppData.RegTblMutex);

PBLIB_DeregisterMessage_Exit_Tag:
    return status;
}/* End PBLIB_DeregisterMessage */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get Serialization Function Address                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
PBLib_EncodeFuncPtr_t PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode)
{
	PBLib_EncodeFuncPtr_t funcAddr = 0;
	char encFuncName[64];
	int32 status = 0;

    if(msgId == 0)
    {
    	goto PBLIB_GetSerializationFunc_Exit_Tag;
    }

    /* Lock the mutex */
	OS_MutSemTake(PBLIB_AppData.RegTblMutex);

	/* Find the registration entry */
    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_AppData.RegisteredFuncs[i].msgId == msgId && PBLIB_AppData.RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		strcpy(encFuncName, PBLIB_AppData.RegisteredFuncs[i].msgName);
			strcat(encFuncName, "_Enc");
			status = OS_SymbolLookup((cpuaddr*)&funcAddr, (const char*)&encFuncName);
    		break;
    	}
    }

    /* Unlock the mutex */
	OS_MutSemGive(PBLIB_AppData.RegTblMutex);


PBLIB_GetSerializationFunc_Exit_Tag:
    return funcAddr;
}/* End PBLIB_GetSerializationFunc */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get Deserialization Function Address                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
PBLib_DecodeFuncPtr_t PBLIB_GetDeserializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode)
{
	PBLib_DecodeFuncPtr_t funcAddr = 0;
	char decFuncName[64];
	int32 status = 0;

    if(msgId == 0)
    {
    	goto PBLIB_GetDeserializationFunc_Exit_Tag;
    }

    /* Lock the mutex */
	OS_MutSemTake(PBLIB_AppData.RegTblMutex);

    /* Find the registration entry */
    for(int i = 0; i < PBLIB_REG_MAX_ENTRY; ++i)
    {
    	if(PBLIB_AppData.RegisteredFuncs[i].msgId == msgId && PBLIB_AppData.RegisteredFuncs[i].cmdCode == cmdCode)
    	{
    		strcpy(decFuncName, PBLIB_AppData.RegisteredFuncs[i].msgName);
			strcat(decFuncName, "_Dec");
    		status = OS_SymbolLookup((cpuaddr*)&funcAddr, (const char*)&decFuncName);
    		break;
    	}
    }

    /* Unlock the mutex */
	OS_MutSemGive(PBLIB_AppData.RegTblMutex);

PBLIB_GetDeserializationFunc_Exit_Tag:
    return funcAddr;
}/* End PBLIB_GetSerializationFunc */

/************************/
/*  End of File Comment */
/************************/
