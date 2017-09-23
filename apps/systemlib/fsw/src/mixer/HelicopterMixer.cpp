
#include "HelicopterMixer.h"
#include <math.h>


namespace
{

float constrain(float val, float min, float max)
{
	return (val < min) ? min : ((val > max) ? max : val);
}

} // anonymous namespace

HelicopterMixer::HelicopterMixer(ControlCallback control_cb,
				 cpuaddr cb_handle,
		         MixerHeli_t *mixer_info) :
	Mixer(control_cb, cb_handle),
    m_MixerInfo(*mixer_info)
{

}

HelicopterMixer::~HelicopterMixer()
{
}

uint32
HelicopterMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    /* Find index to use for curves */
    float thrust_cmd = get_control(0, 3);
    int idx = (thrust_cmd / 0.25f);

    /* Make sure idx is in range */
    if (idx < 0) {
        idx = 0;

    } else if (idx > HELI_CURVES_NR_POINTS - 2) {
        /* We access idx + 1 below, so max legal index is (size - 2) */
        idx = HELI_CURVES_NR_POINTS - 2;
    }

    /* Local throttle curve gradient and offset */
    float tg = (m_MixerInfo.throttle_curve[idx + 1] - m_MixerInfo.throttle_curve[idx]) / 0.25f;
    float to = (m_MixerInfo.throttle_curve[idx]) - (tg * idx * 0.25f);
    float throttle = constrain((tg * thrust_cmd + to), 0.0f, 1.0f);

    /* Local pitch curve gradient and offset */
    float pg = (m_MixerInfo.pitch_curve[idx + 1] - m_MixerInfo.pitch_curve[idx]) / 0.25f;
    float po = (m_MixerInfo.pitch_curve[idx]) - (pg * idx * 0.25f);
    float collective_pitch = constrain((pg * thrust_cmd + po), -0.5f, 0.5f);

    float roll_cmd = get_control(0, 0);
    float pitch_cmd = get_control(0, 1);

    outputs[0] = throttle;

    for (unsigned i = 0; i < m_MixerInfo.control_count; i++) {
        outputs[i + 1] = collective_pitch
                 + cosf(m_MixerInfo.servos[i].angle) * pitch_cmd * m_MixerInfo.servos[i].arm_length
                 - sinf(m_MixerInfo.servos[i].angle) * roll_cmd * m_MixerInfo.servos[i].arm_length;
        outputs[i + 1] *= m_MixerInfo.servos[i].scale;
        outputs[i + 1] += m_MixerInfo.servos[i].offset;
        outputs[i + 1] = constrain(outputs[i + 1], m_MixerInfo.servos[i].min_output, m_MixerInfo.servos[i].max_output);
    }

    return m_MixerInfo.control_count + 1;
}

void
HelicopterMixer::groups_required(uint32 &groups)
{
    /* XXX for now, hardcoded to indexes 0-3 in control group zero */
    groups |= (1 << 0);
}

