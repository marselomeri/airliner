
#include "SimpleMixer.h"

SimpleMixer::SimpleMixer(ControlCallback control_cb,
			 cpuaddr cb_handle, const SYSTEMLIB_MixerScaler_t &scaler) :
	Mixer(control_cb, cb_handle)
{
}

SimpleMixer::~SimpleMixer()
{
}

uint32 SimpleMixer::set_trim(float trim)
{
	return 1;
}

int32
SimpleMixer::parse_output_scaler(const char *buf, uint32 &buflen, const SYSTEMLIB_MixerScaler_t &scaler)
{
	return 0;
}

int32
SimpleMixer::parse_control_scaler(const char *buf, uint32 &buflen, const SYSTEMLIB_MixerScaler_t &scaler,
        uint8 &control_group, uint8 &control_index)
{
    return 0;
}

SimpleMixer *
SimpleMixer::pwm_input(Mixer::ControlCallback control_cb, cpuaddr cb_handle, uint32 input, uint16 min,
		       uint16 mid, uint16 max)
{
    return 0;
}

uint32
SimpleMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    return 0;
}

uint16
SimpleMixer::get_saturation_status()
{
	return 0;
}

void
SimpleMixer::groups_required(uint32 &groups)
{
}

int32
SimpleMixer::check()
{
	return 0;
}
