#ifndef _SYSTEMLIB_MIXER_HELICOPTER_MIXER_H
#define _SYSTEMLIB_MIXER_HELICOPTER_MIXER_H value

#include "cfe.h"
#include "Mixer.h"


/** helicopter swash servo mixer */
typedef struct {
	float angle;
	float arm_length;
	float scale;
	float offset;
	float min_output;
	float max_output;
} MixerHeliServo_t;

#define HELI_CURVES_NR_POINTS 5

/** helicopter swash plate mixer */
typedef struct {
	uint8				control_count;	/**< number of inputs */
	float				throttle_curve[HELI_CURVES_NR_POINTS];
	float				pitch_curve[HELI_CURVES_NR_POINTS];
	MixerHeliServo_t	servos[4];	/**< up to four inputs */
} MixerHeli_t;


/**
 * Generic helicopter mixer for helicopters with swash plate.
 *
 * Collects four inputs (roll, pitch, yaw, thrust) and mixes them to servo commands
 * for swash plate tilting and throttle- and pitch curves.
 */
class HelicopterMixer : public Mixer
{
public:
	/**
	 * Constructor.
	 *
	 * @param control_cb		Callback invoked to read inputs.
	 * @param cb_handle		Passed to control_cb.
	 * @param mixer_info		Pointer to heli mixer configuration
	 */
	HelicopterMixer(ControlCallback control_cb,
			cpuaddr cb_handle,
			MixerHeli_t *mixer_info);
	~HelicopterMixer();

	/**
	 * Factory method.
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
	 * @return			A new HelicopterMixer instance, or nullptr
	 *				if the text format is bad.
	 */
	static HelicopterMixer		*from_text(Mixer::ControlCallback control_cb,
			cpuaddr cb_handle,
			const char *buf,
			uint32 &buflen);

	virtual uint32		mix(float *outputs, uint32 space, uint16 *status_reg);
	virtual void		groups_required(uint32 &groups);

	virtual uint16		get_saturation_status(void) { return 0; }
	uint32 set_trim(float trim)
	{
		return 4;
	}

private:
	MixerHeli_t			m_MixerInfo;

	/* do not allow to copy */
	HelicopterMixer(const HelicopterMixer &);
	HelicopterMixer operator=(const HelicopterMixer &);
};

#endif
