
#include "NullMixer.h"

NullMixer::NullMixer() :
	Mixer(nullptr, 0)
{
}

uint32
NullMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    if (space > 0) {
        *outputs = 0.0f;
        return 1;
    }

    return 0;
}

uint16
NullMixer::get_saturation_status()
{
	return 0;
}

void
NullMixer::groups_required(uint32 &groups)
{

}
