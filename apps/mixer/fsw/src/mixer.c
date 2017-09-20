/*************************************************************************
** Includes
*************************************************************************/
#include "mixer.h"
#include "mixer_version.h"
#include <string.h>
#include <math.h>
#include <float.h>

/*************************************************************************
** Macro Definitions
*************************************************************************/
#define PROGRESS_INT_SCALING    10000

/*
 * time for the ESCs to initialize
 * (this is not actually needed if PWM is sent right after boot)
 */
#define INIT_TIME_US 50000
/*
 * time to slowly ramp up the ESCs
 */
#define RAMP_TIME_US 500000

typedef uint64 hrt_abstime;


/*************************************************************************
** Private Function Prototypes
*************************************************************************/
int32 MIXER_LibInit(void);
float MIXER_Constrain(float val, float min, float max);
float MIXER_GetControl(MIXER_Data_t *MixerData, uint8 group, uint8 index);
void MIXER_UpdateSaturationStatus(MIXER_Data_t *Data, uint32 index, boolean clipping_high, boolean clipping_low);
uint64 hrt_elapsed_time(uint64 *input);

void PwmLimit_Init(PwmLimit_Data_t *limit);
void PwmLimit_Calc(
        const boolean armed,
        const boolean pre_armed,
        const unsigned num_channels,
        const uint16 reverse_mask,
        const uint16 *disarmed_pwm,
        const uint16 *min_pwm,
        const uint16 *max_pwm,
        const float *output,
        uint16 *effective_pwm,
        PwmLimit_Data_t *limit);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MIXER_LibInit(void)
{
    OS_printf ("Mixer Lib Initialized.  Version %d.%d.%d.%d",
                MIXER_MAJOR_VERSION,
                MIXER_MINOR_VERSION,
                MIXER_REVISION,
                MIXER_MISSION_REV);
                
    return OS_SUCCESS;
 
}/* End Mixer_LibInit */



int32 MIXER_MixerInit(
        MIXER_ControlCallback_t ControlCb,
        void *Controls,
        MIXER_Data_t *MixerData,
        float RollScale,
        float PitchScale,
        float YawScale,
        float IdleSpeed,
        uint32 RotorCount,
        MIXER_Rotor *RotorConfig)
{
    uint32 i = 0;

    if(ControlCb == 0)
    {
        return -1;
    }

    if(MixerData == 0)
    {
        return -1;
    }

    if(RotorConfig == 0)
    {
        return -1;
    }

    MixerData->RollScale = RollScale;
    MixerData->PitchScale = PitchScale;
    MixerData->YawScale = YawScale;
    MixerData->IdleSpeed = -1.0f + IdleSpeed * 2.0f; /* shift to output range here to avoid runtime calculation */
    MixerData->DeltaOutMax = 0.0f;
    MixerData->ThrustFactor = 0.0f;
    MixerData->RotorCount = RotorCount;

    memset(MixerData->RotorConfig, 0, sizeof(MixerData->RotorConfig));

    for(i=0; i < RotorCount; ++i)
    {
        MixerData->RotorConfig[i].RollScale = RotorConfig[i].RollScale;
        MixerData->RotorConfig[i].PitchScale = RotorConfig[i].PitchScale;
        MixerData->RotorConfig[i].YawScale = RotorConfig[i].YawScale;
        MixerData->RotorConfig[i].OutScale = RotorConfig[i].OutScale;
    }

    memset(MixerData->PrevOutputs, 0, sizeof(MixerData->PrevOutputs));
    memset(MixerData->PrevOutputs, IdleSpeed, RotorCount * sizeof(float));

    MixerData->Controls = Controls;
    MixerData->ControlCb = ControlCb;

    return 0;
}



