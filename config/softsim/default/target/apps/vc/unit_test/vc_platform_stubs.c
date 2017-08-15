#include <sys/ioctl.h>
#include <errno.h>
#include "vc_platform_stubs.h"

VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns = { 0,
                                                          0,
                                                          0 };

int __wrap_ioctl(int fh, int request, void *arg)
{
    if (VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno)
    {
        errno = VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Errno_Value;
    }
    return VC_Platform_Stubs_Returns.VC_Wrap_Ioctl_Return;
}
