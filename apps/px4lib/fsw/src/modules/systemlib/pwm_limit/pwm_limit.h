#ifndef PWM_LIMIT_H
#define PWM_LIMIT_H

#include "cfe.h"

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

uint64 hrt_elapsed_time(uint64 *input);

void PwmLimit_Init(PwmLimit_Data_t *limit);

void PwmLimit_Calc(const boolean armed, const boolean pre_armed, const unsigned num_channels, const uint16 reverse_mask,
            const uint16 *disarmed_pwm, const uint16 *min_pwm, const uint16 *max_pwm,
            const float *output, uint16 *effective_pwm, PwmLimit_Data_t *limit);
#endif /* PWM_LIMIT_H_ */
