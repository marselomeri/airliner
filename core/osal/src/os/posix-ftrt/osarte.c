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
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "osarte.h"
#include "osapi.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
OS_Arte_Handle_t Arte_Handle;


void OS_ArteInitData(void)
{
    strncpy(Arte_Handle.ArteIP, OS_ARTE_SERVER_IP, INET_ADDRSTRLEN); 
    Arte_Handle.ArtePort = OS_ARTE_SERVER_PORT;
    
    /* Init for CCSDS packet to ARTE server "ready" */
    CCSDS_CLR_PRI_HDR(Arte_Handle.ready_notification.PriHdr);
    CCSDS_CLR_TLMSEC_HDR(Arte_Handle.ready_notification.SecHdr);
    /* Write the length of the packet to the primary header */
    CCSDS_WR_LEN(Arte_Handle.ready_notification.PriHdr, 
            sizeof(Arte_Handle.ready_notification));
    /* Set the secondary header flag in the primary header to 1 = 
     * present */
    CCSDS_WR_SHDR(Arte_Handle.ready_notification.PriHdr, 1);

    /* Init for CCSDS packet to ARTE server "shutdown" success */
    CCSDS_CLR_PRI_HDR(Arte_Handle.shutdown_notification.PriHdr);
    CCSDS_CLR_TLMSEC_HDR(Arte_Handle.shutdown_notification.SecHdr);
    /* Write the length of the packet to the primary header */
    CCSDS_WR_LEN(Arte_Handle.shutdown_notification.PriHdr, 
            sizeof(Arte_Handle.shutdown_notification));
    /* Set the secondary header flag in the primary header to 1 = 
     * present */
    CCSDS_WR_SHDR(Arte_Handle.shutdown_notification.PriHdr, 1);
}


int32 OS_ArteInit(void)
{
    int returnCode = OS_SUCCESS;
    int on = 1;
    struct sockaddr_in serv_addr;

    /* Initialize any data */
    OS_ArteInitData();

    /* Create a TCP socket */
    Arte_Handle.SocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if(Arte_Handle.SocketFd < 0)
    {
        /* Socket creation failed */
        OS_printf("OSAL: ARTE socket creation error. err = '%s'\n", strerror(errno));
        returnCode = -1;
        goto end_of_function;
    }
    
    /* Set socket options */
    if(-1 == setsockopt(Arte_Handle.SocketFd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)))
    {
        OS_printf("OSAL: ARTE setsockopt TCP_NODELAY err = '%s'\n", strerror(errno));
    }
    if(-1 == setsockopt(Arte_Handle.SocketFd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on)))
    {
        OS_printf("OSAL: ARTE setsockopt SO_KEEPALIVE err = '%s'\n", strerror(errno));
    }

    /* Configure server address struct */
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Arte_Handle.ArtePort);

    /* Convert the server address to bin form */
    if(inet_aton(Arte_Handle.ArteIP, &serv_addr.sin_addr) == 0)
    {
        OS_printf("OSAL: ARTE invalid IP address error. err = '%s'\n", strerror(errno));
        returnCode = -1;
        goto end_of_function;
    }
    /* Connect to ARTE server */
    if(connect(Arte_Handle.SocketFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        /* Connect failed */
        OS_printf("OSAL: ARTE server connect failed. err = '%s'\n", strerror(errno));
        returnCode = -1;
        goto end_of_function;
    }

end_of_function:

    return returnCode;
}


boolean OS_ArteSendReady(void)
{
    int status;
    /* Send the ready notification to ARTE server */
    status = send(Arte_Handle.SocketFd, &Arte_Handle.ready_notification, 
            sizeof(Arte_Handle.ready_notification), MSG_NOSIGNAL);
    /* If send encountered an error... */
    if (status < 0)
    {
        OS_printf("OSAL: ARTE: ready notification failed send err = '%s'\n", strerror(errno));
        return FALSE;
    }
    else if (status < sizeof(Arte_Handle.ready_notification))
    {
        OS_printf("OSAL: ARTE: ready notification failed to send complete packet\n");
        return FALSE;
    }
    return TRUE;
}


