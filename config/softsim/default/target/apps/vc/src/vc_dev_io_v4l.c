/*==============================================================================
Copyright (c) 2017, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of CmdIn nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY VCPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, VCEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "vc_dev_io_v4l.h"
#include "cfe.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <string.h>
#include "vc_app.h"
#include <linux/videodev2.h>

/**
 * Device modes
 */
typedef enum
{
    /*! Device state unused  */
    VC_DEVICE_UNUSED       = 0,
    /*! Device state disabled */
    VC_DEVICE_DISABLED     = 1,
    /*! Device state enabled */
    VC_DEVICE_ENABLED      = 2
} VC_DeviceMode_t;


/**
 * Device status
 */
typedef enum
{
    /*! Device status uninitialized */
    VC_DEVICE_UNINITIALIZED = 0,
    /*! Device status uninitialized */
    VC_DEVICE_INITIALIZED   = 1,
    /*! Device status streaming */
    VC_DEVICE_STREAMING     = 2
} VC_DeviceStatus_t;


/**
 * Buffer pointers for V4L user pointer IO
 */
typedef struct {
    /*! Pointer to user defined buffer */
    void   *ptr;
}VC_BufferPtr_t;


/**
 * Device handle
 */
typedef struct
{
    /*! Device status */
    VC_DeviceStatus_t   Status;
    /*! Device mode */
    VC_DeviceMode_t     Mode;
    /*! Device resource channel identifier */
    uint8               ChannelID;
    /*! Path to device */
    char                DevName[VC_MAX_DEVICE_PATH];
    /*! Device file descriptor */
    int                 DeviceFd;
    /*! V4L buffer type */
    uint32              BufferType;
    /*! V4L frame width */
    uint32              FrameWidth;
    /*! V4L frame height */
    uint32              FrameHeight;
    /*! V4L video format */
    uint32              VideoFormat;
    /*! V4L field order */
    uint8               FieldOrder;
    /*! V4L buffer request */
    uint8               BufferRequest;
    /*! V4L memory type */
    uint32              MemoryType;
    /*! V4L user defined buffer(s) */
    char                Buffers[VC_V4L_BUFFER_REQUEST][VC_MAX_BUFFER_SIZE];
    /*! V4L buffer size (for all buffers)  */
    uint32              Buffer_Size;
    /*! V4L user defined buffer pointer(s) */
    VC_BufferPtr_t      Buffer_Ptrs[VC_V4L_BUFFER_REQUEST];
} VC_Device_Handle_t;


/**
 * Global data structure for custom device IO layer
 */
typedef struct
{
    /*! Flag to start and stop streaming */
    boolean                         ContinueFlag;
    /*! Streaming task priority */
    uint8                           Priority;
    /*! Streaming child task identifier */
    uint32                          ChildTaskID;
    /*! Streaming task function pointer */
    CFE_ES_ChildTaskMainFuncPtr_t   StreamingTask;
    /*! Device resource(s) channels */
    VC_Device_Handle_t              Channel[VC_MAX_DEVICES];
} VC_AppCustomDevice_t;


/**
 * Local Function Prototypes
 */
int32 VC_Init_CustomDevices(void); 
int32 VC_InitDevice(uint8 DeviceID, const char *DeviceName);
int32 VC_ConfigureDevice(uint8 DeviceID);
int32 VC_Start_Streaming(void);
int32 VC_Start_StreamingDevice(uint8 DeviceID);
void VC_Stream_Task(void);
int32 VC_Send_Buffer(uint8 DeviceID);
int32 VC_Stop_Streaming(void);
int32 VC_Stop_StreamingDevice(uint8 DeviceID);
int32 VC_DisableDevice(uint8 DeviceID);


/**
 * Custom device layer app data initialization
 */
