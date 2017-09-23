#ifndef _SYSTEMLIB_MIXER_SIMPLE_MIXER_H
#define _SYSTEMLIB_MIXER_SIMPLE_MIXER_H value

#include "cfe.h"
#include "Mixer.h"

/**
 * Simple summing mixer.
 *
 * Collects zero or more inputs and mixes them to a single output.
 */
class SimpleMixer : public Mixer
{
public:
	/**
	 * Constructor
	 *
	 * @param mixinfo		Mixer configuration.  The pointer passed
	 *				becomes the property of the mixer and
	 *				will be freed when the mixer is deleted.
	 */
	SimpleMixer(ControlCallback control_cb,
		    cpuaddr cb_handle,
		    const SYSTEMLIB_MixerScaler_t &scaler);
	~SimpleMixer();

	/**
	 * Factory method with full external configuration.
	 *
	 * Given a pointer to a buffer containing a text description of the mixer,
	 * returns a pointer to a new instance of the mixer.
	 *
	 * @param control_cb		The callback to invoke when fetching a
	 *				control value.
	 * @param cb_handle		Handle passed to the control callback.
	 * @param buf			Buffer containing a text description of
	 *				the mixer.
	 * @param buflen		Length of the buffer in bytes, adjusted
	 *				to reflect the bytes consumed.
	 * @return			A new SimpleMixer instance, or nullptr
	 *				if the text format is bad.
	 */
	static SimpleMixer		*from_text(Mixer::ControlCallback control_cb,
			cpuaddr cb_handle,
			const char *buf,
			uint32 &buflen);

	/**
	 * Factory method for PWM/PPM input to internal float representation.
	 *
	 * @param control_cb		The callback to invoke when fetching a
	 *				control value.
	 * @param cb_handle		Handle passed to the control callback.
	 * @param input			The control index used when fetching the input.
	 * @param min			The PWM/PPM value considered to be "minimum" (gives -1.0 out)
	 * @param mid			The PWM/PPM value considered to be the midpoint (gives 0.0 out)
	 * @param max			The PWM/PPM value considered to be "maximum" (gives 1.0 out)
	 * @return			A new SimpleMixer instance, or nullptr if one could not be
	 *				allocated.
	 */
	static SimpleMixer		*pwm_input(Mixer::ControlCallback control_cb,
			cpuaddr cb_handle,
			uint32 input,
			uint16 min,
			uint16 mid,
			uint16 max);

	virtual uint32		mix(float *outputs, uint32 space, uint16 *status_reg);
	virtual uint16		    get_saturation_status(void);
	virtual void			groups_required(uint32 &groups);

	/**
	 * Check that the mixer configuration as loaded is sensible.
	 *
	 * Note that this function will call control_cb, but only cares about
	 * error returns, not the input value.
	 *
	 * @return			Zero if the mixer makes sense, nonzero otherwise.
	 */
	int32			check();

	uint32 set_trim(float trim);

protected:

private:
	static int32		parse_output_scaler(const char *buf, uint32 &buflen, const SYSTEMLIB_MixerScaler_t &scaler);
	static int32		parse_control_scaler(const char *buf,
	        uint32 &buflen,
	        const SYSTEMLIB_MixerScaler_t &scaler,
			uint8 &control_group,
			uint8 &control_index);

	/* do not allow to copy due to ptr data members */
	//SimpleMixer(const SimpleMixer &);
	//SimpleMixer operator=(const SimpleMixer &);
};


#endif
