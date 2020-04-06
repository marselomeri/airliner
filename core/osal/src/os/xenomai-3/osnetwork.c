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

#include "osapi.h"



#ifdef OS_INCLUDE_NETWORK
int32 OS_SocketOpen(uint32 *sock_id, OS_SocketDomain_t Domain, OS_SocketType_t Type)
{
	return OS_ERROR;
}



int32 OS_SocketClose(uint32 sock_id)
{
	return OS_ERROR;
}



int32 OS_SocketBind(uint32 sock_id, const OS_SockAddr_t *Addr)
{
	return OS_ERROR;
}



int32 OS_SocketConnect(uint32 sock_id, const OS_SockAddr_t *Addr, int32 timeout)
{
	return OS_ERROR;
}



int32 OS_SocketAccept(uint32 sock_id, uint32 *connsock_id, OS_SockAddr_t *Addr, int32 timeout)
{
	return OS_ERROR;
}



int32 OS_SocketRecvFrom(uint32 sock_id, void *buffer, uint32 buflen, OS_SockAddr_t *RemoteAddr, int32 timeout)
{
	return OS_ERROR;
}



int32 OS_SocketSendTo(uint32 sock_id, const void *buffer, uint32 buflen, const OS_SockAddr_t *RemoteAddr)
{
	return OS_ERROR;
}



int32 OS_SocketGetIdByName (uint32 *sock_id, const char *sock_name)
{
	return OS_ERROR;
}



int32 OS_SocketGetInfo (uint32 sock_id, OS_socket_prop_t *sock_prop)
{
	return OS_ERROR;
}



int32 OS_SocketAddrInit(OS_SockAddr_t *Addr, OS_SocketDomain_t Domain)
{
	return OS_ERROR;
}



int32 OS_SocketAddrToString(char *buffer, uint32 buflen, const OS_SockAddr_t *Addr)
{
	return OS_ERROR;
}



int32 OS_SocketAddrFromString(OS_SockAddr_t *Addr, const char *string)
{
	return OS_ERROR;
}



int32 OS_SocketAddrGetPort(uint16 *PortNum, const OS_SockAddr_t *Addr)
{
	return OS_ERROR;
}



int32 OS_SocketAddrSetPort(OS_SockAddr_t *Addr, uint16 PortNum)
{
	return OS_ERROR;
}



/*
** OS_NetworkGetID is currently [[deprecated]] as its behavior is
** unknown and not consistent across operating systems.
*/
int32 OS_NetworkGetID             (void)
{
	return OS_ERROR;
}



int32 OS_NetworkGetHostName       (char *host_name, uint32 name_len)
{
	return OS_ERROR;
}



#endif