VC_AppCustomDevice_t VC_AppCustomDevice = {
    .ContinueFlag = TRUE,
    .Priority = VC_STREAMING_TASK_PRIORITY,
    .ChildTaskID = 0,
    .StreamingTask = VC_Stream_Task,
    {
        { 
            .Status            = VC_DEVICE_UNINITIALIZED, \
            .Mode              = VC_DEVICE_ENABLED, \
            .ChannelID         = 0, \
            .DevName           = VC_DEVICE_PATH, \
            .DeviceFd          = 0, \
            .BufferType        = VC_V4L_BUFFER_TYPE, \
            .FrameWidth        = VC_FRAME_WIDTH, \
            .FrameHeight       = VC_FRAME_HEIGHT, \
            .VideoFormat       = VC_V4L_VIDEO_FORMAT, \
            .FieldOrder        = VC_V4L_VIDEO_FIELD_ORDER, \
            .BufferRequest     = VC_V4L_BUFFER_REQUEST, \
            .MemoryType        = VC_V4L_MEMORY_TYPE, \
            .Buffers           = {{0}}, \
            .Buffer_Size       = VC_MAX_BUFFER_SIZE, \
            .Buffer_Ptrs       = {0}
        }
    }
};


/**
 * @brief ioctl with limited EINTR retry attempts
 * @param fh file descriptor
 * @param request ioctl request code
 * @param arg pointer to a device specific struct
 * @return usually 0 for success and -1 for failure 
 * @note see ioctl man-page for more info
 */
static int32 VC_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode;
    uint32 i = 0;

    for (i=0; i < VC_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(VC_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


/**
 * Configure device resource
 * @param DeviceID the device ID of the resource to configure
 * @return 0 for success -1 for failure
 */
int32 VC_ConfigureDevice(uint8 DeviceID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    struct v4l2_format              Format;
    struct v4l2_capability          Capabilities;
    struct v4l2_requestbuffers      Request;
    struct v4l2_buffer              Buffer;

    bzero(&Format, sizeof(Format));
    Format.type                = VC_AppCustomDevice.Channel[DeviceID].BufferType;
    Format.fmt.pix.width       = VC_AppCustomDevice.Channel[DeviceID].FrameWidth;
    Format.fmt.pix.height      = VC_AppCustomDevice.Channel[DeviceID].FrameHeight;
    Format.fmt.pix.pixelformat = VC_AppCustomDevice.Channel[DeviceID].VideoFormat;
    Format.fmt.pix.field       = VC_AppCustomDevice.Channel[DeviceID].FieldOrder;

    bzero(&Request, sizeof(Request));
    Request.count              = VC_AppCustomDevice.Channel[DeviceID].BufferRequest;
    Request.type               = VC_AppCustomDevice.Channel[DeviceID].BufferType;
    Request.memory             = VC_AppCustomDevice.Channel[DeviceID].MemoryType;

    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_QUERYCAP, &Capabilities)) 
    {            
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC VIDIOC_QUERYCAP returned %i on %s channel %u", errno,
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    if (!(Capabilities.capabilities & VC_AppCustomDevice.Channel[DeviceID].BufferType)) 
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Capabilities %u on %s channel %u not found", 
                        (unsigned int)VC_AppCustomDevice.Channel[DeviceID].BufferType,
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    if (!(Capabilities.capabilities & V4L2_CAP_STREAMING)) 
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Capabilities %u on %s channel %u not found", 
                        V4L2_CAP_STREAMING,
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }

    VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_S_FMT, &Format);
    
    if (Format.fmt.pix.pixelformat != VC_AppCustomDevice.Channel[DeviceID].VideoFormat)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC device %s channel %u didn't accept format %u.",
                        VC_AppCustomDevice.Channel[DeviceID].DevName,
                        (unsigned int)DeviceID, 
                        (unsigned int)VC_AppCustomDevice.Channel[DeviceID].VideoFormat);
        returnCode = -1;
        goto end_of_function;
    }
    
    if ((Format.fmt.pix.width != VC_AppCustomDevice.Channel[DeviceID].FrameWidth) || 
    (Format.fmt.pix.height != VC_AppCustomDevice.Channel[DeviceID].FrameHeight))
    {
         CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC device %s channel %u didn't accept resolution instead %d:%d.",
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID, 
                        Format.fmt.pix.width, Format.fmt.pix.height);
        returnCode = -1;
        goto end_of_function;
    }
    
    if (Format.fmt.pix.sizeimage != VC_AppCustomDevice.Channel[DeviceID].Buffer_Size)
    {
         CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC device %s channel %u size image %u > buffer size %lu.",
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID, 
                        Format.fmt.pix.sizeimage, VC_AppCustomDevice.Channel[DeviceID].Buffer_Size);
        returnCode = -1;
        goto end_of_function;
    }
    
    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_REQBUFS, &Request))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC VIDIOC_REQBUFS returned %i on %s channel %u", errno,
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    if (Request.count != VC_AppCustomDevice.Channel[DeviceID].BufferRequest)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC VIDIOC_REQBUFS did not comply. Only %u buffers on %s channel %u", Request.count, 
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    for (i=0; i < VC_AppCustomDevice.Channel[DeviceID].BufferRequest; i++)
    {
        VC_AppCustomDevice.Channel[DeviceID].Buffer_Ptrs[i].ptr = (void*)&VC_AppCustomDevice.Channel[DeviceID].Buffers[i][0];
        
        bzero(&Buffer, sizeof(Buffer));
        Buffer.type            = VC_AppCustomDevice.Channel[DeviceID].BufferType;
        Buffer.memory          = VC_AppCustomDevice.Channel[DeviceID].MemoryType;
        Buffer.index           = i;
        Buffer.m.userptr       = (unsigned long)VC_AppCustomDevice.Channel[DeviceID].Buffer_Ptrs[i].ptr;
        Buffer.length          = VC_AppCustomDevice.Channel[DeviceID].Buffer_Size;

        if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_QBUF, &Buffer))
        {
            CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC VIDIOC_QBUF returned %i on %s channel %u", errno,
                        VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
            returnCode = -1;
            goto end_of_function;
        }
    }
    
