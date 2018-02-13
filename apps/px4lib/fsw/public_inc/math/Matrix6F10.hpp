#ifndef MATRIX6F10_HPP
#define MATRIX6F10_HPP

#include "cfe.h"
#include "Vector6F.hpp"

namespace math
{

class Matrix6F10
{
private:
	static const int SIZE = 10;
	Vector6F data[SIZE];
	Vector6F nan;

public:
	Matrix6F10(Vector6F m0, Vector6F m1, Vector6F m2, Vector6F m3,
               Vector6F m4, Vector6F m5, Vector6F m6, Vector6F m7,
               Vector6F m8, Vector6F m9);
	~Matrix6F10();
	Vector6F& operator [] (uint32 i);
	Vector6F operator [] (uint32 i) const;
    void Zero(void);
	Matrix6F10();

protected:

};

}

#endif
