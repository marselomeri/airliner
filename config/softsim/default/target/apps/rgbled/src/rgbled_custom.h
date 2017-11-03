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

#ifndef RGBLED_CUSTOM_H
#define RGBLED_CUSTOM_H

/************************************************************************
** Includes
*************************************************************************/

/************************************************************************
** Local Defines
*************************************************************************/
/** \brief I2C slave address of the TCA62724FMG LED driver in hex.
**
**  \par Description:
**       8-bit address in little-endian format is 1010101(R/W) where R/W
**       bit-0 indicates read (bit set to "H") or write mode (bit set to 
**       "L"). This is the 7-bit address without the R/W bit.
*/
#define RGBLED_I2C_ADDRESS              (0x55)

/** \brief I2C address write mode.
**
**  \par Description:
**       Bit-0 of the I2C slave address for write mode. 
*/
#define RGBLED_I2C_ADDRESS_WRITE        (0x00)

/** \brief I2C address read mode.
**
**  \par Description:
**       Bit-0 of the I2C slave address for read mode. 
*/
#define RGBLED_I2C_ADDRESS_READ         (0x01)

/** \brief I2C sub-address for PWM Output 0 connected to the blue LED.
**
**  \par Description:
**       8-bit address in little-endian format is (AI)0000001 where AI
**       is the auto-increment OFF (bit set to "H") or auto-increment ON
**       (bit set to "L"). This is the 8-bit address with AI OFF.
*/
#define RGBLED_I2C_SUB_ADDR_PWM0        (0x81)

/** \brief I2C sub-address for PWM Output 1 connected to the green LED.
**
**  \par Description:
**       8-bit address in little-endian format is (AI)0000010 where AI
**       is the auto-increment OFF (bit set to "H") or auto-increment ON
**       (bit set to "L"). This is the 8-bit address with AI OFF.
*/
#define RGBLED_I2C_SUB_ADDR_PWM1        (0x82)

/** \brief I2C sub-address for PWM Output 2 connected to the red LED.
**
**  \par Description:
**       8-bit address in little-endian format is (AI)0000011 where AI
**       is the auto-increment OFF (bit set to "H") or auto-increment ON
**       (bit set to "L"). This is the 8-bit address with AI OFF.
*/
#define RGBLED_I2C_SUB_ADDR_PWM1        (0x83)

/** \brief I2C sub-address for settings.
**
**  \par Description:
**       8-bit address in little-endian format is (AI)0000100 where AI
**       is the auto-increment OFF (bit set to "H") or auto-increment ON
**       (bit set to "L"). This is the 8-bit address with AI OFF.
*/
#define RGBLED_I2C_SUB_ADDR_SETTINGS    (0x84)

/** \brief I2C setting NOT powersave mode (NOT SHDN).
**
**  \par Description:
**       Bit-0 of the "ENABLE/NOT SHDN DATA" byte. Set to "H" output 
**       blinks at PWM0, PWM1, PWM2 rate. 
*/
#define RGBLED_I2C_SET_NOT_POWERSAVE    (0x01)

/** \brief I2C setting powersave mode (NOT SHDN).
**
**  \par Description:
**       Bit-0 of the "ENABLE/NOT SHDN DATA" byte. Set to "L" 
**       power-saving mode.
*/
#define RGBLED_I2C_SET_POWERSAVE        (0x00)

/** \brief I2C setting enable (ENABLE).
**
**  \par Description:
**       Bit-1 of the "ENABLE/NOT SHDN DATA" byte. Set to "H" output
**       blinks at PWM0, PWM1, PWM2 rate.
*/
#define RGBLED_I2C_SET_ENABLE           (0x01)

/** \brief I2C setting NOT enable (ENABLE).
**
**  \par Description:
**       Bit-1 of the "ENABLE/NOT SHDN DATA" byte. Set to "L" output
**       is OFF.
*/
#define RGBLED_I2C_SET_DISABLE          (0x00)

/** \brief Max brightness setting for an LED (max PWM duty cycle).
**
**  \par Description:
**       The PWM ON Duty DATA byte uses 4-bits (bit-3 through bit 0) to 
**       set brightness.
*/
#define RGBLED_MAX_BRIGHTNESS           (15)

/** \brief Device path.
**
**  \par Description:
**       The I2C interface device path. The "-1" is the adapter number. 
*/
#define RGBLED_DEVICE_PATH              "/dev/i2c-1"

/** \brief Max device path.
**
**  \par Description:
**       None.
*/
#define RGBLED_MAX_DEVICE_PATH          OS_MAX_LOCAL_PATH_LEN

/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define RGBLED_MAX_RETRY_ATTEMPTS       (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define RGBLED_MAX_RETRY_SLEEP_USEC     (10)

/************************************************************************
** Structure Declarations
*************************************************************************/
typedef struct
{
    /*! Device file descriptor */
    int                 DeviceFd;
    /*! Path to device */
    char                DevName[RGBLED_MAX_DEVICE_PATH];
    /*! */
    uint8               Settings;
    uint8               RedDutyCycle;
    uint8               GreenDutyCycle;
    uint8               BlueDutyCycle;
} RGBLED_AppCustomData_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief ioctl with limited EINTR retry attempts. 
**
**  \par Description
**       This function is a wrapper for ioctl with retry attempts added.
**
**  \param [in] fh file descriptor.
**  \param [in] request code.
**  \param [in] arg pointer to a device specific struct.
**
**  \returns
**  usually 0 for success and -1 for failure, see ioctl man-page for 
**  more info.
**  \endreturns
**
*************************************************************************/
int32 RGBLED_Ioctl(int fh, int request, void *arg);

/************************************************************************/
/** \brief Custom function to initialize custom device data structure. 
**
**  \par Description
**       This function is called on app startup, reload, restart etc
**       to initialize non-zero data.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean RGBLED_Custom_InitData(void);

/************************************************************************/
/** \brief Custom function to initialize custom device(s).
**
**  \par Description
**       This function is called at initialization and allows the
**       custom layer to provide specific functionality to initialize
**       internal objects.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean RGBLED_Custom_Init(void);

int32 RGBLED_Custom_Send(...);

int32 RGBLED_Custom_Receive(...);

/************************************************************************/
/** \brief Custom function to uninitialize custom device(s).
**
**  \par Description
**       This function is called in preparation for loading a new
**       configuration, allowing the custom layer to do whatever it
**       needs with the current configuration before reconfiguration,
**       if anything. Also, called in cleanup to close and uninitialize
**       device resources.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean RGBLED_Custom_Uninit(void);

#endif /* RGBLED_CUSTOM_H */
