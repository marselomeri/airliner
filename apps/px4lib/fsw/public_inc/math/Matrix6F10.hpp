#ifndef MATRIX6F10_HPP
#define MATRIX6F10_HPP

#include "cfe.h"
#include "Vector6F.hpp"
#include "Vector10F.hpp"
#include "Matrix10F6.hpp"
#include "Matrix6F6.hpp"
#include "Matrix10F10.hpp"

namespace math
{

class Matrix10F6;
class Matrix10F10;

class Matrix6F10
{
private:
	static const int ROWS = 6;
	static const int COLS = 10;
	Vector10F data[ROWS];
	Vector10F nan;

public:
	Matrix6F10();
	Matrix6F10(Vector10F m0, Vector10F m1, Vector10F m2, Vector10F m3,
               Vector10F m4, Vector10F m5);
	~Matrix6F10();
	Vector10F& operator [] (uint32 i);
	Vector10F operator [] (uint32 i) const;
    Vector6F operator*(const Vector10F &vecIn);
    Matrix6F6 operator*(const Matrix10F6 &matIn);
    Matrix6F10 operator*(const Matrix10F10 &matIn);
    Matrix10F6 Transpose(void);
    void Zero(void);


protected:

};

}

#endif
