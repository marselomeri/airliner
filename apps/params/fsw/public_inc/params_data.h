    
#ifndef PARAMS_DATA_H
#define PARAMS_DATA_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "params_platform_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Global Command Codes
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
#define PARAMS_REQUEST_ALL_CC                 (0)

#define PARAMS_REQUEST_PARAM_CC               (1)

#define PARAMS_SET_PARAM_CC               	  (2)

#define PARAMS_PARAM_DATA_CC               	  (3)

/************************************************************************
** Global Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #PARAMS_NOOP_CC, #PARAMS_RESET_CC
**  Also see #PARAMS_SEND_HK_MID
*/


typedef struct
{
	char name[PARAMS_MSG_PARAM_NAME_LEN];
    float value;
    uint8 type;
} PARAMS_ParamData_t;

/**
**  \brief MAVLINK parameter broadcast
*/
typedef struct
{
	uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
	PARAMS_ParamData_t param_data;
    uint16 param_count;
    uint16 param_index;
} PARAMS_SendParamDataCmd_t;

#ifdef __cplusplus
}
#endif

#endif /* PARAMS_DATA_H */

/************************/
/*  End of File Comment */
/************************/
