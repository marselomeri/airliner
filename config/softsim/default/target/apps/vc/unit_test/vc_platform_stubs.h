#ifndef VC_PLATFORM_STUBS_H
#define VC_PLATFORM_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/videodev2.h>


typedef struct
{
    int     VC_Wrap_Ioctl_Return;
    int     VC_Wrap_Ioctl_Return1;
    int     VC_Wrap_Ioctl_Return2;
    int     VC_Wrap_Ioctl_Errno;
    int     VC_Wrap_Ioctl_Errno_Value;
    int     VC_Wrap_Ioctl_Struct;
    int     VC_Wrap_Open_Return;
    int     VC_Wrap_Open_Errno;
    int     VC_Wrap_Open_Errno_Value;
    int     VC_Wrap_Close_Return;
    int     VC_Wrap_Select_Return;
    int     VC_Wrap_Select_Errno;
    int     VC_Wrap_Select_Errno_Value;
    int     VC_Wrap_Socket_Return;
    int     VC_Wrap_Socket_Errno;
    int     VC_Wrap_Socket_Errno_Value;
    int     VC_Wrap_Bind_Return;
    int     VC_Wrap_Bind_Errno;
    int     VC_Wrap_Bind_Errno_Value;
    int     VC_Wrap_SendTo_Return;
    int     VC_Wrap_SendTo_Errno;
    int     VC_Wrap_SendTo_Errno_Value;
    int     VC_Wrap_Ioctl_CallCount;
} VC_Platform_Stubs_Returns_t;


extern VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns;


#ifdef __cplusplus
}
#endif

#endif /* VC_PLATFORM_STUBS_H */
