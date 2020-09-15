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

#ifndef ICM20689_TBLDEFS_H
#define ICM20689_TBLDEFS_H

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
#include "icm20689_platform_cfg.h"
#include "icm20689_map.h"

/************************************************************************
** Local Defines
*************************************************************************/

/**
 * \brief Defines the table identification name used for the
 * configuration table registration.
 */
#define ICM20689_CONFIG_TABLENAME ("CONFIG_TBL")

#define ICM20689_MAX_CONFIG_LEN (6)

/** \brief Definition for a single config table entry */
typedef struct
{
    /** \brief Acceleration X-axis calibration scale. */
    float AccXScale;
    /** \brief Acceleration Y-axis calibration scale. */
    float AccYScale;
    /** \brief Acceleration Z-axis calibration scale. */
    float AccZScale;
    /** \brief Acceleration X-axis calibration offset. */
    float AccXOffset;
    /** \brief Acceleration Y-axis calibration offset. */
    float AccYOffset;
    /** \brief Acceleration Z-axis calibration offset. */
    float AccZOffset;
    /** \brief Gyro X-axis calibration scale. */
    float GyroXScale;
    /** \brief Gyro Y-axis calibration scale. */
    float GyroYScale;
    /** \brief Gyro Z-axis calibration scale. */
    float GyroZScale;
    /** \brief Gyro X-axis calibration offset. */
    float GyroXOffset;
    /** \brief Gyro Y-axis calibration offset. */
    float GyroYOffset;
    /** \brief Gyro Z-axis calibration offset. */
    float GyroZOffset;
    /** \brief Room temperature offset. */
    float TempOffset;
    /** \brief Temperature sensitivity. */
    float TempSensitivity;
    /** \brief Who Am I Register Value. */
    uint8 WhoAmIValue;
    /** \brief Accel unit value */
    float AccUnit;
    /** \brief Gyro unit value */
    float GyroUnit;
    /** \brief Accel divider value */
    float AccDivider;
    /** \brief Gyro divider value */
    float GyroDivider;
    /** \brief Gyro divider value */
    float AccScale;
    /** \brief Gyro divider value */
    float GyroScale;
    /* Settings */
    /** \brief Gyro scale setting. */
    uint8 GyroScaleSetting;
    /** \brief Accel scale setting. */
    uint8 AccelScaleSetting;
    /** \brief Clock source setting. */
    uint8 ClockSourceSetting;
    /** \brief Sample rate divider setting. */
    uint8 SampleRateDivSetting;
    /* SPI settings */
    /** \brief SPI device mode. */
    int8 SpiModeSetting;
    /** \brief SPI device bits. */
    int8 SpiBitsSetting;
    /** \brief SPI device speed. */
    uint32 SpiSpeedSetting;
    /** \brief SPI device path. */
    char SpiPathSetting[OS_MAX_PATH_LEN];
    /** \brief SPI path settings. */
    /* Delays */
    /** \brief Reset delay uS. */
    uint32 ResetDelayUs;
    /** \brief Init delay uS. */
    uint32 InitDelayUs;
    /** \brief Wakeup delay uS. */
    uint32 WakeupDelayUs;
    /** \brief Retry delay uS. */
    uint32 RetryDelayUs;
    /* Configuration */
    /** \brief Registers for initialization. */
    uint8 ConfigRegisters[ICM20689_MAX_CONFIG_LEN];
    /** \brief Values for initialization. */
    uint8 ConfigValues[ICM20689_MAX_CONFIG_LEN];
    /** \brief The number of registers to configure at initialization. */
    uint8 ConfigCount;

} ICM20689_ConfigTbl_t;


#ifdef __cplusplus
}
#endif

#endif /* ICM20689_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