end_of_function:
    return returnCode;
}


/**
 * @brief start streaming on a particular device
 * @param DeviceID the device ID to start streaming on
 * @return 0 for success -1 for failure
 */
int32 VC_Start_StreamingDevice(uint8 DeviceID)
{
    int32 returnCode = 0;
    enum v4l2_buf_type              Type;
    
    Type = VC_AppCustomDevice.Channel[DeviceID].BufferType;

    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_STREAMON, &Type))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "VC VIDIOC_STREAMON returned %i on %s channel %u", errno,
                    VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
    }
    else
    {
        //VC_AppCustomDevice.Channel[DeviceID].Status = VC_DEVICE_STREAMING;
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "VC VIDIOC_STREAMON success on %s channel %u", 
                    VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
    }

    return returnCode;
}


/**
 * @brief stop streaming on a particular device
 * @param DeviceID the device ID to stop streaming on
 * @return 0 for success -1 for failure
 */
int32 VC_Stop_StreamingDevice(uint8 DeviceID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    enum v4l2_buf_type Type;
    
    Type = VC_AppCustomDevice.Channel[DeviceID].BufferType;
    
    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_STREAMOFF, &Type))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC VIDIOC_STREAMOFF returned %i on %s channel %u", errno,
                    VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
    }
    else
    {
        //VC_AppCustomDevice.Channel[DeviceID].Status = VC_DEVICE_INITIALIZED;
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC VIDIOC_STREAMOFF success on %s channel %u", 
                    VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
    }
    return returnCode;
}


/**
 * @brief dequeue and send a buffer from a "ready" device
 * @param DeviceID the device ID of the "ready" device
 * @return 0 for success -1 for failure
 */
