#ifndef VC_PLATFORM_STUBS_H
#define VC_PLATFORM_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    int     VC_Wrap_Ioctl_Return;
    int     VC_Wrap_Ioctl_Errno;
    int     VC_Wrap_Ioctl_Errno_Value;
} VC_Platform_Stubs_Returns_t;


extern VC_Platform_Stubs_Returns_t VC_Platform_Stubs_Returns;


#ifdef __cplusplus
}
#endif

#endif /* VC_PLATFORM_STUBS_H */