boolean OS_ArteSendShutdown(boolean success)
{
    int status;
    if (success == TRUE)
    {
        /* Set the app id to 1 which is the ARTE success shutdown code */
        CCSDS_WR_APID(Arte_Handle.shutdown_notification.PriHdr, 1);
    }
    else
    {
        /* Set the app id to 1 which is the ARTE success shutdown code */
        CCSDS_WR_APID(Arte_Handle.shutdown_notification.PriHdr, 2);
    }
    /* Send a shutdown notification to ARTE server */
    status = send(Arte_Handle.SocketFd, &Arte_Handle.shutdown_notification, 
            sizeof(Arte_Handle.shutdown_notification), MSG_NOSIGNAL);
    /* If send encountered an error... */
    if (status < 0)
    {
        OS_printf("OSAL: ARTE: shutdown notification failed send err = '%s'\n", strerror(errno));
        return FALSE;
    }
    else if (status < sizeof(Arte_Handle.ready_notification))
    {
        OS_printf("OSAL: ARTE: ready notification failed to send complete packet\n");
        return FALSE;
    }
    return TRUE;
}


/* TODO */
boolean OS_ArteVerifyCommand(char *buffer)
{
    if (buffer == 0)
    {
        OS_printf("OSAL: ARTE: ArteVerifyCommand null pointer\n");
        return FALSE;
    }
    /* TODO verify the checksum */
    /* TODO verify all packet bit field values? */
    return TRUE;
}


boolean OS_ArteRecvNextStep(void)
{
    int status, i;
    boolean returnBool = FALSE;

    /* Clear the buffer */
    memset(&Arte_Handle.buffer, 0, sizeof(Arte_Handle.buffer));
    /* Clear the packet */
    memset(&Arte_Handle.step_command, 0, sizeof(Arte_Handle.step_command));
    /* Block until the "next step" command is received and loop if recv 
     * gets interrupted by a signal and has to be called again to 
     * continue reading. */
    do {
        status = recv(Arte_Handle.SocketFd, Arte_Handle.buffer, sizeof(Arte_Handle.step_command), MSG_WAITALL);
    } while (-1 == status && EINTR == errno);
    /* If recv encountered an error... */
    if (status < 0)
    {
        OS_printf("OSAL: ARTE: failed next step command recv err = '%s'\n", strerror(errno));
        return FALSE;
    }
    /* Copy into the step command struct */
    memcpy(&Arte_Handle.step_command, Arte_Handle.buffer, sizeof(Arte_Handle.step_command));
    /* Verify the command */
    returnBool = OS_ArteVerifyCommand(Arte_Handle.buffer);
    if (returnBool == FALSE)
    {
        OS_printf("OSAL: ARTE: failed command verification.\n");
        return FALSE;
    }
    /* Update the sequence count */
    Arte_Handle.SequenceCount = CCSDS_RD_SEQ(Arte_Handle.step_command.PriHdr);
    /* Update the frame count*/
    Arte_Handle.FrameCount = CCSDS_RD_APID(Arte_Handle.step_command.PriHdr);
    return TRUE;
}


int32 OS_ArteStepNext(uint32 *sequence, uint32 *frame)
{
    boolean status;
    
    if (sequence == 0 || frame == 0)
    {
        OS_printf("OSAL: ARTE: OS_ArteStepNext Null pointer\n");
        return -1;
    }
    status = OS_ArteSendReady();
    if (status == FALSE)
    {
        OS_printf("OSAL: ARTE: failed ArteSendReady err = '%s'\n", strerror(errno));
        return -1;
    }
    status = OS_ArteRecvNextStep();
    if (status == FALSE)
    {
        OS_printf("OSAL: ARTE: failed ArteRecvNextStep err = '%s'\n", strerror(errno));
        return -1;
    }
    /* Update the sequence count */
    *sequence = Arte_Handle.SequenceCount;
    *frame = Arte_Handle.FrameCount;
    return 0;
}


int32 OS_ArteCleanup(void)
{
    int returnCode = -1;

    returnCode = close(Arte_Handle.SocketFd);
    if (returnCode == 0)
    {
        returnCode = OS_SUCCESS;
    }

    return returnCode;
}
