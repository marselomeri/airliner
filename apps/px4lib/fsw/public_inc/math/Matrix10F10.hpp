#ifndef MATRIX10F10_HPP
#define MATRIX10F10_HPP

#include "cfe.h"
#include "Vector10F.hpp"
#include "Matrix10F1.hpp"
#include "Matrix10F3.hpp"
#include "Matrix10F6.hpp"

#define M_DEG_TO_RAD_F		(0.01745329251994329576f)

namespace math
{

/* Forward declare 10F1 */
class Matrix10F1;
class Matrix10F3;

class Matrix10F6;

class Matrix10F10
{
public:

private:
	static const int SIZE = 10;
	Vector10F data[SIZE];
	Vector10F nan;

public:
	Matrix10F10(Vector10F m0, Vector10F m1, Vector10F m2, Vector10F m3, Vector10F m4, Vector10F m5, Vector10F m6, Vector10F m7, Vector10F m8, Vector10F m9);
	~Matrix10F10();
	Vector10F& operator [] (uint32 i);
	Vector10F operator [] (uint32 i) const;
	Matrix10F10();
	Matrix10F10 Transpose(void);
	static Matrix10F10 Identity(void);
	Vector10F operator*(const Vector10F &vecIn);
    Matrix10F1 operator*(const Matrix10F1 &matIn);
    Matrix10F3 operator*(const Matrix10F3 &matIn);
    Matrix10F6 operator*(const Matrix10F6 &matIn);
	Matrix10F10 operator*(const Matrix10F10 &matIn);
	Matrix10F10 operator*(const float &scalar);
	//void operator+=(const Matrix10F10 &mat);
    //void operator-=(const Matrix10F10 &matIn);
	void Zero(void);
    Matrix10F10 operator+(const Matrix10F10 &matIn) const;
    Matrix10F10 operator-(const Matrix10F10 &matIn) const;
    void Print();



protected:

};

}

#endif
