#ifndef _SYSTEMLIB_MIXER_NULL_MIXER_H
#define _SYSTEMLIB_MIXER_NULL_MIXER_H value

#include "cfe.h"
#include "Mixer.h"

/**
 * Null mixer; returns zero.
 *
 * Used as a placeholder for output channels that are unassigned in groups.
 */
class NullMixer : public Mixer
{
public:
	NullMixer();
	~NullMixer() {};

	virtual uint32  		mix(float *outputs, uint32 space, uint16 *status_reg);
	virtual uint16  		get_saturation_status(void);
	virtual void			groups_required(uint32 &groups);
	virtual void 			set_offset(float trim) {};
	uint32 set_trim(float trim)
	{
		return 0;
	}

};


#endif
