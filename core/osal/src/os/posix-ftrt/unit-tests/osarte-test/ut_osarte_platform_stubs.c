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
#include "ut_osarte_platform_stubs.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ccsds.h"
#include <string.h>


int enable_wrappers = 0;

OS_ARTE_Platform_Stubs_Returns_t OS_ARTE_Platform_Stubs_Returns = {0};

int __real_socket(int domain, int type, int protocol);
int __real_setsockopt(int socket, int level, int option_name,
        const void *option_value, socklen_t option_len);
int __real_connect(int sockfd, const struct sockaddr *addr,
        socklen_t addrlen);
ssize_t __real_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t __real_recv(int sockfd, void *buf, size_t len, int flags);
int __real_close(int fildes);
int __real_inet_aton(const char *cp, struct in_addr *inp);

int __wrap_socket(int domain, int type, int protocol)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_socket(domain, type, protocol);
    }
    else
    {
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Errno)
        {
            errno = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Errno_Return;
        }
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Socket_Return;
    }
    return returnCode;
}


int __wrap_setsockopt(int socket, int level, int option_name,
        const void *option_value, socklen_t option_len)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_setsockopt(socket, level, option_name, option_value, option_len);
    }
    else
    {
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Setsockopt_Errno)
        {
            errno = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Setsockopt_Errno_Return;
        }
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Setsockopt_Return;
    }
    return returnCode;
}


int __wrap_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_connect(sockfd, addr, addrlen);
    }
    else
    {
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Connect_Errno)
        {
            errno = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Connect_Errno_Return;
        }
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Connect_Return;
    }
    return returnCode;
}


ssize_t __wrap_send(int sockfd, const void *buf, size_t len, int flags)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_send(sockfd, buf, len, flags);
    }
    else
    {
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Errno)
        {
            errno = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Errno_Return;
        }
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Send_Return;
    }
    return returnCode;
}


ssize_t __wrap_recv(int sockfd, void *buf, size_t len, int flags)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_recv(sockfd, buf, len, flags);
    }
    else
    {
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Errno)
        {
            errno = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Errno_Return;
        }
        if (OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Nominal)
        {
            CCSDS_CmdPkt_t step_command;
            CCSDS_CLR_PRI_HDR(step_command.PriHdr);
            CCSDS_CLR_CMDSEC_HDR(step_command.SecHdr);
            CCSDS_WR_SEQ(step_command.PriHdr, 100);
            memcpy(buf, &step_command, sizeof(step_command));
        }
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Recv_Return;
    }
    return returnCode;
}


int __wrap_close(int fildes)
{
    int returnCode = 0;

    if(enable_wrappers == 0)
    {
        returnCode = __real_close(fildes);
    }
    else
    {
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_Close_Return;
    }
    return returnCode;
}


int __wrap_inet_aton(const char *cp, struct in_addr *inp)
{
    int returnCode = 0;

    if(enable_wrappers == 0)
    {
        returnCode = __real_inet_aton(cp, inp);
    }
    else
    {
        returnCode = OS_ARTE_Platform_Stubs_Returns.OS_ARTE_InetAton_Return;
    }
    return returnCode;
}