int32 VC_Send_Buffer(uint8 DeviceID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    boolean checkFlag = FALSE;
    
    struct v4l2_buffer Buffer;
    
    bzero(&Buffer, sizeof(Buffer));
    Buffer.type            = VC_AppCustomDevice.Channel[DeviceID].BufferType;
    Buffer.memory          = VC_AppCustomDevice.Channel[DeviceID].MemoryType;

    /* Dequeue the ready buffer */
    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_DQBUF, &Buffer))
    {
        /* VIDIOC_DQBUF failed */
            CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "VC VIDIOC_DQBUF returned %i on %s channel %u", errno,
                    VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
            returnCode = -1;
            goto end_of_function;
    }
    
    /* The dequeued buffer is larger than max transmit packet size */
    if (Buffer.bytesused > VC_MAX_PACKET_SIZE)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC Packet on %s channel %u is too large",
                VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
    }
    
    /* Check and make sure VIDIOC_DQBUF returned a valid address 
     * from possible addresses (user buffer pointers)
     */
    for (i=0; i < VC_AppCustomDevice.Channel[DeviceID].BufferRequest; i++)
    {
        if ((Buffer.m.userptr == (unsigned long)VC_AppCustomDevice.Channel[DeviceID].Buffer_Ptrs[i].ptr)
        && (Buffer.length == VC_AppCustomDevice.Channel[DeviceID].Buffer_Size))
        {
            checkFlag = TRUE;
        }
    }
    if (checkFlag == FALSE)
    {
        /* VIDIOC_DQBUF returned an unknown buffer address */
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC VIDIOC_DQBUF returned unknown user pointer on %s channel %u",
                VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    /* Send data, for now map device id to senddata channel */
    if (-1 == VC_SendData(DeviceID, (void*)Buffer.m.userptr, Buffer.bytesused))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC send data failed on %s channel %u",
                VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    /* Queue the next buffer */
    if (-1 == VC_Ioctl(VC_AppCustomDevice.Channel[DeviceID].DeviceFd, VIDIOC_QBUF, &Buffer))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "VC VIDIOC_QBUF returned %i on %s channel %u", errno,
                VC_AppCustomDevice.Channel[DeviceID].DevName, (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
end_of_function:
    return returnCode;
}


/**
 * @brief Streaming task, takes ready buffer and sends
 * @note This is a loop to be run in a VC app child task
 */
void VC_Stream_Task(void)
{
    int32 returnCode = 0;
    int32 timeouts = 0;
    
    uint32 i = 0;
    uint32 j = 0;
    uint32 maxFd = 0;
    uint32 retryAttempts = 0;
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
            retryAttempts = 0;
            
            /* select modifies the timeout value with time left until 
             * the timeout would expire so timeValue needs to be set
             * every loop iteration
             */
            timeValue.tv_sec = VC_BUFFER_FILL_TIMEOUT_SEC;
            timeValue.tv_usec = VC_BUFFER_FILL_TIMEOUT_USEC;

            /* initialize the set */
            FD_ZERO(&fds);
        
            /* Add enabled and streaming devices to the fd set */
            for (i=0; i < VC_MAX_DEVICES; i++)
            {
                if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED 
                && VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING)
                {
                    FD_SET(VC_AppCustomDevice.Channel[i].DeviceFd, &fds);
            
                    /* Get the greatest fd value for select() */
                    if (VC_AppCustomDevice.Channel[i].DeviceFd > maxFd)
                    {
                        /* maxFd is needed for select */
                        maxFd = VC_AppCustomDevice.Channel[i].DeviceFd; 
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
                    returnCode = -1;
                    goto end_of_function;
                }
            }
            /* select timed out */
            if (0 == returnCode)
            {
                if (timeouts < VC_BUFFER_TIMEOUTS_ALLOWED)
                {
                    timeouts++;
                    /* select timed out so query the buffer status for debug info */    
                    for (i=0; i < VC_MAX_DEVICES; i++)
                    {        
                        struct v4l2_buffer Buffer;
            
                        if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED 
                        && VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING)
                        {
                            for (j=0; j < VC_AppCustomDevice.Channel[i].BufferRequest; j++)
                            {  
                            bzero(&Buffer, sizeof(Buffer));
                            Buffer.type = VC_AppCustomDevice.Channel[i].BufferType;
                            Buffer.memory = VC_AppCustomDevice.Channel[i].MemoryType;
                            Buffer.index = j;
                    
                            VC_Ioctl(VC_AppCustomDevice.Channel[i].DeviceFd, VIDIOC_QUERYBUF, &Buffer);
                            CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                                "VC buffer flags for device channel %lu buffer %lu = %x", i, j, Buffer.flags);
                            }
                        }
                    }
                    continue;
                }
                else 
                {
                    CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC buffer timeout streaming stopped");
                }
            returnCode = -1;
            goto end_of_function;
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
                        if(FD_ISSET(VC_AppCustomDevice.Channel[i].DeviceFd, &fds))
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
    CFE_EVS_SendEvent(VC_DEV_INF_EID, CFE_EVS_INFORMATION,
        "VC streaming task exited with %lu", returnCode);
    CFE_ES_ExitChildTask();
}


