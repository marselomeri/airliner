#ifndef VC_MSG_H
#define VC_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "vc_platform_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** VC Command Codes
*************************************************************************/

/** \vccmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the VC task is alive
**
**  \vccmdmnemonic \VC_NOOP
**
**  \par Command Structure
**       #VC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \VC_CMDACPTCNT - command counter will increment
**       - The #VC_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \VC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #VC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #VC_RESET_CC
*/
#define VC_NOOP_CC            (0)

/** \vccmd Reset Counters
**  
**  \par Description
**       Resets the vc housekeeping counters
**
**  \vccmdmnemonic \VC_TLMRST
**
**  \par Command Structure
**       #VC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \VC_CMDACTPCNT       - command counter will be cleared
**       - \b \c \VC_CMDRJCTCNT       - command error counter will be cleared
**       - The #VC_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \VC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #VC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #VC_NOOP_CC
*/
#define VC_RESET_CC           (1)
/* start streaming command */
#define VC_STARTSTREAMING_CC  (2)
/* stop streaming command */
#define VC_STOPSTREAMING_CC   (3)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #VC_NOOP_CC, #VC_RESET_CC
**  Also see #VC_SEND_HK_MID
*/
typedef struct
{
    uint8                 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} VC_NoArgCmd_t;


/** 
**  \brief VC application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8                 TlmHeader[CFE_SB_TLM_HDR_SIZE];
    /* Command interface counters */
    /** \vctlmmnemonic \VC_CMDACPTCNT
    \brief Count of accepted commands */
    uint8                 usCmdCnt;
    /** \vctlmmnemonic \VC_CMDRJCTCNT
    \brief Count of failed commands */
    uint8                 usCmdErrCnt;
    /** \brief VC App State */
    uint8                 State;
} VC_HkTlm_t;


/** 
**  \brief Start Streaming Command
*/
typedef struct 
{
    uint8                  CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint16                 Port;
    char                   Address[VC_ADDRESS_LENGTH];
} VC_StartStreamCmd_t;


#ifdef __cplusplus
}
#endif

#endif /* VC_MSG_H */

/************************/
/*  End of File Comment */
/************************/

