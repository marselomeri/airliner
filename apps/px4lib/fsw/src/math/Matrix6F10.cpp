#include <math/Matrix6F10.hpp>
#include <math.h>

using namespace math;

Matrix6F10::Matrix6F10(Vector6F m0, Vector6F m1, Vector6F m2, Vector6F m3,
                       Vector6F m4, Vector6F m5, Vector6F m6, Vector6F m7,
                       Vector6F m8, Vector6F m9) :
	data{m0, m1, m2, m3, m4, m5, m6, m7, m8, m9},
	nan{NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix6F10::Matrix6F10() :
	data{
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	},
	nan{NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix6F10::~Matrix6F10()
{
};


void Matrix6F10::Zero(void)
{
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			data[i][j] = 0.0f;
		}
	}
}


Vector6F& Matrix6F10::operator [] (uint32 i)
{
	if(i >= 6)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


Vector6F Matrix6F10::operator [] (uint32 i) const
{
	if(i >= 6)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};





