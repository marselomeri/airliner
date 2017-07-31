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
#include <errno.h>
#include <string.h>
#include "vc_app.h"

VC_Transmit_Handle_t TransmitHandle = { .DestPort = VC_DESTINATION_PORT, \
                                        .MyPort = VC_SOURCE_PORT, \
                                        .DestIP = VC_DESTINATION_IP, \
                                        .MyIP = VC_SOURCE_IP, \
                                        .SocketFd = -1 }; 

boolean VC_Transmit_Init(void)
{
    int Socket = -1;
    struct sockaddr_in MyAddr;
    struct sockaddr_in DestAddr;
    
    /* setup source info */
    memset((char *)&MyAddr, 0, sizeof(MyAddr));
    MyAddr.sin_family = AF_INET;
    MyAddr.sin_port = htons(TransmitHandle.MyPort);
    
    if (inet_aton(TransmitHandle.MyIP, &MyAddr.sin_addr) == 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC: inet_aton failed for MyIP in VC_Transmit_Init");
        return FALSE;
    }
    
    /* setup destination info */
    memset((char *)&DestAddr, 0, sizeof(DestAddr));
    MyAddr.sin_family = AF_INET;
    MyAddr.sin_port = htons(TransmitHandle.DestPort);
    
    if (inet_aton(TransmitHandle.DestIP, &DestAddr.sin_addr) == 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC: inet_aton failed for DestIP in VC_Transmit_Init");
        return FALSE;
    }
    
    /* create a socket */
    if ((Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC: socket errno: %i in VC_Transmit_Init", errno);
        return FALSE;
    }
    
    //setsockopt();
    
    /* bind the socket to the address */
    if (bind(Socket, (struct sockaddr *)&MyAddr, sizeof(MyAddr)) < 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC: bind errno: %i in VC_Transmit_Init", errno);
        return FALSE;
    }

    TransmitHandle.SocketFd = Socket;
    
    CFE_EVS_SendEvent(VC_CHA_INF_EID, CFE_EVS_INFORMATION,
                            "VC UDP output enabled channel %u on port %u.",
                            0, TransmitHandle.DestPort);

    return TRUE;
}


boolean VC_Transmit_Uninit(void)
{
    return FALSE;
}


int VC_SendData(const void *buf, size_t len)
{
    return -1;
}
