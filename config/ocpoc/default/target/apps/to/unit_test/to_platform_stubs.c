#include <arpa/inet.h>
#include <errno.h>

#include "to_platform_stubs.h"


int enable_wrappers = 0;

int __real_socket(int domain, int type, int protocol);
int __real_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int __real_sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);

TO_Platform_Stubs_Returns_t TO_Platform_Stubs_Returns = {0};


int __wrap_socket(int domain, int type, int protocol)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_socket(domain, type, protocol);
    }
    else
    {
        if (TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno)
        {
            errno = TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno_Value;
        }
        returnCode = TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return;
    }
    return returnCode;
}


int __wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_bind(sockfd, addr, addrlen);
    }
    else
    {
        if (TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno)
        {
            errno = TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno_Value;
        }
        returnCode = TO_Platform_Stubs_Returns.TO_Wrap_Bind_Return;
    }
    return returnCode;
}


int __wrap_sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_sendto(sockfd, buf, len, flags, dest_addr, addrlen);
    }
    else
    {
        if (TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno)
        {
            errno = TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno_Value;
        }
        returnCode = TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Return;
    }
    return returnCode;
}
