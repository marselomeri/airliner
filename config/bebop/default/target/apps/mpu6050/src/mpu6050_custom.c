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
#include "cfe.h"
#include "mpu6050_i2c.h"
#include "mpu6050_events.h"
#include "mpu6050_perfids.h"
#include "px4lib.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'MPU6050 - ' </tt>
**  \event <tt> 'MPU6050 - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    MPU6050_DEVICE_ERR_EID = MPU6050_EVT_CNT,

/** \brief <tt> 'MPU6050 - ' </tt>
**  \event <tt> 'MPU6050 - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    MPU6050_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    MPU6050_CUSTOM_EVT_CNT
} MPU6050_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
MPU6050_AppCustomData_t MPU6050_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 MPU6050_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < MPU6050_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(MPU6050_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


void MPU6050_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&MPU6050_AppCustomData, sizeof(MPU6050_AppCustomData));
}


boolean MPU6050_Custom_Init()
{
    boolean returnBool = TRUE;
    int32 returnCode   = 0;

    MPU6050_AppCustomData.DeviceFd = open(MPU6050_I2C_DEVICE_PATH, O_RDWR);
    if (MPU6050_AppCustomData.DeviceFd < 0) 
    {
        (void) CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 Device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }

    returnCode = MPU6050_ResetDevice();
    if (-1 == returnCode)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Reset device failed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* TODO Add Gyroscope Self-Test */
    /* TODO Add Accelerometer Self-Test */

    /* Set clock source. */
    returnBool = MPU6050_WriteReg(MPU6050_MPU_CLK_SEL_PLLGYROX, MPU6050_REG_PWR_MGMT_1, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Set clock source failed.");
        goto end_of_function;
    }

    usleep(1000);

    /* Clear any standby modes. */
    returnBool = MPU6050_WriteReg(0x00, MPU6050_REG_PWR_MGMT_2, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Enable Acc and Gyro failed");
        goto end_of_function;
    }

    usleep(1000);

    /* Set DLPF.  */
    returnBool = MPU6050_WriteReg(MPU6050_DEFAULT_LOWPASS_FILTER, MPU6050_REG_CONFIG, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Set DLPF failed. ");
        goto end_of_function;
    }

    usleep(1000);

    /* Set sample divider.  
     * sample rate = Gyroscope_Output_Rate / (1 + sample_divider)
     * If DLPF is disabled (0 or 7) Gyroscope_Output_Rate = 8 kHz
     * otherwise Gyroscope_Output_Rate = 1kHz */
    returnBool = MPU6050_WriteReg(0x00, MPU6050_REG_SMPLRT_DIV, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Set accel resolution failed. ");
        goto end_of_function;
    }
    
    usleep(1000);

    /* Set gyro resolution. */
    returnBool = MPU6050_WriteReg(MPU6050_BITS_FS_2000DPS, MPU6050_REG_GYRO_CONFIG, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Set gyro resolution failed. ");
        goto end_of_function;
    }

    usleep(1000);

    /* Set accel resolution. */
    returnBool = MPU6050_WriteReg(MPU6050_BITS_FS_4G, MPU6050_REG_ACCEL_CONFIG, 1);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Set accel resolution failed. ");
        goto end_of_function;
    }

    usleep(1000);

    /* LATCH_INT_EN INT pin level held unitl interrupt status is 
     * cleared. IN_ANYRD_2CLEAR interrupt status is cleared if
     * any read operation is performed. */
    //returnBool = MPU6050_WriteReg(0x30, MPU6050_REG_INT_PIN_CFG, 1);
    //if(FALSE == returnBool)
    //{
        //CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                //"Set accel resolution failed. ");
        //goto end_of_function;
    //}

    //usleep(1000);

    MPU6050_AppCustomData.Status = MPU6050_CUSTOM_INITIALIZED;

end_of_function:
    return returnBool;
}


