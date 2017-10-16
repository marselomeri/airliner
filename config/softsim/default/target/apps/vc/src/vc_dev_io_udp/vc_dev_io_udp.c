/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

VC_AppCustomDevice_t VC_AppCustomDevice;


int32 VC_Devices_InitData(void)
{
    int32 iStatus = CFE_SUCCESS;
    
    /* Set all struct zero values */
    bzero(&VC_AppCustomDevice, sizeof(VC_AppCustomDevice));
    
    /* Set all non-zero values for channel zero */
    VC_AppCustomDevice.Channel[0].Status        = VC_DEVICE_UNINITIALIZED;
    VC_AppCustomDevice.Channel[0].Mode          = VC_DEVICE_ENABLED;
    /* TODO move these to platform config */
    VC_AppCustomDevice.Channel[0].Socket        = 0;
    VC_AppCustomDevice.Channel[0].Port          = 5600;

    return (iStatus);
}


boolean VC_Devices_Start(void)
{
    int32 returnCode = 0;
    
    /* Set loop flag to continue forever */
    VC_AppCustomDevice.ContinueFlag = TRUE;
    
    /* Start streaming on all devices */
    if(-1 == VC_Start_Streaming())
    {
        VC_AppCustomDevice.ContinueFlag = FALSE;
        return FALSE;
    }

    /* Create the streaming task */
    returnCode = CFE_ES_CreateChildTask(
        &VC_AppCustomDevice.ChildTaskID,
        VC_STREAMING_TASK_NAME,
        VC_AppCustomDevice.StreamingTask,
        0,
        CFE_ES_DEFAULT_STACK_SIZE,
        VC_AppCustomDevice.Priority,
        0);

    if(returnCode != CFE_SUCCESS)
    {
        VC_AppCustomDevice.ContinueFlag = FALSE;
        return FALSE;
    }
    return TRUE;
}


boolean VC_Devices_Stop(void)
{
    /* Delete the child task */
    CFE_ES_DeleteChildTask(VC_AppCustomDevice.ChildTaskID);
    
    /* Set streaming task loop flag to stop */
    VC_AppCustomDevice.ContinueFlag = FALSE;
    
    /* Set app state to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    
    if(-1 == VC_Stop_Streaming())
    {
        return FALSE;
    }
    return TRUE;
}


boolean VC_Devices_Init(void)
{
    if(-1 == VC_Init_CustomDevices())
    {
        return FALSE;
    }
    return TRUE;
}

boolean VC_Devices_Uninit(void)
{
    if(-1 == VC_CleanupDevices())
    {
        return FALSE;
    }
    return TRUE;
}


int32 VC_CleanupDevices(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_DEVICES; i++)
    {
        if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED)
        {
            if(-1 == close(VC_AppCustomDevice.Channel[i].Socket))
            {
                /* Close failed */
                returnCode = -1;
            }
            else
            {
                VC_AppCustomDevice.Channel[i].Mode = VC_DEVICE_DISABLED;
            }
        }
    }
    return returnCode;
}


int32 VC_Init_CustomDevices(void)
{
    int32 returnCode = 0;
    int reuseaddr = 1;
    struct sockaddr_in address;
    uint32 i = 0;

    for (i=0; i < VC_MAX_DEVICES; i++)
    {
        if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED)
        {
            /* Create socket */
            VC_AppCustomDevice.Channel[i].Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (VC_AppCustomDevice.Channel[i].Socket < 0)
            {
                CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR, "Socket errno: %i", errno);
                returnCode = -1;
                /* Socket creation failed set device to disabled */
                VC_AppCustomDevice.Channel[i].Mode = VC_DEVICE_DISABLED;
                goto end_of_function;
            }
            setsockopt(VC_AppCustomDevice.Channel[i].Socket, SOL_SOCKET, 
                    SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
            bzero((char *) &address, sizeof(address));
            address.sin_family      = AF_INET;
            address.sin_addr.s_addr = htonl (INADDR_ANY);
            address.sin_port        = htons(VC_AppCustomDevice.Channel[i].Port);
        }
        if((bind(VC_AppCustomDevice.Channel[i].Socket , (struct sockaddr *) &address, sizeof(address)) < 0))
        {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,"Bind socket failed = %d", errno);
        returnCode = -1;
        goto end_of_function;
        }
        CFE_EVS_SendEvent(VC_DEV_INF_EID, CFE_EVS_INFORMATION,
                "VC Device configured channel %u", (unsigned int)i);
    }
    return returnCode;
}


