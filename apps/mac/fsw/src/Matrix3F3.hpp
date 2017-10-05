#ifndef MATRIX3F3_HPP
#define MATRIX3F3_HPP

#include "cfe.h"
#include "Matrix3F3.hpp"
#include "Vector3F.hpp"

namespace math
{

class Matrix3F3
{
private:
	static const int SIZE = 3;
	Vector3F data[SIZE];

public:
	Matrix3F3(Vector3F m0, Vector3F m1, Vector3F m2);
	~Matrix3F3();
	Vector3F& operator [] (uint32 i);
	Vector3F operator [] (uint32 i) const;
	Matrix3F3();
	Matrix3F3 Transpose(void);
	static Matrix3F3 Identity(void);
	Vector3F operator*(const Vector3F &vecIn);
	Matrix3F3 operator*(const Matrix3F3 &matIn);
	Matrix3F3 operator*(const float &scalar);
	void Zero(void);
    Matrix3F3 operator+(const Matrix3F3 &matIn) const;

protected:

};

}

#endif
