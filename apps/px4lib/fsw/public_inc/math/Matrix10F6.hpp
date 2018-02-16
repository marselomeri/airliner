#ifndef MATRIX10F6_HPP
#define MATRIX10F6_HPP

#include "cfe.h"
#include "Vector6F.hpp"
#include "Matrix6F6.hpp"
#include "Matrix6F10.hpp"
#include "Matrix10F10.hpp"
#include "Vector10F.hpp"


namespace math
{
    
class Matrix6F10;

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
    Matrix10F6 operator*(const Matrix6F6 &matIn);
    Vector10F operator*(const Vector6F &vecIn);
    Matrix10F10 operator*(const Matrix6F10 &matIn);
	void Zero(void);

protected:

};

}

#endif
