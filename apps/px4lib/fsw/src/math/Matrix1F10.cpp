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


void Matrix1F10::Zero(void)
{
    int i = 0;

    for(i = 0; i < SIZE; i++)
    {
        data[0][i] = 0.0f;
    }
};

// overload * operator to provide a matrix product
Matrix1F10 Matrix1F10::operator*(const Matrix10F10 &matIn)
{
    Matrix1F10 matOut;
    int i, j, k = 0;
    /* Rows in matrix 1 */
    int rows1 = 1;
    /* Columns in matrix 1 */
    int cols1 = 10;
    /* Columns in matrix 2 */
    int cols2 = 10;

    for(i = 0; i < rows1; i++)
    {
        for(j = 0; j < cols2; j++)
        {
            for(k = 0; k < cols1; k++)
            {
                matOut[i][j] += data[i][k] * matIn[k][j];
            }
        }
    }

    return matOut;
};
