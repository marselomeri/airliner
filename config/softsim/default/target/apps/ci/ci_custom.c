
#include "ci_custom.h"
#include "ci_platform_cfg.h"
#include <fcntl.h>
#include <errno.h>

#define CI_CUSTOM_RETURN_CODE_NULL_POINTER      (-1)


typedef struct
{
    int fd;
} CI_AppCustomData_t;

CI_AppCustomData_t CI_AppCustomData;



int32 CI_InitCustom(void)
{
    int32 returnCode = 0;

    CI_AppCustomData.fd = open(CI_CUSTOM_DEV_PATH, O_RDONLY);

    if(CI_AppCustomData.fd < 0)
    {
        /* The open failed.  Just return the errno and let the caller send an
         * event message.
         */
        returnCode = errno;
    }

    return returnCode;
}


int32 CI_ReadMessage(const char* buffer, uint32* size)
{
    int32 returnCode = 0;

    /* Check the input parameters. */
    if(buffer == 0)
    {
        returnCode = CI_CUSTOM_RETURN_CODE_NULL_POINTER;
    }
    else
    {
        returnCode = read(CI_AppCustomData.fd, buffer, *size);
        if(returnCode < 0)
        {
            /* The read failed.  Just return the errno and let the caller send an
             * event message.
             */
            returnCode = errno;
            *size = 0;
        }
        else
        {
            *size = returnCode;
        }
    }

    return returnCode;
}


int32 CI_CleanupCustom(void)
{
    return close(CI_AppCustomData.fd);
}

