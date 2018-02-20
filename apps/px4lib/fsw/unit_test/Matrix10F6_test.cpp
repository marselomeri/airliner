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

