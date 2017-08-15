#ifndef VC_PLATFORM_STUBS_H
#define VC_PLATFORM_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/videodev2.h>


typedef struct
{
    int     VC_Wrap_Ioctl_Return;
    int     VC_Wrap_Ioctl_Errno;
    int     VC_Wrap_Ioctl_Errno_Value;
    int     VC_Wrap_Ioctl_Struct;
    int     VC_Wrap_Open_Return;
    int     VC_Wrap_Open_Errno;
    int     VC_Wrap_Open_Errno_Value;
    uint8   VC_Wrap_Ioctl_Return_Values;
    uint8   VC_Wrap_Ioctl_CallCount;
} VC_Platform_Stubs_Returns_t;


extern VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns;


#ifdef __cplusplus
}
#endif

#endif /* VC_PLATFORM_STUBS_H */
