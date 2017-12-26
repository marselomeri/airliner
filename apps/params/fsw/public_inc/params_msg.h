    
#ifndef PARAMS_MSG_H
#define PARAMS_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "mavlink.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** PARAMS Command Codes
*************************************************************************/

/** \paramscmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the PARAMS task is alive
**
**  \paramscmdmnemonic \PARAMS_NOOP
**
**  \par Command Structure
**       #PARAMS_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \PARAMS_CMDACPTCNT - command counter will increment
**       - The #PARAMS_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \PARAMS_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #PARAMS_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #PARAMS_RESET_CC
*/
#define PARAMS_NOOP_CC                 (0)

/** \paramscmd Reset Counters
**  
**  \par Description
**       Resets the params housekeeping counters
**
**  \paramscmdmnemonic \PARAMS_TLMRST
**
**  \par Command Structure
**       #PARAMS_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \PARAMS_CMDACTPCNT       - command counter will be cleared
**       - \b \c \PARAMS_CMDRJCTCNT       - command error counter will be cleared
**       - The #PARAMS_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \PARAMS_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #PARAMS_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #PARAMS_NOOP_CC
*/
#define PARAMS_RESET_CC                (1)



#define PARAMS_REQUEST_ALL_CC                 (2)

#define PARAMS_REQUEST_PARAM_CC               (3)

#define PARAMS_SET_PARAM_CC               	  (4)

#define PARAMS_PARAM_DATA_CC               	  (5)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #PARAMS_NOOP_CC, #PARAMS_RESET_CC
**  Also see #PARAMS_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} PARAMS_NoArgCmd_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific incoming data
*/
typedef struct
{
    uint8   TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices.
    **        Option: for data that is already defined by another app, include
    **        that app's message header above.
    */

} PARAMS_InData_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} PARAMS_OutData_t;


typedef struct
{
	char name[PARAMS_MSG_PARAM_NAME_LEN];
    float value;
    uint8 type;
	uint8 vehicle_id;
	uint8 component_id;
} PARAMS_ParamData_t;

/**
**  \brief MAVLINK parameter broadcast
*/
typedef struct
{
	uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint16 param_count;
    uint16 param_index;
	PARAMS_ParamData_t param_data;
} PARAMS_SendParamDataCmd_t;

/**
**  \brief MAVLINK parameter broadcast
*/
typedef struct
{
	uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint16 param_index;
    char name[PARAMS_MSG_PARAM_NAME_LEN];
} PARAMS_RequestParamDataCmd_t;

/**
**  \brief PARAMS application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \paramstlmmnemonic \PARAMS_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;

    /** \paramstlmmnemonic \PARAMS_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt;

	/** \brief  */
	boolean  ParamsInitialized;

} PARAMS_HkTlm_t;




/**
**  \brief MAVLINK parameter broadcast
*/
typedef struct
{
	uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
	char name[PARAMS_MSG_PARAM_NAME_LEN];
	uint16 param_index;
} PARAMS_GetParamCmd_t;

/**
**  \brief MAVLINK parameter broadcast
*/
typedef struct
{
	uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
	PARAMS_ParamData_t param_data;
} PARAMS_SetParamCmd_t;




#ifdef __cplusplus
}
#endif

#endif /* PARAMS_MSG_H */

/************************/
/*  End of File Comment */
/************************/
