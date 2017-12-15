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
#include "mavlink_platform_cfg.h"
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include "mavlink_events.h"
#include <strings.h>
#include <unistd.h>

#define MAVLINK_CUSTOM_RETURN_CODE_NULL_POINTER      (-1)


typedef struct
{
	int  Socket;
	uint16 Port;
} MAVLINK_SocketData_t;

MAVLINK_SocketData_t MAVLINK_IngestSocketData = {0, 5014};
MAVLINK_SocketData_t MAVLINK_OutputSocketData = {0, 5015};

int32 MAVLINK_InitCustom(void)
{
    int32 Status = 0;
    int reuseaddr = 1;
	struct sockaddr_in address;
	struct sockaddr_in serial_address;

    if((MAVLINK_IngestSocketData.Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
    	CFE_EVS_SendEvent(MAVLINK_SOCKET_ERR_EID, CFE_EVS_ERROR,
    		   "Socket errno: %i", errno);
    		Status = -1;
    		goto end_of_function;
    }

    setsockopt(MAVLINK_IngestSocketData.Socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    //fcntl(MAVLINK_IngestSocketData.Socket, F_SETFL, O_NONBLOCK);

    bzero((char *) &address, sizeof(address));
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = htonl (INADDR_ANY);
    address.sin_port        = htons(MAVLINK_IngestSocketData.Port);

	if ( (bind(MAVLINK_IngestSocketData.Socket, (struct sockaddr *) &address, sizeof(address)) < 0) )
	{
		CFE_EVS_SendEvent(MAVLINK_SOCKET_ERR_EID, CFE_EVS_ERROR,"Bind socket failed = %d", errno);
		Status = -1;
		goto end_of_function;
	}

	CFE_EVS_SendEvent(MAVLINK_ENA_INF_EID, CFE_EVS_INFORMATION,
					  "Mavlink UDP command input enabled on port %u.",
					  MAVLINK_IngestSocketData.Port);

end_of_function:
    return Status;

}


int32 MAVLINK_ReadMessage(char* buffer, uint32* size)
{
    //OS_printf("In MAVLINK read message\n");
	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	*size = recvfrom(MAVLINK_IngestSocketData.Socket,
					   (char *)buffer,
					   (size_t)size, 0,
					   (struct sockaddr*)&client,
					   &len);
}

int32 MAVLINK_SendMessage(const char* buffer, uint32 Size)
{
	struct sockaddr_in s_addr;
    int    status = 0;
    int32  returnCode = 0;

    bzero((char *) &s_addr, sizeof(s_addr));


    /* Send message via UDP socket */
    s_addr.sin_family      = AF_INET;
    s_addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);//inet_addr("10.10.0.13");
    s_addr.sin_port        = htons(MAVLINK_IngestSocketData.Port);

    status = sendto(MAVLINK_IngestSocketData.Socket, (char *)buffer, Size, 0,
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
    return close(MAVLINK_IngestSocketData.Socket);
}

