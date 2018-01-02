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

#include "cfe.h"
#include "amc_app.h"
#include "simlib.h"
#include <math.h>


#define PWM_CUSTOM_OUT_MIN  (0.0f)
#define PWM_CUSTOM_OUT_MAX  (1.0f)


int32 AMC::InitDevice(void)
{
    return 0;
}



float AMC_Map(float inValue, uint16 in_min, uint16 in_max, float out_min, float out_max)
{
	/* Use the mapping equation:  Y = (X-A)/(B-A) * (D-C) + C */
	float out = (inValue - in_min) /
			(in_max - in_min) *
			(out_max - out_min) +
			out_min;

	if(out > out_max)
	{
		out = out_max;
	}

	if(out < out_min)
	{
		out = out_min;
	}

	return out;
}


void AMC::SetMotorOutputs(const uint16 *PWM)
{
	float controls[16];
	uint32 controlCount = 11;
	uint32 i = 0;

    for (i = 0; i < 6; ++i)
    {
    	controls[i] = AMC_Map(PWM[i], PwmConfigTblPtr->PwmMin, PwmConfigTblPtr->PwmMax, PWM_CUSTOM_OUT_MIN, PWM_CUSTOM_OUT_MAX);
    }

    controls[6] = 0.0f;
    controls[7] = 0.0f;
    controls[8] = 0.0f;
    controls[9] = NAN;
    controls[10] = NAN;
    controls[11] = 0.0f;
    controls[12] = 0.0f;
    controls[13] = 0.0f;
    controls[14] = 0.0f;
    controls[15] = 0.0f;

	//OS_printf("- ActuatorOutputs.Count = %u (11)\n" , ActuatorOutputs.Count);
	OS_printf("- ActuatorOutputs.Output[0] = %f (1396.680176)\n" , controls[0]);
	OS_printf("- ActuatorOutputs.Output[1] = %f (1391.089600)\n" , controls[1]);
	OS_printf("- ActuatorOutputs.Output[2] = %f (1385.925171)\n" , controls[2]);
	OS_printf("- ActuatorOutputs.Output[3] = %f (1401.844604)\n" , controls[3]);
	OS_printf("- ActuatorOutputs.Output[4] = %f (1407.727173)\n" , controls[4]);
	OS_printf("- ActuatorOutputs.Output[5] = %f (1380.042480)\n" , controls[5]);
	OS_printf("- ActuatorOutputs.Output[6] = %f (1500.000000)\n" , controls[6]);
	OS_printf("- ActuatorOutputs.Output[7] = %f (1500.000000)\n" , controls[7]);
	OS_printf("- ActuatorOutputs.Output[8] = %f (1500.000000)\n" , controls[8]);
	OS_printf("- ActuatorOutputs.Output[9] = %f (1000.000000)\n" , controls[9]);
	OS_printf("- ActuatorOutputs.Output[10] = %f (1000.000000)\n" , controls[10]);
	OS_printf("- ActuatorOutputs.Output[11] = %f (nan)\n" , controls[11]);
	OS_printf("- ActuatorOutputs.Output[12] = %f (nan)\n" , controls[12]);
	OS_printf("- ActuatorOutputs.Output[13] = %f (nan)\n" , controls[13]);
	OS_printf("- ActuatorOutputs.Output[14] = %f (nan)\n" , controls[14]);
	OS_printf("- ActuatorOutputs.Output[15] = %f (nan)\n" , controls[15]);

	SIMLIB_SetActuatorControls(controls, controlCount, 0);
}
