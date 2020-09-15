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

#ifndef ICM20689_DEVICE_H
#define ICM20689_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "icm20689_tbldefs.h"
#include "icm20689_app.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Definitions
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief Initialize the device.
**
**  \par Description
**       This function performs device initialization.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean ICM20689_Device_Init(ICM20689_ConfigTbl_t* ConfigTblPtr);


int32 ICM20689_Reset_Device(ICM20689_ConfigTbl_t* ConfigTblPtr);

/************************************************************************/
/** \brief Returns the device ID.
**
**  \par Description
**       This returns the device ID for identification.
**
**  \par Assumptions, External Events, and Notes:
**       Initialization must be completed before this function is 
**       called. 
**
**  \param [out]   Value      Device ID value.
**
**  \returns TRUE for success, FALSE for failure.
**
*************************************************************************/
boolean ICM20689_Read_WhoAmI(uint8 *Value);

/************************************************************************/
/** \brief Read raw gyro data.
**
**  \par Description
**       This function reads raw X-axis, Y-axis, and Z-axis gyro data.
**
**  \par Assumptions, External Events, and Notes:
**       Initialization must be completed before this function is 
**       called.
**
**  \param [out]   X      Raw X-axis value.
**
**  \param [out]   Y      Raw Y-axis value.
**
**  \param [out]   Z      Raw Z-axis value.
**
**  \returns TRUE for success, FALSE for failure.
**
*************************************************************************/
boolean ICM20689_Read_Gyro(int16 *X, int16 *Y, int16 *Z);

/************************************************************************/
/** \brief Read raw accel data.
**
**  \par Description
**       This function reads raw X-axis, Y-axis, and Z-axis accel data.
**
**  \par Assumptions, External Events, and Notes:
**       Initialization must be completed before this function is 
**       called. 
**
**  \param [out]   X      Raw X-axis value.
**
**  \param [out]   Y      Raw Y-axis value.
**
**  \param [out]   Z      Raw Z-axis value.
**
**  \returns TRUE for success, FALSE for failure.
**
*************************************************************************/
boolean ICM20689_Read_Accel(int16 *X, int16 *Y, int16 *Z);

/************************************************************************/
/** \brief Read raw temperature data.
**
**  \par Description
**       This function reads raw temperature data.
**
**  \par Assumptions, External Events, and Notes:
**       Initialization must be completed before this function is 
**       called. 
**
**  \param [out]   Temp    Raw temperature value.
**
**  \returns TRUE for success, FALSE for failure.
**
*************************************************************************/
boolean ICM20689_Read_Temp(uint16 *Temp);

/************************************************************************/
/** \brief Get platform rotation.
**
**  \par Description
**       This function returns the rotation of the device.
**
**  \par Assumptions, External Events, and Notes:
**       None.
**
**  \param [out]   Rotation    The platform rotation.
**
*************************************************************************/
void ICM20689_Get_Rotation(uint8 *Rotation);

/************************************************************************/
/** \brief Apply the platform rotation to measurements.
**
**  \par Description
**       This applies any required platform rotation to the X, Y, and Z
**       measurements.
**
**  \par Assumptions, External Events, and Notes:
**       None. 
**
**  \param [in/out]   X      X-axis value.
**
**  \param [in/out]   Y      Y-axis value.
**
**  \param [in/out]   Z      Z-axis value.
**
**  \returns TRUE for success, FALSE for failure.
**
*************************************************************************/
boolean ICM20689_Apply_Platform_Rotation(float *X, float *Y, float *Z);

#ifdef __cplusplus
}
#endif 

#endif /* ICM20689_DEVICE_H */
