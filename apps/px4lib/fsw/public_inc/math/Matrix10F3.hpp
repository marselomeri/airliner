#ifndef MATRIX10F3_HPP
#define MATRIX10F3_HPP

#include "cfe.h"
#include "Vector3F.hpp"
#include "Vector10F.hpp"
#include "Matrix3F3.hpp"
#include "Matrix3F10.hpp"
#include "Matrix10F10.hpp"

#define M_DEG_TO_RAD_F		(0.01745329251994329576f)

namespace math
{

/* Forward declares */
class Matrix3F10;
class Matrix10F10;
class Vector10F;

class Matrix10F3
{
public:

private:
	static const int ROWS = 10;
	static const int COLS = 3;
	Vector3F data[ROWS];
	Vector3F nan;

public:
	Matrix10F3(Vector3F m0, Vector3F m1, Vector3F m2, Vector3F m3, Vector3F m4, Vector3F m5, Vector3F m6, Vector3F m7, Vector3F m8, Vector3F m9);
	~Matrix10F3();
	Vector3F& operator [] (uint32 i);
	Vector3F operator [] (uint32 i) const;
	Matrix10F3();
	Matrix3F10 Transpose(void);
	static Matrix10F3 Identity(void);
	Vector10F operator*(const Vector3F &vecIn);
	Matrix10F3 operator*(const Matrix10F3 &matIn);
	Matrix10F3 operator*(const Matrix3F3 &matIn);
    Matrix10F10 operator*(const Matrix3F10 &matIn);
	Matrix10F3 operator*(const float &scalar);
	void Zero(void);
    Matrix10F3 operator+(const Matrix10F3 &matIn) const;

protected:

};

}

#endif
