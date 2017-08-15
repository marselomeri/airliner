#include <sys/ioctl.h>

int __wrap_ioctl(int fh, int request, void *arg)
{
    return -1;
}
