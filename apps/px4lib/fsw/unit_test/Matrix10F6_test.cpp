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

#include "Matrix10F6_test.hpp"
#include <math/Matrix10F6.hpp>
#include <math/Matrix10F10.hpp>


#include "utassert.h"
#include <float.h>


void Test_Matrix10F6_Constructor(void)
{
    math::Matrix10F6 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
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

    UtAssert_True(matrix[0][3] == 4.0f, "matrix[0][3] == 4.0f");
    UtAssert_True(matrix[1][3] == 4.0f, "matrix[1][3] == 4.0f");
    UtAssert_True(matrix[2][3] == 4.0f, "matrix[2][3] == 4.0f");
    UtAssert_True(matrix[3][3] == 4.0f, "matrix[3][3] == 4.0f");
    UtAssert_True(matrix[4][3] == 4.0f, "matrix[4][3] == 4.0f");
    UtAssert_True(matrix[5][3] == 4.0f, "matrix[5][3] == 4.0f");
    UtAssert_True(matrix[6][3] == 4.0f, "matrix[6][3] == 4.0f");
    UtAssert_True(matrix[7][3] == 4.0f, "matrix[7][3] == 4.0f");
    UtAssert_True(matrix[8][3] == 4.0f, "matrix[8][3] == 4.0f");
    UtAssert_True(matrix[9][3] == 4.0f, "matrix[9][3] == 4.0f");

    UtAssert_True(matrix[0][4] == 5.0f, "matrix[0][4] == 5.0f");
    UtAssert_True(matrix[1][4] == 5.0f, "matrix[1][4] == 5.0f");
    UtAssert_True(matrix[2][4] == 5.0f, "matrix[2][4] == 5.0f");
    UtAssert_True(matrix[3][4] == 5.0f, "matrix[3][4] == 5.0f");
    UtAssert_True(matrix[4][4] == 5.0f, "matrix[4][4] == 5.0f");
    UtAssert_True(matrix[5][4] == 5.0f, "matrix[5][4] == 5.0f");
    UtAssert_True(matrix[6][4] == 5.0f, "matrix[6][4] == 5.0f");
    UtAssert_True(matrix[7][4] == 5.0f, "matrix[7][4] == 5.0f");
    UtAssert_True(matrix[8][4] == 5.0f, "matrix[8][4] == 5.0f");
    UtAssert_True(matrix[9][4] == 5.0f, "matrix[9][4] == 5.0f");

    UtAssert_True(matrix[0][5] == 6.0f, "matrix[0][5] == 6.0f");
    UtAssert_True(matrix[1][5] == 6.0f, "matrix[1][5] == 6.0f");
    UtAssert_True(matrix[2][5] == 6.0f, "matrix[2][5] == 6.0f");
    UtAssert_True(matrix[3][5] == 6.0f, "matrix[3][5] == 6.0f");
    UtAssert_True(matrix[4][5] == 6.0f, "matrix[4][5] == 6.0f");
    UtAssert_True(matrix[5][5] == 6.0f, "matrix[5][5] == 6.0f");
    UtAssert_True(matrix[6][5] == 6.0f, "matrix[6][5] == 6.0f");
    UtAssert_True(matrix[7][5] == 6.0f, "matrix[7][5] == 6.0f");
    UtAssert_True(matrix[8][5] == 6.0f, "matrix[8][5] == 6.0f");
    UtAssert_True(matrix[9][5] == 6.0f, "matrix[9][5] == 6.0f");
}


void Test_Matrix10F6_OutOfBounds(void)
{
    math::Matrix10F6 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );

    /* Verify results */
    UtAssert_True(!isfinite(matrix[0][6]), "matrix[0][6] == NAN");
    UtAssert_True(!isfinite(matrix[10][0]), "matrix[10][0] == NAN");
}


