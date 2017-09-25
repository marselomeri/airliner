#ifndef MIXER_GROUP_H
#define MIXER_GROUP_H

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
