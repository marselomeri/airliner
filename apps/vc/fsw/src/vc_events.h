#ifndef VC_EVENTS_H
#define VC_EVENTS_H

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
    VC_RESERVED_EID = 0,  /* Do not use this event ID */

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  TODO fill this in
**
*/
    VC_INF_EID,

/** \brief <tt> 'VC Initialized. Version \%d.\%d.\%d' </tt>
**  \event <tt> 'VC Initialized. Version \%d.\%d.\%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  completed initialization.
**
**  The first \c %d field contains the Application's Major Version Number
**  The second \c %d field contains the Application's Minor Version Number
**  The third \c %d field contains the Application's Revision Number
*/
    VC_INIT_INF_EID,

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This message is generated when a table is initialized.
**
*/
    VC_CONFIG_TABLE_INF_EID,

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a NOOP command is received.
**
*/
    VC_NOOP_INF_EID,

    /** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a RESET command is received.
**
*/
    VC_RESET_INF_EID,

/** \brief <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  received and processed a command.
**
*/
    VC_CMD_INF_EID,
    
/** \brief <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a device resource channel
**  has been created.
**
*/
    VC_DEV_INF_EID,

/** \brief <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'VC - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a transmit resource channel
**  has been created.
**
*/
    VC_CHA_INF_EID,
/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    VC_ERR_EID,

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error in initialization.
**
*/
    VC_INIT_ERR_EID,
    
    
/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error in uninitialization.
**
*/
    VC_UNINIT_ERR_EID,

/** \brief <tt> 'VC - ' </tt>
**  \event <tt> 'VC - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error with the configuration table.
**
*/
    VC_CONFIG_TABLE_ERR_EID,

/** \brief <tt> 'VC - $commandError' </tt>
**  \event <tt> 'VC - $commandError' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error processing a command.
**
*/
    VC_CMD_ERR_EID,

/** \brief <tt> 'VC: SB pipe read error (0x%08X), app will exit' </tt>
**  \event <tt> 'VC: SB pipe read error (0x%08X), app will exit' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error reading from a pipe.
**
*/
    VC_PIPE_ERR_EID,

/** \brief <tt> 'VC - Recvd invalid $type msgId (0x%04x)' </tt>
**  \event <tt> 'VC - Recvd invalid $type msgId (0x%04x)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  received an invalid message ID.
**
*/
    VC_MSGID_ERR_EID,

/** \brief <tt> 'VC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  \event <tt> 'VC - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  received a message with a bad length.
**
*/
    VC_MSGLEN_ERR_EID,

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
    VC_SOCKET_ERR_EID,
    
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

/** \brief <tt> This is a count of all the app events and should not be used. </tt> */
    VC_EVT_CNT
} VC_EventIds_t;


#ifdef __cplusplus
}
#endif

#endif /* VC_EVENTS_H */

/************************/
/*  End of File Comment */
/************************/
