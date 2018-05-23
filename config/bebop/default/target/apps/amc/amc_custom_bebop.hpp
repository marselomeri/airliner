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

#ifndef AMC_CUSTOM_BEBOP_H
#define AMC_CUSTOM_BEBOP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Defines for the Bebop Brushless Driver Controller (BLDC). */


/* Bebop motor controller configuration. */
/** \brief Path to the Cypress motor controller. */
#define AMC_BLDC_I2C_DEVICE_PATH     "/dev/i2c-cypress"
/** \brief Motor controller I2C slave address. */
#define AMC_BLDC_I2C_SLAVE_ADDRESS   (0x08)

/* Bebop motor controller Cypress BLDC register map. */
/** \brief BLDC Register set speed. */
#define AMC_BLDC_REG_SET_ESC_SPEED   (0x02)
/** \brief BLDC Register get observation. */
#define AMC_BLDC_REG_GET_OBS         (0x20)
/** \brief BLDC Register start motors. */
#define AMC_BLDC_REG_START_BLDC      (0x40)
/** \brief BLDC Register stop motors. */
#define AMC_BLDC_REG_STOP_BLDC       (0x60)
/** \brief BLDC Register toggle GPIO. */
#define AMC_BLDC_REG_TOGGLE_GPIO     (0x4D)
/** \brief BLDC Register clear error. */
#define AMC_BLDC_REG_CLEAR_ERROR     (0x80)
/** \brief BLDC Register play sound. */
#define AMC_BLDC_REG_PLAY_SOUND      (0x82)
/** \brief BLDC Register get information.  */
#define AMC_BLDC_REG_GET_INFO        (0xA0)


/* Bebop motor controller Cypress BLDC bit mask. */
/** \brief BLDC bit mask rotation direction RLRL.  */
/* front left: clockwise
 * front right: counterclockwise
 * back right: clockwise
 * back left: counterclockwise */
#define AMC_BLDC_BITS_RLRL           (0b00001010)
/** \brief BLDC bit mask rotation direction LRLR.  */
/* front left: counterclockwise
 * front right: clockwise
 * back right: counterclockwise
 * back left: clockwise */
#define AMC_BLDC_BITS_LRLR           (0b00000101)


/* Bebop motor controller Cypress BLDC limits. */
/** \brief BLDC limits minimum RPM.  */
#define AMC_BLDC_LIMITS_RPM_MIN      (3000)
/** \brief BLDC limits maximum RPM.  */
#define AMC_BLDC_LIMITS_RPM_MAX      (12200)



/**
 * \brief Bebop motor controller errors.
 */
typedef enum
{
    /*! BLDC no error. */
    AMC_BLDC_ERROR_NO             = 0x00,
    /*! BLDC error EEPROM corruption. */
    AMC_BLDC_ERROR_EEPROM         = 0x01,
    /*! BLDC error motor stalled. */
    AMC_BLDC_ERROR_STALLED        = 0x02,
    /*! BLDC error propeller security. */
    AMC_BLDC_ERROR_PROP_SECURITY  = 0x03,
    /*! BLDC error communication lost. */
    AMC_BLDC_ERROR_COMM_LOST      = 0x04,
    /*! BLDC error battery voltage too low. */
    AMC_BLDC_ERROR_LOW_BATT       = 0x09,
    /*! BLDC error incorrect number of LIPO cells. */
    AMC_BLDC_ERROR_LIPO_CELLS     = 0x0A,
    /*! BLDC error unplugged or broken motor phase or defectuous MOS. */
    AMC_BLDC_ERROR_BLDC           = 0x0B
} AMC_BLDC_Error_Status_t;


/**
 * \brief Bebop BLDC states, read in observations.
 */
typedef enum
{
    AMC_BLDC_STATUS_INIT          = 0x00,
    AMC_BLDC_STATUS_IDLE          = 0x01,
    AMC_BLDC_STATUS_RAMPING       = 0x02,
    AMC_BLDC_STATUS_SPINNING_1    = 0x03,
    AMC_BLDC_STATUS_SPINNING_2    = 0x04,
    AMC_BLDC_STATUS_STOPPING      = 0x05,
    AMC_BLDC_STATUS_CRITICAL      = 0x06
} AMC_BLDC_Status_t;


/**
 * \brief Bebop BLDC sounds to play.
 */
typedef enum
{
    AMC_BLDC_SOUND_NONE           = 0,
    AMC_BLDC_SOUND_SHORT          = 1,
    AMC_BLDC_SOUND_BOOT           = 2,
    AMC_BLDC_SOUND_MELODY         = 3,
    AMC_BLDC_SOUND_REPEAT         = -1
} AMC_BLDC_Sound_t;


typedef enum
{
    AMC_BLDC_GPIO_RESET           = 0x01,
    AMC_BLDC_GPIO_RED             = 0x02,
    AMC_BLDC_GPIO_GREEN           = 0x04
} AMC_BLDC_GPIO_t;


typedef struct 
{
    float battery_voltage_v;
    uint16_t rpm[4];
} AMC_BLDC_State_t;


typedef struct
{
    uint16 rpm_front_left;
    uint16 rpm_front_right;
    uint16 rpm_back_right;
    uint16 rpm_back_left;
    uint16 battery_voltage_mv;
    uint8  status;
    uint8  error;
    uint8  motors_in_fault;
    uint8  temperatur_c;
    uint8  checksum;
} AMC_BLDC_Observation_t;


typedef struct
{
    uint8 version_major;
    uint8 version_minor;
    uint8 type;
    uint8 n_motors_controlled;
    uint16 n_flights;
    uint16 last_flight_time;
    uint32 total_flight_time;
    uint8 last_error;
} AMC_BLDC_Info_t;


typedef struct 
{
    uint16 rpm_front_left;
    uint16 rpm_front_right;
    uint16 rpm_back_right;
    uint16 rpm_back_left;
    uint8  enable_security;
    uint8  checksum;
} AMC_BLDC_ESC_Speeds_t;


#ifdef __cplusplus
}
#endif 

#endif /* AMC_CUSTOM_BEBOP_H */

/************************/
/*  End of File Comment */
/************************/