/**
 * @brief Start streaming on all devices
 * @return 0 for success -1 for failure
 */
int32 VC_Start_Streaming(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_DEVICES; i++)
    {
        if((VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED) &&
        (VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_INITIALIZED))
        {
            if(-1 == VC_Start_StreamingDevice(i))
            {
                /* Start streaming failed */
                returnCode = -1;
            }
            else
            {
                /* Start streaming was successful set status to streaming */
                VC_AppCustomDevice.Channel[i].Status = VC_DEVICE_STREAMING;
            }
        }
    }
    return returnCode;
}


/**
 * @brief Stop streaming on all devices
 * @return 0 for success -1 for failure
 */
int32 VC_Stop_Streaming(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_DEVICES; i++)
    {
        if((VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED) &&
        (VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING))
        {
            if(-1 == VC_Stop_StreamingDevice(i))
            {
                /* Stop streaming failed */
                returnCode = -1;
            }
            else
            {
                /* Stop streaming was successful set status to initialized */
                VC_AppCustomDevice.Channel[i].Status = VC_DEVICE_INITIALIZED;
            }
        }
    }
    return returnCode;
}


/**
 * @brief Initialize an enabled device
 * @param DeviceID the device to initialize
 * @param DeviceName the device name (path) to open
 * @return 0 for success -1 for failure
 */
int32 VC_InitDevice(uint8 DeviceID, const char *DeviceName)
{
    int32 returnCode = 0;
    uint32 i = 0;

    if((VC_AppCustomDevice.Channel[DeviceID].Mode == VC_DEVICE_ENABLED) &
        (VC_AppCustomDevice.Channel[DeviceID].DeviceFd != 0))
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Device %s for channel %u already initialized.", DeviceName, (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    if(DeviceName == 0)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Device name for channel %u is null.", (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    if(DeviceID >= VC_MAX_DEVICES)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC DeviceID (%u) invalid.", (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }
    
    if((VC_AppCustomDevice.Channel[DeviceID].DeviceFd = open(DeviceName, O_RDWR | O_NONBLOCK, 0)) < 0)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Device open errno: %i on channel %u", errno, (unsigned int)i);
        //VC_AppCustomDevice.Channel[DeviceID].Mode = VC_DEVICE_DISABLED;
        returnCode = -1;
        goto end_of_function;
    }

end_of_function:
    return returnCode;
}


/**
 * @brief Initialize, configure, and start all enabled devices
 * @return usually 0 for success -1 for failure
 * @note see ioctl man-page for more info
 */
