#ifndef VC_CUSTOM_SHARED_H
#define VC_CUSTOM_SHARED_H
/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "vc_app.h"
#include "vc_custom.h"

/************************************************************************
** Local Defines
*************************************************************************/
/* start streaming command */
#define VC_STARTSTREAMING_CC  (2)
/* stop streaming command */
#define VC_STOPSTREAMING_CC   (3)


/************************************************************************
** Structure Declarations
*************************************************************************/
/** 
**  \brief Start Streaming Command
*/
typedef struct 
{
    uint8                  CmdHeader[CFE_SB_CMD_HDR_SIZE];
    char                   Address[VC_ADDRESS_LENGTH];
    uint16                 Port;
} VC_StartStreamCmd_t;


/* VC_CUSTOM_EVT_CNT must be defined in platform config */
typedef enum {

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a transmit resource encounters an 
**  socket error.
**
*/
    VC_SOCKET_ERR_EID = VC_EVT_CNT,
    
/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    VC_DEVICE_ERR_EID,
    
/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a start streaming command is 
**  received with a bad address command parameter.
**
*/
    VC_ADDR_ERR_EID,
    
/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a start streaming command is 
**  received with a NULL address command parameter.
**
*/
    VC_ADDR_NUL_ERR_EID,
} TO_CustomEventIds_t;

/************************************************************************
** External Global Variables
*************************************************************************/

extern VC_AppData_t VC_AppData;

#endif /* VC_CUSTOM_SHARED_H */
