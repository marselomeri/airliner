/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#include "Matrix3F10_test.hpp"
#include <math/Matrix3F10.hpp>


#include "utassert.h"
#include <float.h>

int rows = 3;
int cols = 10;


void Test_Matrix3F10_Constructor(void)
{
    math::Matrix3F10 matrix(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    /* Verify results */
    UtAssert_True(matrix[0][0] == 1.0f, "matrix[0][0] == 1.0f");
    UtAssert_True(matrix[0][1] == 2.0f, "matrix[1][0] == 2.0f");
    UtAssert_True(matrix[0][2] == 3.0f, "matrix[2][0] == 3.0f");
    UtAssert_True(matrix[0][3] == 4.0f, "matrix[3][0] == 4.0f");
    UtAssert_True(matrix[0][4] == 5.0f, "matrix[4][0] == 5.0f");
    UtAssert_True(matrix[0][5] == 6.0f, "matrix[5][0] == 6.0f");
    UtAssert_True(matrix[0][6] == 7.0f, "matrix[6][0] == 7.0f");
    UtAssert_True(matrix[0][7] == 8.0f, "matrix[7][0] == 8.0f");
    UtAssert_True(matrix[0][8] == 9.0f, "matrix[8][0] == 9.0f");
    UtAssert_True(matrix[0][9] == 10.0f, "matrix[9][0] == 10.0f");
    
    UtAssert_True(matrix[1][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[1][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[1][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[1][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[1][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[1][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[1][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[1][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[1][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[1][9] == 10.0f, "matrix[9][1] == 10.0f");
    
    UtAssert_True(matrix[2][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[2][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[2][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[2][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[2][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[2][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[2][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[2][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[2][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[2][9] == 10.0f, "matrix[9][1] == 10.0f");
}


void Test_Matrix3F10_OutOfBounds(void)
{
    math::Matrix3F10 matrix(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );


    /* Verify results */
    UtAssert_True(!isfinite(matrix[0][10]), "matrix[0][10] == NAN");
    UtAssert_True(!isfinite(matrix[4][0]), "matrix[4][0] == NAN");
}

void Test_Matrix3F10_Transpose(void)
{
    math::Matrix3F10 matrix(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F3 matrixT(
        {1.0f, 1.0f, 1.0f},
        {2.0f, 2.0f, 2.0f},
        {3.0f, 3.0f, 3.0f},
        {4.0f, 4.0f, 4.0f},
        {5.0f, 5.0f, 5.0f},
        {6.0f, 6.0f, 6.0f},
        {7.0f, 7.0f, 7.0f},
        {8.0f, 8.0f, 8.0f},
        {9.0f, 9.0f, 9.0f},
        {10.0f, 10.0f, 10.0f}
    );

    math::Matrix10F3 result;
    result.Zero();

    result = matrix.Transpose();

    /* Verify results */
    for(int i = 0; i < cols; ++i)
    {
        for(int j = 0; j < rows; ++j)
        {
            UtAssert_True(result[i][j] == matrixT[i][j], "matrix transpose correct");
        }
    }
}


void Test_Matrix3F10_Zero(void)
{
    math::Matrix3F10 matrix(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    matrix.Zero();

    /* Verify results */
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            UtAssert_True(0.0 == matrix[i][j], "matrix idx == 0.0");
        }
    }
}

void Test_Matrix3F10_Mult_10F(void)
{
    math::Matrix3F10 matrixA(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Vector10F vectorB(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);

    math::Vector3F result;
    result.Zero();

    result = matrixA * vectorB;

    UtAssert_True(result[0] == 385.0, "result[0] == 385.0");
    UtAssert_True(result[1] == 385.0, "result[1] == 385.0");
    UtAssert_True(result[2] == 385.0, "result[2] == 385.0");
}


void Test_Matrix3F10_Mult_10F3(void)
{
    math::Matrix3F10 matrixA(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F3 matrixB(
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f}
    );

    math::Matrix3F3 result;
    result.Zero();

    result = matrixA * matrixB;

    /* Verify results */
    for(int i = 0; i < rows; ++i)
    {
        UtAssert_True(result[i][0] == 55.0f,  "result[i][0] == 55.0f");
        UtAssert_True(result[i][1] == 110.0f, "result[i][1] == 110.0f");
        UtAssert_True(result[i][2] == 165.0f, "result[i][2] == 165.0f");
    }
}

