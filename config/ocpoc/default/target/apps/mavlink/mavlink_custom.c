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
#include "mavlink_custom.h"
#include "mavlink_app.h"
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

typedef struct
{
	int  Socket;
	uint16 Port;
} MAVLINK_SocketData_t;

MAVLINK_SocketData_t MAVLINK_SocketData = {0, MAVLINK_GCS_PORT};
MAVLINK_SocketData_t MAVLINK_PassThruSocket = {0, MAVLINK_PASSTHRU_INGEST_PORT};
uint16 px4_port = 14556;

int32 MAVLINK_InitCustom(void)
{
    int32 Status = 0;
    int reuseaddr = 1;
	struct sockaddr_in address;

	/* Initialize output socket */
	if((MAVLINK_SocketData.Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		CFE_EVS_SendEvent(MAVLINK_SOCKET_ERR_EID, CFE_EVS_ERROR,
			   "Socket errno: %i", errno);
			Status = -1;
			goto end_of_function;
	}

	setsockopt(MAVLINK_SocketData.Socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

	/* Initialize pass thru socket */
    if((MAVLINK_PassThruSocket.Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
    	CFE_EVS_SendEvent(MAVLINK_SOCKET_ERR_EID, CFE_EVS_ERROR,
    		   "Socket errno: %i", errno);
    		Status = -1;
    		goto end_of_function;
    }

    setsockopt(MAVLINK_PassThruSocket.Socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    bzero((char *) &address, sizeof(address));
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    address.sin_port        = htons(MAVLINK_PassThruSocket.Port);

	if ( (bind(MAVLINK_PassThruSocket.Socket, (struct sockaddr *) &address, sizeof(address)) < 0) )
	{
		CFE_EVS_SendEvent(MAVLINK_SOCKET_ERR_EID, CFE_EVS_ERROR,"Bind socket failed = %d", errno);
		Status = -1;
		goto end_of_function;
	}

	CFE_EVS_SendEvent(MAVLINK_ENA_INF_EID, CFE_EVS_INFORMATION,
					  "Passthru ingest port enabled on: %u.",
					  MAVLINK_PassThruSocket.Port);

end_of_function:
    return Status;
}

int32 MAVLINK_ReadPassThru(char* buffer, uint32* size)
{
	struct sockaddr_in address;
	socklen_t len = sizeof(address);

	*size = recvfrom(MAVLINK_PassThruSocket.Socket,
					   (char *)buffer,
					   (size_t)size, 0,
					   (struct sockaddr*)&address,
					   &len);

	//px4_port = address.sin_port;
}

int32 MAVLINK_SendPassThru(const char* buffer, uint32 size)
{
	struct sockaddr_in s_addr;
    int    status = 0;
    int32  returnCode = 0;

    /* Send message via UDP socket */
    bzero((char *) &s_addr, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(MAVLINK_PASSTHRU_IP_SRC);
    s_addr.sin_port        = htons(px4_port);

    status = sendto(MAVLINK_PassThruSocket.Socket, (char *)buffer, size, 0,
                            (struct sockaddr *) &s_addr,
                             sizeof(s_addr));
    if (status < 0)
    {
        OS_printf("MAVLINK passthru send error\n");
        returnCode = -1;
    }
}

int32 MAVLINK_ReadMessage(char* buffer, uint32* size)
{
	struct sockaddr_in address;
	address.sin_family      = AF_INET;
	address.sin_addr.s_addr = htonl (INADDR_ANY);// todo is this needed
	socklen_t len = sizeof(address);

	*size = recvfrom(MAVLINK_SocketData.Socket,
					   (char *)buffer,
					   (size_t)size, 0,
					   (struct sockaddr*)&address,
					   &len);
}

int32 MAVLINK_SendMessage(const char* buffer, uint32 size)
{
	struct sockaddr_in s_addr;
    int    status = 0;
    int32  returnCode = 0;

    /* Send message via UDP socket */
    bzero((char *) &s_addr, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(MAVLINK_GCS_IP);
    s_addr.sin_port        = htons(MAVLINK_SocketData.Port);

    status = sendto(MAVLINK_SocketData.Socket, (char *)buffer, size, 0,
                            (struct sockaddr *) &s_addr,
                             sizeof(s_addr));
    if (status < 0)
    {
        OS_printf("MAVLINK send error\n");
        returnCode = -1;
    }

}

int32 MAVLINK_CleanupCustom(void)
{
    return close(MAVLINK_SocketData.Socket);
}

