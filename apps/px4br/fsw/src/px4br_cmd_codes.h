/****************************************************************************
 *
 *   Copyright (c) 2016-2017 Windhover Labs, L.L.C. All rights reserved.
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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 ****************************************************************************/

#ifndef _PX4BR_CMD_CODES_H_
#define _PX4BR_CMD_CODES_H_

#define PX4BR_NOP_CC                		0       /*  No-op command     */
#define PX4BR_RESET_STATUS_CC       		1       /*  Reset status      */
#define PX4BR_VEHICLE_COMMAND_CC       		2       /*  Vehicle Command   */
#define PX4BR_VEHICLE_LAUNCH_CC       		3       /*  Vehicle Command   */
#define PX4BR_VEHICLE_LAND_CC       		4       /*  Vehicle Command   */
#define PX4BR_VEHICLE_ARM_CC       			5       /*  Vehicle Command   */
#define PX4BR_VEHICLE_DISARM_CC       		6       /*  Vehicle Command   */
#define PX4BR_VEHICLE_RTL_CC       			7       /*  Vehicle Command   */
#define PX4BR_VEHICLE_INVERTED_FLIGHT_CC    8       /*  Vehicle Command   */
#define PX4BR_VEHICLE_SET_MODE_CC    		9       /*  Vehicle Command   */
#define PX4BR_MANUAL_CONTROL_SETPOINT_CC	10      /*  Vehicle Command   */

#endif
