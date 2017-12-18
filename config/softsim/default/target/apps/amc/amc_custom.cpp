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

int32 AMC::InitDevice(void)
{
    return 0;
}



float AMC_Map(float x, uint16 in_min, uint16 in_max)
{
	float out = (x - in_min) * (1.0f - 0.0f) / (in_max - in_min) + 0.0f;

	if(out > 1.0f)
	{
		out = 1.0f;
	}

	if(out < 0.0f)
	{
		out = 0.0f;
	}

	return out;
}


void AMC::SetMotorOutputs(const uint16 *PWM)
{
	float controls[16];
	uint32 controlCount = 16;
	uint32 i = 0;

	//OS_printf("*********************\n");
	//OS_printf("Min = %u  Max = %u\n", PwmConfigTblPtr->PwmMin, PwmConfigTblPtr->PwmMax);
    for (i = 0; i < AMC_MAX_MOTOR_OUTPUTS; ++i)
    {
    	controls[i] = AMC_Map(PWM[i], PwmConfigTblPtr->PwmMin, PwmConfigTblPtr->PwmMax);
    //	OS_printf("%f(%u) ", controls[i], PWM[i]);
    }

	for(i = AMC_MAX_MOTOR_OUTPUTS; i < 16; ++i)
	{
		controls[i] = 0.0f;
	//	OS_printf("%f ", controls[i]);
	}
    //OS_printf("\n");

	SIMLIB_SetActuatorControls(controls, controlCount, 0);
}
