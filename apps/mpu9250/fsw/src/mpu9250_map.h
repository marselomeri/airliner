/****************************************************************************
*
*   Copyright (c) 2018 Windhover Labs, L.L.C. All rights reserved.
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

#ifndef MPU9250_MAP_H
#define MPU9250_MAP_H

/* MPU 9250 register map for Gyroscope and Accelerometer */
/* Self test output generated during manufacturing tests. */
/** \brief Factory self test output for gyro X-axis.*/
#define MPU9250_REG_GYRO_X_TEST             (0x00)
/** \brief Factory self test output for gyro Y-axis.*/
#define MPU9250_REG_GYRO_Y_TEST             (0x01)
/** \brief Factory self test output for gyro Z-axis.*/
#define MPU9250_REG_GYRO_Z_TEST             (0x02)
/** \brief Factory self test output for accelerometer X-axis.*/
#define MPU9250_REG_ACCEL_X_TEST            (0x0D)
/** \brief Factory self test output for accelerometer Y-axis.*/
#define MPU9250_REG_ACCEL_Y_TEST            (0x0E)
/** \brief Factory self test output for accelerometer Z-axis.*/
#define MPU9250_REG_ACCEL_Z_TEST            (0x0F)
/* Registers used to remove DC bias from the gyro sensor data output for
 * X, Y, and Z axes. Values are subtracted from the gyro sensor values 
 * before going into the sensor registers. */
/** \brief High byte [15:8], offset X-axis. */
#define MPU9250_REG_GYRO_X_OFF_H            (0x13)
/** \brief Low byte [7:0], offset X-axis. */
#define MPU9250_REG_GYRO_X_OFF_L            (0x14)
/** \brief High byte [15:8], offset Y-axis. */
#define MPU9250_REG_GYRO_Y_OFF_H            (0x15)
/** \brief Low byte [7:0], offset Y-axis. */
#define MPU9250_REG_GYRO_Y_OFF_L            (0x16)
/** \brief High byte [15:8], offset Z-axis. */
#define MPU9250_REG_GYRO_Z_OFF_H            (0x17)
/** \brief Low byte [7:0], offset Z-axis. */
#define MPU9250_REG_GYRO_Z_OFF_L            (0x18)
/* Divides the internal sample rate to generate the sample rate that
 * controls sensor data output rate. Only effective when Fchoice = 2'b11
 * such that the average filter's output is selected.  */
