
#include "Mixer.h"

Mixer::Mixer(ControlCallback ControlCb, cpuaddr CbHandle) :
    m_Next(nullptr),
    m_ControlCb(ControlCb),
    m_CbHandle(CbHandle)
{
    OS_printf("HELLO WORLD!\n");
}

float
Mixer::get_control(uint8 group, uint8 index)
{
    float   value;

    m_ControlCb(m_CbHandle, group, index, value);

    return value;
}


float
Mixer::scale(const MixerScaler_t &scaler, float input)
{
    float output;

    if (input < 0.0f)
    {
        output = (input * scaler.negative_scale) + scaler.offset;
    }
    else
    {
        output = (input * scaler.positive_scale) + scaler.offset;
    }

    if (output > scaler.max_output)
    {
        output = scaler.max_output;
    }
    else if (output < scaler.min_output)
    {
        output = scaler.min_output;
    }

    return output;
}

int32
Mixer::scale_check(const MixerScaler_t &scaler)
{
    if (scaler.offset > 1.001f) {
        return 1;
    }

    if (scaler.offset < -1.001f) {
        return 2;
    }

    if (scaler.min_output > scaler.max_output) {
        return 3;
    }

    if (scaler.min_output < -1.001f) {
        return 4;
    }

    if (scaler.max_output > 1.001f) {
        return 5;
    }

    return 0;
}
