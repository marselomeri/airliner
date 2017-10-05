#include "Matrix4F4.hpp"
#include <math.h>

using namespace math;

Matrix4F4::Matrix4F4(Vector4F m0, Vector4F m1, Vector4F m2, Vector4F m3) :
	data{m0, m1, m2, m3}
{
};


Matrix4F4::Matrix4F4() :
	data{
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0}
	}
{
};


Matrix4F4::~Matrix4F4()
{
};


Vector4F& Matrix4F4::operator [] (uint32 i)
{
	return data[i];
};

