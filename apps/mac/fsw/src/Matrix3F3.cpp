#include "Matrix3F3.hpp"
#include <math.h>

using namespace math;

Matrix3F3::Matrix3F3(Vector3F m0, Vector3F m1, Vector3F m2) :
	data{m0, m1, m2}
{
};


Matrix3F3::Matrix3F3() :
	data{
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0}
    }
{
};


Matrix3F3::~Matrix3F3()
{
};


Vector3F& Matrix3F3::operator [] (uint32 i)
{
	return data[i];
};


Vector3F Matrix3F3::operator [] (uint32 i) const
{
	return data[i];
};


Matrix3F3 Matrix3F3::Transpose(void)
{
	Matrix3F3 res;

	res[0][0] = data[0][0];
	res[0][1] = data[1][0];
	res[0][2] = data[2][0];
	res[1][0] = data[0][1];
	res[1][1] = data[1][1];
	res[1][2] = data[2][1];
	res[2][0] = data[0][2];
	res[2][1] = data[1][2];
	res[2][2] = data[2][2];

	return res;
}


Matrix3F3 Matrix3F3::Identity() {
    Matrix3F3 matOut(
    		{1.0f, 0.0f, 0.0f},
    		{0.0f, 1.0f, 0.0f},
    		{0.0f, 0.0f, 1.0f}
			);

    return matOut;
}


void Matrix3F3::Zero(void)
{
	data[0][0] = 0.0f;
	data[0][1] = 0.0f;
	data[0][2] = 0.0f;
	data[1][0] = 0.0f;
	data[1][1] = 0.0f;
	data[1][2] = 0.0f;
	data[2][0] = 0.0f;
	data[2][1] = 0.0f;
	data[2][2] = 0.0f;
}


// overload * operator to provide a matrix product
Matrix3F3 Matrix3F3::operator*(const Matrix3F3 &matIn)
{
    Matrix3F3 matOut;

    matOut[0][0] = data[0][0]*matIn[0][0] + data[0][1]*matIn[1][0] + data[0][2]*matIn[2][0];
    matOut[0][1] = data[0][0]*matIn[0][1] + data[0][1]*matIn[1][1] + data[0][2]*matIn[2][1];
    matOut[0][2] = data[0][0]*matIn[0][2] + data[0][1]*matIn[1][2] + data[0][2]*matIn[2][2];

    matOut[1][0] = data[1][0]*matIn[0][0] + data[1][1]*matIn[1][0] + data[1][2]*matIn[2][0];
    matOut[1][1] = data[1][0]*matIn[0][1] + data[1][1]*matIn[1][1] + data[1][2]*matIn[2][1];
    matOut[1][2] = data[1][0]*matIn[0][2] + data[1][1]*matIn[1][2] + data[1][2]*matIn[2][2];

    matOut[2][0] = data[2][0]*matIn[0][0] + data[2][1]*matIn[1][0] + data[2][2]*matIn[2][0];
    matOut[2][1] = data[2][0]*matIn[0][1] + data[2][1]*matIn[1][1] + data[2][2]*matIn[2][1];
    matOut[2][2] = data[2][0]*matIn[0][2] + data[2][1]*matIn[1][2] + data[2][2]*matIn[2][2];

    return matOut;
}


// overload * operator to provide a matrix vector product
Vector3F Matrix3F3::operator*(const Vector3F &vecIn)
{
    Vector3F vecOut;
    vecOut[0] = data[0][0]*vecIn[0] + data[0][1]*vecIn[1] + data[0][2]*vecIn[2];
    vecOut[1] = data[1][0]*vecIn[0] + data[1][1]*vecIn[1] + data[1][2]*vecIn[2];
    vecOut[2] = data[2][0]*vecIn[0] + data[2][1]*vecIn[1] + data[2][2]*vecIn[2];
    return vecOut;
}


Matrix3F3 Matrix3F3::operator*(const float &scalar)
{
    Matrix3F3 matOut;

    matOut[0][0] = scalar*data[0][0];
    matOut[1][0] = scalar*data[1][0];
    matOut[2][0] = scalar*data[2][0];

    matOut[0][1] = scalar*data[0][1];
    matOut[1][1] = scalar*data[1][1];
    matOut[2][1] = scalar*data[2][1];

    matOut[0][2] = scalar*data[0][2];
    matOut[1][2] = scalar*data[1][2];
    matOut[2][2] = scalar*data[2][2];

    return matOut;
}


Matrix3F3 Matrix3F3::operator+(const Matrix3F3 &matIn) const
{
    Matrix3F3 matOut;

    matOut[0][0] = data[0][0] + matIn[0][0];
    matOut[1][0] = data[1][0] + matIn[1][0];
    matOut[2][0] = data[2][0] + matIn[2][0];

    matOut[0][1] = data[0][1] + matIn[0][1];
    matOut[1][1] = data[1][1] + matIn[1][1];
    matOut[2][1] = data[2][1] + matIn[2][1];

    matOut[0][2] = data[0][2] + matIn[0][2];
    matOut[1][2] = data[1][2] + matIn[1][2];
    matOut[2][2] = data[2][2] + matIn[2][2];

    return matOut;
}
