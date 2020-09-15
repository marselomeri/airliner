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
#ifndef ICM20689_APP_H
#define ICM20689_APP_H

#ifdef __cplusplus
extern "C" {
#endif


#define ICM20689_WHO_AM_I_VALUE     (0x98)
#define ICM20689_TEMPERATURE_SENS   (326.8f)
#define ICM20689_ROOM_TEMP_OFFSET   (25.0f)
/* Settings */
/* Auto select best clock source. */
#define ICM20689_SET_CLKSEL_1       (0x1)
/* Full scale. */
#define ICM20689_SET_GYRO_2000_DPS  (0x18)
/* Full scale. */
#define ICM20689_SET_ACCEL_16_G     (0x18)
/* 100 Hz sample rate. */
#define ICM20689_SET_SMPLRT_100HZ   (10U)
/* 250 Hz DLPF_CFG*/
#define ICM20689_SET_DLPF_CFG_250HZ (0)


typedef enum
{
    ICM20689_MASK_DEVICE_RESET  = 0x80,
    ICM20689_MASK_SLEEP         = 0x40,
    ICM20689_MASK_ACCEL_CYCLE   = 0x20,
    ICM20689_MASK_GYRO_STANDBY  = 0x10,
    ICM20689_MASK_TEMP_DIS      = 0x04,
    ICM20689_MASK_CLKSEL        = 0x03
} ICM20689_PwrMgmt1Mask_t;


typedef enum
{
    ICM20689_MASK_ACCEL_RST = 0x02,
    ICM20689_MASK_TEMP_RST  = 0x01
} ICM20689_SignalPathRstMask_t;


typedef enum
{
    ICM20689_MASK_DMP_EN       = 0x80,
    ICM20689_MASK_FIFO_EN      = 0x40,
    ICM20689_MASK_I2C_IF_DIS   = 0x10,
    ICM20689_MASK_DMP_RST      = 0x08,
    ICM20689_MASK_FIFO_RST     = 0x04,
    ICM20689_MASK_SIG_COND_RST = 0x01
} ICM20689_UserControlMask_t;


typedef enum
{
    ICM20689_MASK_FIFO_MODE    = 0x40,
    ICM20689_MASK_EXT_SYNC_SET = 0x38,
    ICM20689_MASK_DLPF_CFG     = 0x07
} ICM20689_ConfigMask_t;


typedef enum
{
    ICM20689_MASK_XA_ST        = 0x80,
    ICM20689_MASK_YA_ST        = 0x40,
    ICM20689_MASK_ZA_ST        = 0x20,
    ICM20689_MASK_ACCEL_FS_SEL = 0x18
} ICM20689_AccelConfigMask_t;


typedef enum
{
    ICM20689_MASK_FIFO_SIZE       = 0xC0,
    ICM20689_MASK_DEC2_CFG        = 0x30,
    ICM20689_MASK_ACCEL_FCHOICE_B = 0x08,
    ICM20689_MASK_A_DLPF_CFG      = 0x07
} ICM20689_AccelConfig2Mask_t;


typedef enum
{
    ICM20689_MASK_XG_ST     = 0x80,
    ICM20689_MASK_YG_ST     = 0x40,
    ICM20689_MASK_ZG_ST     = 0x20,
    ICM20689_MASK_FS_SEL    = 0x18,
    ICM20689_MASK_FCHOICE_B = 0x03
} ICM20689_GyroConfigMask_t;


typedef enum
{
    ICM20689_MASK_TEMP_FIFO_EN  = 0x80,
    ICM20689_MASK_XG_FIFO_EN    = 0x40,
    ICM20689_MASK_YG_FIFO_EN    = 0x20,
    ICM20689_MASK_ZG_FIFO_EN    = 0x10,
    ICM20689_MASK_ACCEL_FIFO_EN = 0x08
} ICM20689_FifoEnableMask_t;


typedef enum
{
    ICM20689_MASK_WOM_INT_EN      = 0xE0,
    ICM20689_MASK_FIFO_OFLOW_EN   = 0x10,
    ICM20689_MASK_GDRIVE_INT_EN   = 0x03,
    ICM20689_MASK_DMP_INT_EN      = 0x02,
    ICM20689_MASK_DATA_RDY_INT_EN = 0x01
} ICM20689_IntEnableMask_t;


/** \brief Register map. */
typedef enum
{
    ICM20689_SELF_TEST_X_GYRO  = 0x00,
    ICM20689_SELF_TEST_Y_GYRO  = 0x01,
    ICM20689_SELF_TEST_Z_GYRO  = 0x02,
    ICM20689_SELF_TEST_X_ACCEL = 0x0D,
    ICM20689_SELF_TEST_Y_ACCEL = 0x0E,
    ICM20689_SELF_TEST_Z_ACCEL = 0x0F,
    ICM20689_XG_OFFS_USRH      = 0x13,
    ICM20689_XG_OFFS_USRL      = 0x14,
    ICM20689_YG_OFFS_USRH      = 0x15,
    ICM20689_YG_OFFS_USRL      = 0x16,
    ICM20689_ZG_OFFS_USRH      = 0x17,
    ICM20689_ZG_OFFS_USRL      = 0x18,
    ICM20689_SMPLRT_DIV        = 0x19,
    ICM20689_CONFIG            = 0x1A,
    ICM20689_GYRO_CONFIG       = 0x1B,
    ICM20689_ACCEL_CONFIG      = 0x1C,
    ICM20689_ACCEL_CONFIG_2    = 0x1D,
    ICM20689_LP_MODE_CFG       = 0x1E,
    ICM20689_ACCEL_WOM_X_THR   = 0x20,
    ICM20689_ACCEL_WOM_Y_THR   = 0x21,
    ICM20689_ACCEL_WOM_Z_THR   = 0x22,
    ICM20689_FIFO_EN           = 0x23,
    ICM20689_FSYNC_INT         = 0x36,
    ICM20689_INT_PIN_CFG       = 0x37,
    ICM20689_INT_ENABLE        = 0x38,
    ICM20689_DMP_INT_STATUS    = 0x39,
    ICM20689_INT_STATUS        = 0x3A,
    ICM20689_ACCEL_XOUT_H      = 0x3B,
    ICM20689_ACCEL_XOUT_L      = 0x3C,
    ICM20689_ACCEL_YOUT_H      = 0x3D,
    ICM20689_ACCEL_YOUT_L      = 0x3E,
    ICM20689_ACCEL_ZOUT_H      = 0x3F,
    ICM20689_ACCEL_ZOUT_L      = 0x40,
    ICM20689_TEMP_OUT_H        = 0x41,
    ICM20689_TEMP_OUT_L        = 0x42,
    ICM20689_GYRO_XOUT_H       = 0x43,
    ICM20689_GYRO_XOUT_L       = 0x44,
    ICM20689_GYRO_YOUT_H       = 0x45,
    ICM20689_GYRO_YOUT_L       = 0x46,
    ICM20689_GYRO_ZOUT_H       = 0x47,
    ICM20689_GYRO_ZOUT_L       = 0x48,
    ICM20689_SIGNAL_PATH_RESET = 0x68,
    ICM20689_ACCEL_INTEL_CTRL  = 0x69,
    ICM20689_USER_CTRL         = 0x6A,
    ICM20689_PWR_MGMT_1        = 0x6B,
    ICM20689_PWR_MGMT_2        = 0x6C,
    ICM20689_FIFO_COUNTH       = 0x72,
    ICM20689_FIFO_COUNTL       = 0x73,
    ICM20689_FIFO_R_W          = 0x74,
    ICM20689_WHO_AM_I          = 0x75,
    ICM20689_XA_OFFSET_H       = 0x77,
    ICM20689_XA_OFFSET_L       = 0x78,
    ICM20689_YA_OFFSET_H       = 0x7A,
    ICM20689_YA_OFFSET_L       = 0x7B,
    ICM20689_ZA_OFFSET_H       = 0x7D,
    ICM20689_ZA_OFFSET_L       = 0x7E
} ICM20689_RegisterMap_t;





#ifdef __cplusplus
}
#endif

#endif /* ICM20689_APP_H */

/************************/
/*  End of File Comment */
/************************/
