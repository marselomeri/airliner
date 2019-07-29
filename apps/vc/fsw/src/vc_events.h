/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

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
    VC_INIT_INF_EID = 1,

/** \brief <tt> 'Recvd NOOP cmd, Version %d.%d.%d.%d' </tt>
**  \event <tt> 'Recvd NOOP cmd, Version %d.%d.%d.%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a NOOP command is received.
**
*/
    VC_NOOP_INF_EID = 2,

/** \brief <tt> 'Recvd RESET cmd' </tt>
**  \event <tt> 'Recvd RESET cmd' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when a RESET command is received.
**
*/
    VC_RESET_INF_EID = 3,

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
    VC_CMD_INF_EID = 4,
    
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
    VC_DEV_INF_EID = 5,

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
    VC_CHA_INF_EID = 6,
    
/** \brief <tt> 'Pipe failed to subscribe to MID. (0x%08X)' </tt>
**  \event <tt> 'Pipe failed to subscribe to MID. (0x%08X)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error in initialization.
**
*/
    VC_INIT_ERR_EID = 7,
    
    
/** \brief <tt> 'VC_Devices_Function failed' </tt>
**  \event <tt> 'VC_Devices_Function failed' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error in uninitialization.
**
*/
    VC_UNINIT_ERR_EID = 8,

/** \brief <tt> 'VC is already streaming' </tt>
**  \event <tt> 'VC is already streaming' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS VC Task has
**  had an error processing a command.
**
*/
    VC_CMD_ERR_EID = 9,

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
    VC_PIPE_ERR_EID = 10,

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
    VC_MSGID_ERR_EID = 11,

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
    VC_MSGLEN_ERR_EID = 12,

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
