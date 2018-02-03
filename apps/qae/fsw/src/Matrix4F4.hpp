#ifndef MATRIX4F4_HPP
#define MATRIX4F4_HPP

#include "cfe.h"
#include "Matrix4F4.hpp"
#include "Vector4F.hpp"

namespace math
{

class Matrix4F4
{
private:

protected:
	static const int SIZE = 4;
	Vector4F data[SIZE];
	Vector4F nan;

public:
	Matrix4F4(Vector4F m0, Vector4F m1, Vector4F m2, Vector4F m3);
	~Matrix4F4();
	Vector4F& operator [] (uint32 i);
	Vector4F operator [] (uint32 i) const;
    Vector4F operator*(const Vector4F &v) const;
	Matrix4F4();

};

}

#endif