void Test_Matrix10F6_Mult_6F6(void)
{
    math::Matrix10F6 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );

    math::Matrix6F6 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );
    
    math::Matrix10F6 result;
    
    result = matrixA * matrixB;

    /* Verify results */
    UtAssert_True(result[0][0] == 21.0f, "result[0][0] == 21.0f");
    UtAssert_True(result[1][0] == 21.0f, "result[1][0] == 21.0f");
    UtAssert_True(result[2][0] == 21.0f, "result[2][0] == 21.0f");
    UtAssert_True(result[3][0] == 21.0f, "result[3][0] == 21.0f");
    UtAssert_True(result[4][0] == 21.0f, "result[4][0] == 21.0f");
    UtAssert_True(result[5][0] == 21.0f, "result[5][0] == 21.0f");
    UtAssert_True(result[6][0] == 21.0f, "result[6][0] == 21.0f");
    UtAssert_True(result[7][0] == 21.0f, "result[7][0] == 21.0f");
    UtAssert_True(result[8][0] == 21.0f, "result[8][0] == 21.0f");
    UtAssert_True(result[9][0] == 21.0f, "result[9][0] == 21.0f");

    UtAssert_True(result[0][1] == 42.0f, "result[0][1] == 42.0f");
    UtAssert_True(result[1][1] == 42.0f, "result[1][1] == 42.0f");
    UtAssert_True(result[2][1] == 42.0f, "result[2][1] == 42.0f");
    UtAssert_True(result[3][1] == 42.0f, "result[3][1] == 42.0f");
    UtAssert_True(result[4][1] == 42.0f, "result[4][1] == 42.0f");
    UtAssert_True(result[5][1] == 42.0f, "result[5][1] == 42.0f");
    UtAssert_True(result[6][1] == 42.0f, "result[6][1] == 42.0f");
    UtAssert_True(result[7][1] == 42.0f, "result[7][1] == 42.0f");
    UtAssert_True(result[8][1] == 42.0f, "result[8][1] == 42.0f");
    UtAssert_True(result[9][1] == 42.0f, "result[9][1] == 42.0f");

    UtAssert_True(result[0][2] == 63.0f, "result[0][2] == 63.0f");
    UtAssert_True(result[1][2] == 63.0f, "result[1][2] == 63.0f");
    UtAssert_True(result[2][2] == 63.0f, "result[2][2] == 63.0f");
    UtAssert_True(result[3][2] == 63.0f, "result[3][2] == 63.0f");
    UtAssert_True(result[4][2] == 63.0f, "result[4][2] == 63.0f");
    UtAssert_True(result[5][2] == 63.0f, "result[5][2] == 63.0f");
    UtAssert_True(result[6][2] == 63.0f, "result[6][2] == 63.0f");
    UtAssert_True(result[7][2] == 63.0f, "result[7][2] == 63.0f");
    UtAssert_True(result[8][2] == 63.0f, "result[8][2] == 63.0f");
    UtAssert_True(result[9][2] == 63.0f, "result[9][2] == 63.0f");

    UtAssert_True(result[0][3] == 84.0f, "result[0][3] == 84.0f");
    UtAssert_True(result[1][3] == 84.0f, "result[1][3] == 84.0f");
    UtAssert_True(result[2][3] == 84.0f, "result[2][3] == 84.0f");
    UtAssert_True(result[3][3] == 84.0f, "result[3][3] == 84.0f");
    UtAssert_True(result[4][3] == 84.0f, "result[4][3] == 84.0f");
    UtAssert_True(result[5][3] == 84.0f, "result[5][3] == 84.0f");
    UtAssert_True(result[6][3] == 84.0f, "result[6][3] == 84.0f");
    UtAssert_True(result[7][3] == 84.0f, "result[7][3] == 84.0f");
    UtAssert_True(result[8][3] == 84.0f, "result[8][3] == 84.0f");
    UtAssert_True(result[9][3] == 84.0f, "result[9][3] == 84.0f");

    UtAssert_True(result[0][4] == 105.0f, "result[0][4] == 105.0f");
    UtAssert_True(result[1][4] == 105.0f, "result[1][4] == 105.0f");
    UtAssert_True(result[2][4] == 105.0f, "result[2][4] == 105.0f");
    UtAssert_True(result[3][4] == 105.0f, "result[3][4] == 105.0f");
    UtAssert_True(result[4][4] == 105.0f, "result[4][4] == 105.0f");
    UtAssert_True(result[5][4] == 105.0f, "result[5][4] == 105.0f");
    UtAssert_True(result[6][4] == 105.0f, "result[6][4] == 105.0f");
    UtAssert_True(result[7][4] == 105.0f, "result[7][4] == 105.0f");
    UtAssert_True(result[8][4] == 105.0f, "result[8][4] == 105.0f");
    UtAssert_True(result[9][4] == 105.0f, "result[9][4] == 105.0f");

    UtAssert_True(result[0][5] == 126.0f, "result[0][5] == 126.0f");
    UtAssert_True(result[1][5] == 126.0f, "result[1][5] == 126.0f");
    UtAssert_True(result[2][5] == 126.0f, "result[2][5] == 126.0f");
    UtAssert_True(result[3][5] == 126.0f, "result[3][5] == 126.0f");
    UtAssert_True(result[4][5] == 126.0f, "result[4][5] == 126.0f");
    UtAssert_True(result[5][5] == 126.0f, "result[5][5] == 126.0f");
    UtAssert_True(result[6][5] == 126.0f, "result[6][5] == 126.0f");
    UtAssert_True(result[7][5] == 126.0f, "result[7][5] == 126.0f");
    UtAssert_True(result[8][5] == 126.0f, "result[8][5] == 126.0f");
    UtAssert_True(result[9][5] == 126.0f, "result[9][5] == 126.0f");
}