uint32 MIXER_Mix(MIXER_Data_t *Data, float *Outputs, uint32 Space, uint16 *StatusReg)
{
    /* Summary of mixing strategy:
    1) mix roll, pitch and thrust without yaw.
    2) if some outputs violate range [0,1] then try to shift all outputs to minimize violation ->
        increase or decrease total thrust (boost). The total increase or decrease of thrust is limited
        (max_thrust_diff). If after the shift some outputs still violate the bounds then scale roll & pitch.
        In case there is violation at the lower and upper bound then try to shift such that violation is equal
        on both sides.
    3) mix in yaw and scale if it leads to limit violation.
    4) scale all outputs to range [idle_speed,1]
    */

    float       roll    = MIXER_Constrain(MIXER_GetControl(Data, 0, 0) * Data->RollScale, -1.0f, 1.0f);
    float       pitch   = MIXER_Constrain(MIXER_GetControl(Data, 0, 1) * Data->PitchScale, -1.0f, 1.0f);
    float       yaw     = MIXER_Constrain(MIXER_GetControl(Data, 0, 2) * Data->YawScale, -1.0f, 1.0f);
    float       thrust  = MIXER_Constrain(MIXER_GetControl(Data, 0, 3), 0.0f, 1.0f);
    float       min_out = 1.0f;
    float       max_out = 0.0f;

    // clean out class variable used to capture saturation
    Data->SaturationStatus.value = 0;

    // thrust boost parameters
    float thrust_increase_factor = 1.5f;
    float thrust_decrease_factor = 0.6f;

    /* perform initial mix pass yielding unbounded outputs, ignore yaw */
    for (unsigned i = 0; i < Data->RotorCount; i++) {
        float out = roll * Data->RotorConfig[i].RollScale +
                pitch * Data->RotorConfig[i].PitchScale +
                thrust;

        out *= Data->RotorConfig[i].OutScale;

        /* calculate min and max output values */
        if (out < min_out) {
            min_out = out;
        }

        if (out > max_out) {
            max_out = out;
        }

        Outputs[i] = out;
    }

    float boost = 0.0f;     // value added to demanded thrust (can also be negative)
    float roll_pitch_scale = 1.0f;  // scale for demanded roll and pitch

    if (min_out < 0.0f && max_out < 1.0f && -min_out <= 1.0f - max_out) {
        float max_thrust_diff = thrust * thrust_increase_factor - thrust;

        if (max_thrust_diff >= -min_out) {
            boost = -min_out;

        } else {
            boost = max_thrust_diff;
            roll_pitch_scale = (thrust + boost) / (thrust - min_out);
        }

    } else if (max_out > 1.0f && min_out > 0.0f && min_out >= max_out - 1.0f) {
        float max_thrust_diff = thrust - thrust_decrease_factor * thrust;

        if (max_thrust_diff >= max_out - 1.0f) {
            boost = -(max_out - 1.0f);

        } else {
            boost = -max_thrust_diff;
            roll_pitch_scale = (1 - (thrust + boost)) / (max_out - thrust);
        }

    } else if (min_out < 0.0f && max_out < 1.0f && -min_out > 1.0f - max_out) {
        float max_thrust_diff = thrust * thrust_increase_factor - thrust;
        boost = MIXER_Constrain(-min_out - (1.0f - max_out) / 2.0f, 0.0f, max_thrust_diff);
        roll_pitch_scale = (thrust + boost) / (thrust - min_out);

    } else if (max_out > 1.0f && min_out > 0.0f && min_out < max_out - 1.0f) {
        float max_thrust_diff = thrust - thrust_decrease_factor * thrust;
        boost = MIXER_Constrain(-(max_out - 1.0f - min_out) / 2.0f, -max_thrust_diff, 0.0f);
        roll_pitch_scale = (1 - (thrust + boost)) / (max_out - thrust);

    } else if (min_out < 0.0f && max_out > 1.0f) {
        boost = MIXER_Constrain(-(max_out - 1.0f + min_out) / 2.0f, thrust_decrease_factor * thrust - thrust,
                    thrust_increase_factor * thrust - thrust);
        roll_pitch_scale = (thrust + boost) / (thrust - min_out);
    }

    // capture saturation
    if (min_out < 0.0f) {
        Data->SaturationStatus.flags.motor_neg = TRUE;
    }

    if (max_out > 1.0f) {
        Data->SaturationStatus.flags.motor_pos = TRUE;
    }

    // Thrust reduction is used to reduce the collective thrust if we hit
    // the upper throttle limit
    float thrust_reduction = 0.0f;

    // mix again but now with thrust boost, scale roll/pitch and also add yaw
    for (unsigned i = 0; i < Data->RotorCount; i++) {
        float out = (roll * Data->RotorConfig[i].RollScale +
                 pitch * Data->RotorConfig[i].PitchScale) * roll_pitch_scale +
                yaw * Data->RotorConfig[i].YawScale +
                thrust + boost;

        out *= Data->RotorConfig[i].OutScale;

        // scale yaw if it violates limits. inform about yaw limit reached
        if (out < 0.0f) {
            if (fabsf(Data->RotorConfig[i].YawScale) <= FLT_EPSILON) {
                yaw = 0.0f;

            } else {
                yaw = -((roll * Data->RotorConfig[i].RollScale + pitch * Data->RotorConfig[i].PitchScale) *
                    roll_pitch_scale + thrust + boost) / Data->RotorConfig[i].YawScale;
            }

        } else if (out > 1.0f) {
            // allow to reduce thrust to get some yaw response
            float prop_reduction = fminf(0.15f, out - 1.0f);
            // keep the maximum requested reduction
            thrust_reduction = fmaxf(thrust_reduction, prop_reduction);

            if (fabsf(Data->RotorConfig[i].YawScale) <= FLT_EPSILON) {
                yaw = 0.0f;

            } else {
                yaw = (1.0f - ((roll * Data->RotorConfig[i].RollScale + pitch * Data->RotorConfig[i].PitchScale) *
                           roll_pitch_scale + (thrust - thrust_reduction) + boost)) / Data->RotorConfig[i].YawScale;
            }
        }
    }

    // Apply collective thrust reduction, the maximum for one prop
    thrust -= thrust_reduction;

    // add yaw and scale outputs to range idle_speed...1
    for (unsigned i = 0; i < Data->RotorCount; i++) {
        Outputs[i] = (roll * Data->RotorConfig[i].RollScale +
                  pitch * Data->RotorConfig[i].PitchScale) * roll_pitch_scale +
                 yaw * Data->RotorConfig[i].YawScale +
                 thrust + boost;

        /*
            implement simple model for static relationship between applied motor pwm and motor thrust
            model: thrust = (1 - _thrust_factor) * PWM + _thrust_factor * PWM^2
            this model assumes normalized input / output in the range [0,1] so this is the right place
            to do it as at this stage the outputs are in that range.
         */
        if (Data->ThrustFactor > 0.0f) {
            Outputs[i] = -(1.0f - Data->ThrustFactor) / (2.0f * Data->ThrustFactor) + sqrtf((1.0f - Data->ThrustFactor) *
                    (1.0f - Data->ThrustFactor) / (4.0f * Data->ThrustFactor * Data->ThrustFactor) + (Outputs[i] < 0.0f ? 0.0f : Outputs[i] /
                            Data->ThrustFactor));
        }

        Outputs[i] = MIXER_Constrain(Data->IdleSpeed + (Outputs[i] * (1.0f - Data->IdleSpeed)), Data->IdleSpeed, 1.0f);

    }

    /* slew rate limiting and saturation checking */
    for (unsigned i = 0; i < Data->RotorCount; i++) {
        boolean clipping_high = FALSE;
        boolean clipping_low = FALSE;

        // check for saturation against static limits
        if (Outputs[i] > 0.99f) {
            clipping_high = TRUE;

        } else if (Outputs[i] < Data->IdleSpeed + 0.01f) {
            clipping_low = TRUE;

        }

        // check for saturation against slew rate limits
        if (Data->DeltaOutMax > 0.0f) {
            float delta_out = Outputs[i] - Data->PrevOutputs[i];

            if (delta_out > Data->DeltaOutMax) {
                Outputs[i] = Data->PrevOutputs[i] + Data->DeltaOutMax;
                clipping_high = TRUE;

            } else if (delta_out < -Data->DeltaOutMax) {
                Outputs[i] = Data->PrevOutputs[i] - Data->DeltaOutMax;
                clipping_low = TRUE;

            }
        }

        Data->PrevOutputs[i] = Outputs[i];

        // update the saturation status report
        MIXER_UpdateSaturationStatus(Data, i, clipping_high, clipping_low);

    }

    // this will force the caller of the mixer to always supply new slew rate values, otherwise no slew rate limiting will happen
    Data->DeltaOutMax = 0.0f;

    // Notify saturation status
    if (StatusReg != 0) {
        (*StatusReg) = Data->SaturationStatus.value;
    }

    return Data->RotorCount;
}


