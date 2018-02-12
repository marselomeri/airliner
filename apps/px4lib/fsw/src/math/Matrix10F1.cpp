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


Matrix1F10 Matrix10F1::Transpose(void)
{
    Matrix1F10 matOut;
    matOut[0][0] = data[0][0];
    matOut[0][1] = data[1][0];
    matOut[0][2] = data[2][0];
    matOut[0][3] = data[3][0];
    matOut[0][4] = data[4][0];
    matOut[0][5] = data[5][0];
    matOut[0][6] = data[6][0];
    matOut[0][7] = data[7][0];
    matOut[0][8] = data[8][0];
    matOut[0][9] = data[9][0];

    return matOut;
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