void Test_Matrix10F6_Mult_6F(void)
{
    math::Matrix10F6 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );

    math::Vector6F vectorB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );
    
    math::Vector10F result;
    
    result = matrixA * vectorB;

    /* Verify results */
    UtAssert_True(result[0] == 91.0f, "result[0] == 91.0f");
    UtAssert_True(result[1] == 91.0f, "result[1] == 91.0f");
    UtAssert_True(result[2] == 91.0f, "result[2] == 91.0f");
    UtAssert_True(result[3] == 91.0f, "result[3] == 91.0f");
    UtAssert_True(result[4] == 91.0f, "result[4] == 91.0f");
    UtAssert_True(result[5] == 91.0f, "result[5] == 91.0f");
    UtAssert_True(result[6] == 91.0f, "result[6] == 91.0f");
    UtAssert_True(result[7] == 91.0f, "result[7] == 91.0f");
    UtAssert_True(result[8] == 91.0f, "result[8] == 91.0f");
    UtAssert_True(result[9] == 91.0f, "result[9] == 91.0f");
}


void Test_Matrix10F6_Mult_6F10(void)
{
    math::Matrix10F6 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );

    math::Matrix6F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    
    math::Matrix10F10 result;
    
    result = matrixA * matrixB;

    /* Verify results */
    UtAssert_True(result[0][0] == 21.0f, "result[0][0] == 21.0f");
    UtAssert_True(result[1][0] == 21.0f, "result[1][0] == 21.0f");
    UtAssert_True(result[2][0] == 21.0f, "result[2][0] == 21.0f");
    UtAssert_True(result[3][0] == 21.0f, "result[3][0] == 21.0f");
    UtAssert_True(result[4][0] == 21.0f, "result[4][0] == 21.0f");
    UtAssert_True(result[5][0] == 21.0f, "result[5][0] == 21.0f");
    UtAssert_True(result[6][0] == 21.0f, "result[6][0] == 21.0f");
    UtAssert_True(result[7][0] == 21.0f, "result[7][0] == 21.0f");
    UtAssert_True(result[8][0] == 21.0f, "result[8][0] == 21.0f");
    UtAssert_True(result[9][0] == 21.0f, "result[9][0] == 21.0f");

    UtAssert_True(result[0][1] == 42.0f, "result[0][1] == 42.0f");
    UtAssert_True(result[1][1] == 42.0f, "result[1][1] == 42.0f");
    UtAssert_True(result[2][1] == 42.0f, "result[2][1] == 42.0f");
    UtAssert_True(result[3][1] == 42.0f, "result[3][1] == 42.0f");
    UtAssert_True(result[4][1] == 42.0f, "result[4][1] == 42.0f");
    UtAssert_True(result[5][1] == 42.0f, "result[5][1] == 42.0f");
    UtAssert_True(result[6][1] == 42.0f, "result[6][1] == 42.0f");
    UtAssert_True(result[7][1] == 42.0f, "result[7][1] == 42.0f");
    UtAssert_True(result[8][1] == 42.0f, "result[8][1] == 42.0f");
    UtAssert_True(result[9][1] == 42.0f, "result[9][1] == 42.0f");

    UtAssert_True(result[0][2] == 63.0f, "result[0][2] == 63.0f");
    UtAssert_True(result[1][2] == 63.0f, "result[1][2] == 63.0f");
    UtAssert_True(result[2][2] == 63.0f, "result[2][2] == 63.0f");
    UtAssert_True(result[3][2] == 63.0f, "result[3][2] == 63.0f");
    UtAssert_True(result[4][2] == 63.0f, "result[4][2] == 63.0f");
    UtAssert_True(result[5][2] == 63.0f, "result[5][2] == 63.0f");
    UtAssert_True(result[6][2] == 63.0f, "result[6][2] == 63.0f");
    UtAssert_True(result[7][2] == 63.0f, "result[7][2] == 63.0f");
    UtAssert_True(result[8][2] == 63.0f, "result[8][2] == 63.0f");
    UtAssert_True(result[9][2] == 63.0f, "result[9][2] == 63.0f");

    UtAssert_True(result[0][3] == 84.0f, "result[0][3] == 84.0f");
    UtAssert_True(result[1][3] == 84.0f, "result[1][3] == 84.0f");
    UtAssert_True(result[2][3] == 84.0f, "result[2][3] == 84.0f");
    UtAssert_True(result[3][3] == 84.0f, "result[3][3] == 84.0f");
    UtAssert_True(result[4][3] == 84.0f, "result[4][3] == 84.0f");
    UtAssert_True(result[5][3] == 84.0f, "result[5][3] == 84.0f");
    UtAssert_True(result[6][3] == 84.0f, "result[6][3] == 84.0f");
    UtAssert_True(result[7][3] == 84.0f, "result[7][3] == 84.0f");
    UtAssert_True(result[8][3] == 84.0f, "result[8][3] == 84.0f");
    UtAssert_True(result[9][3] == 84.0f, "result[9][3] == 84.0f");

    UtAssert_True(result[0][4] == 105.0f, "result[0][4] == 105.0f");
    UtAssert_True(result[1][4] == 105.0f, "result[1][4] == 105.0f");
    UtAssert_True(result[2][4] == 105.0f, "result[2][4] == 105.0f");
    UtAssert_True(result[3][4] == 105.0f, "result[3][4] == 105.0f");
    UtAssert_True(result[4][4] == 105.0f, "result[4][4] == 105.0f");
    UtAssert_True(result[5][4] == 105.0f, "result[5][4] == 105.0f");
    UtAssert_True(result[6][4] == 105.0f, "result[6][4] == 105.0f");
    UtAssert_True(result[7][4] == 105.0f, "result[7][4] == 105.0f");
    UtAssert_True(result[8][4] == 105.0f, "result[8][4] == 105.0f");
    UtAssert_True(result[9][4] == 105.0f, "result[9][4] == 105.0f");

    UtAssert_True(result[0][5] == 126.0f, "result[0][5] == 126.0f");
    UtAssert_True(result[1][5] == 126.0f, "result[1][5] == 126.0f");
    UtAssert_True(result[2][5] == 126.0f, "result[2][5] == 126.0f");
    UtAssert_True(result[3][5] == 126.0f, "result[3][5] == 126.0f");
    UtAssert_True(result[4][5] == 126.0f, "result[4][5] == 126.0f");
    UtAssert_True(result[5][5] == 126.0f, "result[5][5] == 126.0f");
    UtAssert_True(result[6][5] == 126.0f, "result[6][5] == 126.0f");
    UtAssert_True(result[7][5] == 126.0f, "result[7][5] == 126.0f");
    UtAssert_True(result[8][5] == 126.0f, "result[8][5] == 126.0f");
    UtAssert_True(result[9][5] == 126.0f, "result[9][5] == 126.0f");

    UtAssert_True(result[0][6] == 147.0f, "result[0][6] == 147.0f");
    UtAssert_True(result[1][6] == 147.0f, "result[1][6] == 147.0f");
    UtAssert_True(result[2][6] == 147.0f, "result[2][6] == 147.0f");
    UtAssert_True(result[3][6] == 147.0f, "result[3][6] == 147.0f");
    UtAssert_True(result[4][6] == 147.0f, "result[4][6] == 147.0f");
    UtAssert_True(result[5][6] == 147.0f, "result[5][6] == 147.0f");
    UtAssert_True(result[6][6] == 147.0f, "result[6][6] == 147.0f");
    UtAssert_True(result[7][6] == 147.0f, "result[7][6] == 147.0f");
    UtAssert_True(result[8][6] == 147.0f, "result[8][6] == 147.0f");
    UtAssert_True(result[9][6] == 147.0f, "result[9][6] == 147.0f");

    UtAssert_True(result[0][7] == 168.0f, "result[0][7] == 168.0f");
    UtAssert_True(result[1][7] == 168.0f, "result[1][7] == 168.0f");
    UtAssert_True(result[2][7] == 168.0f, "result[2][7] == 168.0f");
    UtAssert_True(result[3][7] == 168.0f, "result[3][7] == 168.0f");
    UtAssert_True(result[4][7] == 168.0f, "result[4][7] == 168.0f");
    UtAssert_True(result[5][7] == 168.0f, "result[5][7] == 168.0f");
    UtAssert_True(result[6][7] == 168.0f, "result[6][7] == 168.0f");
    UtAssert_True(result[7][7] == 168.0f, "result[7][7] == 168.0f");
    UtAssert_True(result[8][7] == 168.0f, "result[8][7] == 168.0f");
    UtAssert_True(result[9][7] == 168.0f, "result[9][7] == 168.0f");

    UtAssert_True(result[0][8] == 189.0f, "result[0][8] == 189.0f");
    UtAssert_True(result[1][8] == 189.0f, "result[1][8] == 189.0f");
    UtAssert_True(result[2][8] == 189.0f, "result[2][8] == 189.0f");
    UtAssert_True(result[3][8] == 189.0f, "result[3][8] == 189.0f");
    UtAssert_True(result[4][8] == 189.0f, "result[4][8] == 189.0f");
    UtAssert_True(result[5][8] == 189.0f, "result[5][8] == 189.0f");
    UtAssert_True(result[6][8] == 189.0f, "result[6][8] == 189.0f");
    UtAssert_True(result[7][8] == 189.0f, "result[7][8] == 189.0f");
    UtAssert_True(result[8][8] == 189.0f, "result[8][8] == 189.0f");
    UtAssert_True(result[9][8] == 189.0f, "result[9][8] == 189.0f");

    UtAssert_True(result[0][9] == 210.0f, "result[0][9] == 210.0f");
    UtAssert_True(result[1][9] == 210.0f, "result[1][9] == 210.0f");
    UtAssert_True(result[2][9] == 210.0f, "result[2][9] == 210.0f");
    UtAssert_True(result[3][9] == 210.0f, "result[3][9] == 210.0f");
    UtAssert_True(result[4][9] == 210.0f, "result[4][9] == 210.0f");
    UtAssert_True(result[5][9] == 210.0f, "result[5][9] == 210.0f");
    UtAssert_True(result[6][9] == 210.0f, "result[6][9] == 210.0f");
    UtAssert_True(result[7][9] == 210.0f, "result[7][9] == 210.0f");
    UtAssert_True(result[8][9] == 210.0f, "result[8][9] == 210.0f");
    UtAssert_True(result[9][9] == 210.0f, "result[9][9] == 210.0f");
}


