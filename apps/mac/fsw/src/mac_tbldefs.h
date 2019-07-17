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

#ifndef MAC_TBLDEFS_H
#define MAC_TBLDEFS_H

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
#include "mac_platform_cfg.h"

/************************************************************************
** Local Defines
*************************************************************************/
#define MAC_PARAM_NAME_MAX_LEN   (32)
#define MC_ROLL_P_MIN            (0.0f)
#define MC_ROLL_P_MAX            (12.0f)
#define MC_ROLLRATE_P_MIN        (0.0f)
#define MC_ROLLRATE_P_MAX        (0.5f)
#define MC_ROLLRATE_I_MIN        (0.0f)
#define MC_ROLLRATE_I_MAX        (1.0f) // Not explicitly defined max
#define MC_ROLLRATE_D_MIN        (0.0f)
#define MC_ROLLRATE_D_MAX        (0.01f)
#define MC_RR_INT_LIM_MIN        (0.0f)
#define MC_RR_INT_LIM_MAX        (1.0f) // Not explicitly defined max
#define MC_ROLLRATE_FF_MIN       (0.0f)
#define MC_ROLLRATE_FF_MAX       (10.0f) // Not explicitly defined max
#define MC_PITCH_P_MIN           (0.0f)
#define MC_PITCH_P_MAX           (12.0f)
#define MC_PITCHRATE_P_MIN       (0.0f)
#define MC_PITCHRATE_P_MAX       (0.6f)
#define MC_PITCHRATE_I_MIN       (0.0f)
#define MC_PITCHRATE_I_MAX       (1.0f) //
#define MC_PR_INT_LIM_MIN        (0.0f)
#define MC_PR_INT_LIM_MAX        (1.0f) //
#define MC_PITCHRATE_D_MIN       (0.0f)
#define MC_PITCHRATE_D_MAX       (0.1f) //
#define MC_PITCHRATE_FF_MIN      (0.0f)
#define MC_PITCHRATE_FF_MAX      (10.0f) //
#define MC_TPA_BREAK_P_MIN       (0.0f)
#define MC_TPA_BREAK_P_MAX       (1.0f)
#define MC_TPA_BREAK_I_MIN       (0.0f)
#define MC_TPA_BREAK_I_MAX       (1.0f)
#define MC_TPA_BREAK_D_MIN       (0.0f)
#define MC_TPA_BREAK_D_MAX       (1.0f)
#define MC_TPA_RATE_P_MIN        (0.0f)
#define MC_TPA_RATE_P_MAX        (1.0f)
#define MC_TPA_RATE_I_MIN        (0.0f)
#define MC_TPA_RATE_I_MAX        (1.0f)
#define MC_TPA_RATE_D_MIN        (0.0f)
#define MC_TPA_RATE_D_MAX        (1.0f)
#define MC_YAW_P_MIN             (0.0f)
#define MC_YAW_P_MAX             (5.0f)
#define MC_YAWRATE_P_MIN         (0.0f)
#define MC_YAWRATE_P_MAX         (0.6f)
#define MC_YAWRATE_I_MIN         (0.0)
#define MC_YAWRATE_I_MAX         (1.0f) //
#define MC_YR_INT_LIM_MIN        (0.0f)
#define MC_YR_INT_LIM_MAX        (1.0f) //
#define MC_YAWRATE_D_MIN         (0.0f)
#define MC_YAWRATE_D_MAX         (1.0f) //
#define MC_YAWRATE_FF_MIN        (0.0f)
#define MC_YAWRATE_FF_MAX        (1.0f) //
#define MC_ROLLRATE_MAX_MIN      (0.0f)
#define MC_ROLLRATE_MAX_MAX      (1800.0f)
#define MC_PITCHRATE_MAX_MIN     (0.0f)
#define MC_PITCHRATE_MAX_MAX     (1800.0f)
#define MC_YAWRATE_MAX_MIN       (0.0f)
#define MC_YAWRATE_MAX_MAX       (1800.0f)
#define MC_YAWRAUTO_MAX_MIN      (0.0f)
#define MC_YAWRAUTO_MAX_MAX      (360.0f)
#define MC_ACRO_R_MAX_MIN        (0.0f)
#define MC_ACRO_R_MAX_MAX        (1800.0f)
#define MC_ACRO_P_MAX_MIN        (0.0f)
#define MC_ACRO_P_MAX_MAX        (1800.0f)
#define MC_ACRO_Y_MAX_MIN        (0.0f)
#define MC_ACRO_Y_MAX_MAX        (1800.0f)
#define MC_RATT_TH_MIN           (0.0f)
#define MC_RATT_TH_MAX           (1.0f)
#define MC_ROLL_TC_MIN           (0.15f)
#define MC_ROLL_TC_MAX           (0.25f)
#define MC_PITCH_TC_MIN          (0.15f)
#define MC_PITCH_TC_MAX          (0.25f)
#define MC_BAT_SCALE_EN_MIN      (0)
#define MC_BAT_SCALE_EN_MAX      (1)
#define SENS_BOARD_ROT_MIN       (0)
#define SENS_BOARD_ROT_MAX       (34)
#define SENS_BOARD_X_OFF_MIN     (0.0f)
#define SENS_BOARD_X_OFF_MAX     (10.0f) //
#define SENS_BOARD_Y_OFF_MIN     (0.0f)
#define SENS_BOARD_Y_OFF_MAX     (10.0f) //
#define SENS_BOARD_Z_OFF_MIN     (0.0f)
#define SENS_BOARD_Z_OFF_MAX     (10.0f) //

/**
 * \brief Defines the table identification name used for table registration.
 */
#define MAC_PARAM_TABLENAME ("PARAM_TBL")

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** \brief Definition for a single config table entry */
typedef struct
{
    float roll_p;
    float roll_rate_p;
    float roll_rate_i;
    float roll_rate_integ_lim;
    float roll_rate_d;
    float roll_rate_ff;
    float pitch_p;
    float pitch_rate_p;
    float pitch_rate_i;
    float pitch_rate_integ_lim;
    float pitch_rate_d;
    float pitch_rate_ff;
    float tpa_breakpoint_p;
    float tpa_breakpoint_i;
    float tpa_breakpoint_d;
    float tpa_rate_p;
    float tpa_rate_i;
    float tpa_rate_d;
    float yaw_p;
    float yaw_rate_p;
    float yaw_rate_i;
    float yaw_rate_integ_lim;
    float yaw_rate_d;
    float yaw_rate_ff;
    float yaw_ff;
    float roll_rate_max;
    float pitch_rate_max;
    float yaw_rate_max;
    float yaw_auto_max;
    float acro_roll_max;
    float acro_pitch_max;
    float acro_yaw_max;
    float rattitude_thres;
    float roll_tc;
    float pitch_tc;
    int32 bat_scale_en;
    int32 board_rotation;
    float board_offset_x;
    float board_offset_y;
    float board_offset_z;
} MAC_ParamTbl_t;

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
** Local Function Prototypes
*************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* MAC_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
