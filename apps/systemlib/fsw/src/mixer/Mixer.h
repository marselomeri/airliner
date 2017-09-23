/**
 * @file mixer.h
 *
 * Generic, programmable, procedural control signal mixers.
 *
 * This library implements a generic mixer interface that can be used
 * by any driver or subsytem that wants to combine several control signals
 * into a single output.
 *
 * Terminology
 * ===========
 *
 * control value
 *	A mixer input value, typically provided by some controlling
 *	component of the system.
 *
 * control group
 * 	A collection of controls provided by a single controlling component.
 *
 * actuator
 *	The mixer output value.
 *
 *
 * Mixing basics
 * =============
 *
 * An actuator derives its value from the combination of one or more
 * control values. Each of the control values is scaled according to
 * the actuator's configuration and then combined to produce the
 * actuator value, which may then be further scaled to suit the specific
 * output type.
 *
 * Internally, all scaling is performed using floating point values.
 * Inputs and outputs are clamped to the range -1.0 to 1.0.
 *
 * control    control   control
 *    |          |         |
 *    v          v         v
 *  scale      scale     scale
 *    |          |         |
 *    |          v         |
 *    +-------> mix <------+
 *               |
 *             scale
 *               |
 *               v
 *              out
 *
 * Scaling
 * -------
 *
 * Each scaler allows the input value to be scaled independently for
 * inputs greater/less than zero. An offset can be applied to the output,
 * as well as lower and upper boundary constraints.
 * Negative scaling factors cause the output to be inverted (negative input
 * produces positive output).
 *
 * Scaler pseudocode:
 *
 * if (input < 0)
 *     output = (input * NEGATIVE_SCALE) + OFFSET
 * else
 *     output = (input * POSITIVE_SCALE) + OFFSET
 *
 * if (output < LOWER_LIMIT)
 *     output = LOWER_LIMIT
 * if (output > UPPER_LIMIT)
 *     output = UPPER_LIMIT
 *
 *
 * Mixing
 * ------
 *
 * Mixing behaviour varies based on the specific mixer class; each
 * mixer class describes its behaviour in more detail.
 *
 *
 * Controls
 * --------
 *
 * The precise assignment of controls may vary depending on the
 * application, but the following assignments should be used
 * when appropriate.  Some mixer classes have specific assumptions
 * about the assignment of controls.
 *
 * control | standard meaning
 * --------+-----------------------
 *     0   | roll
 *     1   | pitch
 *     2   | yaw
 *     3   | primary thrust
 */


#ifndef _SYSTEMLIB_MIXER_H
#define _SYSTEMLIB_MIXER_H value

#include "cfe.h"

struct SYSTEMLIB_MixerScaler_t {
    float negative_scale;
    float positive_scale;
    float offset;
    float min_output;
    float max_output;
};

/**
 * Abstract class defining a mixer mixing zero or more inputs to
 * one or more outputs.
 */
class Mixer
{
public:
	/** next mixer in a list */
	Mixer				*m_Next;

	/**
	 * Fetch a control value.
	 *
	 * @param handle		Token passed when the callback is registered.
	 * @param control_group		The group to fetch the control from.
	 * @param control_index		The group-relative index to fetch the control from.
	 * @param control		The returned control
	 * @return			Zero if the value was fetched, nonzero otherwise.
	 */
	typedef int32	(* ControlCallback)(cpuaddr handle,
					    uint8 control_group,
					    uint8 control_index,
					    float &control);

	/**
	 * Constructor.
	 *
	 * @param control_cb		Callback invoked when reading controls.
	 */
	Mixer(ControlCallback control_cb, cpuaddr cb_handle);
	virtual ~Mixer() {};

	/**
	 * Perform the mixing function.
	 *
	 * @param outputs		Array into which mixed output(s) should be placed.
	 * @param space			The number of available entries in the output array;
	 * @return			The number of entries in the output array that were populated.
	 */
	virtual uint32		mix(float *outputs, uint32 space, uint16 *status_reg) = 0;

	/**
	 * Get the saturation status.
	 *
	 * @return			Integer bitmask containing saturation_status from multirotor_motor_limits.msg .
	 */
	virtual uint16		get_saturation_status(void) = 0;

	/**
	 * Analyses the mix configuration and updates a bitmask of groups
	 * that are required.
	 *
	 * @param groups		A bitmask of groups (0-31) that the mixer requires.
	 */
	virtual void			groups_required(uint32 &groups) = 0;

	/**
	 * @brief      Empty method, only implemented for MultirotorMixer and MixerGroup class.
	 *
	 * @param[in]  delta_out_max  Maximum delta output.
	 *
	 */
	virtual void 			set_max_delta_out_once(float delta_out_max) {};

	/**
	 * @brief Set trim offset for this mixer
	 *
	 * @return the number of outputs this mixer feeds to
	 */
	virtual uint32 set_trim(float trim) = 0;

	/*
	 * @brief      Sets the thrust factor used to calculate mapping from desired thrust to pwm.
	 *
	 * @param[in]  val   The value
	 */
	virtual void 			set_thrust_factor(float val) {};

protected:
	/** client-supplied callback used when fetching control values */
	ControlCallback	m_ControlCb;
	cpuaddr			m_CbHandle;

	/**
	 * Invoke the client callback to fetch a control value.
	 *
	 * @param group			Control group to fetch from.
	 * @param index			Control index to fetch.
	 * @return			The control value.
	 */
	float				get_control(uint8 group, uint8 index);

	/**
	 * Perform simpler linear scaling.
	 *
	 * @param scaler		The scaler configuration.
	 * @param input			The value to be scaled.
	 * @return			The scaled value.
	 */
	static float			scale(const SYSTEMLIB_MixerScaler_t &scaler, float input);

	/**
	 * Validate a scaler
	 *
	 * @param scaler		The scaler to be validated.
	 * @return			Zero if good, nonzero otherwise.
	 */
	static int32			scale_check(const SYSTEMLIB_MixerScaler_t &scaler);

private:

	/* do not allow to copy due to pointer data members */
	Mixer(const Mixer &);
	Mixer &operator=(const Mixer &);
};


#endif
