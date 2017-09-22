
#include "mixer.h"

MixerGroup::MixerGroup(ControlCallback control_cb, cpuaddr cb_handle) :
	Mixer(control_cb, cb_handle),
    m_First(nullptr)
{
}

MixerGroup::~MixerGroup()
{
    reset();
}

void
MixerGroup::add_mixer(Mixer *mixer)
{
    Mixer **mpp;

    mpp = &m_First;

    while (*mpp != nullptr) {
        mpp = &((*mpp)->m_Next);
    }

    *mpp = mixer;
    mixer->m_Next = nullptr;
}

void
MixerGroup::reset()
{
    Mixer *mixer;
    Mixer *next = m_First;

    /* flag mixer as invalid */
    m_First = nullptr;

    /* discard sub-mixers */
    while (next != nullptr) {
        mixer = next;
        next = mixer->m_Next;
        delete mixer;
        mixer = nullptr;
    }
}

uint32
MixerGroup::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    Mixer   *mixer = m_First;
    uint32 index = 0;

    while ((mixer != nullptr) && (index < space)) {
        index += mixer->mix(outputs + index, space - index, status_reg);
        mixer = mixer->m_Next;
    }

    return index;
}

/*
 * set_trims() has no effect except for the SimpleMixer implementation for which set_trim()
 * always returns the value one.
 * The only other existing implementation is MultirotorMixer, which ignores the trim value
 * and returns _rotor_count.
 */
uint32
MixerGroup::set_trims(int16 *values, uint32 n)
{
    Mixer   *mixer = m_First;
    uint32 index = 0;

    while ((mixer != nullptr) && (index < n)) {
        /* convert from integer to float */
        float offset = (float)values[index] / 10000;

        /* to be safe, clamp offset to range of [-100, 100] usec */
        if (offset < -0.2f) { offset = -0.2f; }

        if (offset >  0.2f) { offset =  0.2f; }

        index += mixer->set_trim(offset);
        mixer = mixer->m_Next;
    }

    return index;
}

void
MixerGroup::set_thrust_factor(float val)
{
    Mixer   *mixer = m_First;

    while (mixer != nullptr) {
        mixer->set_thrust_factor(val);
        mixer = mixer->m_Next;
    }

}

uint16
MixerGroup::get_saturation_status()
{
    Mixer   *mixer = m_First;
    uint16  sat = 0;

    while (mixer != nullptr) {
        sat |= mixer->get_saturation_status();
        mixer = mixer->m_Next;
    }

    return sat;
}

uint32
MixerGroup::count()
{
    Mixer   *mixer = m_First;
    uint32 index = 0;

    while (mixer != nullptr) {
        mixer = mixer->m_Next;
        index++;
    }

    return index;
}

void
MixerGroup::groups_required(uint32 &groups)
{
    Mixer   *mixer = m_First;

    while (mixer != nullptr) {
        mixer->groups_required(groups);
        mixer = mixer->m_Next;
    }
}

void MixerGroup::set_max_delta_out_once(float delta_out_max)
{
    Mixer   *mixer = m_First;

    while (mixer != nullptr) {
        mixer->set_max_delta_out_once(delta_out_max);
        mixer = mixer->m_Next;
    }
}
