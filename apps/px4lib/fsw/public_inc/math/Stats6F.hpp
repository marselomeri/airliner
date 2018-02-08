#ifndef STATS6F_H
#define STATS6F_H

#include "cfe.h"
#include "math/Vector6F.hpp"

class Stats6F
{
public:
	Stats6F();
	~Stats6F();
	void update(math::Vector6F u);
    void reset()
	{
		m_Sum.Zero();
		m_SumSq.Zero();
		m_Count = 0;
	}

	size_t getCount() { return m_Count; }
	math::Vector6F getMean() { return m_Sum / m_Count; }
	math::Vector6F getVar()
	{
		return (m_SumSq - m_Sum.EMult(m_Sum) / m_Count) / m_Count;
	}
	math::Vector6F getStdDev()
	{
		return getVar().pow(0.5);
	}
private:
	math::Vector6F m_Sum;
	math::Vector6F m_SumSq;
	size_t m_Count;
};

#endif