/** \brief Sample rate divisor. */
#define MPU9250_REG_SMPLRT_DIV              (0x19)
/** \brief Configuration. */
#define MPU9250_REG_CONFIG                  (0x1A)
/** \brief Gyroscope configuration. */
#define MPU9250_REG_GYRO_CONFIG             (0x1B)
/** \brief Accelerometer configuration 1. */
#define MPU9250_REG_ACCEL_CONFIG            (0x1C)
/** \brief Accelerometer configuration 2. */
#define MPU9250_REG_ACCEL_CONFIG2           (0x1D)
/** \brief Low Power Accelerometer Output Data Rate (ODR) Control. */
#define MPU9250_REG_LPACCEL_ODR             (0x1E)
/** \brief Wake-on Motion Threshold. */
#define MPU9250_REG_WOM_THRESH              (0x1F)
/** \brief FIFO Enable. */
#define MPU9250_REG_FIFO_EN                 (0x23)
/** \brief I2C Master Control. */
#define MPU9250_REG_I2C_MST_CTRL            (0x24)
/** \brief I2C Slave 0 Address. */
#define MPU9250_REG_I2C_SLV0_ADDR           (0x25)
/** \brief I2C Slave 0 Register. */
#define MPU9250_REG_I2C_SLV0_REG            (0x26)
/** \brief I2C Slave 0 Control. */
#define MPU9250_REG_I2C_SLV0_CTRL           (0x27)
/** \brief I2C Slave 1 Address. */
#define MPU9250_REG_I2C_SLV1_ADDR           (0x28)
/** \brief I2C Slave 1 Registers. */
#define MPU9250_REG_I2C_SLV1_REG            (0x29)
/** \brief I2C Slave 1 Control. */
#define MPU9250_REG_I2C_SLV1_CTRL           (0x2A)
/** \brief I2C Slave 2 Address. */
#define MPU9250_REG_I2C_SLV2_ADDR           (0x2B)
/** \brief I2C Slave 2 Registers. */
#define MPU9250_REG_I2C_SLV2_REG            (0x2C)
/** \brief I2C Slave 2 Control. */
#define MPU9250_REG_I2C_SLV2_CTRL           (0x2D)
/** \brief I2C Slave 3 Address. */
#define MPU9250_REG_I2C_SLV3_ADDR           (0x2E)
/** \brief I2C Slave 3 Registers. */
#define MPU9250_REG_I2C_SLV3_REG            (0x2F)
/** \brief I2C Slave 3 Control. */
#define MPU9250_REG_I2C_SLV3_CTRL           (0x30)
/** \brief I2C Slave 4 Address. */
#define MPU9250_REG_I2C_SLV4_ADDR           (0x31)
/** \brief I2C Slave 4 Registers. */
#define MPU9250_REG_I2C_SLV4_REG            (0x32)
/** \brief I2C Data out, Data to be written to I2C Slave 4. */
#define MPU9250_REG_I2C_SLV4_DO             (0x33)
/** \brief I2C Slave 4 Control. */
#define MPU9250_REG_I2C_SLV4_CTRL           (0x34)
/** \brief I2C Data in, Data to be read from I2C Slave 4. */
#define MPU9250_REG_I2C_SLV4_DI             (0x35)
/** \brief I2C Master Status. */
#define MPU9250_REG_I2C_MST_STATUS          (0x36)
/** \brief Interrupt Pin / Bypass Enable Configuration. */
#define MPU9250_REG_INT_PIN_CFG             (0x37)
/** \brief Interrupt Enable. */
#define MPU9250_REG_INT_ENABLE              (0x38)
/** \brief Interrupt Status. */
#define MPU9250_REG_INT_STATUS              (0x3A)
/** \brief High byte accelerometer measurement X-axis. */
#define MPU9250_REG_ACCEL_XOUT_H            (0x3B)
/** \brief Low byte accelerometer measurement X-axis. */
#define MPU9250_REG_ACCEL_XOUT_L            (0x3C)
/** \brief High byte accelerometer measurement Y-axis. */
#define MPU9250_REG_ACCEL_YOUT_H            (0x3D)
/** \brief Low byte accelerometer measurement Y-axis. */
#define MPU9250_REG_ACCEL_YOUT_L            (0x3E)
/** \brief High byte accelerometer measurement Z-axis. */
#define MPU9250_REG_ACCEL_ZOUT_H            (0x3F)
/** \brief Low byte accelerometer measurement Z-axis. */
#define MPU9250_REG_ACCEL_ZOUT_L            (0x40)
/** \brief High byte temperature measurement. */
#define MPU9250_REG_TEMP_OUT_H              (0x41)
/** \brief Low byte temperature measurement. */
#define MPU9250_REG_TEMP_OUT_L              (0x42)
/** \brief High byte gyroscope measurement X-axis. */
#define MPU9250_REG_GYRO_XOUT_H             (0x43)
/** \brief Low byte gyroscope measurement X-axis. */
#define MPU9250_REG_GYRO_XOUT_L             (0x44)
/** \brief High byte gyroscope measurement Y-axis. */
#define MPU9250_REG_GYRO_YOUT_H             (0x45)
/** \brief Low byte gyroscope measurement Y-axis. */
#define MPU9250_REG_GYRO_YOUT_L             (0x46)
/** \brief High byte gyroscope measurement Z-axis. */
#define MPU9250_REG_GYRO_ZOUT_H             (0x47)
/** \brief Low byte gyroscope measurement Z-axis. */
#define MPU9250_REG_GYRO_ZOUT_L             (0x48)
/** \brief External sensor data 0 */
#define MPU9250_REG_EXT_SENS_DATA_00        (0x49)
/** \brief External sensor data 1 */
#define MPU9250_REG_EXT_SENS_DATA_01        (0x4A)
/** \brief External sensor data 2 */
#define MPU9250_REG_EXT_SENS_DATA_02        (0x4B)
/** \brief I2C Data out, Data to be written to I2C Slave 0. */
#define MPU9250_REG_I2C_SLV0_DO             (0x63)
/** \brief I2C Data out, Data to be written to I2C Slave 1. */
#define MPU9250_REG_I2C_SLV1_DO             (0x64)
/** \brief I2C Data out, Data to be written to I2C Slave 2. */
#define MPU9250_REG_I2C_SLV2_DO             (0x65)
/** \brief I2C Data out, Data to be written to I2C Slave 3. */
#define MPU9250_REG_I2C_SLV3_DO             (0x66)
/** \brief I2C Master Delay Control. */
#define MPU9250_REG_I2C_MST_DELAY_CTRL      (0x67)
/** \brief Digital signal path reset. */
#define MPU9250_REG_SIGNAL_PATH_RESET       (0x68)
/** \brief Accelerometer interrupt control. */
#define MPU9250_REG_MOT_DETECT_CTRL         (0x69)
/** \brief User control. */
#define MPU9250_REG_USER_CTRL               (0x6A)
/** \brief Power management 1. */
#define MPU9250_REG_PWR_MGMT_1              (0x6B)
/** \brief Power management 2. */
#define MPU9250_REG_PWR_MGMT_2              (0x6C)
/** \brief High bits, number of written bytes in FIFO. */
#define MPU9250_REG_FIFO_COUNTH             (0x72)
/** \brief Low bits, number of written bytes in FIFO. */
#define MPU9250_REG_FIFO_COUNTL             (0x73)
/** \brief FIFO read/write command. */
#define MPU9250_REG_FIFO_R_W                (0x74)
/** \brief Indicate to user which device is being accessed. */
#define MPU9250_REG_WHOAMI                  (0x75)

