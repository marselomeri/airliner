/****************************************************************************
 *
 *   Copyright (c) 2012-2016 PX4 Development Team. All rights reserved.
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

#include "MultirotorMixer.h"
#include <math.h>
#include <string.h>
#include <math/Limits.hpp>
#include <float.h>

#define AMC_THRUST_INCREASE_FACTOR (1.5f)
#define AMC_THRUST_DECREASE_FACTOR (0.6f)

/*
 * Clockwise: 1
 * Counter-clockwise: -1
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer constructor.                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MultirotorMixer::MultirotorMixer(ControlCallback control_cb,
        cpuaddr cb_handle) :
        Mixer(control_cb, cb_handle), m_ThrustFactor(0.0f)
{
//    memset(&m_SaturationStatus, 0, sizeof(m_SaturationStatus));
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer destructor.                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MultirotorMixer::~MultirotorMixer()
{
    return;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer SetConfigTablePtr function.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MultirotorMixer::SetConfigTablePtr(
        MultirotorMixer_ConfigTablePtr_t &ConfigTablePtr)
{

    if (ConfigTablePtr != 0)
    {
        m_ConfigTablePtr = ConfigTablePtr;

        /* shift to output range here to avoid runtime calculation */
        float idle_speed_fixed = -1.0f + m_ConfigTablePtr->IdleSpeed * 2.0f;
        memset(m_OutputsPrev, idle_speed_fixed, sizeof(m_OutputsPrev));

        return CFE_SUCCESS;
    }

    return -1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer Contrain function.                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float MultirotorMixer::Contrain(float value, float minimum, float maximum)
{
    float result;

    if(value < minimum)
    {
        result = minimum;
    }
    else
    {
        if(value > minimum)
        {
            result = maximum;
        }
        else
        {
            result = value;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer mix function.                                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
uint32 MultirotorMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    /* Summary of mixing strategy:
     1) mix roll, pitch and thrust without yaw.
     2) if some outputs violate range [0,1] then try to shift all outputs to
        minimize violation -> increase or decrease total thrust (boost). The
        total increase or decrease of thrust is limited (max_thrust_diff). If
        after the shift some outputs still violate the bounds then scale roll
        & pitch.
        In case there is violation at the lower and upper bound then try to
        shift such that violation is equal on both sides.
     3) mix in yaw and scale if it leads to limit violation.
     4) scale all outputs to range [idle_speed,1]
     */

    float roll = Contrain(get_control(0, 0) * m_ConfigTablePtr->RollScale,
            -1.0f, 1.0f);
    float pitch = Contrain(get_control(0, 1) * m_ConfigTablePtr->PitchScale,
            -1.0f, 1.0f);
    float yaw = Contrain(get_control(0, 2) * m_ConfigTablePtr->YawScale, -1.0f,
            1.0f);
    float thrust = Contrain(get_control(0, 3) * 1.0f, 0.0f, 1.0f);
    float min_out = 1.0f;
    float max_out = 0.0f;

    // clean out class variable used to capture saturation
    m_SaturationStatus.value = 0;

    /* perform initial mix pass yielding unbounded outputs, ignore yaw */
    for (uint32 i = 0; i < m_ConfigTablePtr->RotorCount; ++i)
    {
        float out = roll * m_ConfigTablePtr->RotorConfig[i].RollScale
                + pitch * m_ConfigTablePtr->RotorConfig[i].PitchScale + thrust;

        out *= m_ConfigTablePtr->RotorConfig[i].OutScale;

        /* calculate min and max output values */
        if (out < min_out)
        {
            min_out = out;
        }

        if (out > max_out)
        {
            max_out = out;
        }

        outputs[i] = out;
    }

    /* Value added to demanded thrust (can also be negative) */
    float boost = 0.0f;
    /* Scale for demanded roll and pitch */
    float roll_pitch_scale = 1.0f;

    if (min_out < 0.0f && max_out < 1.0f && -min_out <= 1.0f - max_out)
    {
        float max_thrust_diff = thrust * AMC_THRUST_INCREASE_FACTOR - thrust;

        if (max_thrust_diff >= -min_out)
        {
            boost = -min_out;

        }
        else
        {
            boost = max_thrust_diff;
            roll_pitch_scale = (thrust + boost) / (thrust - min_out);
        }

    }
    else if (max_out > 1.0f && min_out > 0.0f && min_out >= max_out - 1.0f)
    {
        float max_thrust_diff = thrust - AMC_THRUST_DECREASE_FACTOR * thrust;

        if (max_thrust_diff >= max_out - 1.0f)
        {
            boost = -(max_out - 1.0f);

        }
        else
        {
            boost = -max_thrust_diff;
            roll_pitch_scale = (1 - (thrust + boost)) / (max_out - thrust);
        }

    }
    else if (min_out < 0.0f && max_out < 1.0f && -min_out > 1.0f - max_out)
    {
        float max_thrust_diff = thrust * AMC_THRUST_INCREASE_FACTOR - thrust;
        boost = math::constrain(-min_out - (1.0f - max_out) / 2.0f, 0.0f,
                max_thrust_diff);
        roll_pitch_scale = (thrust + boost) / (thrust - min_out);

    }
    else if (max_out > 1.0f && min_out > 0.0f && min_out < max_out - 1.0f)
    {
        float max_thrust_diff = thrust - AMC_THRUST_DECREASE_FACTOR * thrust;
        boost = math::constrain(-(max_out - 1.0f - min_out) / 2.0f,
                -max_thrust_diff, 0.0f);
        roll_pitch_scale = (1 - (thrust + boost)) / (max_out - thrust);

    }
    else if (min_out < 0.0f && max_out > 1.0f)
    {
        boost = math::constrain(-(max_out - 1.0f + min_out) / 2.0f,
                AMC_THRUST_DECREASE_FACTOR * thrust - thrust,
                AMC_THRUST_INCREASE_FACTOR * thrust - thrust);
        roll_pitch_scale = (thrust + boost) / (thrust - min_out);
    }

    // capture saturation
    if (min_out < 0.0f)
    {
        m_SaturationStatus.flags.motor_neg = true;
    }

    if (max_out > 1.0f)
    {
        m_SaturationStatus.flags.motor_pos = true;
    }

    // Thrust reduction is used to reduce the collective thrust if we hit
    // the upper throttle limit
    float thrust_reduction = 0.0f;

    // mix again but now with thrust boost, scale roll/pitch and also add yaw
    for (uint32 i = 0; i < m_ConfigTablePtr->RotorCount; ++i)
    {
        float out = (roll * m_ConfigTablePtr->RotorConfig[i].RollScale
                + pitch * m_ConfigTablePtr->RotorConfig[i].PitchScale)
                * roll_pitch_scale
                + yaw * m_ConfigTablePtr->RotorConfig[i].YawScale + thrust
                + boost;

        out *= m_ConfigTablePtr->RotorConfig[i].OutScale;

        // scale yaw if it violates limits. inform about yaw limit reached
        if (out < 0.0f)
        {
            if (fabsf(m_ConfigTablePtr->RotorConfig[i].YawScale)
                    <= FLT_EPSILON)
            {
                yaw = 0.0f;
            }
            else
            {
                yaw = -((roll * m_ConfigTablePtr->RotorConfig[i].RollScale
                        + pitch * m_ConfigTablePtr->RotorConfig[i].PitchScale)
                        * roll_pitch_scale + thrust + boost)
                        / m_ConfigTablePtr->RotorConfig[i].YawScale;
            }

        }
        else if (out > 1.0f)
        {
            // allow to reduce thrust to get some yaw response
            float prop_reduction = fminf(0.15f, out - 1.0f);
            // keep the maximum requested reduction
            thrust_reduction = fmaxf(thrust_reduction, prop_reduction);

            if (fabsf(m_ConfigTablePtr->RotorConfig[i].YawScale)
                    <= FLT_EPSILON)
            {
                yaw = 0.0f;
            }
            else
            {
                yaw = (1.0f - (
                        (roll * m_ConfigTablePtr->RotorConfig[i].RollScale
                                + pitch
                                * m_ConfigTablePtr->RotorConfig[i].PitchScale)
                                * roll_pitch_scale + (thrust
                                        - thrust_reduction) + boost))
                                / m_ConfigTablePtr->RotorConfig[i].YawScale;
            }
        }
    }

    // Apply collective thrust reduction, the maximum for one prop
    thrust -= thrust_reduction;

    // add yaw and scale outputs to range idle_speed...1
    for (uint32 i = 0; i < m_ConfigTablePtr->RotorCount; ++i)
    {
        /* shift to output range here to avoid runtime calculation */
        float idle_speed_fixed = -1.0f + m_ConfigTablePtr->IdleSpeed * 2.0f;

        outputs[i] = (roll * m_ConfigTablePtr->RotorConfig[i].RollScale
                + pitch * m_ConfigTablePtr->RotorConfig[i].PitchScale)
                * roll_pitch_scale
                + yaw * m_ConfigTablePtr->RotorConfig[i].YawScale + thrust
                + boost;

        /*
         implement simple model for static relationship between applied motor pwm and motor thrust
         model: thrust = (1 - _thrust_factor) * PWM + _thrust_factor * PWM^2
         this model assumes normalized input / output in the range [0,1] so this is the right place
         to do it as at this stage the outputs are in that range.
         */
        if (m_ThrustFactor > 0.0f)
        {
            outputs[i] =
                    -(1.0f - m_ThrustFactor) / (2.0f * m_ThrustFactor)
                            + sqrtf(
                                    (1.0f - m_ThrustFactor)
                                            * (1.0f - m_ThrustFactor)
                                            / (4.0f * m_ThrustFactor
                                                    * m_ThrustFactor)
                                            + (outputs[i] < 0.0f ?
                                                    0.0f :
                                                    outputs[i] / m_ThrustFactor));
        }

        outputs[i] = math::constrain(
                idle_speed_fixed + (outputs[i] * (1.0f - idle_speed_fixed)),
                idle_speed_fixed, 1.0f);

    }

    /* slew rate limiting and saturation checking */
    for (uint32 i = 0; i < m_ConfigTablePtr->RotorCount; ++i)
    {
        /* shift to output range here to avoid runtime calculation */
        float idle_speed_fixed = -1.0f + m_ConfigTablePtr->IdleSpeed * 2.0f;
        bool clipping_high = false;
        bool clipping_low = false;

        // check for saturation against static limits
        if (outputs[i] > 0.99f)
        {
            clipping_high = true;

        }
        else if (outputs[i] < idle_speed_fixed + 0.01f)
        {
            clipping_low = true;

        }

        // check for saturation against slew rate limits
        if (m_ConfigTablePtr->DeltaOutMax > 0.0f)
        {
            float delta_out = outputs[i] - m_OutputsPrev[i];

            if (delta_out > m_ConfigTablePtr->DeltaOutMax)
            {
                outputs[i] = m_OutputsPrev[i] + m_ConfigTablePtr->DeltaOutMax;
                clipping_high = true;

            }
            else if (delta_out < -m_ConfigTablePtr->DeltaOutMax)
            {
                outputs[i] = m_OutputsPrev[i] - m_ConfigTablePtr->DeltaOutMax;
                clipping_low = true;

            }
        }

        m_OutputsPrev[i] = outputs[i];

        // update the saturation status report
        update_saturation_status(i, clipping_high, clipping_low);

    }

    // this will force the caller of the mixer to always supply new slew rate values, otherwise no slew rate limiting will happen
    m_ConfigTablePtr->DeltaOutMax = 0.0f;

    // Notify saturation status
    if (status_reg != nullptr)
    {
        (*status_reg) = m_SaturationStatus.value;
    }

    return m_ConfigTablePtr->RotorCount;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer update_saturation_status function.              */
/*                                                                 */
/* This function update the control saturation status report using */
/* the following inputs:                                           */
/*   index:         0 based index identifying the motor that is    */
/*                  saturating.                                    */
/*   clipping_high: true if the motor demand is being limited in   */
/*                  the positive direction.                        */
/*   clipping_low:  true if the motor demand is being limited in   */
/*                  the negative direction.                        */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MultirotorMixer::update_saturation_status(uint32 index, bool clipping_high,
        bool clipping_low)
{
    // The motor is saturated at the upper limit
    // check which control axes and which directions are contributing
    if (clipping_high)
    {
        if (m_ConfigTablePtr->RotorConfig[index].RollScale > 0.0f)
        {
            // A positive change in roll will increase saturation
            m_SaturationStatus.flags.roll_pos = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].RollScale < 0.0f)
        {
            // A negative change in roll will increase saturation
            m_SaturationStatus.flags.roll_neg = true;

        }

        // check if the pitch input is saturating
        if (m_ConfigTablePtr->RotorConfig[index].PitchScale > 0.0f)
        {
            // A positive change in pitch will increase saturation
            m_SaturationStatus.flags.pitch_pos = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].PitchScale < 0.0f)
        {
            // A negative change in pitch will increase saturation
            m_SaturationStatus.flags.pitch_neg = true;

        }

        // check if the yaw input is saturating
        if (m_ConfigTablePtr->RotorConfig[index].YawScale > 0.0f)
        {
            // A positive change in yaw will increase saturation
            m_SaturationStatus.flags.yaw_pos = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].YawScale < 0.0f)
        {
            // A negative change in yaw will increase saturation
            m_SaturationStatus.flags.yaw_neg = true;

        }

        // A positive change in thrust will increase saturation
        m_SaturationStatus.flags.thrust_pos = true;

    }

    // The motor is saturated at the lower limit
    // check which control axes and which directions are contributing
    if (clipping_low)
    {
        // check if the roll input is saturating
        if (m_ConfigTablePtr->RotorConfig[index].RollScale > 0.0f)
        {
            // A negative change in roll will increase saturation
            m_SaturationStatus.flags.roll_neg = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].RollScale < 0.0f)
        {
            // A positive change in roll will increase saturation
            m_SaturationStatus.flags.roll_pos = true;

        }

        // check if the pitch input is saturating
        if (m_ConfigTablePtr->RotorConfig[index].PitchScale > 0.0f)
        {
            // A negative change in pitch will increase saturation
            m_SaturationStatus.flags.pitch_neg = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].PitchScale < 0.0f)
        {
            // A positive change in pitch will increase saturation
            m_SaturationStatus.flags.pitch_pos = true;

        }

        // check if the yaw input is saturating
        if (m_ConfigTablePtr->RotorConfig[index].YawScale > 0.0f)
        {
            // A negative change in yaw will increase saturation
            m_SaturationStatus.flags.yaw_neg = true;

        }
        else if (m_ConfigTablePtr->RotorConfig[index].YawScale < 0.0f)
        {
            // A positive change in yaw will increase saturation
            m_SaturationStatus.flags.yaw_pos = true;

        }

        // A negative change in thrust will increase saturation
        m_SaturationStatus.flags.thrust_neg = true;

    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer groups_required function.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MultirotorMixer::groups_required(uint32 &groups)
{
    /* XXX for now, hardcoded to indexes 0-3 in control group zero */
    groups |= (1 << 0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer get_saturation_status function.                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
uint16 MultirotorMixer::get_saturation_status()
{
    return m_SaturationStatus.value;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer set_trim function.                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
uint32 MultirotorMixer::set_trim(float trim)
{
    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MultirotorMixer set_thrust_factor function.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MultirotorMixer::set_thrust_factor(float val)
{
    m_ThrustFactor = val;
}