void Test_Matrix10F6_Zero(void)
{
    math::Matrix10F6 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}
    );
    
    math::Matrix10F6 result = matrix;
    result.Zero();

    /* Verify results */
    UtAssert_True(result[0][0] == 0.0f, "result[0][0] == 0.0f");
    UtAssert_True(result[1][0] == 0.0f, "result[1][0] == 0.0f");
    UtAssert_True(result[2][0] == 0.0f, "result[2][0] == 0.0f");
    UtAssert_True(result[3][0] == 0.0f, "result[3][0] == 0.0f");
    UtAssert_True(result[4][0] == 0.0f, "result[4][0] == 0.0f");
    UtAssert_True(result[5][0] == 0.0f, "result[5][0] == 0.0f");
    UtAssert_True(result[6][0] == 0.0f, "result[6][0] == 0.0f");
    UtAssert_True(result[7][0] == 0.0f, "result[7][0] == 0.0f");
    UtAssert_True(result[8][0] == 0.0f, "result[8][0] == 0.0f");
    UtAssert_True(result[9][0] == 0.0f, "result[9][0] == 0.0f");

    UtAssert_True(result[0][1] == 0.0f, "result[0][1] == 0.0f");
    UtAssert_True(result[1][1] == 0.0f, "result[1][1] == 0.0f");
    UtAssert_True(result[2][1] == 0.0f, "result[2][1] == 0.0f");
    UtAssert_True(result[3][1] == 0.0f, "result[3][1] == 0.0f");
    UtAssert_True(result[4][1] == 0.0f, "result[4][1] == 0.0f");
    UtAssert_True(result[5][1] == 0.0f, "result[5][1] == 0.0f");
    UtAssert_True(result[6][1] == 0.0f, "result[6][1] == 0.0f");
    UtAssert_True(result[7][1] == 0.0f, "result[7][1] == 0.0f");
    UtAssert_True(result[8][1] == 0.0f, "result[8][1] == 0.0f");
    UtAssert_True(result[9][1] == 0.0f, "result[9][1] == 0.0f");

    UtAssert_True(result[0][2] == 0.0f, "result[0][2] == 0.0f");
    UtAssert_True(result[1][2] == 0.0f, "result[1][2] == 0.0f");
    UtAssert_True(result[2][2] == 0.0f, "result[2][2] == 0.0f");
    UtAssert_True(result[3][2] == 0.0f, "result[3][2] == 0.0f");
    UtAssert_True(result[4][2] == 0.0f, "result[4][2] == 0.0f");
    UtAssert_True(result[5][2] == 0.0f, "result[5][2] == 0.0f");
    UtAssert_True(result[6][2] == 0.0f, "result[6][2] == 0.0f");
    UtAssert_True(result[7][2] == 0.0f, "result[7][2] == 0.0f");
    UtAssert_True(result[8][2] == 0.0f, "result[8][2] == 0.0f");
    UtAssert_True(result[9][2] == 0.0f, "result[9][2] == 0.0f");

    UtAssert_True(result[0][3] == 0.0f, "result[0][3] == 0.0f");
    UtAssert_True(result[1][3] == 0.0f, "result[1][3] == 0.0f");
    UtAssert_True(result[2][3] == 0.0f, "result[2][3] == 0.0f");
    UtAssert_True(result[3][3] == 0.0f, "result[3][3] == 0.0f");
    UtAssert_True(result[4][3] == 0.0f, "result[4][3] == 0.0f");
    UtAssert_True(result[5][3] == 0.0f, "result[5][3] == 0.0f");
    UtAssert_True(result[6][3] == 0.0f, "result[6][3] == 0.0f");
    UtAssert_True(result[7][3] == 0.0f, "result[7][3] == 0.0f");
    UtAssert_True(result[8][3] == 0.0f, "result[8][3] == 0.0f");
    UtAssert_True(result[9][3] == 0.0f, "result[9][3] == 0.0f");

    UtAssert_True(result[0][4] == 0.0f, "result[0][4] == 0.0f");
    UtAssert_True(result[1][4] == 0.0f, "result[1][4] == 0.0f");
    UtAssert_True(result[2][4] == 0.0f, "result[2][4] == 0.0f");
    UtAssert_True(result[3][4] == 0.0f, "result[3][4] == 0.0f");
    UtAssert_True(result[4][4] == 0.0f, "result[4][4] == 0.0f");
    UtAssert_True(result[5][4] == 0.0f, "result[5][4] == 0.0f");
    UtAssert_True(result[6][4] == 0.0f, "result[6][4] == 0.0f");
    UtAssert_True(result[7][4] == 0.0f, "result[7][4] == 0.0f");
    UtAssert_True(result[8][4] == 0.0f, "result[8][4] == 0.0f");
    UtAssert_True(result[9][4] == 0.0f, "result[9][4] == 0.0f");

    UtAssert_True(result[0][5] == 0.0f, "result[0][5] == 0.0f");
    UtAssert_True(result[1][5] == 0.0f, "result[1][5] == 0.0f");
    UtAssert_True(result[2][5] == 0.0f, "result[2][5] == 0.0f");
    UtAssert_True(result[3][5] == 0.0f, "result[3][5] == 0.0f");
    UtAssert_True(result[4][5] == 0.0f, "result[4][5] == 0.0f");
    UtAssert_True(result[5][5] == 0.0f, "result[5][5] == 0.0f");
    UtAssert_True(result[6][5] == 0.0f, "result[6][5] == 0.0f");
    UtAssert_True(result[7][5] == 0.0f, "result[7][5] == 0.0f");
    UtAssert_True(result[8][5] == 0.0f, "result[8][5] == 0.0f");
    UtAssert_True(result[9][5] == 0.0f, "result[9][5] == 0.0f");
}
