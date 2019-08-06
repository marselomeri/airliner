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

#include "mpu9250_custom_stubs.h"
#include "mpu9250_custom.h"

MPU9250_Custom_Returns_t MPU9250_Custom_Returns;


void MPU9250_Custom_InitData(void)
{
    
}


boolean MPU9250_Custom_Init(void)
{
    return TRUE;
}


boolean MPU9250_Custom_Uninit(void)
{
    return TRUE;
}


int32 MPU9250_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    return 0;
}


boolean MPU9250_SetAccScale(uint8 Scale, float *AccDivider)
{
    return TRUE;
}


boolean MPU9250_SetGyroScale(uint32 Scale, float *GyroDivider)
{
    return TRUE;
}

boolean MPU9250_Measure(MPU9250_SampleQueue_t *SampleQueue)
{
    SampleQueue->Samples[0].GX = MPU9250_Custom_Returns.MPU9250_Read_Gyro_X_Value;
    SampleQueue->Samples[0].GY = MPU9250_Custom_Returns.MPU9250_Read_Gyro_Y_Value;
    SampleQueue->Samples[0].GZ = MPU9250_Custom_Returns.MPU9250_Read_Gyro_Z_Value;
    SampleQueue->Samples[0].AX = MPU9250_Custom_Returns.MPU9250_Read_Accel_X_Value;
    SampleQueue->Samples[0].AY = MPU9250_Custom_Returns.MPU9250_Read_Accel_Y_Value;
    SampleQueue->Samples[0].AZ = MPU9250_Custom_Returns.MPU9250_Read_Accel_Z_Value;
    SampleQueue->Samples[0].MX = MPU9250_Custom_Returns.MPU9250_Read_Mag_X_Value;
    SampleQueue->Samples[0].MY = MPU9250_Custom_Returns.MPU9250_Read_Mag_Y_Value;
    SampleQueue->Samples[0].MZ = MPU9250_Custom_Returns.MPU9250_Read_Mag_Z_Value;
    SampleQueue->Samples[0].Temp = MPU9250_Custom_Returns.MPU9250_Read_Temp_Value;
    SampleQueue->Samples[0].MagDataValid = TRUE;
    SampleQueue->SampleCount = 1;

    return TRUE;
}


boolean MPU9250_Read_WhoAmI(uint8 *Value)
{
    *Value = MPU9250_Custom_Returns.MPU9250_WhoAmI_Value;
    return MPU9250_Custom_Returns.MPU9250_WhoAmI_Return;
}


boolean MPU9250_Read_MagDeviceID(uint8 *Value)
{
    return TRUE;
}


uint64 PX4LIB_GetPX4TimeUs(void)
{
    return MPU9250_Custom_Returns.MPU9250_Get_Time_Return;
}


boolean MPU9250_Apply_Platform_Rotation(float *X, float *Y, float *Z)
{
    return TRUE;
}


void MPU9250_Get_Rotation(uint8 *Rotation)
{
    
}


void MPU9250_Get_Mag_Rotation(uint8 *Rotation)
{
 
}


boolean MPU9250_Apply_Mag_Platform_Rotation(float *X, float *Y, float *Z)
{
    return TRUE;
}


boolean MPU9250_Read_MagAdj(uint8 *X, uint8 *Y, uint8 *Z)
{
    return TRUE;
} 
