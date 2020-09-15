/****************************************************************************
*
*   Copyright (c) 2020 Windhover Labs, L.L.C. All rights reserved.
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
#include "icm20689_spi.h"
#include "icm20689_events.h"
#include "icm20689_perfids.h"
#include "icm20689_map.h"
#include "icm20689_device.h"
#include "px4lib.h"
#include <unistd.h>
#include <errno.h>

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

boolean ICM20689_Device_Init(ICM20689_ConfigTbl_t* ConfigTblPtr)
{
    boolean returnBool = TRUE;
    int ret = 0;
    int i = 0;

    ret = ICM20689_Reset_Device(ConfigTblPtr);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Reset device failed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    for(i = 0; i < ConfigTblPtr->ConfigCount; i++) 
    {
        returnBool = ICM20689_Write_Reg(ConfigTblPtr->ConfigRegisters[i],
                                       ConfigTblPtr->ConfigValues[i]);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
        usleep(ConfigTblPtr->InitDelayUs);
    }

end_of_function:
    return returnBool;
}


int32 ICM20689_Reset_Device(ICM20689_ConfigTbl_t* ConfigTblPtr)
{
    int32 ret = 0;
    boolean returnBool = TRUE;
    
    returnBool = ICM20689_Write_Reg(ICM20689_PWR_MGMT_1, ICM20689_MASK_DEVICE_RESET);
    if (FALSE == returnBool) 
    {            
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689_Write_Reg returned %i", errno);
        ret = -1;
    }
    else
    {
        usleep(ConfigTblPtr->ResetDelayUs);
    }
    return ret;
}


boolean ICM20689_Read_Gyro(int16 *X, int16 *Y, int16 *Z)
{
    uint8 hValue = 0;
    uint8 lValue = 0;
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Read_Gyro Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_XOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_XOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *X = (hValue << 8) | lValue;

    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_YOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_YOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *Y = (hValue << 8) | lValue;

    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_ZOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_GYRO_ZOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *Z = (hValue << 8) | lValue;

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 read error in Read_Gyro");
    }
    return returnBool;
}


boolean ICM20689_Read_Accel(int16 *X, int16 *Y, int16 *Z)
{
    uint8 hValue = 0;
    uint8 lValue = 0;
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Read_Accel Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_XOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_XOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *X = (hValue << 8) | lValue;

    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_YOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_YOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *Y = (hValue << 8) | lValue;

    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_ZOUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_ACCEL_ZOUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    *Z = (hValue << 8) | lValue;

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 read error in Read_Accel");
    }
    return returnBool;
};


boolean ICM20689_Read_Temp(uint16 *Temp)
{
    uint8 hValue = 0;
    uint8 lValue = 0;
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == Temp)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Read_Temp Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = ICM20689_Read_Reg(ICM20689_TEMP_OUT_H, &hValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    returnBool = ICM20689_Read_Reg(ICM20689_TEMP_OUT_L, &lValue);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    *Temp = (hValue << 8) | lValue;

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 read error in Read_Temp");
    }
    return returnBool;
}


boolean ICM20689_Read_WhoAmI(uint8 *Value)
{
    boolean returnBool = TRUE;
    /* Null pointer check */
    if(0 == Value)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Read_WhoAmI Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = ICM20689_Read_Reg(ICM20689_WHO_AM_I, Value);

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 read error in WhoAmI");
    }
    return returnBool;
}


boolean ICM20689_Apply_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Apply_Platform_Rotation Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }
    /* ROTATION_PITCH_180 */
    *X = -*X; 
    *Z = -*Z;

end_of_function:

    return returnBool;
}


void ICM20689_Get_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "ICM20689 Get_Rotation Null Pointer");
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_PITCH_180;

end_of_function:
    return;
}