/* Configuration bits mpu9250 */

/* Config register bits. */
/** \brief Fifo overwrite mode. */
#define MPU9250_CONFIG_FIFO_MODE_OVERWRITE  (0x00)

/* Gyro config register bits. */
/** \brief Gyro Full Scale Select bit 250 DPS. */
#define MPU9250_BITS_FS_250DPS              (0x00)
/** \brief Gyro Full Scale Select bit 500 DPS. */
#define MPU9250_BITS_FS_500DPS              (0x08)
/** \brief Gyro Full Scale Select bit 1000 DPS. */
#define MPU9250_BITS_FS_1000DPS             (0x10)
/** \brief Gyro Full Scale Select bit 2000 DPS. */
#define MPU9250_BITS_FS_2000DPS             (0x18)

/* Accel config register bits. */
/** \brief Accel Full Scale Select bit 2G. */
#define MPU9250_BITS_FS_2G                  (0x00)
/** \brief Accel Full Scale Select bit 4G. */
#define MPU9250_BITS_FS_4G                  (0x08)
/** \brief Accel Full Scale Select bit 8G. */
#define MPU9250_BITS_FS_8G                  (0x10)
/** \brief Accel Full Scale Select bit 16G. */
#define MPU9250_BITS_FS_16G                 (0x18)

/* Accel config 2 register bits. */
/** \brief Accel bandwidth 41 Hz */
#define MPU9250_ACCEL_CONFIG2_BW_41HZ       (0x03)
/** \brief Accel bandwidth 184 Hz */
#define MPU9250_ACCEL_CONFIG2_BW_184HZ      (0x09)

