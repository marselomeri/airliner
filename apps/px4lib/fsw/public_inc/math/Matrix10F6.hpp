#ifndef MATRIX10F6_HPP
#define MATRIX10F6_HPP

#include "cfe.h"
#include "Vector6F.hpp"


namespace math
{

class Matrix10F6
{
public:

private:
	static const int ROWS = 10;
	static const int COLS = 6;
	Vector6F data[ROWS];
	Vector6F nan;

public:
	Matrix10F6();
	Matrix10F6(Vector6F m0, Vector6F m1, Vector6F m2, Vector6F m3, Vector6F m4, Vector6F m5, Vector6F m6, Vector6F m7, Vector6F m8, Vector6F m9);
	~Matrix10F6();
	Vector6F& operator [] (uint32 i);
	Vector6F operator [] (uint32 i) const;
	void Zero(void);

protected:

};

}

#endif
