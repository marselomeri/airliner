    
#ifndef PARAMS_EVENTS_H
#define PARAMS_EVENTS_H

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
    PARAMS_RESERVED_EID = 0,  /* Do not use this event ID */

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  TODO fill this in
**
*/
    PARAMS_INF_EID,

/** \brief <tt> 'PARAMS Initialized. Version \%d.\%d.\%d' </tt>
**  \event <tt> 'PARAMS Initialized. Version \%d.\%d.\%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  completed initialization.
**
**  The first \c %d field contains the Application's Major Version Number
**  The second \c %d field contains the Application's Minor Version Number
**  The third \c %d field contains the Application's Revision Number
*/
    PARAMS_INIT_INF_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This message is generated when a table is initialized.
**
*/
    PARAMS_CONFIG_TABLE_INF_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    PARAMS_CDS_INF_EID,

/** \brief <tt> 'PARAMS - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'PARAMS - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  received and processed a command.
**
*/
    PARAMS_CMD_INF_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    PARAMS_ERR_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  had an error in initialization.
**
*/
    PARAMS_INIT_ERR_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  had an error with the configuration table.
**
*/
    PARAMS_CONFIG_TABLE_ERR_EID,

/** \brief <tt> 'PARAMS - ' </tt>
**  \event <tt> 'PARAMS - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  had an error in CDS.
**
*/
    PARAMS_CDS_ERR_EID,

/** \brief <tt> 'PARAMS - $commandError' </tt>
**  \event <tt> 'PARAMS - $commandError' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  had an error processing a command.
**
*/
    PARAMS_CMD_ERR_EID,

/** \brief <tt> 'PARAMS: SB pipe read error (0x%08X), app will exit' </tt>
**  \event <tt> 'PARAMS: SB pipe read error (0x%08X), app will exit' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  had an error reading from a pipe.
**
*/
    PARAMS_PIPE_ERR_EID,

/** \brief <tt> 'PARAMS - Recvd invalid $type msgId (0x%04x)' </tt>
**  \event <tt> 'PARAMS - Recvd invalid $type msgId (0x%04x)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  received an invalid message ID.
**
*/
    PARAMS_MSGID_ERR_EID,

/** \brief <tt> 'PARAMS - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  \event <tt> 'PARAMS - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS PARAMS Task has
**  received a message with a bad length.
**
*/
    PARAMS_MSGLEN_ERR_EID,


/** \brief <tt> This is a count of all the app events and should not be used. </tt> */
    PARAMS_EVT_CNT
} PARAMS_EventIds_t;


#ifdef __cplusplus
}
#endif

#endif /* PARAMS_EVENTS_H */

/************************/
/*  End of File Comment */
/************************/
    