boolean MPU6050_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    (void) MPU6050_ResetDevice();

    returnCode = close(MPU6050_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        returnBool = FALSE;
    }
    else
    {
        MPU6050_AppCustomData.Status = MPU6050_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


int32 MPU6050_ResetDevice(void)
{
    int32 ret = 0;
    boolean returnBool = TRUE;
    
    returnBool = MPU6050_WriteReg(MPU6050_BIT_H_RESET, MPU6050_REG_PWR_MGMT_1, 1);
    if (FALSE == returnBool) 
    {            
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU6050 ioctl returned %i", errno);
        ret = -1;
    }
    else
    {
        usleep(100000);
    }
    return ret;
}


boolean MPU6050_WriteReg(uint8 Addr, uint8 Data)
{
    int returnCode      = 0;
    boolean returnBool  = FALSE;
    struct i2c_msg Messages[1];
    struct i2c_rdwr_ioctl_data Packets;
    uint8 buf[2];

    buf[0] = Addr;
    buf[1] = Data;

    Messages[0].addr  = MPU6050_I2C_SLAVE_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf   = &buf[0];
    Messages[0].len   = 2;

    Packets.msgs  = Messages;
    Packets.nmsgs = 1;

    CFE_ES_PerfLogEntry(MPU6050_SEND_PERF_ID);
    returnCode = MPU6050_Ioctl(MPU6050_AppCustomData.DeviceFd, I2C_RDWR, &Packets);
    CFE_ES_PerfLogExit(MPU6050_SEND_PERF_ID);
    
    if (-1 == returnCode) 
    {            
        (void) CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU6050 ioctl returned errno %i", errno);
    }
    else
    {
        returnBool = TRUE;
    }

    return (returnBool);
}


boolean MPU6050_ReadReg(uint8 Reg, void *Buffer, size_t Length)
{
    int returnCode       = 0;
    boolean returnBool   = FALSE;
    uint8 cmd            = Reg;

    struct i2c_rdwr_ioctl_data Packets;
    struct i2c_msg Messages[2];

    /* send */
    Messages[0].addr  = MPU6050_I2C_SLAVE_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf   = &cmd;
    Messages[0].len   = 1;

    /* receive */
    Messages[1].addr  = MPU6050_I2C_SLAVE_ADDRESS;
    Messages[1].flags = MPU6050_I2C_M_READ;
    Messages[1].buf   = Buffer;
    Messages[1].len   = Length;

    Packets.msgs  = Messages;
    Packets.nmsgs = 2;

    CFE_ES_PerfLogEntry(MPU6050_RECEIVE_PERF_ID);
    returnCode = MPU6050_Ioctl(MPU6050_AppCustomData.DeviceFd, I2C_RDWR, &Packets);
    CFE_ES_PerfLogExit(MPU6050_RECEIVE_PERF_ID);

    if (-1 == returnCode) 
    {            
        (void) CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU6050 ioctl returned errno %i", errno);
    }
    else
    {
        returnBool = TRUE;
    }

    return (returnBool);
}





boolean MPU6050_SetAccScale(uint8 Scale, float *AccDivider)
{
    boolean returnBool = TRUE;
    uint8 value = 0;

    /* Null pointer check */
    if(0 == AccDivider)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 SetAccScale Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 2:
            *AccDivider = 16384;
            value = MPU6050_BITS_FS_2G;
            break;

        case 4:
            *AccDivider = 8192;
            value = MPU6050_BITS_FS_4G;
            break;

        case 8:
            *AccDivider = 4096;
            value = MPU6050_BITS_FS_8G;
            break;

        case 16:
            *AccDivider = 2048;
            value = MPU6050_BITS_FS_16G;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

    returnBool = MPU6050_WriteReg(MPU6050_REG_ACCEL_CONFIG, value, 1);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU6050_SetGyroScale(uint32 Scale, float *GyroDivider)
{
    boolean returnBool = TRUE;
    uint8 value = 0;

    /* Null pointer check */
    if(0 == GyroDivider)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 SetGyroScale Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 250:
            *GyroDivider = 131;
            value = MPU6050_BITS_FS_250DPS;
            break;

        case 500:
            *GyroDivider = 65.5;
            value = MPU6050_BITS_FS_500DPS;
            break;

        case 1000:
            *GyroDivider = 32.8;
            value = MPU6050_BITS_FS_1000DPS;
            break;

        case 2000:
            *GyroDivider = 16.4;
            value = MPU6050_BITS_FS_2000DPS;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

    returnBool = MPU6050_WriteReg(MPU6050_REG_GYRO_CONFIG, value, 1);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


/* Todo update to passing a structure to this function. */
boolean MPU6050_Measure(int16 *GX, int16 *GY, int16 *GZ, int16 *AX, int16 *AY, int16 *AZ, int16 Temp)
{
    uint8 intStatus = 0;
    MPU6050_Sample_t sample = {0};
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == GX || 0 == GY || 0 == GZ || 0 == AX || 0 == AY || 0 == AZ || 0 == Temp)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 Read_Gyro Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Check data ready interrupt bit. */
    returnBool = MPU6050_ReadReg(MPU6050_REG_INT_STATUS, &intStatus);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Check for DATA_RDY_INT set... */
    if(intStatus & MPU6050_BIT_INT_STATUS_DATA)
    {
        returnBool = MPU6050_ReadReg(MPU6050_REG_GYRO_XOUT_H, &sample, sizeof(sample));
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
    }
    else
    {
        /* Data not ready skipping measurement. */
        returnBool = FALSE;
        goto end_of_function;
    }

    *GX = MPU6050_Swap16(sample.val[0]);
    *GY = MPU6050_Swap16(sample.val[1]);
    *GZ = MPU6050_Swap16(sample.val[2]);
    *Temp = MPU6050_Swap16(sample.val[3]);
    *AX = MPU6050_Swap16(sample.val[4]);
    *AY = MPU6050_Swap16(sample.val[5]);
    *AZ = MPU6050_Swap16(sample.val[6]);

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 read error in Measure");
    }
    return returnBool;
}


boolean MPU6050_Read_WhoAmI(uint8 *Value)
{
    boolean returnBool = TRUE;
    /* Null pointer check */
    if(0 == Value)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 Read_WhoAmI Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = MPU6050_ReadReg(MPU6050_REG_WHOAMI, Value, 1);

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 read error in WhoAmI");
    }
    return returnBool;
}


boolean MPU6050_Perform_AccelSelfTest(void)
{
    return TRUE;
}


boolean MPU6050_Perform_GyroSelfTest(void)
{
    return TRUE;
}


boolean MPU6050_Apply_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;
    float temp;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 Apply_Platform_Rotation Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }
    /* ROTATION_ROLL_180 */
    *Y = -*Y; 
    *Z = -*Z;

end_of_function:

    return returnBool;
}


boolean MPU6050_Custom_Max_Events_Not_Reached(int32 ind)
{
    if ((ind < CFE_EVS_MAX_EVENT_FILTERS) && (ind > 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


int32 MPU6050_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == MPU6050_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = MPU6050_DEVICE_ERR_EID;
        EventTbl[customEventCount++].Mask    = CFE_EVS_FIRST_16_STOP;
    }
    else
    {
        customEventCount = -1;
        goto end_of_function;
    }
    
end_of_function:

    return customEventCount;
}


void MPU6050_Get_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        CFE_EVS_SendEvent(MPU6050_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU6050 Get_Rotation Null Pointer");
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_ROLL_180;

end_of_function:
;
}


uint16 MPU6050_Swap16(uint16 val) 
{
    return (val >> 8) | (val << 8); 
}
