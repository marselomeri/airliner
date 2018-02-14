#include <math/Matrix6F6.hpp>
#include <math.h>

using namespace math;

Matrix6F6::Matrix6F6(Vector6F m0, Vector6F m1, Vector6F m2, Vector6F m3,
                       Vector6F m4, Vector6F m5) :
	data{m0, m1, m2, m3, m4, m5},
	nan{NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix6F6::Matrix6F6() :
	data{
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


Matrix6F6::~Matrix6F6()
{
};


void Matrix6F6::Zero(void)
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			data[i][j] = 0.0f;
		}
	}
}


Vector6F& Matrix6F6::operator [] (uint32 i)
{
	if(i >= SIZE)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


Vector6F Matrix6F6::operator [] (uint32 i) const
{
	if(i >= SIZE)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};





