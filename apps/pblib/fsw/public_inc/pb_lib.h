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

/**
**  \brief Registered Serialization Data
*/
typedef struct
{
	/** \brief Message ID of serialized message */
	CFE_SB_MsgId_t 	msgId;

	/** \brief Name of serialized message data type */
	char			msgName[CFE_SB_MAX_SB_MSG_SIZE];

	/** \brief Command code for serialized message */
    uint16	 		cmdCode;
} PBLIB_RegData_t;

/**
**  \brief PB Lib Data
*/
typedef struct
{
	/** \brief Registration array for serialization functions */
	PBLIB_RegData_t RegisteredFuncs[PBLIB_REG_MAX_ENTRY];

	/** \brief Mutex for registration array */
	uint32          RegTblMutex;
}PBLIB_AppData_t;

typedef uint32 (*PBLib_DecodeFuncPtr_t)(char *, uint32, const void *);
typedef uint32 (*PBLib_EncodeFuncPtr_t)(const void *, char *, uint32);

/*************************************************************************
** Local Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief Initialize the Protobuf Library (PBLIB)
**
**  \par Description
**       Protobuf Library initialization routine. This function performs all
**       the required startup steps to initialize PBL's registration
**       array.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
**  \retstmt Return codes from #OS_MutSemCreate \endcode
**  \endreturns
**
*************************************************************************/
int32 PBLIB_LibInit(void);

/************************************************************************/
/** \brief Register Message
**
**  \par Description
**       This function adds an entry to the serialization registration
**       array.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   msgID        A #CFE_SB_MsgId_t that specifies the
**  						   message ID if of the command
**
**  \param [in]   cmdCode      A #uint16 that specifies the command code
**
**  \param [in]   msgName      A #char pointer of the message name
**
**  \returns
**  #int32 Returns 0 if successful, -1 if MsgID is invalid, or
**  -2 if array is full
**  \endreturns
*************************************************************************/
int32 PBLIB_RegisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode, char *msgName);

/************************************************************************/
/** \brief Deregister Message
**
**  \par Description
**       This function removes an entry from the serialization
**       registration array.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   msgID        A #CFE_SB_MsgId_t that specifies the
**  						   message ID if of the command
**
**  \param [in]   cmdCode      A #uint16 that specifies the command code
**
**  \returns
**  #int32 Returns 0 if successful, -1 if MsgID is invalid, or
**  -2 if MsgID with cmdCode not found
**  \endreturns
*************************************************************************/
int32 PBLIB_DeregisterMessage(CFE_SB_MsgId_t msgId, uint16 cmdCode);

/************************************************************************/
/** \brief Get Serialization Function
**
**  \par Description
**       This function looks up the address of a serialization function
**       registered with PBL.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   msgID        A #CFE_SB_MsgId_t that specifies the
**  						   message ID if of the command
**
**  \param [in]   cmdCode      A #uint16 that specifies the command code
**
**  \returns
**  #PBLib_EncodeFuncPtr_t Pointer to the serialization function address
**  or 0 if not found.
**  \endreturns
*************************************************************************/
PBLib_EncodeFuncPtr_t PBLIB_GetSerializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);

/************************************************************************/
/** \brief Get Deserialization Function
**
**  \par Description
**       This function looks up the address of a deserialization function
**       registered with PBL.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   msgID        A #CFE_SB_MsgId_t that specifies the
**  						   message ID if of the command
**
**  \param [in]   cmdCode      A #uint16 that specifies the command code
**
**  \returns
**  #PBLib_EncodeFuncPtr_t Pointer to the deserialization function address
**  or 0 if not found.
**  \endreturns
*************************************************************************/
PBLib_DecodeFuncPtr_t PBLIB_GetDeserializationFunc(CFE_SB_MsgId_t msgId, uint16 cmdCode);

/************************/
/*  End of File Comment */
/************************/
#endif