void VC_Stream_Task(void)
{
    int32 returnCode = 0;
    static int32 timeouts = 0;
    
    uint32 i = 0;
    uint32 j = 0;
    uint32 maxFd = 0;
    static uint32 retryAttempts = 0;
    fd_set fds;
    
    struct timeval timeValue;
    uint32 iStatus = -1;
    
    iStatus = CFE_ES_RegisterChildTask();
    
    if (iStatus == CFE_SUCCESS)
    {
        while (VC_AppCustomDevice.ContinueFlag == TRUE)
        {
            maxFd = 0;
            returnCode = 0;
            
            /* Select modifies the timeout value with time left until 
             * the timeout would expire so timeValue needs to be set
             * every loop iteration
             */
            timeValue.tv_sec = VC_BUFFER_FILL_TIMEOUT_SEC;
            timeValue.tv_usec = VC_BUFFER_FILL_TIMEOUT_USEC;

            /* Initialize the set */
            FD_ZERO(&fds);
        
            /* Add enabled and streaming devices to the fd set */
            for (i=0; i < VC_MAX_DEVICES; i++)
            {
                if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED 
                && VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING)
                {
                    FD_SET(VC_AppCustomDevice.Channel[i].Socket, &fds);
            
                    /* Get the greatest fd value for select() */
                    if (VC_AppCustomDevice.Channel[i].Socket > maxFd)
                    {
                        /* maxFd is needed for select */
                        maxFd = VC_AppCustomDevice.Channel[i].Socket; 
                    }
                }
            }
            /* If maxFd is > 0 a fd was added the set so call select */
            if (maxFd > 0)
            {
                CFE_ES_PerfLogEntry(VC_DEVICE_GET_PERF_ID);
                /* Wait for a queued buffer to be filled by the device */
                returnCode = select(maxFd + 1, &fds, 0, 0, &timeValue);
                CFE_ES_PerfLogExit(VC_DEVICE_GET_PERF_ID);
            }
            else
            {
                /* No fd's were added to the set so error out */
                CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC can't start streaming no devices are streaming enabled");
                returnCode = -1;
                goto end_of_function;
            }
            
            /* select() wasn't successful */
            if (-1 == returnCode)
            {
                /* select was interrupted, try again */
                if (EINTR == errno)
                {
                    if (retryAttempts == VC_MAX_RETRY_ATTEMPTS)
                    {
                        goto end_of_function;
                    }
                    retryAttempts++;
                    usleep(VC_MAX_RETRY_SLEEP_USEC);
                    CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC select was interrupted");
                    continue;
                }
                else
                {
                    /* select returned an error other than EINTR */
                    CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC start streaming failed select() returned %i", errno);
                    goto end_of_function;
                }
            }
            /* select timed out */
            if (0 == returnCode)
            {
                if (timeouts == VC_BUFFER_TIMEOUTS_ALLOWED)
                {
                    returnCode = -1;
                    goto end_of_function;
                }
                timeouts++;
                usleep(VC_MAX_RETRY_SLEEP_USEC);
                CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC select timed out");
                continue;
            } 
            /* select() returned and a buffer is ready to be dequeued */
            if(returnCode > 0)
            {   
                /* Determine which device is ready */    
                for (i=0; i < VC_MAX_DEVICES; i++)
                {
                    if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED 
                    && VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING)
                    {
                        if(FD_ISSET(VC_AppCustomDevice.Channel[i].Socket, &fds))
                        {
                            /* Call send buffer with the device that is ready */
                            VC_Send_Buffer(i);
                        }
                    }
                }
            }    
        } /* end while loop */
    } /* end if status == success */

end_of_function:

    /* Streaming task is exiting so set app flag to initialized */
    VC_AppData.AppState = VC_INITIALIZED;
    CFE_EVS_SendEvent(VC_DEV_INF_EID, CFE_EVS_INFORMATION,
        "VC streaming task exited with return code %li task status (0x%08lX)",
        returnCode, iStatus);

    /* The child task was successfully created so exit from it */
    if (iStatus == CFE_SUCCESS)
    {
        CFE_ES_ExitChildTask();
    }
}



int32 VC_Send_Buffer(uint8 DeviceID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    uint32 size;
    /* TODO: Move this buffer size to platform config */
    char *buffer[65527];
    
    
    /* ADD MAGIC HERE FOR MULTIPARTMUX OVER UDP*/
    //while(size != 65527 && 
        //size += recv(VC_AppCustomDevice.Channel[i].Socket, buffer, , 0);


    
    /* Send data, for now map device id to senddata channel */
    if (-1 == VC_SendData(DeviceID, (void*)buffer, size))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC send data failed on channel %u", (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    

    
end_of_function:
    return returnCode;
}
