#ifndef STATS1F_H
#define STATS1F_H

#include "cfe.h"
#include "math/Vector1F.hpp"

class Stats1F
{
public:
	Stats1F();
	~Stats1F();
	void update(math::Vector1F u);
    void reset()
	{
		m_Sum.Zero();
		m_SumSq.Zero();
		m_Count = 0;
	}

	size_t getCount() { return m_Count; }
	math::Vector1F getMean() { return m_Sum / m_Count; }
	math::Vector1F getVar()
	{
		return (m_SumSq - m_Sum.EMult(m_Sum) / m_Count) / m_Count;
	}
	math::Vector1F getStdDev()
	{
		return getVar().pow(0.5);
	}
private:
	math::Vector1F m_Sum;
	math::Vector1F m_SumSq;
	size_t m_Count;
};

#endif
