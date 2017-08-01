/*==============================================================================
Copyright (c) 2017, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of CmdIn nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY VCPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, VCEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "vc_transmit_udp.h"
#include "cfe.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "vc_app.h"

//VC_Transmit_Handle_t TransmitHandle = { .DestPort = VC_DESTINATION_PORT, \
                                        .MyPort = VC_SOURCE_PORT, \
                                        .DestIP = VC_DESTINATION_IP, \
                                        .MyIP = VC_SOURCE_IP, \
                                        .SocketFd = -1 }; 
                                        
VC_AppCustomData_t VC_AppCustomData = {
    {
        { 
          .Mode = VC_CHANNEL_ENABLED, \
          .ChannelID = 0, \
          .DestPort = VC_DESTINATION_PORT, \
          .MyPort = VC_SOURCE_PORT, \
          .DestIP = VC_DESTINATION_IP, \
          .MyIP = VC_SOURCE_IP, \
          .SocketFd = -1 \
        }
    }
};

int32 VC_EnableChannel(uint8 ChannelID, const char *DestinationAddress, uint16 DestinationPort)
{
    int32 returnCode = 0;
    uint32 i = 0;
    struct sockaddr_in servaddr;
    int status;
    int reuseaddr=1;

    if((VC_AppCustomData.Channel[ChannelID].Mode == VC_CHANNEL_ENABLED) &
        (VC_AppCustomData.Channel[ChannelID].SocketFd != 0))
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "UDP telemetry for channel %u already enabled.", (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    if(DestinationAddress == 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "Destination address for channel %u is null.", (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    if(ChannelID >= VC_MAX_OUTPUT_CHANNELS)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "ChannelID (%u) invalid.", (unsigned int)ChannelID);
        returnCode = -1;
        goto end_of_function;
    }

    memcpy(VC_AppCustomData.Channel[ChannelID].DestIP, DestinationAddress, sizeof(VC_AppCustomData.Channel[ChannelID].DestIP));
    VC_AppCustomData.Channel[ChannelID].DestPort = DestinationPort;

    if((VC_AppCustomData.Channel[ChannelID].SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        VC_AppCustomData.Channel[ChannelID].Mode = VC_CHANNEL_DISABLED;
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC socket errno: %i on channel %u", errno, (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    /* Set the Reuse Address flag.  If we don't set this flag, the socket will
     * lock the port on termination and the kernel won't unlock it until it
     * times out after a minute or so.
     */
    setsockopt(VC_AppCustomData.Channel[ChannelID].SocketFd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    /* Set the input arguments to the socket bind.
     */
     
     
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port=htons(VC_AppCustomData.Channel[ChannelID].MyPort);
    
    if (inet_aton(VC_AppCustomData.Channel[ChannelID].MyIP, &servaddr.sin_addr) == 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC socket errno: %i on channel %u", errno, (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }
    
    status = bind(VC_AppCustomData.Channel[ChannelID].SocketFd,
            (struct sockaddr *)&servaddr,sizeof(servaddr));
    if(status < 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "TLM bind errno: %i on channel %u", errno, (unsigned int)i);
        VC_AppCustomData.Channel[ChannelID].Mode = VC_CHANNEL_DISABLED;
        returnCode = -1;
        goto end_of_function;
    }

end_of_function:
    return returnCode;
}


int32 VC_InitCustom(void)
{
    uint32 i = 0;
    int32 returnCode = 0;

    for (i=0; i < VC_MAX_OUTPUT_CHANNELS; i++)
    {
        if(VC_AppCustomData.Channel[i].Mode == VC_CHANNEL_ENABLED)
        {
            if(returnCode = VC_EnableChannel(i, VC_AppCustomData.Channel[i].DestIP, VC_AppCustomData.Channel[i].DestPort))
            {
                VC_AppCustomData.Channel[i].Mode = VC_CHANNEL_DISABLED;
            }
            else
            {
                CFE_EVS_SendEvent(VC_CHA_INF_EID, CFE_EVS_INFORMATION,
                        "UDP telemetry output enabled channel %u to %s:%u",
                        (unsigned int)i, VC_AppCustomData.Channel[i].DestIP,
                        (unsigned int)VC_AppCustomData.Channel[i].DestPort);
            }
        }
    }
    return returnCode;
}


int32 VC_DisableChannel(uint8 ChannelID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    struct sockaddr_in servaddr;
    int status;
    int reuseaddr=1;

    if(VC_AppCustomData.Channel[ChannelID].Mode != VC_CHANNEL_ENABLED)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                            "UDP telemetry for channel %u is not enabled.", (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    close(VC_AppCustomData.Channel[ChannelID].SocketFd);

end_of_function:
    return returnCode;
}


int32 VC_CleanupCustom(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_OUTPUT_CHANNELS; i++)
    {
        if(VC_AppCustomData.Channel[i].Mode == VC_CHANNEL_ENABLED)
        {
            if(VC_DisableChannel(i) == -1)
            {
                returnCode = -1;
            }
        }
    }
return returnCode;
}


boolean VC_Transmit_Init(void)
{
    if(VC_InitCustom() == -1)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC_Transmit_Init Failed");
        return FALSE;
    }
    return TRUE;
}


boolean VC_Transmit_Uninit(void)
{
    if(VC_CleanupCustom() == -1)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC_Transmit_Uninit Failed");
        return FALSE;
    }
    return TRUE;
}


int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size)
{
    static struct sockaddr_in s_addr;
    int status = 0;
    int32 returnCode = 0;

    bzero((char *) &s_addr, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;

    if(ChannelID < VC_MAX_OUTPUT_CHANNELS)
    {
        VC_Transmit_Handle_t *channel = &VC_AppCustomData.Channel[ChannelID];

        if(channel->Mode == VC_CHANNEL_ENABLED)
        {
            CFE_ES_PerfLogEntry(VC_SOCKET_SEND_PERF_ID);
            /* Send message via UDP socket */
            s_addr.sin_addr.s_addr = inet_addr(channel->DestIP);
            s_addr.sin_port        = htons(channel->DestPort);
            status = sendto(channel->SocketFd, (char *)Buffer, Size, 0,
                                    (struct sockaddr *) &s_addr,
                                    sizeof(s_addr));
            if (status < 0)
            {
                if(errno == 90)
                {
                    CFE_EVS_SendEvent(VC_SOCKET_ERR_EID,CFE_EVS_ERROR,
                                "L%d VC sendto errno %d.  Message too long.  Size=%u", __LINE__, errno, (unsigned int)Size);
                }
                else
                {
                    CFE_EVS_SendEvent(VC_SOCKET_ERR_EID,CFE_EVS_ERROR,
                                "L%d VC sendto errno %d.", __LINE__, errno);
                    channel->Mode = VC_CHANNEL_DISABLED;
                }
                returnCode = -1;
            }
            CFE_ES_PerfLogExit(VC_SOCKET_SEND_PERF_ID);
        }
    }

    return returnCode;
}
