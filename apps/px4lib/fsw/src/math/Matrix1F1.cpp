#include <math/Matrix1F1.hpp>
#include <math.h>

using namespace math;

Matrix1F1::Matrix1F1(Vector1F m0) :
	data{m0[0]},
	nan{NAN}
{
};


Matrix1F1::Matrix1F1() :
    data{0.0},
    nan{NAN}
{
};


Matrix1F1::~Matrix1F1()
{
};


Vector1F& Matrix1F1::operator [] (uint32 i)
{
    if(i >= 1)
    {
        return nan[0];
    }
    else
    {
        return data[0];
    }
};


Vector1F Matrix1F1::operator [] (uint32 i) const
{
    if(i >= 1)
    {
        return nan[0];
    }
    else
    {
        return data[0];
    }
};


void Matrix1F1::Zero()
{
    data[0] = 0.0f;
};