float MIXER_Constrain(float val, float min, float max)
{
    return (val < min) ? min : ((val > max) ? max : val);
}


float MIXER_GetControl(MIXER_Data_t *MixerData, uint8 group, uint8 index)
{
    float   value;

    MixerData->ControlCb(MixerData->Controls, group, index, &value);

    return value;
}


/*
 * This function update the control saturation status report using hte following inputs:
 *
 * index: 0 based index identifying the motor that is saturating
 * clipping_high: true if the motor demand is being limited in the positive direction
 * clipping_low: true if the motor demand is being limited in the negative direction
*/
void MIXER_UpdateSaturationStatus(MIXER_Data_t *Data, uint32 index, boolean clipping_high, boolean clipping_low)
{
    // The motor is saturated at the upper limit
    // check which control axes and which directions are contributing
    if (clipping_high) {
        if (Data->RotorConfig[index].RollScale > 0.0f) {
            // A positive change in roll will increase saturation
            Data->SaturationStatus.flags.roll_pos = TRUE;

        } else if (Data->RotorConfig[index].RollScale < 0.0f) {
            // A negative change in roll will increase saturation
            Data->SaturationStatus.flags.roll_neg = TRUE;

        }

        // check if the pitch input is saturating
        if (Data->RotorConfig[index].PitchScale > 0.0f) {
            // A positive change in pitch will increase saturation
            Data->SaturationStatus.flags.pitch_pos = TRUE;

        } else if (Data->RotorConfig[index].PitchScale < 0.0f) {
            // A negative change in pitch will increase saturation
            Data->SaturationStatus.flags.pitch_neg = TRUE;

        }

        // check if the yaw input is saturating
        if (Data->RotorConfig[index].YawScale > 0.0f) {
            // A positive change in yaw will increase saturation
            Data->SaturationStatus.flags.yaw_pos = TRUE;

        } else if (Data->RotorConfig[index].YawScale < 0.0f) {
            // A negative change in yaw will increase saturation
            Data->SaturationStatus.flags.yaw_neg = TRUE;

        }

        // A positive change in thrust will increase saturation
        Data->SaturationStatus.flags.thrust_pos = TRUE;

    }

    // The motor is saturated at the lower limit
    // check which control axes and which directions are contributing
    if (clipping_low) {
        // check if the roll input is saturating
        if (Data->RotorConfig[index].RollScale > 0.0f) {
            // A negative change in roll will increase saturation
            Data->SaturationStatus.flags.roll_neg = TRUE;

        } else if (Data->RotorConfig[index].RollScale < 0.0f) {
            // A positive change in roll will increase saturation
            Data->SaturationStatus.flags.roll_pos = TRUE;

        }

        // check if the pitch input is saturating
        if (Data->RotorConfig[index].PitchScale > 0.0f) {
            // A negative change in pitch will increase saturation
            Data->SaturationStatus.flags.pitch_neg = TRUE;

        } else if (Data->RotorConfig[index].PitchScale < 0.0f) {
            // A positive change in pitch will increase saturation
            Data->SaturationStatus.flags.pitch_pos = TRUE;

        }

        // check if the yaw input is saturating
        if (Data->RotorConfig[index].YawScale > 0.0f) {
            // A negative change in yaw will increase saturation
            Data->SaturationStatus.flags.yaw_neg = TRUE;

        } else if (Data->RotorConfig[index].YawScale < 0.0f) {
            // A positive change in yaw will increase saturation
            Data->SaturationStatus.flags.yaw_pos = TRUE;

        }

        // A negative change in thrust will increase saturation
        Data->SaturationStatus.flags.thrust_neg = TRUE;

    }
}


