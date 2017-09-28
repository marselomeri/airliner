#ifndef MAC_MSG_H
#define MAC_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"


/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** MAC Command Codes
*************************************************************************/

/** \maccmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the MAC task is alive
**
**  \maccmdmnemonic \MAC_NOOP
**
**  \par Command Structure
**       #MAC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \MAC_CMDACPTCNT - command counter will increment
**       - The #MAC_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \MAC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #MAC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #MAC_RESET_CC
*/
#define MAC_NOOP_CC                 (0)

/** \maccmd Reset Counters
**  
**  \par Description
**       Resets the mac housekeeping counters
**
**  \maccmdmnemonic \MAC_TLMRST
**
**  \par Command Structure
**       #MAC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \MAC_CMDACTPCNT       - command counter will be cleared
**       - \b \c \MAC_CMDRJCTCNT       - command error counter will be cleared
**       - The #MAC_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \MAC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #MAC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #MAC_NOOP_CC
*/
#define MAC_RESET_CC                (1)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #MAC_NOOP_CC, #MAC_RESET_CC
**  Also see #MAC_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} MAC_NoArgCmd_t;

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

} MAC_InData_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} MAC_OutData_t;

/** 
**  \brief MAC application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \mactlmmnemonic \MAC_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \mactlmmnemonic \MAC_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 

} MAC_HkTlm_t;


#ifdef __cplusplus
}
#endif

#endif /* MAC_MSG_H */

/************************/
/*  End of File Comment */
/************************/
