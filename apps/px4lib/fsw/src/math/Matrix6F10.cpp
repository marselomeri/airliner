#include <math/Matrix6F10.hpp>
#include <math.h>

using namespace math;

Matrix6F10::Matrix6F10(Vector10F m0, Vector10F m1, Vector10F m2, Vector10F m3,
                       Vector10F m4, Vector10F m5) :
	data{m0, m1, m2, m3, m4, m5},
	nan{NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix6F10::Matrix6F10() :
	data{
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	},
	nan{NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix6F10::~Matrix6F10()
{
};


void Matrix6F10::Zero(void)
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			data[i][j] = 0.0f;
		}
	}
}


Vector10F& Matrix6F10::operator [] (uint32 i)
{
	if(i >= ROWS)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


Vector10F Matrix6F10::operator [] (uint32 i) const
{
	if(i >= ROWS)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


// overload * operator to provide a matrix vector product
Vector6F Matrix6F10::operator*(const Vector10F &vecIn)
{
    Vector6F vecOut;
    int i, j, k = 0;
    /* Rows in matrix 1 */
    int rows1 = 6;
    /* Columns in matrix 1 */
    int cols1 = 10;
    /* Columns in matrix 2 */
    int cols2 = 1;

    for(i = 0; i < rows1; i++)
    {
        for(j = 0; j < cols2; j++)
        {
            for(k = 0; k < cols1; k++)
            {
                vecOut[i] += data[i][k] * vecIn[k];
            }
        }
    }

    return vecOut;
}



