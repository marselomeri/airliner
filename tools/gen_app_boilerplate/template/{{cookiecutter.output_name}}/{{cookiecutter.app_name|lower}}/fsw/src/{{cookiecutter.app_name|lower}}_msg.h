    
#ifndef {{cookiecutter.app_name}}_MSG_H
#define {{cookiecutter.app_name}}_MSG_H

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
** {{cookiecutter.app_name}} Command Codes
*************************************************************************/

/** \{{cookiecutter.app_name|lower}}cmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the {{cookiecutter.app_name}} task is alive
**
**  \{{cookiecutter.app_name|lower}}cmdmnemonic \{{cookiecutter.app_name}}_NOOP
**
**  \par Command Structure
**       #{{cookiecutter.app_name}}_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \{{cookiecutter.app_name}}_CMDACPTCNT - command counter will increment
**       - The #{{cookiecutter.app_name}}_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \{{cookiecutter.app_name}}_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #{{cookiecutter.app_name}}_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #{{cookiecutter.app_name}}_RESET_CC
*/
#define {{cookiecutter.app_name}}_NOOP_CC                 (0)

/** \{{cookiecutter.app_name|lower}}cmd Reset Counters
**  
**  \par Description
**       Resets the {{cookiecutter.app_name|lower}} housekeeping counters
**
**  \{{cookiecutter.app_name|lower}}cmdmnemonic \{{cookiecutter.app_name}}_TLMRST
**
**  \par Command Structure
**       #{{cookiecutter.app_name}}_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \{{cookiecutter.app_name}}_CMDACTPCNT       - command counter will be cleared
**       - \b \c \{{cookiecutter.app_name}}_CMDRJCTCNT       - command error counter will be cleared
**       - The #{{cookiecutter.app_name}}_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \{{cookiecutter.app_name}}_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #{{cookiecutter.app_name}}_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #{{cookiecutter.app_name}}_NOOP_CC
*/
#define {{cookiecutter.app_name}}_RESET_CC                (1)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #{{cookiecutter.app_name}}_NOOP_CC, #{{cookiecutter.app_name}}_RESET_CC
**  Also see #{{cookiecutter.app_name}}_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} {{cookiecutter.app_name}}_NoArgCmd_t;

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

} {{cookiecutter.app_name}}_InData_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} {{cookiecutter.app_name}}_OutData_t;

/** 
**  \brief {{cookiecutter.app_name}} application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \{{cookiecutter.app_name|lower}}tlmmnemonic \{{cookiecutter.app_name}}_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \{{cookiecutter.app_name|lower}}tlmmnemonic \{{cookiecutter.app_name}}_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 

} {{cookiecutter.app_name}}_HkTlm_t;


#ifdef __cplusplus
}
#endif

#endif /* {{cookiecutter.app_name}}_MSG_H */

/************************/
/*  End of File Comment */
/************************/
