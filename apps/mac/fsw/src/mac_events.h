#ifndef MAC_EVENTS_H
#define MAC_EVENTS_H

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
    MAC_RESERVED_EID = 0,  /* Do not use this event ID */

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  TODO fill this in
**
*/
    MAC_INF_EID,

/** \brief <tt> 'MAC Initialized. Version \%d.\%d.\%d' </tt>
**  \event <tt> 'MAC Initialized. Version \%d.\%d.\%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  completed initialization.
**
**  The first \c %d field contains the Application's Major Version Number
**  The second \c %d field contains the Application's Minor Version Number
**  The third \c %d field contains the Application's Revision Number
*/
    MAC_INIT_INF_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This message is generated when a table is initialized.
**
*/
    MAC_CONFIG_TABLE_INF_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    MAC_CDS_INF_EID,

/** \brief <tt> 'MAC - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'MAC - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  received and processed a command.
**
*/
    MAC_CMD_INF_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    MAC_ERR_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  had an error in initialization.
**
*/
    MAC_INIT_ERR_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  had an error with the configuration table.
**
*/
    MAC_CONFIG_TABLE_ERR_EID,

/** \brief <tt> 'MAC - ' </tt>
**  \event <tt> 'MAC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  had an error in CDS.
**
*/
    MAC_CDS_ERR_EID,

/** \brief <tt> 'MAC - $commandError' </tt>
**  \event <tt> 'MAC - $commandError' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  had an error processing a command.
**
*/
    MAC_CMD_ERR_EID,

/** \brief <tt> 'MAC: SB pipe read error (0x%08X), app will exit' </tt>
**  \event <tt> 'MAC: SB pipe read error (0x%08X), app will exit' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  had an error reading from a pipe.
**
*/
    MAC_PIPE_ERR_EID,

/** \brief <tt> 'MAC - Recvd invalid $type msgId (0x%04x)' </tt>
**  \event <tt> 'MAC - Recvd invalid $type msgId (0x%04x)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  received an invalid message ID.
**
*/
    MAC_MSGID_ERR_EID,

/** \brief <tt> 'MAC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  \event <tt> 'MAC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS MAC Task has
**  received a message with a bad length.
**
*/
    MAC_MSGLEN_ERR_EID,

    MAC_PWM_CALIB_INFO_EID,


/** \brief <tt> This is a count of all the app events and should not be used. </tt> */
    MAC_EVT_CNT
} MAC_EventIds_t;


#ifdef __cplusplus
}
#endif

#endif /* MAC_EVENTS_H */

/************************/
/*  End of File Comment */
/************************/
    
