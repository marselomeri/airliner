#ifndef VC_CMDS_H
#define VC_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

#include "cfe.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Definitions
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief Ground command (NO-OP)
**
**  \par Description
**       This function increments the command counter and raises an
*        event with the version of the application.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**
*************************************************************************/
void VC_NoopCmd(CFE_SB_Msg_t* MsgPtr);


/************************************************************************/
/** \brief Ground command (reset)
**
**  \par Description
**       This function initializes the command counters to 0;
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**
*************************************************************************/
void VC_ResetCmd(CFE_SB_Msg_t* MsgPtr);


/************************************************************************/
/** \brief Sends VC housekeeping message
**
**  \par Description
**       This function sends the housekeeping message
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void VC_ReportHousekeeping(CFE_SB_Msg_t* MsgPtr);


/************************************************************************/
/** \brief Ground command (start streaming)
**
**  \par Description
**       This function starts streaming video to the ground system.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
void VC_StartStreamingCmd(CFE_SB_Msg_t* MsgPtr); 



/************************************************************************/
/** \brief Ground command (stop streaming)
**
**  \par Description
**       This function stops streaming video to the ground system.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
void VC_StopStreamingCmd(CFE_SB_Msg_t* MsgPtr); 


/************************************************************************/
/** \brief Verify Command Length
**
**  \par Description
**       This function verifies the command message length.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**  \param [in]   usExpectedLen The expected length of the message
**
**  \returns
**  TRUE if the message length matches expectations, FALSE if it does not.
**  \endreturns
**
*************************************************************************/
boolean VC_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 ExpectedLength); 

#ifdef __cplusplus
}
#endif

#endif /* VC_CMDS_H */

/************************/
/*  End of File Comment */
/************************/
    