int32 VC_Init_CustomDevices(void)
{
    uint32 i = 0;
    int32 returnCode = 0;

    for (i=0; i < VC_MAX_DEVICES; i++)
    {
        if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED)
        {
            /* If the device is enabled initialize it */
            if (returnCode = VC_InitDevice(i, VC_AppCustomDevice.Channel[i].DevName))
            {
                /* If the device failed to be initialized set to disabled */
                VC_AppCustomDevice.Channel[i].Mode = VC_DEVICE_DISABLED;
            }
            else
            {
                /* Success, raise info event */
                CFE_EVS_SendEvent(VC_DEV_INF_EID, CFE_EVS_INFORMATION,
                        "VC Device initialized channel %u from %s",
                        (unsigned int)i, VC_AppCustomDevice.Channel[i].DevName);
                        
                /* The device is initialized so now configure it */
                if (returnCode = VC_ConfigureDevice(i))
                {
                    /* The device failed to be configured so make sure
                     * the status is set to uninitialized 
                     */
                    VC_AppCustomDevice.Channel[i].Status = VC_DEVICE_UNINITIALIZED;
                }
                else
                {
                    /* Success, set status to device initialized and
                     * raise a info event
                     */
                    VC_AppCustomDevice.Channel[i].Status = VC_DEVICE_INITIALIZED;
                        CFE_EVS_SendEvent(VC_DEV_INF_EID, CFE_EVS_INFORMATION,
                            "VC Device configured channel %u from %s",
                            (unsigned int)i, VC_AppCustomDevice.Channel[i].DevName);
                }
            }
        }
    }
    return returnCode;
}

/**
 * @brief Cleanup (stop & close) all enabled and initialized devices
 * @return 0 for success -1 for failure
 */
int32 VC_CleanupDevices(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_DEVICES; i++)
    {
        if(VC_AppCustomDevice.Channel[i].Mode == VC_DEVICE_ENABLED)
        {
            if(VC_AppCustomDevice.Channel[i].Status == VC_DEVICE_STREAMING)
            {    
                if(-1 == VC_Stop_StreamingDevice(i))
                {
                    /* VC_Stop_Streaming failed */
                    returnCode = -1;
                }
                else
                {
                    /* Success set device status to initialized */
                    VC_AppCustomDevice.Channel[i].Status = VC_DEVICE_INITIALIZED;
                }
            }
            
            if(-1 == VC_DisableDevice(i))
            {
                /* VC_DisableDevice failed */
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


/**
 * @brief Disable a device
 * @param DeviceID the device to enable
 * @return 0 for success -1 for failure
 */
int32 VC_DisableDevice(uint8 DeviceID)
{
    int32 returnCode = 0;

    if(VC_AppCustomDevice.Channel[DeviceID].Mode != VC_DEVICE_ENABLED)
    {
        CFE_EVS_SendEvent(VC_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "VC Device for channel %u is not enabled.", (unsigned int)DeviceID);
        returnCode = -1;
        goto end_of_function;
    }

    close(VC_AppCustomDevice.Channel[DeviceID].DeviceFd);

end_of_function:
    return returnCode;
}


/*
 * Start streaming on all enabled and initialized devices
 * True for success, false for failure
 * Creates streaming task
 */
boolean VC_Devices_Start(void)
{
    int32 returnCode = 0;
    
    /* Set loop flag to continue forever */
    VC_AppCustomDevice.ContinueFlag = TRUE;
    
    /* Start streaming on all devices */
    if(-1 == VC_Start_Streaming())
    {
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
        return FALSE;
    }
    return TRUE;
}


/*
 * Stop streaming on all enabled and initialized devices
 * True for success, false for failure
 */
boolean VC_Devices_Stop(void)
{
    /* Set streaming task loop flag to stop */
    VC_AppCustomDevice.ContinueFlag = FALSE;
    
    /* TODO: Wait for task to stop? */
    
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
