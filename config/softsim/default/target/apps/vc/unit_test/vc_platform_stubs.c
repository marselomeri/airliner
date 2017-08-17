#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>


#include <sys/time.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include "vc_platform_stubs.h"
#include "vc_platform_cfg.h"

int enable_wrappers = 0;

int __real_open(char *filename, int  access, int  permission);
int __real_close(int fildes);
int __real_ioctl(int fh, int request, void *arg);
int __real_select(int nfds, fd_set *readfds, fd_set *writefds, 
                    fd_set *exceptfds, struct timeval *timeout);

VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns = {0};

int __wrap_ioctl(int fh, int request, void *arg)
{
    int returnCode = 0;

    if(enable_wrappers == 0)
    {
        returnCode = __real_ioctl(fh, request, arg);
    }
    else
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
                    if(1 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct)
                    {
                        ((struct v4l2_capability *)arg)->capabilities = VC_V4L_BUFFER_TYPE;
                    }
                    if(2 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct)
                    {
                        ((struct v4l2_capability *)arg)->capabilities = (VC_V4L_BUFFER_TYPE +
                        V4L2_CAP_STREAMING);
                    }
                    break;
                case VIDIOC_S_FMT:
                        ((struct v4l2_format *)arg)->fmt.pix.pixelformat = VC_V4L_VIDEO_FORMAT;
                        ((struct v4l2_format *)arg)->fmt.pix.width = VC_FRAME_WIDTH;
                        ((struct v4l2_format *)arg)->fmt.pix.height = VC_FRAME_HEIGHT;
                        ((struct v4l2_format *)arg)->fmt.pix.sizeimage = VC_MAX_BUFFER_SIZE;
                    break;
                case VIDIOC_REQBUFS:
                        ((struct v4l2_requestbuffers *)arg)->count = VC_V4L_BUFFER_REQUEST;
                case VIDIOC_DQBUF:
                    if(1 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct)
                    {
                        ((struct v4l2_buffer *)arg)->bytesused = VC_MAX_PACKET_SIZE;
                    }
                    if(2 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Struct)
                    {
                        ((struct v4l2_buffer *)arg)->bytesused = (VC_MAX_PACKET_SIZE + 1);
                    }
                        
                default:
                    break;
            }
        }

        if (1 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_CallCount)
        {
            returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return1;
        }
        else if (2 == VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_CallCount)
        {
            returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return2;
        }
        else
        {
        returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return;
        }

        VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_CallCount++;
    }
    return returnCode;
}


int __wrap_open(char *filename, int  access, int  permission)
{
    int returnCode = 0;

    if(enable_wrappers == 0)
    {
        returnCode = __real_open(filename, access, permission);
    }
    else
    {
        if (VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno)
        {
            errno = VC_Platform_Stubs_Returns.VC_Wrap_Open_Errno_Value;
        }
        returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Open_Return;
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
        returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Close_Return;
    }
    return returnCode;
}



int __wrap_select(int nfds, fd_set *readfds, fd_set *writefds, 
                    fd_set *exceptfds, struct timeval *timeout)
{
    int returnCode = 0;
    if(enable_wrappers == 0)
    {
        returnCode = __real_select(nfds, readfds, writefds, exceptfds, timeout);
    }
    else
    {
        if (VC_Platform_Stubs_Returns.VC_Wrap_Select_Errno)
        {
            errno = VC_Platform_Stubs_Returns.VC_Wrap_Select_Errno_Value;
        }
        returnCode = VC_Platform_Stubs_Returns.VC_Wrap_Select_Return;
    }
    return returnCode;
}

