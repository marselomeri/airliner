
#include "SimpleMixer.h"

/* TODO:  Add in _pinfo(mixinfo) but do it so it doesn't have to be freed later. */
SimpleMixer::SimpleMixer(ControlCallback control_cb,
			 cpuaddr cb_handle, const MixerScaler_t &scaler) :
	Mixer(control_cb, cb_handle)
{
}

SimpleMixer::~SimpleMixer()
{
}

uint32 SimpleMixer::set_trim(float trim)
{
	//_pinfo->output_scaler.offset = trim;
	return 1;
}

/* TODO:  Need to rewrite this to remove the malloc and free */
SimpleMixer *
SimpleMixer::pwm_input(Mixer::ControlCallback control_cb, cpuaddr cb_handle, uint32 input, uint16 min,
		       uint16 mid, uint16 max)
{
//	SimpleMixer *sm = nullptr;
//	mixer_simple_s *mixinfo = nullptr;
//
//	mixinfo = (mixer_simple_s *)malloc(MIXER_SIMPLE_SIZE(1));
//
//	if (mixinfo == nullptr) {
//		//debug("could not allocate memory for mixer info");
//		goto out;
//	}
//
//	mixinfo->control_count = 1;
//
//	/*
//	 * Always pull from group 0, with the input value giving the channel.
//	 */
//	mixinfo->controls[0].control_group = 0;
//	mixinfo->controls[0].control_index = input;
//
//	/*
//	 * Conversion uses both the input and output side of the mixer.
//	 *
//	 * The input side is used to slide the control value such that the min argument
//	 * results in a value of zero.
//	 *
//	 * The output side is used to apply the scaling for the min/max values so that
//	 * the resulting output is a -1.0 ... 1.0 value for the min...max range.
//	 */
//	mixinfo->controls[0].scaler.negative_scale = 1.0f;
//	mixinfo->controls[0].scaler.positive_scale = 1.0f;
//	mixinfo->controls[0].scaler.offset = -mid;
//	mixinfo->controls[0].scaler.min_output = -(mid - min);
//	mixinfo->controls[0].scaler.max_output = (max - mid);
//
//	mixinfo->output_scaler.negative_scale = 500.0f / (mid - min);
//	mixinfo->output_scaler.positive_scale = 500.0f / (max - mid);
//	mixinfo->output_scaler.offset = 0.0f;
//	mixinfo->output_scaler.min_output = -1.0f;
//	mixinfo->output_scaler.max_output = 1.0f;
//
//	sm = new SimpleMixer(control_cb, cb_handle, mixinfo);
//
//	if (sm != nullptr) {
//		mixinfo = nullptr;
//		//debug("PWM input mixer for %d", input);
//
//	} else {
//		//debug("could not allocate memory for PWM input mixer");
//	}
//
//out:
//
//	if (mixinfo != nullptr) {
//		free(mixinfo);
//	}
//
//	return sm;
	return 0;
}

/* TODO: Update this to remove the _pinfo.  _pinfo requires dynamic memory. */
uint32
SimpleMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
	float		sum = 0.0f;

	//if (_pinfo == nullptr) {
	//	return 0;
	//}

	if (space < 1) {
		return 0;
	}

	//for (uint32 i = 0; i < _pinfo->control_count; i++) {
	//	float input;
    //
	//	_control_cb(_cb_handle,
	//		    _pinfo->controls[i].control_group,
	//		    _pinfo->controls[i].control_index,
	//		    input);
    //
	//	sum += scale(_pinfo->controls[i].scaler, input);
	//}

	//*outputs = scale(_pinfo->output_scaler, sum);
	return 1;
}

uint16
SimpleMixer::get_saturation_status()
{
	return 0;
}


/* TODO: Update this to remove the _pinfo.  _pinfo requires dynamic memory. */
void
SimpleMixer::groups_required(uint32 &groups)
{
	//for (unsigned i = 0; i < _pinfo->control_count; i++) {
	//	groups |= 1 << _pinfo->controls[i].control_group;
	//}
}

/* TODO: Update this to remove the _pinfo.  _pinfo requires dynamic memory. */
int32
SimpleMixer::check()
{
	int ret;
	float junk;

	/* sanity that presumes that a mixer includes a control no more than once */
	/* max of 32 groups due to groups_required API */
//	if (_pinfo->control_count > 32) {
//		return -2;
//	}

	/* validate the output scaler */
//	ret = scale_check(_pinfo->output_scaler);

	if (ret != 0) {
		return ret;
	}

	/* validate input scalers */
//	for (unsigned i = 0; i < _pinfo->control_count; i++) {
//
//		/* verify that we can fetch the control */
//		if (_control_cb(_cb_handle,
//				_pinfo->controls[i].control_group,
//				_pinfo->controls[i].control_index,
//				junk) != 0) {
//			return -3;
//		}
//
//		/* validate the scaler */
//		ret = scale_check(_pinfo->controls[i].scaler);
//
//		if (ret != 0) {
//			return (10 * i + ret);
//		}
//	}

	return 0;
}
