#include "math/Matrix10F10.hpp"
#include <math.h>

using namespace math;

Matrix10F10::Matrix10F10(Vector10F m0, Vector10F m1, Vector10F m2, Vector10F m3, Vector10F m4, Vector10F m5, Vector10F m6, Vector10F m7, Vector10F m8, Vector10F m9) :
	data{m0, m1, m2, m3, m4, m5, m6, m7, m8, m9},
	nan{NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN,NAN}
{
};


Matrix10F10::Matrix10F10() :
	data{
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
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


Matrix10F10::~Matrix10F10()
{
};


Vector10F& Matrix10F10::operator [] (uint32 i)
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


Vector10F Matrix10F10::operator [] (uint32 i) const
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


Matrix10F10 Matrix10F10::Transpose(void)
{
	Matrix10F10 res;

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			res[i][j] = data[j][i];
		}
	}

	return res;
}


Matrix10F10 Matrix10F10::Identity() {
    Matrix10F10 matOut(
    		{1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0},
    		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0f});

    return matOut;
}


void Matrix10F10::Zero(void)
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			data[i][j] = 0.0f;
		}
	}
}


// overload * operator to provide a matrix product
Matrix10F10 Matrix10F10::operator*(const Matrix10F10 &matIn)
{
    Matrix10F10 matOut;
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < SIZE; i++)
    {
    	for(int j = 0; j < SIZE; j++)
		{

    		for(int k = 0; k < SIZE; k++)
			{
    			value += data[i][j] * matIn[j][k];
			}

    		matOut[i][j] = value;
    		value = 0.0f;
		}
    }

    return matOut;
}


// overload * operator to provide a matrix vector product
Vector10F Matrix10F10::operator*(const Vector10F &vecIn)
{
    Vector10F vecOut;
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < SIZE; i++)
    {
    	for(int j = 0; j < SIZE; j++)
		{
    		value += data[i][j]*vecIn[j];

    		vecOut[i] = value;
    		value = 0.0f;
		}
    }

    return vecOut;
}

Vector10F Matrix10F10::operator+(const Vector10F &vecIn)
{
    Vector10F vecOut;
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < SIZE; i++)
    {
    	for(int j = 0; j < SIZE; j++)
		{
    		value += data[i][j]+vecIn[j];

    		vecOut[i] = value;
    		value = 0.0f;
		}
    }

    return vecOut;
}

void Matrix10F10::operator+=(const Matrix10F10 &mat)
{
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < SIZE; i++)
    {
    	for(int j = 0; j < SIZE; j++)
		{
    		 data[i][j] += mat[i][j];
		}
    }
}

Matrix10F1 Matrix10F10::operator*(const Matrix10F1 &matIn)
{
    Matrix10F1 matOut;
    int i, j, k = 0;
    /* Rows in matrix 1 */
    int rows1 = 10;
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
                matOut[i][j] += data[i][k] * matIn[k][j];
            }
        }
    }

    return matOut;
}


Matrix10F10 Matrix10F10::operator*(const float &scalar)
{
    Matrix10F10 matOut;

    // TODO: verify correct
    for(int i = 0; i < SIZE; i++)
    {
    	for(int j = 0; j < SIZE; j++)
		{
    		matOut[j][i] = scalar*data[j][i];
		}
    }

    return matOut;
}


Matrix10F10 Matrix10F10::operator+(const Matrix10F10 &matIn) const
{
    Matrix10F10 matOut;

    // TODO: verify correct
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			matOut[j][i] = data[j][i] + matIn[j][i];
		}
	}

    return matOut;
}

Matrix10F10 Matrix10F10::operator-(const Matrix10F10 &matIn) const
{
    Matrix10F10 matOut;

    // TODO: verify correct
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			matOut[j][i] = data[j][i] - matIn[j][i];
		}
	}

    return matOut;
}

void Matrix10F10::Print()
{
    for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			OS_printf("%f, ", data[i][j]);
		}
		OS_printf("\n");
	}
}
