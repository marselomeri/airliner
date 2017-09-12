    
#ifndef PMC_MSG_H
#define PMC_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** PMC Command Codes
*************************************************************************/

/** \pmccmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the PMC task is alive
**
**  \pmccmdmnemonic \PMC_NOOP
**
**  \par Command Structure
**       #PMC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \PMC_CMDACPTCNT - command counter will increment
**       - The #PMC_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \PMC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #PMC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #PMC_RESET_CC
*/
#define PMC_NOOP_CC                 (0)

/** \pmccmd Reset Counters
**  
**  \par Description
**       Resets the pmc housekeeping counters
**
**  \pmccmdmnemonic \PMC_TLMRST
**
**  \par Command Structure
**       #PMC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \PMC_CMDACTPCNT       - command counter will be cleared
**       - \b \c \PMC_CMDRJCTCNT       - command error counter will be cleared
**       - The #PMC_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \PMC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #PMC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #PMC_NOOP_CC
*/
#define PMC_RESET_CC                (1)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #PMC_NOOP_CC, #PMC_RESET_CC
**  Also see #PMC_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} PMC_NoArgCmd_t;

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

} PMC_InData_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} PMC_OutData_t;

/** 
**  \brief PMC application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \pmctlmmnemonic \PMC_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \pmctlmmnemonic \PMC_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 

} PMC_HkTlm_t;


#ifdef __cplusplus
}
#endif

#endif /* PMC_MSG_H */

/************************/
/*  End of File Comment */
/************************/