/* FIFO enable register bits. */
/** \brief Enable temperature in the FIFO queue. */
#define MPU9250_FIFO_EN_TEMP_OUT            (0x80)
/** \brief Enable gyro X in the FIFO queue. */
#define MPU9250_FIFO_EN_GYRO_XOUT           (0x40)
/** \brief Enable gyro Y in the FIFO queue. */
#define MPU9250_FIFO_EN_GYRO_YOUT           (0x20)
/** \brief Enable gyro Z in the FIFO queue. */
#define MPU9250_FIFO_EN_GYRO_ZOUT           (0x10)
/** \brief Enable accel in the FIFO queue. */
#define MPU9250_FIFO_EN_ACCEL_OUT           (0x08)
/** \brief Enable slave 2 in the FIFO queue. */
#define MPU9250_FIFO_EN_SLV2_OUT            (0x04)
/** \brief Enable slave 1 in the FIFO queue. */
#define MPU9250_FIFO_EN_SLV1_OUT            (0x02)
/** \brief Enable slave 0 in the FIFO queue. */
#define MPU9250_FIFO_EN_SLV0_OUT            (0x01)

/* User control register bits. */
/** \brief FIFO enable. */
#define MPU9250_USER_CTRL_FIFO_EN           (0x40)
/** \brief I2C master enable. */
#define MPU9250_USER_CTRL_I2C_MST_EN        (0x20)
/** \brief Disable slave, SPI only. */
#define MPU9250_USER_CTRL_I2C_IF_DIS        (0x10)
/** \brief Digital motion processor reset. */
#define MPU9250_USER_CTRL_DMP_RST           (0x08)
/** \brief FIFO reset. */
#define MPU9250_USER_CTRL_FIFO_RST          (0x04)
/** \brief I2C master reset. */
#define MPU9250_USER_CTRL_I2C_MST_RST       (0x02)
/** \brief Reset signal paths, clear sensor registers. */
#define MPU9250_USER_CTRL_SIG_COND_RST      (0x01)

/* Power management 1 register bits. */
/** \brief Power Management 1 hardware reset bit. */
#define MPU9250_PWR_MGMT_1_H_RESET          (0x80)
/** \brief Power Management 1 sleep bit. */
#define MPU9250_PWR_MGMT_1_SLEEP            (0x40)
/** \brief Power Management 1 cycle bit. */
#define MPU9250_PWR_MGMT_1_CYCLE            (0x20)
/** \brief Power Management 1 gyro standby bit. */
#define MPU9250_PWR_MGMT_1_GYRO_STDBY       (0x10)
/** \brief Power Management 1 power down PTAT. */
#define MPU9250_PWR_MGMT_1_PD_PTAT          (0x08)
/** \brief Power Management 1 clock select bit. */
#define MPU9250_PWR_MGMT_1_CLKSEL           (0x07)
/** \brief Power Management 1 auto clock select bit. */
#define MPU9250_PWR_MGMT_1_AUTO_CLKSEL      (0x01)
/** \brief Power Management 1 sleep bit. */
#define MPU9250_BIT_SLEEP                   (0x40)
/** \brief Power Management 1 hardware reset bit. */
#define MPU9250_BIT_H_RESET                 (0x80)
/** \brief Power Management 1 clock select bit. */
#define MPU9250_BITS_CLKSEL                 (0x07)

/* I2C Master delay control. */
/** \brief Slave 0 delay enable. */
#define MPU9250_SLAVE_0_DLY_EN              (0x01)

/* I2C Slave CTRL bits. */
/** \brief Slave enable. */
#define MPU9250_SLAVE_EN                    (0x80)
#define MPU9250_SLAVE_READ_8BYTES           (0x08)

/* I2C Slave ADDR bits. */
/** \brief Slave read. */
#define MPU9250_SLAVE_READ                  (0x80)
/** \brief Slave write. */
#define MPU9250_SLAVE_WRITE                 (0x00)

/* I2C master status bits. */
/** \brief Slave 4 done. */
#define MPU9250_I2C_SLV4_DONE               (0x40)

