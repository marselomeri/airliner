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

//#include "Vector3F.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"
#include "mac_platform_cfg.h"

/************************************************************************
** Local Defines
*************************************************************************/

/**
 * \brief Defines the table identification name used for table registration.
 */
#define MAC_PARAM_TABLENAME ("PARAM_TBL")

typedef enum
{
	MAC_TAILSITTER	= 0,
	MAC_TILTROTOR   = 1,
	MAC_STANDARD    = 2
} MAC_VTOL_Type_t;

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
	MAC_VTOL_Type_t vtol_type;
	float roll_tc;
	float pitch_tc;
	int32 vtol_opt_recovery_enabled;
	float vtol_wv_yaw_rate_scale;
	int32 bat_scale_en;
	int32 board_rotation;
	float board_offset[3];
} MAC_ParamTbl_t;


/** \brief Definition for Critical Data Storage (CDS) table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for CDS data here. */
} MAC_CdsTbl_t;

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
