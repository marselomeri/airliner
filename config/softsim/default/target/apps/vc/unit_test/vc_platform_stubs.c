#include <sys/ioctl.h>
#include <errno.h>

#include <stdio.h>

#include "vc_platform_stubs.h"

VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns = { 0,
                                                          0,
                                                          0,
                                                          0,
                                                          0,
                                                          0,
                                                          0 };

int __wrap_ioctl(int fh, int request, void *arg)
{
    if (VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno)
    {
        errno = VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value;
    }
    if (VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct)
    {
        switch(request) 
        {
            case VIDIOC_QUERYCAP:
                ((struct v4l2_capability *)arg)->capabilities = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                break;
    
            default:
            break;
        }
        
    }
    return VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return;
}


int __wrap_open(char *filename, int  access, int  permission)
{
    if (VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno)
    {
        errno = VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno_Value;
    }
    return VC_Platform_Stubs_Returns.VC_Wrap_Open_Return;
}