void PwmLimit_Init(PwmLimit_Data_t *limit)
{
    limit->state = PWM_LIMIT_STATE_INIT;
    limit->time_armed = 0;
}


void PwmLimit_Calc(const boolean armed, const boolean pre_armed, const unsigned num_channels, const uint16 reverse_mask,
            const uint16 *disarmed_pwm, const uint16 *min_pwm, const uint16 *max_pwm,
            const float *output, uint16 *effective_pwm, PwmLimit_Data_t *limit)
{

    /* first evaluate state changes */
    switch (limit->state) {
    case PWM_LIMIT_STATE_INIT:

        if (armed) {

            /* set arming time for the first call */
            if (limit->time_armed == 0) {
                uint32 sec = 0;
                uint32 ms = 0;

                /* reset arming time, used for ramp timing */
                CFE_PSP_Get_Timebase(&sec, &ms);
                limit->time_armed = sec*1000000 + ms;
            }

            uint32 sec = 0;
            uint32 ms = 0;
            uint64 now = 0;
            uint64 delta = 0;

            /* reset arming time, used for ramp timing */
            CFE_PSP_Get_Timebase(&sec, &ms);
            now = sec*1000000 + ms;

            delta = now - limit->time_armed;

            if (delta >= INIT_TIME_US) {
                limit->state = PWM_LIMIT_STATE_OFF;
            }
        }

        break;

    case PWM_LIMIT_STATE_OFF:
        if (armed) {
            uint32 sec = 0;
            uint32 ms = 0;

            /* reset arming time, used for ramp timing */
            CFE_PSP_Get_Timebase(&sec, &ms);
            limit->time_armed = sec*1000000 + ms;

            limit->state = PWM_LIMIT_STATE_RAMP;
        }

        break;

    case PWM_LIMIT_STATE_RAMP:
        if (!armed) {
            limit->state = PWM_LIMIT_STATE_OFF;

        } else if (hrt_elapsed_time(&limit->time_armed) >= RAMP_TIME_US) {
            limit->state = PWM_LIMIT_STATE_ON;
        }

        break;

    case PWM_LIMIT_STATE_ON:
        if (!armed) {
            limit->state = PWM_LIMIT_STATE_OFF;
        }

        break;

    default:
        break;
    }

    /* if the system is pre-armed, the limit state is temporarily on,
     * as some outputs are valid and the non-valid outputs have been
     * set to NaN. This is not stored in the state machine though,
     * as the throttle channels need to go through the ramp at
     * regular arming time.
     */

    unsigned local_limit_state = limit->state;

    if (pre_armed) {
        local_limit_state = PWM_LIMIT_STATE_ON;
    }

    unsigned progress;

    /* then set effective_pwm based on state */
    switch (local_limit_state) {
    case PWM_LIMIT_STATE_OFF:
    case PWM_LIMIT_STATE_INIT:
        for (unsigned i = 0; i < num_channels; i++) {
            effective_pwm[i] = disarmed_pwm[i];
        }

        break;

    case PWM_LIMIT_STATE_RAMP: {
            hrt_abstime diff = hrt_elapsed_time(&limit->time_armed);

            progress = diff * PROGRESS_INT_SCALING / RAMP_TIME_US;

            if (progress > PROGRESS_INT_SCALING) {
                progress = PROGRESS_INT_SCALING;
            }

            for (unsigned i = 0; i < num_channels; i++) {

                float control_value = output[i];

                /* check for invalid / disabled channels */
                if (!isfinite(control_value)) {
                    effective_pwm[i] = disarmed_pwm[i];
                    continue;
                }

                uint16 ramp_min_pwm;

                /* if a disarmed pwm value was set, blend between disarmed and min */
                if (disarmed_pwm[i] > 0) {

                    /* safeguard against overflows */
                    unsigned disarmed = disarmed_pwm[i];

                    if (disarmed > min_pwm[i]) {
                        disarmed = min_pwm[i];
                    }

                    unsigned disarmed_min_diff = min_pwm[i] - disarmed;
                    ramp_min_pwm = disarmed + (disarmed_min_diff * progress) / PROGRESS_INT_SCALING;

                } else {

                    /* no disarmed pwm value set, choose min pwm */
                    ramp_min_pwm = min_pwm[i];
                }

                if (reverse_mask & (1 << i)) {
                    control_value = -1.0f * control_value;
                }

                effective_pwm[i] = control_value * (max_pwm[i] - ramp_min_pwm) / 2 + (max_pwm[i] + ramp_min_pwm) / 2;

                /* last line of defense against invalid inputs */
                if (effective_pwm[i] < ramp_min_pwm) {
                    effective_pwm[i] = ramp_min_pwm;

                } else if (effective_pwm[i] > max_pwm[i]) {
                    effective_pwm[i] = max_pwm[i];
                }
            }
        }
        break;

    case PWM_LIMIT_STATE_ON:

        for (unsigned i = 0; i < num_channels; i++) {

            float control_value = output[i];

            /* check for invalid / disabled channels */
            if (!isfinite(control_value)) {
                effective_pwm[i] = disarmed_pwm[i];
                continue;
            }

            if (reverse_mask & (1 << i)) {
                control_value = -1.0f * control_value;
            }

            effective_pwm[i] = control_value * (max_pwm[i] - min_pwm[i]) / 2 + (max_pwm[i] + min_pwm[i]) / 2;

            /* last line of defense against invalid inputs */
            if (effective_pwm[i] < min_pwm[i]) {
                effective_pwm[i] = min_pwm[i];

            } else if (effective_pwm[i] > max_pwm[i]) {
                effective_pwm[i] = max_pwm[i];
            }

        }

        break;

    default:
        break;
    }
}

uint64 hrt_elapsed_time(uint64 *input)
{
    uint32 sec = 0;
    uint32 ms = 0;
    uint64 now = 0;
    uint64 delta = 0;

    /* reset arming time, used for ramp timing */
    CFE_PSP_Get_Timebase(&sec, &ms);
    now = sec*1000000 + ms;

    delta = now - *input;

    return delta;
}

/************************/
/*  End of File Comment */
/************************/