/* Interrupt status bits. */
/** \brief Fifo overflow bit. */
#define MPU9250_INT_STATUS_FIFO_OVERFLOW    (0x10)
/** \brief Clock select gyro X. */
#define MPU9250_MPU_CLK_SEL_PLLGYROX        (0x01)
/** \brief Clock select gyro Z. */
#define MPU9250_MPU_CLK_SEL_PLLGYROZ        (0x03)
#define MPU9250_MPU_EXT_SYNC_GYROX          (0x02)
/** \brief Digital Low Pass Filter Configuration bit 250Hz. */
#define MPU9250_BITS_FS_MASK                (0x18)
#define MPU9250_BITS_DLPF_CFG_250HZ         (0x00)
/** \brief Digital Low Pass Filter Configuration bit 184Hz. */
#define MPU9250_BITS_DLPF_CFG_184HZ         (0x01)
/** \brief Digital Low Pass Filter Configuration bit 92Hz. */
#define MPU9250_BITS_DLPF_CFG_92HZ          (0x02)
/** \brief Digital Low Pass Filter Configuration bit 41Hz. */
#define MPU9250_BITS_DLPF_CFG_41HZ          (0x03)
/** \brief Digital Low Pass Filter Configuration bit 20Hz. */
#define MPU9250_BITS_DLPF_CFG_20HZ          (0x04)
/** \brief Digital Low Pass Filter Configuration bit 10Hz. */
#define MPU9250_BITS_DLPF_CFG_10HZ          (0x05)
/** \brief Digital Low Pass Filter Configuration bit 5Hz. */
#define MPU9250_BITS_DLPF_CFG_5HZ           (0x06)
/** \brief Digital Low Pass Filter Configuration bit 3600Hz. */
#define MPU9250_BITS_DLPF_CFG_3600HZ        (0x07)
#define MPU9250_BITS_DLPF_CFG_MASK          (0x07)
/** \brief Interrupt status cleared configuration bit. */
#define MPU9250_BIT_INT_ANYRD_2CLEAR        (0x10)
/** \brief Enable raw sensor data ready interrupt to pin bit. */
#define MPU9250_BIT_RAW_RDY_EN              (0x01)
/** \brief Reset I2C slave and set interface to SPI mode only. */
#define MPU9250_BIT_I2C_IF_DIS              (0x10)
/** \brief Read flag bit. */
#define MPU9250_READ_FLAG                   (0x80)
/** \brief Enable raw sensor data ready interrupt bit */
#define MPU9250_BIT_RAW_RDY_EN              (0x01)
/** \brief Interrupt status clear if read */
#define MPU9250_BIT_INT_ANYRD_2CLEAR        (0x10)
/** \brief The default value of the MPU9250 device ID. */
#define MPU9250_WHOAMI_9250                 (0x71)
/** \brief The I2C address of the Magnetometer. */
#define MPU9250_AK8963_I2C_ADDR             (0x0c)
/** \brief The default value of the AK8963 device ID. */
#define MPU9250_AK8963_Device_ID            (0x48)

/* AK8963 Register map for the Magnetometer */
/* Read-only registers */
/** \brief Device ID. */
#define MPU9250_AK8963_WIA                  (0x00)
/** \brief Device information. */
#define MPU9250_AK8963_INFO                 (0x01)
/** \brief Status 1. */
#define MPU9250_AK8963_ST1                  (0x02)
/** \brief Measurement data X-axis lower 8-bits */
#define MPU9250_AK8963_HXL                  (0x03)
/** \brief Measurement data X-axis upper 8-bits */
#define MPU9250_AK8963_HXH                  (0x04)
/** \brief Measurement data Y-axis lower 8-bits */
#define MPU9250_AK8963_HYL                  (0x05)
/** \brief Measurement data Y-axis upper 8-bits */
#define MPU9250_AK8963_HYH                  (0x06)
/** \brief Measurement data Z-axis lower 8-bits */
#define MPU9250_AK8963_HZL                  (0x07)
/** \brief Measurement data Z-axis upper 8-bits */
#define MPU9250_AK8963_HZH                  (0x08)
/** \brief Status 2. */
#define MPU9250_AK8963_ST2                  (0x09)
/* Write/Read registers */
/** \brief Control 1. */
#define MPU9250_AK8963_CNTL1                (0x0A)
/** \brief Control 2. */
#define MPU9250_AK8963_CNTL2                (0x0B)
/** \brief Self-test control. */
#define MPU9250_AK8963_ASTC                 (0x0C)
//#define MPU9250_AK8963_TS1                  (0x0D)
//#define MPU9250_AK8963_TS2                  (0x0E)
/** \brief I2C disable. */
#define MPU9250_AK8963_I2CDIS               (0x0F)
/* Read-only registers (ROM) */
/** \brief Sensitivity adjustment value X-axis. */
#define MPU9250_AK8963_ASAX                 (0x10)
/** \brief Sensitivity adjustment value Y-axis. */
#define MPU9250_AK8963_ASAY                 (0x11)
/** \brief Sensitivity adjustment value Z-axis. */
#define MPU9250_AK8963_ASAZ                 (0x12)

