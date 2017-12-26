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


#define PWM_CUSTOM_OUT_MIN  (1000.0f)
#define PWM_CUSTOM_OUT_MAX  (2000.0f)


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
	uint32 controlCount = 16;
	uint32 i = 0;

    for (i = 0; i < AMC_MAX_MOTOR_OUTPUTS; ++i)
    {
    	controls[i] = AMC_Map(PWM[i], PwmConfigTblPtr->PwmMin, PwmConfigTblPtr->PwmMax, PWM_CUSTOM_OUT_MIN, PWM_CUSTOM_OUT_MAX);
    }

	for(i = AMC_MAX_MOTOR_OUTPUTS; i < 16; ++i)
	{
		controls[i] = NAN;
	}

	SIMLIB_SetActuatorControls(controls, controlCount, 0);
}
