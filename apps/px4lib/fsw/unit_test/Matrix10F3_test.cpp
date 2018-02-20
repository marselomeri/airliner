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

#include "Matrix10F3_test.hpp"
#include <math/Matrix10F3.hpp>


#include "utassert.h"
#include <float.h>


void Test_Matrix10F3_Constructor(void)
{
    math::Matrix10F3 matrix(
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

    /* Verify results */
    UtAssert_True(matrix[0][0] == 1.0f, "matrix[0][0] == 1.0f");
    UtAssert_True(matrix[1][0] == 1.0f, "matrix[1][0] == 1.0f");
    UtAssert_True(matrix[2][0] == 1.0f, "matrix[2][0] == 1.0f");
    UtAssert_True(matrix[3][0] == 1.0f, "matrix[3][0] == 1.0f");
    UtAssert_True(matrix[4][0] == 1.0f, "matrix[4][0] == 1.0f");
    UtAssert_True(matrix[5][0] == 1.0f, "matrix[5][0] == 1.0f");
    UtAssert_True(matrix[6][0] == 1.0f, "matrix[6][0] == 1.0f");
    UtAssert_True(matrix[7][0] == 1.0f, "matrix[7][0] == 1.0f");
    UtAssert_True(matrix[8][0] == 1.0f, "matrix[8][0] == 1.0f");
    UtAssert_True(matrix[9][0] == 1.0f, "matrix[9][0] == 1.0f");

    UtAssert_True(matrix[0][1] == 2.0f, "matrix[0][1] == 2.0f");
    UtAssert_True(matrix[1][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[2][1] == 2.0f, "matrix[2][1] == 2.0f");
    UtAssert_True(matrix[3][1] == 2.0f, "matrix[3][1] == 2.0f");
    UtAssert_True(matrix[4][1] == 2.0f, "matrix[4][1] == 2.0f");
    UtAssert_True(matrix[5][1] == 2.0f, "matrix[5][1] == 2.0f");
    UtAssert_True(matrix[6][1] == 2.0f, "matrix[6][1] == 2.0f");
    UtAssert_True(matrix[7][1] == 2.0f, "matrix[7][1] == 2.0f");
    UtAssert_True(matrix[8][1] == 2.0f, "matrix[8][1] == 2.0f");
    UtAssert_True(matrix[9][1] == 2.0f, "matrix[9][1] == 2.0f");

    UtAssert_True(matrix[0][2] == 3.0f, "matrix[0][2] == 3.0f");
    UtAssert_True(matrix[1][2] == 3.0f, "matrix[1][2] == 3.0f");
    UtAssert_True(matrix[2][2] == 3.0f, "matrix[2][2] == 3.0f");
    UtAssert_True(matrix[3][2] == 3.0f, "matrix[3][2] == 3.0f");
    UtAssert_True(matrix[4][2] == 3.0f, "matrix[4][2] == 3.0f");
    UtAssert_True(matrix[5][2] == 3.0f, "matrix[5][2] == 3.0f");
    UtAssert_True(matrix[6][2] == 3.0f, "matrix[6][2] == 3.0f");
    UtAssert_True(matrix[7][2] == 3.0f, "matrix[7][2] == 3.0f");
    UtAssert_True(matrix[8][2] == 3.0f, "matrix[8][2] == 3.0f");
    UtAssert_True(matrix[9][2] == 3.0f, "matrix[9][2] == 3.0f");
}


void Test_Matrix10F3_OutOfBounds(void)
{
    math::Matrix10F3 matrix(
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

    /* Verify results */
    UtAssert_True(!isfinite(matrix[0][4]), "matrix[0][6] == NAN");
    UtAssert_True(!isfinite(matrix[10][0]), "matrix[10][0] == NAN");
}


void Test_Matrix10F3_Identity(void)
{
    math::Matrix10F3 matrix(
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    );

    /* Verify results */
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(i == j)
            {
                UtAssert_True(1.0 == matrix[i][j], "matrix diagnol == 1.0");
            }
            else
            {
                UtAssert_True(0.0 == matrix[i][j], "matrix non diag == 0.0");
            }
        }
    }
}


void Test_Matrix10F3_Zero(void)
{
    math::Matrix10F3 matrix(
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

    matrix.Zero();

    /* Verify results */
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            UtAssert_True(0.0 == matrix[i][j], "matrix idx == 0.0");
        }
    }
}


void Test_Matrix10F3_Mult_3F(void)
{
    math::Matrix10F3 matrixA(
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

    math::Vector3F vectorB(1.0f, 2.0f, 3.0f);

    math::Vector10F result;
    result.Zero();

    result = matrixA * vectorB;

    UtAssert_True(result[0] == 14.0, "result[0] == 14.0");
    UtAssert_True(result[1] == 14.0, "result[1] == 14.0");
    UtAssert_True(result[2] == 14.0, "result[2] == 14.0");
    UtAssert_True(result[3] == 14.0, "result[3] == 14.0");
    UtAssert_True(result[4] == 14.0, "result[4] == 14.0");
    UtAssert_True(result[5] == 14.0, "result[5] == 14.0");
    UtAssert_True(result[6] == 14.0, "result[6] == 14.0");
    UtAssert_True(result[7] == 14.0, "result[7] == 14.0");
    UtAssert_True(result[8] == 14.0, "result[8] == 14.0");
    UtAssert_True(result[9] == 14.0, "result[9] == 14.0");
}


void Test_Matrix10F3_Mult_3F10(void)
{
    math::Matrix10F3 matrixA(
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

    math::Matrix3F10 matrixB(
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
        {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = matrixA * matrixB;

    /* Verify results */
    for(int i = 0; i < 10; ++i)
    {
        UtAssert_True(result[i][0] == 6.0f,  "result[i][0] == 6.0f");
        UtAssert_True(result[i][1] == 12.0f, "result[i][1] == 12.0f");
        UtAssert_True(result[i][2] == 18.0f, "result[i][2] == 18.0f");
        UtAssert_True(result[i][3] == 24.0f, "result[i][3] == 24.0f");
        UtAssert_True(result[i][4] == 30.0f, "result[i][4] == 30.0f");
        UtAssert_True(result[i][5] == 36.0f, "result[i][5] == 36.0f");
        UtAssert_True(result[i][6] == 42.0f, "result[i][6] == 42.0f");
        UtAssert_True(result[i][7] == 48.0f, "result[i][7] == 48.0f");
        UtAssert_True(result[i][8] == 54.0f, "result[i][8] == 54.0f");
        UtAssert_True(result[i][9] == 60.0f, "result[i][9] == 60.0f");
    }
}


void Test_Matrix10F3_Mult_3F3(void)
{
    math::Matrix10F3 matrixA(
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

    math::Matrix3F3 matrixB(
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f},
        {1.0f, 2.0f, 3.0f}
    );

    math::Matrix10F3 result;
    result.Zero();

    result = matrixA * matrixB;

    /* Verify results */
    for(int i = 0; i < 10; ++i)
    {
        UtAssert_True(result[i][0] == 6.0f,  "result[i][0] == 6.0f");
        UtAssert_True(result[i][1] == 12.0f, "result[i][1] == 12.0f");
        UtAssert_True(result[i][2] == 18.0f, "result[i][2] == 18.0f");
    }
}


