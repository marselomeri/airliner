#include <math/Matrix10F1.hpp>
#include <math.h>

using namespace math;

Matrix10F1::Matrix10F1(Vector10F m0) :
	data{m0[0], m0[1], m0[2], m0[3], m0[4], m0[5], m0[6], m0[7], m0[8], m0[9]},
	nan{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix10F1::Matrix10F1() :
    data{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    nan{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix10F1::~Matrix10F1()
{
};


Vector1F& Matrix10F1::operator [] (uint32 i)
{
    if(i >= 10)
    {
        return nan[0];
    }
    else
    {
        return data[i];
    }
};


Vector1F Matrix10F1::operator [] (uint32 i) const
{
    if(i >= 10)
    {
        return nan[0];
    }
    else
    {
        return data[i];
    }
};
