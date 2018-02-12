#include <math/Matrix1F10.hpp>
#include <math.h>

using namespace math;

Matrix1F10::Matrix1F10(Vector10F m0) :
	data{m0},
	nan{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix1F10::Matrix1F10() :
    data{
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
    },
    nan{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}
{
};


Matrix1F10::~Matrix1F10()
{
};


Vector10F& Matrix1F10::operator [] (uint32 i)
{
    if(i >= 10)
    {
        return nan;
    }
    else
    {
        return data[i];
    }
};


Vector10F Matrix1F10::operator [] (uint32 i) const
{
    if(i >= 10)
    {
        return nan;
    }
    else
    {
        return data[i];
    }
};
