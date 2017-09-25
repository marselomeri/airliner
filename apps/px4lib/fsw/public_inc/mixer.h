#ifndef _mixer_h_
#define _mixer_h_

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

/************************************************************************
** Type Definitions
*************************************************************************/

#define MIXER_MAX_ROTOR_COUNT   (8)


typedef struct {
    float   RollScale; /**< scales roll for this rotor */
    float   PitchScale;/**< scales pitch for this rotor */
    float   YawScale;  /**< scales yaw for this rotor */
    float   OutScale;  /**< scales total out for this rotor */
} MIXER_RotorConfig_t;

typedef enum
{
    MIXER_QUAD_X,
    MIXER_QUAD_H,
    MIXER_QUAD_PLUS,
    MIXER_QUAD_V,
    MIXER_QUAD_WIDE,
    MIXER_QUAD_S250AQ,
    MIXER_QUAD_DEADCAT,
    MIXER_HEX_X,
    MIXER_HEX_PLUS,
    MIXER_HEX_COX,
    MIXER_HEX_T,
    MIXER_OCTA_X,
    MIXER_OCTA_PLUS,
    MIXER_OCTA_COX,
    MIXER_OCTA_COX_WIDE,
    MIXER_TWIN_ENGINE,
    MIXER_TRI_Y,
    MIXER_MAX_GEOMETRY
} MIXER_MultirotorGeometry_t;


typedef struct {
    uint16 motor_pos  : 1; // 0 - true when any motor has saturated in the positive direction
    uint16 motor_neg  : 1; // 1 - true when any motor has saturated in the negative direction
    uint16 roll_pos   : 1; // 2 - true when a positive roll demand change will increase saturation
    uint16 roll_neg   : 1; // 3 - true when a negative roll demand change will increase saturation
    uint16 pitch_pos  : 1; // 4 - true when a positive pitch demand change will increase saturation
    uint16 pitch_neg  : 1; // 5 - true when a negative pitch demand change will increase saturation
    uint16 yaw_pos    : 1; // 6 - true when a positive yaw demand change will increase saturation
    uint16 yaw_neg    : 1; // 7 - true when a negative yaw demand change will increase saturation
    uint16 thrust_pos : 1; // 8 - true when a positive thrust demand change will increase saturation
    uint16 thrust_neg : 1; // 9 - true when a negative thrust demand change will increase saturation
} MIXER_SaturationFlags_t;

typedef union {
    MIXER_SaturationFlags_t flags;
    uint16 value;
} MIXER_SaturationStatus_t;






typedef struct
{
    float  RollScale;
    float  PitchScale;
    float  YawScale;
    float  IdleSpeed;
    float  DeltaOutMax;
    float  ThrustFactor;
    uint32 RotorCount;
    float  PrevOutputs[MIXER_MAX_ROTOR_COUNT];
    MIXER_RotorConfig_t RotorConfig[MIXER_MAX_ROTOR_COUNT];
    MIXER_ControlCallback_t ControlCb;
    void *Controls;
    MIXER_SaturationStatus_t SaturationStatus;
} MIXER_Data_t;


int32 MIXER_MixerInit(
        MIXER_ControlCallback_t ControlCb,
        void *Controls,
        MIXER_Data_t *MixerData,
        float RollScale,
        float PitchScale,
        float YawScale,
        float IdleSpeed,
        uint32 RotorCount,
        MIXER_RotorConfig_t *RotorConfig);


uint32 MIXER_Mix(MIXER_Data_t *Data, float *Outputs, uint32 Space, uint16 *StatusReg);


typedef enum {
    PWM_LIMIT_STATE_OFF = 0,
    PWM_LIMIT_STATE_INIT,
    PWM_LIMIT_STATE_RAMP,
    PWM_LIMIT_STATE_ON
} PwmLimit_State_t;

typedef struct
{
    PwmLimit_State_t state;
    uint64 time_armed;
} PwmLimit_Data_t;

void PwmLimit_Init(PwmLimit_Data_t *limit);

void PwmLimit_Calc(const boolean armed, const boolean pre_armed, const unsigned num_channels, const uint16 reverse_mask,
            const uint16 *disarmed_pwm, const uint16 *min_pwm, const uint16 *max_pwm,
            const float *output, uint16 *effective_pwm, PwmLimit_Data_t *limit);

#endif /* _mixer_h_ */

/************************/
/*  End of File Comment */
/************************/
