#ifndef VC_CUSTOM_H
#define VC_CUSTOM_H


/************************************************************************/
/** \brief Video Control Task custom application commands
**
**  \par Description
**       This function processes custom command messages
**       specific to the VC application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr       A #CFE_SB_Msg_t pointer that
**                             references the software bus message
**
*************************************************************************/
void VC_ProcessNewCustomCmds(CFE_SB_Msg_t* MsgPtr);


/************************************************************************/
/** \brief Custom function to initialize custom events. 
**
**  \par Description
**       This function is called in init event before CFE_EVS_Register
**       to add custom events to the event filter table.
**
**  \par Assumptions, External Events, and Notes:
**       This function must be defined, but not all custom
**       layers will do anything in this function.
**
**  \returns
**       The number of events written to the filter table and -1 for 
**       failure i.e. CFE_EVS_MAX_EVENT_FILTERS reached.
**
*************************************************************************/
int32 VC_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl);


#endif /* VC_CUSTOM_H */