/* Mag bits */
/** \brief Mag power down mode bit. */
#define MPU9250_MAG_CNTL1_MODE_POWER_DOWN       (0x00)
/** \brief Mag single measurement mode bit. */
#define MPU9250_MAG_CNTL1_MODE_SINGLE_MEASURE   (0x01)
/** \brief Mag continuous measurement mode 1 bit. */
#define MPU9250_MAG_CNTL1_MODE_CONT_MEASURE_1   (0x02)
/** \brief Mag continuous measurement mode 2 bit. */
#define MPU9250_MAG_CNTL1_MODE_CONT_MEASURE_2   (0x06)
/** \brief Mag fuse rom access mode bit. */
#define MPU9250_MAG_CNTL1_FUSE_ROM_ACCESS_MODE  (0x0F)
/** \brief Mag 16-bit measurement mode bit. */
#define MPU9250_MAG_CNTL1_16_BITS               (0x10)
/** \brief Mag magnetic overflow bit. */
#define MPU9250_MAG_HOFL                        (0x08)
/** \brief Mag soft reset bit. */
#define MPU9250_MAG_CNTL2_SOFT_RESET            (0x01)

/* Masks Mag */
/** \brief Data ready. */
#define MPU9250_ST1_DRDY_MASK               (0x01)
/** \brief Data overrun. */
#define MPU9250_ST1_DOR_MASK                (0x02)
/** \brief Output bit setting (mirror). */
#define MPU9250_ST2_BITM_MASK               (0x10)
/** \brief Magnetic sensor overflow. */
#define MPU9250_ST2_HOFL_MASK               (0x08)
/** \brief AK8963 fuse ROM access mode. */
#define MPU9250_AK8963_FUSE_MODE            (0x0F)
/** \brief AK8963 continues measurement mode 1 */
#define MPU9250_AK8963_MEA1_MODE            (0x02)
/** \brief AK8963 output bit setting. */
#define MPU9250_AK8963_16BIT_ADC            (0x10)

/* Masks IMU */
/** \brief Data ready. */
#define MPU9250_ST_INT_RDY_MASK             (0x01)
/** \brief Fsync interrupt occurred. */
#define MPU9250_ST_INT_FSYNC_MASK           (0x04)
/** \brief Fifo overflow interrupt occurred. */
#define MPU9250_ST_INT_FIFO_OFL_MASK        (0x05)
/** \brief Wake on motion interrupt occurred. */
#define MPU9250_ST_INT_WOM_MASK             (0x07)
/** \brief Stop between slave reads. */
#define MPU9250_I2C_MST_P_NSR               (0x10)
/** \brief Delay data ready int until external sensor data is loaded. */
#define MPU9250_I2C_MST_WAIT_FOR_ES         (0x40)
/** \brief I2C master clock speed */
#define MPU9250_I2C_MST_CLOCK_400HZ         (0x0D)


#endif /* MPU9250_MAP_H */
