#ifndef LOWPASSVECTOR10F_H
#define LOWPASSVECTOR10F_H

#include "cfe.h"
#include "math.h"
#include "Vector10F.hpp"
#include "Matrix10F10.hpp"

class LowPassVector10F
{
public:
	LowPassVector10F();
	~LowPassVector10F();
	math::Vector10F Update(math::Vector10F input, float dt, float cutoff);
    float operator [] (uint32 i) const;

private:
	bool m_Initialized;
	math::Vector10F m_State;
};

#endif
