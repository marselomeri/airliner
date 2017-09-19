#ifndef TO_PLATFORM_STUBS_H
#define TO_PLATFORM_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int     TO_Wrap_Socket_Return;
    int     TO_Wrap_Socket_Errno;
    int     TO_Wrap_Socket_Errno_Value;
    int     TO_Wrap_Bind_Return;
    int     TO_Wrap_Bind_Errno;
    int     TO_Wrap_Bind_Errno_Value;
    int     TO_Wrap_SendTo_Return;
    int     TO_Wrap_SendTo_Errno;
    int     TO_Wrap_SendTo_Errno_Value;
} TO_Platform_Stubs_Returns_t;

extern TO_Platform_Stubs_Returns_t TO_Platform_Stubs_Returns;


#ifdef __cplusplus
}
#endif

#endif /* TO_PLATFORM_STUBS_H */
