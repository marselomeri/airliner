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


Matrix6F6 Matrix6F6::operator+(const Matrix6F6 &matIn) const
{
    Matrix6F6 matOut;

    matOut[0][0] = data[0][0] + matIn[0][0];
    matOut[1][0] = data[1][0] + matIn[1][0];
    matOut[2][0] = data[2][0] + matIn[2][0];
    matOut[3][0] = data[3][0] + matIn[3][0];
    matOut[4][0] = data[4][0] + matIn[4][0];
    matOut[5][0] = data[5][0] + matIn[5][0];

    matOut[0][1] = data[0][1] + matIn[0][1];
    matOut[1][1] = data[1][1] + matIn[1][1];
    matOut[2][1] = data[2][1] + matIn[2][1];
    matOut[3][1] = data[3][1] + matIn[3][1];
    matOut[4][1] = data[4][1] + matIn[4][1];
    matOut[5][1] = data[5][1] + matIn[5][1];

    matOut[0][2] = data[0][2] + matIn[0][2];
    matOut[1][2] = data[1][2] + matIn[1][2];
    matOut[2][2] = data[2][2] + matIn[2][2];
    matOut[3][2] = data[3][2] + matIn[3][2];
    matOut[4][2] = data[4][2] + matIn[4][2];
    matOut[5][2] = data[5][2] + matIn[5][2];

    matOut[0][3] = data[0][3] + matIn[0][3];
    matOut[1][3] = data[1][3] + matIn[1][3];
    matOut[2][3] = data[2][3] + matIn[2][3];
    matOut[3][3] = data[3][3] + matIn[3][3];
    matOut[4][3] = data[4][3] + matIn[4][3];
    matOut[5][3] = data[5][3] + matIn[5][3];

    matOut[0][4] = data[0][4] + matIn[0][4];
    matOut[1][4] = data[1][4] + matIn[1][4];
    matOut[2][4] = data[2][4] + matIn[2][4];
    matOut[3][4] = data[3][4] + matIn[3][4];
    matOut[4][4] = data[4][4] + matIn[4][4];
    matOut[5][4] = data[5][4] + matIn[5][4];

    matOut[0][5] = data[0][5] + matIn[0][5];
    matOut[1][5] = data[1][5] + matIn[1][5];
    matOut[2][5] = data[2][5] + matIn[2][5];
    matOut[3][5] = data[3][5] + matIn[3][5];
    matOut[4][5] = data[4][5] + matIn[4][5];
    matOut[5][5] = data[5][5] + matIn[5][5];

    return matOut;
}


//Matrix6F6 Matrix6F6::Inverse(void)
//{
    //Matrix6F6 matOut;
    
    
    
//}


