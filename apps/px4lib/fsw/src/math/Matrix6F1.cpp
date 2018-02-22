#include <math/Matrix6F1.hpp>
#include <math.h>

using namespace math;


Matrix6F1::Matrix6F1(Vector6F m0) :
	data{m0[0], m0[1], m0[2], m0[3], m0[4], m0[5]},
	nan{NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix6F1::Matrix6F1() :
    data{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    nan{NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix6F1::~Matrix6F1()
{
};


Vector1F& Matrix6F1::operator [] (uint32 i)
{
    if(i >= 6)
    {
        return nan[0];
    }
    else
    {
        return data[i];
    }
};


Vector1F Matrix6F1::operator [] (uint32 i) const
{
    if(i >= 6)
    {
        return nan[0];
    }
    else
    {
        return data[i];
    }
};


void Matrix6F1::Zero(void)
{
    data[0][0] = 0.0f;
    data[1][0] = 0.0f;
    data[2][0] = 0.0f;
    data[3][0] = 0.0f;
    data[4][0] = 0.0f;
    data[5][0] = 0.0f;
}
