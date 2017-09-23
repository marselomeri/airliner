#ifndef _SYSTEMLIB_MIXER_MIXER_GROUP_H
#define _SYSTEMLIB_MIXER_MIXER_GROUP_H

#include "cfe.h"
#include "Mixer.h"
/**
 * Group of mixers, built up from single mixers and processed
 * in order when mixing.
 */
class MixerGroup : public Mixer
{
public:
	MixerGroup(ControlCallback control_cb, cpuaddr cb_handle);
	~MixerGroup();

	virtual uint32		mix(float *outputs, uint32 space, uint16 *status_reg);
	virtual uint16		get_saturation_status(void);
	virtual void		groups_required(uint32 &groups);

	/**
	 * Add a mixer to the group.
	 *
	 * @param mixer			The mixer to be added.
	 */
	void				add_mixer(Mixer *mixer);

	/**
	 * Remove all the mixers from the group.
	 */
	void				reset();

	/**
	 * Count the mixers in the group.
	 */
	uint32			count();

	/**
	 * @brief      Update slew rate parameter. This tells instances of the class MultirotorMixer
	 *             the maximum allowed change of the output values per cycle.
	 *             The value is only valid for one cycle, in order to have continuous
	 *             slew rate limiting this function needs to be called before every call
	 *             to mix().
	 *
	 * @param[in]  delta_out_max  Maximum delta output.
	 *
	 */
	virtual void 			set_max_delta_out_once(float delta_out_max);

	/*
	 * Invoke the set_offset method of each mixer in the group
	 * for each value in page r_page_servo_control_trim
	 */
	uint32 set_trims(int16 *v, uint32 n);

	uint32 set_trim(float trim)
	{
		return 0;
	}

	/**
	 * @brief      Sets the thrust factor used to calculate mapping from desired thrust to pwm.
	 *
	 * @param[in]  val   The value
	 */
	virtual void	set_thrust_factor(float val);

private:
	Mixer				*m_First;	/**< linked list of mixers */

	/* do not allow to copy due to pointer data members */
	MixerGroup(const MixerGroup &);
	MixerGroup operator=(const MixerGroup &);
};

#endif
