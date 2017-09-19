    
#ifndef PMC_EVENTS_H
#define PMC_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/


/* Event IDs
 * Conventions: _EID is the event identifier.  _EVT_CNT is the total number of
 * events and should always be last.  Events can be added before _EVT_CNT.
 * For long-term maintenance, consider not removing an event but replacing it
 * with an unused, reserved, enum to preserve the IDs later in the list. */
typedef enum {

/** \brief <tt> Value of zero is reserved, and should not be used. </tt> */
    PMC_RESERVED_EID = 0,  /* Do not use this event ID */

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  TODO fill this in
**
*/
    PMC_INF_EID,

/** \brief <tt> 'PMC Initialized. Version \%d.\%d.\%d' </tt>
**  \event <tt> 'PMC Initialized. Version \%d.\%d.\%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  completed initialization.
**
**  The first \c %d field contains the Application's Major Version Number
**  The second \c %d field contains the Application's Minor Version Number
**  The third \c %d field contains the Application's Revision Number
*/
    PMC_INIT_INF_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This message is generated when a table is initialized.
**
*/
    PMC_CONFIG_TABLE_INF_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    PMC_CDS_INF_EID,

/** \brief <tt> 'PMC - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'PMC - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  received and processed a command.
**
*/
    PMC_CMD_INF_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    PMC_ERR_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  had an error in initialization.
**
*/
    PMC_INIT_ERR_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  had an error with the configuration table.
**
*/
    PMC_CONFIG_TABLE_ERR_EID,

/** \brief <tt> 'PMC - ' </tt>
**  \event <tt> 'PMC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  had an error in CDS.
**
*/
    PMC_CDS_ERR_EID,

/** \brief <tt> 'PMC - $commandError' </tt>
**  \event <tt> 'PMC - $commandError' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  had an error processing a command.
**
*/
    PMC_CMD_ERR_EID,

/** \brief <tt> 'PMC: SB pipe read error (0x%08X), app will exit' </tt>
**  \event <tt> 'PMC: SB pipe read error (0x%08X), app will exit' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  had an error reading from a pipe.
**
*/
    PMC_PIPE_ERR_EID,

/** \brief <tt> 'PMC - Recvd invalid $type msgId (0x%04x)' </tt>
**  \event <tt> 'PMC - Recvd invalid $type msgId (0x%04x)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  received an invalid message ID.
**
*/
    PMC_MSGID_ERR_EID,

/** \brief <tt> 'PMC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  \event <tt> 'PMC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PMC Task has
**  received a message with a bad length.
**
*/
    PMC_MSGLEN_ERR_EID,


/** \brief <tt> This is a count of all the app events and should not be used. </tt> */
    PMC_EVT_CNT
} PMC_EventIds_t;


#ifdef __cplusplus
}
#endif

#endif /* PMC_EVENTS_H */

/************************/
/*  End of File Comment */
/************************/
    
