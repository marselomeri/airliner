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

#ifndef MPU9250_MSG_H
#define MPU9250_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"


/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** MPU9250 Command Codes
*************************************************************************/

/** \mpu9250cmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the MPU9250 task is alive
**
**  \mpu9250cmdmnemonic \MPU9250_NOOP
**
**  \par Command Structure
**       #MPU9250_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \MPU9250_CMDACPTCNT - command counter will increment
**       - The #MPU9250_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \MPU9250_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #MPU9250_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #MPU9250_RESET_CC
*/
#define MPU9250_NOOP_CC                 (0)

/** \mpu9250cmd Reset Counters
**  
**  \par Description
**       Resets the MPU9250 housekeeping counters
**
**  \mpu9250cmdmnemonic \MPU9250_TLMRST
**
**  \par Command Structure
**       #MPU9250_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \MPU9250_CMDACTPCNT       - command counter will be cleared
**       - \b \c \MPU9250_CMDRJCTCNT       - command error counter will be cleared
**       - The #MPU9250_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \MPU9250_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #MPU9250_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #MPU9250_NOOP_CC
*/
#define MPU9250_RESET_CC                (1)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #MPU9250_NOOP_CC, #MPU9250_RESET_CC
**  Also see #MPU9250_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} MPU9250_NoArgCmd_t;

/** 
**  \brief MPU9250 application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \mpu9250tlmmnemonic \MPU9250_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \mpu9250tlmmnemonic \MPU9250_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 
    /** \brief App State */
    uint8              State;
} MPU9250_HkTlm_t;


typedef struct
{
    float AccDivider;
    float GyroDivider;

    float AccXCoef;
    float AccYCoef;
    float AccZCoef;
    float AccXBias;
    float AccYBias;
    float AccZBias;
    float GyroXCoef;
    float GyroYCoef;
    float GyroZCoef;
    float GyroXBias;
    float GyroYBias;
    float GyroZBias;
    float MagXCoef;
    float MagYCoef;
    float MagZCoef;
    float MagXBias;
    float MagYBias;
    float MagZBias;

    uint8 MagXAdj;
    uint8 MagYAdj;
    uint8 MagZAdj;

    float RoomTempOffset;
    float TempSensitivity;
} MPU9250_CalibrationMsg_t;

typedef struct
{
    uint8 TlmHeader[CFE_SB_TLM_HDR_SIZE];

    int16 AccelX;
    int16 AccelY;
    int16 AccelZ;

    int16 GyroX;
    int16 GyroY;
    int16 GyroZ;

    int16 MagX;
    int16 MagY;
    int16 MagZ;

    uint8 Spare;

    uint16 Temp;

    boolean WOM;
    boolean FifoOvflw;
    boolean Fsync;
    boolean ImuDataReady;
    boolean Overrun;
    boolean MagDataReady;
    boolean Overflow;
    boolean Output16Bit;
} MPU9250_RawMeasMsg_t;


typedef struct
{
    uint8 TlmHeader[CFE_SB_TLM_HDR_SIZE];

    float AccelX;
    float AccelY;
    float AccelZ;

    float GyroX;
    float GyroY;
    float GyroZ;
    
    float MagX;
    float MagY;
    float MagZ;

    float Temp;
} MPU9250_CalMeasMsg_t;


/** 
**  \brief MPU9250 diagnostic data
*/
typedef struct
{
    uint8           TlmHeader[CFE_SB_TLM_HDR_SIZE];
    MPU9250_CalibrationMsg_t          Calibration;
    MPU9250_RawMeasMsg_t              RawMeasure;
    MPU9250_CalMeasMsg_t              CalMeasure;
} MPU9250_DiagPacket_t;


#ifdef __cplusplus
}
#endif

#endif /* MPU9250_MSG_H */

/************************/
/*  End of File Comment */
/************************/
