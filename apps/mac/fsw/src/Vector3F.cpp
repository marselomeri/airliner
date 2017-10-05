#include "Vector3F.hpp"
#include <math.h>

using namespace math;

Vector3F::Vector3F(float X, float Y, float Z) :
    data{X,Y,Z},
	nan(FP_NAN)
{
};


Vector3F::Vector3F()
{
};


Vector3F::~Vector3F()
{
};


float& Vector3F::operator [] (uint32 i)
{
	if(i < SIZE)
	{
		return data[i];
	}

	return nan;
};


float Vector3F::operator [] (uint32 i) const
{
	if(i < SIZE)
	{
		return data[i];
	}

	return nan;
};


float Vector3F::length() const
{
    return sqrtf(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}

void Vector3F::zero()
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
}

// overload + operator to provide a vector addition
Vector3F Vector3F::operator+(const Vector3F &vecIn)
{
    Vector3F vecOut;
    vecOut[0] = data[0] + vecIn[0];
    vecOut[1] = data[1] + vecIn[1];
    vecOut[2] = data[2] + vecIn[2];
    return vecOut;
}

// overload - operator to provide a vector subtraction
Vector3F Vector3F::operator-(const Vector3F &vecIn)
{
    Vector3F vecOut;
    vecOut[0] = data[0] - vecIn[0];
    vecOut[1] = data[1] - vecIn[1];
    vecOut[2] = data[2] - vecIn[2];
    return vecOut;
}

// overload % operator to provide a vector cross product
Vector3F Vector3F::operator%(const Vector3F &vecIn)
{
    Vector3F vecOut;
    vecOut[0] = data[1]*data[2] - data[2]*vecIn[1];
    vecOut[1] = data[2]*data[0] - data[0]*vecIn[2];
    vecOut[2] = data[0]*data[1] - data[1]*vecIn[0];
    return vecOut;
}

// overload * operator to provide a vector scaler product
Vector3F Vector3F::operator*(const float scalar)
{
    Vector3F vecOut;
    vecOut[0] = data[0] * scalar;
    vecOut[1] = data[1] * scalar;
    vecOut[2] = data[2] * scalar;
    return vecOut;
}

// overload / operator to provide a vector scalar division
Vector3F Vector3F::operator/(const float scalar)
{
    Vector3F vecOut;
    vecOut[0] = data[0] / scalar;
    vecOut[1] = data[1] / scalar;
    vecOut[2] = data[2] / scalar;
    return vecOut;
}

// overload * operator to provide a vector scaler product
float Vector3F::operator*(const Vector3F &vecIn)
{
	float res = 0.0f;

	res = data[0] * vecIn[0];
	res += data[1] * vecIn[1];
	res += data[2] * vecIn[2];

	return res;
}


Vector3F Vector3F::operator-() const
{
	Vector3F res;

	res[0] = -data[0];
	res[1] = -data[1];
	res[2] = -data[2];

    return res;
}
