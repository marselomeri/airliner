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

#include "Matrix10F10_test.hpp"
#include <math/Matrix10F10.hpp>
#include <math/Matrix10F1.hpp>
#include <math/Matrix1F10.hpp>
#include <math/Matrix1F1.hpp>
#include <math/Vector10F.hpp>
#include <math/Vector1F.hpp>

#include "utassert.h"
#include <float.h>


void Test_Matrix10F10_Constructor(void)
{
    math::Matrix10F10 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
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
    
    UtAssert_True(matrix[3][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[3][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[3][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[3][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[3][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[3][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[3][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[3][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[3][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[3][9] == 10.0f, "matrix[9][1] == 10.0f");
    
    UtAssert_True(matrix[4][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[4][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[4][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[4][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[4][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[4][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[4][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[4][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[4][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[4][9] == 10.0f, "matrix[9][1] == 10.0f");

    UtAssert_True(matrix[5][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[5][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[5][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[5][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[5][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[5][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[5][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[5][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[5][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[5][9] == 10.0f, "matrix[9][1] == 10.0f");

    UtAssert_True(matrix[6][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[6][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[6][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[6][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[6][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[6][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[6][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[6][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[6][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[6][9] == 10.0f, "matrix[9][1] == 10.0f");

    UtAssert_True(matrix[7][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[7][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[7][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[7][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[7][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[7][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[7][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[7][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[7][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[7][9] == 10.0f, "matrix[9][1] == 10.0f");

    UtAssert_True(matrix[8][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[8][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[8][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[8][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[8][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[8][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[8][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[8][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[8][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[8][9] == 10.0f, "matrix[9][1] == 10.0f");

    UtAssert_True(matrix[9][0] == 1.0f, "matrix[0][1] == 1.0f");
    UtAssert_True(matrix[9][1] == 2.0f, "matrix[1][1] == 2.0f");
    UtAssert_True(matrix[9][2] == 3.0f, "matrix[2][1] == 3.0f");
    UtAssert_True(matrix[9][3] == 4.0f, "matrix[3][1] == 4.0f");
    UtAssert_True(matrix[9][4] == 5.0f, "matrix[4][1] == 5.0f");
    UtAssert_True(matrix[9][5] == 6.0f, "matrix[5][1] == 6.0f");
    UtAssert_True(matrix[9][6] == 7.0f, "matrix[6][1] == 7.0f");
    UtAssert_True(matrix[9][7] == 8.0f, "matrix[7][1] == 8.0f");
    UtAssert_True(matrix[9][8] == 9.0f, "matrix[8][1] == 9.0f");
    UtAssert_True(matrix[9][9] == 10.0f, "matrix[9][1] == 10.0f");
}


void Test_Matrix10F10_Zero(void)
{
    int i, j = 0;
    math::Matrix10F10 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    matrix.Zero();

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
            UtAssert_True(matrix[i][j] == 0.0f, "matrix[i][j] == 0.0f");
		}
	}
}


void Test_Matrix10F10_Identity(void)
{
    int i, j = 0;
    math::Matrix10F10 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    matrix = matrix.Identity();


    UtAssert_True(matrix[0][0] == 1.0f, "matrix[0][0] == 1.0f");
    UtAssert_True(matrix[1][1] == 1.0f, "matrix[1][1] == 1.0f");
    UtAssert_True(matrix[2][2] == 1.0f, "matrix[2][2] == 1.0f");
    UtAssert_True(matrix[3][3] == 1.0f, "matrix[3][3] == 1.0f");
    UtAssert_True(matrix[4][4] == 1.0f, "matrix[4][4] == 1.0f");
    UtAssert_True(matrix[5][5] == 1.0f, "matrix[5][5] == 1.0f");
    UtAssert_True(matrix[6][6] == 1.0f, "matrix[6][6] == 1.0f");
    UtAssert_True(matrix[7][7] == 1.0f, "matrix[7][7] == 1.0f");
    UtAssert_True(matrix[8][8] == 1.0f, "matrix[8][8] == 1.0f");
    UtAssert_True(matrix[9][9] == 1.0f, "matrix[9][9] == 1.0f");

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
            if(i != j)
            {
                UtAssert_True(matrix[i][j] == 0.0f, "matrix[i][j] == 0.0f");
            }
        }
    }
}


void Test_Matrix10F10_Transpose(void)
{
    int i, j = 0;
    math::Matrix10F10 matrix(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    matrix = matrix.Transpose();

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
            if(0 == i)
            {
                UtAssert_True(matrix[i][j] == 1.0f, "matrix[i][j] == 1.0f");
            }
            else if (1 == i)
            {
                UtAssert_True(matrix[i][j] == 2.0f, "matrix[i][j] == 2.0f");
            }
            else if (2 == i)
            {
                UtAssert_True(matrix[i][j] == 3.0f, "matrix[i][j] == 3.0f");
            }
            else if (3 == i)
            {
                UtAssert_True(matrix[i][j] == 4.0f, "matrix[i][j] == 4.0f");
            }
            else if (4 == i)
            {
                UtAssert_True(matrix[i][j] == 5.0f, "matrix[i][j] == 5.0f");
            }
            else if (5 == i)
            {
                UtAssert_True(matrix[i][j] == 6.0f, "matrix[i][j] == 6.0f");
            }
            else if (6 == i)
            {
                UtAssert_True(matrix[i][j] == 7.0f, "matrix[i][j] == 7.0f");
            }
            else if (7 == i)
            {
                UtAssert_True(matrix[i][j] == 8.0f, "matrix[i][j] == 8.0f");
            }
            else if (8 == i)
            {
                UtAssert_True(matrix[i][j] == 9.0f, "matrix[i][j] == 9.0f");
            }
            else if (9 == i)
            {
                UtAssert_True(matrix[i][j] == 10.0f, "matrix[i][j] == 10.0f");
            }
        }
    }
}


void Test_Matrix10F10_Mult_10F(void)
{
    math::Matrix10F10 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    math::Vector10F vectorB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Vector10F result;
    result.Zero();

    result = matrixA * vectorB;

    UtAssert_True(result[0] == 385.0f, "result[0][0] == 385.0f");
    UtAssert_True(result[1] == 385.0f, "result[1][0] == 385.0f");
    UtAssert_True(result[2] == 385.0f, "result[2][0] == 385.0f");
    UtAssert_True(result[3] == 385.0f, "result[3][0] == 385.0f");
    UtAssert_True(result[4] == 385.0f, "result[4][0] == 385.0f");
    UtAssert_True(result[5] == 385.0f, "result[5][0] == 385.0f");
    UtAssert_True(result[6] == 385.0f, "result[6][0] == 385.0f");
    UtAssert_True(result[7] == 385.0f, "result[7][0] == 385.0f");
    UtAssert_True(result[8] == 385.0f, "result[8][0] == 385.0f");
    UtAssert_True(result[9] == 385.0f, "result[9][0] == 385.0f");
}


void Test_Matrix10F10_Mult_10F_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {-0.321200, 0.505708, -0.536335, 0.187432, 0.312530, -0.801615, 0.414770, -0.292737, 0.180358, -0.770146},
        {0.822430, -0.319400, -0.587464, 0.488797, 0.787293, -0.351115, 0.737150, 0.439155, -0.218142, 0.505710},
        {0.075102, -0.654048, -0.249987, -0.553256, 0.339278, 0.489740, -0.217197, 0.339519, 0.785456, 0.827381},
        {0.750164, 0.791548, 0.884845, 0.904560, 0.898250, 0.079170, -0.811473, -0.071029, 0.105117, 0.332759},
        {0.664760, -0.880650, -0.473452, 0.847499, -0.732206, 0.855843, 0.684167, -0.721014, -0.357233, -0.939900},
        {0.685722, -0.910677, 0.299931, -0.109639, 0.363117, 0.117587, 0.548984, 0.517466, 0.019081, -0.021461},
        {0.305134, -0.788515, 0.591695, 0.500583, -0.137919, -0.461170, 0.894633, -0.997882, -0.908739, 0.417964},
        {0.756073, 0.393335, -0.932825, 0.232462, 0.315382, 0.824797, -0.559982, 0.409534, -0.194485, -0.155474},
        {-0.243241, -0.564209, 0.320543, -0.092056, -0.007966, -0.561551, 0.275095, 0.433222, 0.961172, -0.881753},
        {-0.813359, 0.404504, -0.568303, -0.409739, -0.609289, 0.467275, 0.815649, 0.794081, 0.996040, -0.521853}
    );

    math::Vector10F B (
        {-0.449502,-0.298601,0.170530,0.218850,-0.813969,-0.102041,-0.366406,-0.652456,-0.716551,0.130637}
    );

    math::Vector10F expected (
        {-0.420481,-1.206773,-0.924975,-0.652108,0.930487,-0.871967,1.497102,-0.849356,-0.811261,-1.092350}
    );

    math::Vector10F result;
    result.Zero();

    result = A * B;

    for(i = 0; i < 10; i++)
    {
        UtAssert_True(fabs(result[i] - expected[i]) < 0.00001f, "fabs(result[i] - expected[i]) < 0.00001f");

    }
}


void Test_Matrix10F10_Mult_10F1(void)
{
    math::Matrix10F10 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    
    math::Matrix10F1 matrixB(
            {1.0f}, 
            {2.0f}, 
            {3.0f}, 
            {4.0f}, 
            {5.0f}, 
            {6.0f}, 
            {7.0f}, 
            {8.0f}, 
            {9.0f}, 
            {10.0f}
    );
    
    math::Matrix10F1 result;
    
    result.Zero();
    
    result = matrixA * matrixB;

    UtAssert_True(result[0][0] == 385.0f, "result[0][0] == 385.0f");
    UtAssert_True(result[1][0] == 385.0f, "result[1][0] == 385.0f");
    UtAssert_True(result[2][0] == 385.0f, "result[2][0] == 385.0f");
    UtAssert_True(result[3][0] == 385.0f, "result[3][0] == 385.0f");
    UtAssert_True(result[4][0] == 385.0f, "result[4][0] == 385.0f");
    UtAssert_True(result[5][0] == 385.0f, "result[5][0] == 385.0f");
    UtAssert_True(result[6][0] == 385.0f, "result[6][0] == 385.0f");
    UtAssert_True(result[7][0] == 385.0f, "result[7][0] == 385.0f");
    UtAssert_True(result[8][0] == 385.0f, "result[8][0] == 385.0f");
    UtAssert_True(result[9][0] == 385.0f, "result[9][0] == 385.0f");
}


void Test_Matrix10F10_Mult_10F1_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {-0.674276, 0.870345, -0.735977, -0.885108, 0.213168, -0.376886, -0.395466, 0.548795, 0.982579, 0.293957},
        {-0.832291, -0.272773, -0.875532, -0.357720, -0.921729, 0.299436, 0.497213, 0.915032, -0.610137, 0.106499},
        {-0.114739, -0.404275, 0.138278, 0.425723, -0.789645, -0.426943, 0.489370, -0.245626, -0.861584, -0.488590},
        {0.454370, 0.266651, 0.008222, -0.399166, -0.511096, -0.455970, -0.203747, -0.171679, -0.572028, -0.237497},
        {0.801461, 0.740158, 0.666718, 0.608937, 0.010278, 0.583023, 0.701865, 0.175726, -0.106931, 0.645616},
        {-0.877085, -0.707616, -0.120938, 0.427665, -0.071343, 0.483367, 0.199285, -0.485751, 0.510377, -0.915180},
        {0.226956, 0.715640, 0.730390, -0.687150, 0.266646, -0.622248, 0.240236, 0.930464, -0.048613, 0.679674},
        {-0.827557, 0.717807, 0.032327, 0.054841, 0.394686, 0.176563, -0.782122, 0.303083, -0.471396, -0.685856},
        {0.523228, 0.097505, 0.487578, 0.113715, -0.144929, -0.236480, -0.618538, -0.944216, -0.973352, -0.311958},
        {-0.447963, 0.113441, -0.467065, 0.087616, 0.260620, -0.157843, -0.011459, 0.606395, -0.238146, 0.245002}
    );

    math::Matrix10F1 B (
        {0.733877},
        {0.673686},
        {0.158780},
        {-0.531769},
        {0.542537},
        {0.709462},
        {-0.832588},
        {-0.699753},
        {0.988599},
        {0.916192}
    );

    math::Matrix10F1 expected (
        {1.479520},
        {-2.590866},
        {-2.827270},
        {-0.367450},
        {1.066532},
        {-1.222720},
        {0.556797},
        {-0.463678},
        {0.147855},
        {-0.769414}
    );

    math::Matrix10F1 result;
    result.Zero();

    result = A * B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 1; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}


void Test_Matrix10F10_Mult_10F3(void)
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

    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F3 result;
    
    result = matrixB * matrixA;

    UtAssert_True(result[0][0] == 55.0f, "result[0][0] == 55.0f");
    UtAssert_True(result[1][0] == 55.0f, "result[1][0] == 55.0f");
    UtAssert_True(result[2][0] == 55.0f, "result[2][0] == 55.0f");
    UtAssert_True(result[3][0] == 55.0f, "result[3][0] == 55.0f");
    UtAssert_True(result[4][0] == 55.0f, "result[4][0] == 55.0f");
    UtAssert_True(result[5][0] == 55.0f, "result[5][0] == 55.0f");
    UtAssert_True(result[6][0] == 55.0f, "result[6][0] == 55.0f");
    UtAssert_True(result[7][0] == 55.0f, "result[7][0] == 55.0f");
    UtAssert_True(result[8][0] == 55.0f, "result[8][0] == 55.0f");
    UtAssert_True(result[9][0] == 55.0f, "result[9][0] == 55.0f");

    UtAssert_True(result[0][1] == 110.0f, "result[0][1] == 110.0f");
    UtAssert_True(result[1][1] == 110.0f, "result[1][1] == 110.0f");
    UtAssert_True(result[2][1] == 110.0f, "result[2][1] == 110.0f");
    UtAssert_True(result[3][1] == 110.0f, "result[3][1] == 110.0f");
    UtAssert_True(result[4][1] == 110.0f, "result[4][1] == 110.0f");
    UtAssert_True(result[5][1] == 110.0f, "result[5][1] == 110.0f");
    UtAssert_True(result[6][1] == 110.0f, "result[6][1] == 110.0f");
    UtAssert_True(result[7][1] == 110.0f, "result[7][1] == 110.0f");
    UtAssert_True(result[8][1] == 110.0f, "result[8][1] == 110.0f");
    UtAssert_True(result[9][1] == 110.0f, "result[9][1] == 110.0f");

    UtAssert_True(result[0][2] == 165.0f, "result[0][2] == 165.0f");
    UtAssert_True(result[1][2] == 165.0f, "result[1][2] == 165.0f");
    UtAssert_True(result[2][2] == 165.0f, "result[2][2] == 165.0f");
    UtAssert_True(result[3][2] == 165.0f, "result[3][2] == 165.0f");
    UtAssert_True(result[4][2] == 165.0f, "result[4][2] == 165.0f");
    UtAssert_True(result[5][2] == 165.0f, "result[5][2] == 165.0f");
    UtAssert_True(result[6][2] == 165.0f, "result[6][2] == 165.0f");
    UtAssert_True(result[7][2] == 165.0f, "result[7][2] == 165.0f");
    UtAssert_True(result[8][2] == 165.0f, "result[8][2] == 165.0f");
    UtAssert_True(result[9][2] == 165.0f, "result[9][2] == 165.0f");
}


void Test_Matrix10F10_Mult_10F3_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {-0.169733, 0.627693, -0.136929, -0.194117, 0.627388, -0.415890, -0.351426, -0.576962, 0.232774, 0.348147},
        {-0.583979, 0.060119, -0.764933, -0.365871, -0.078567, 0.789349, 0.035531, -0.866291, 0.881323, 0.437826},
        {0.182113, 0.134634, -0.351870, -0.976583, 0.863887, -0.131330, 0.665275, -0.535764, -0.189495, 0.615956},
        {-0.016948, 0.858816, -0.805986, 0.545892, 0.185736, 0.018202, -0.389605, 0.855011, -0.332448, -0.939870},
        {0.275159, 0.375048, -0.755449, 0.858164, -0.141411, 0.671324, 0.491153, 0.877923, 0.763087, 0.558674},
        {-0.809582, -0.711283, 0.677611, -0.416831, -0.158906, -0.159809, 0.225928, -0.525606, 0.308824, 0.996826},
        {0.427142, -0.037993, 0.068136, -0.563129, -0.877925, -0.737193, 0.259029, 0.682003, 0.939280, -0.171015},
        {-0.335605, 0.605250, 0.647776, 0.302647, 0.895212, 0.499911, 0.640518, 0.262114, 0.059355, 0.745223},
        {-0.086057, 0.256487, -0.453717, -0.225623, 0.515560, 0.696098, -0.712981, -0.019025, 0.342657, -0.155266},
        {-0.742838, 0.062333, -0.161248, -0.976607, -0.298983, -0.795746, 0.350239, 0.750943, 0.112282, 0.810170}
    );

    math::Matrix10F3 B (
        {-0.873863, -0.740301, 0.480327},
        {-0.538291, -0.117961, 0.946215},
        {0.625951, -0.528360, 0.670062},
        {-0.102595, 0.633773, -0.678261},
        {0.044146, 0.725259, 0.208157},
        {-0.570746, -0.632317, -0.981253},
        {0.900868, -0.185257, 0.272010},
        {0.442921, 0.403786, -0.937563},
        {0.453203, 0.352439, -0.599578},
        {-0.251615, -0.903494, -0.809833}
    );

    math::Matrix10F3 expected (
        {-0.544531, 0.318550, 1.114844},
        {-0.479740, -0.399931, -1.340038},
        {-0.117421, -0.837014, 1.248232},
        {-0.896648, 1.955677, -0.032168},
        {-0.356073, 0.195726, -2.888860},
        {1.501326, -0.999031, -0.639575},
        {1.133744, -0.162266, 0.143808},
        {0.628604, -0.305446, -0.374536},
        {-1.154623, 0.449394, -0.781173},
        {1.550980, -0.158932, -0.357094}
    );

    math::Matrix10F3 result;
    result.Zero();

    result = A * B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 3; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}



void Test_Matrix10F10_Mult_10F6(void)
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

    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F6 result;
    
    result = matrixB * matrixA;

    UtAssert_True(result[0][0] == 55.0f, "result[0][0] == 55.0f");
    UtAssert_True(result[1][0] == 55.0f, "result[1][0] == 55.0f");
    UtAssert_True(result[2][0] == 55.0f, "result[2][0] == 55.0f");
    UtAssert_True(result[3][0] == 55.0f, "result[3][0] == 55.0f");
    UtAssert_True(result[4][0] == 55.0f, "result[4][0] == 55.0f");
    UtAssert_True(result[5][0] == 55.0f, "result[5][0] == 55.0f");
    UtAssert_True(result[6][0] == 55.0f, "result[6][0] == 55.0f");
    UtAssert_True(result[7][0] == 55.0f, "result[7][0] == 55.0f");
    UtAssert_True(result[8][0] == 55.0f, "result[8][0] == 55.0f");
    UtAssert_True(result[9][0] == 55.0f, "result[9][0] == 55.0f");

    UtAssert_True(result[0][1] == 110.0f, "result[0][1] == 110.0f");
    UtAssert_True(result[1][1] == 110.0f, "result[1][1] == 110.0f");
    UtAssert_True(result[2][1] == 110.0f, "result[2][1] == 110.0f");
    UtAssert_True(result[3][1] == 110.0f, "result[3][1] == 110.0f");
    UtAssert_True(result[4][1] == 110.0f, "result[4][1] == 110.0f");
    UtAssert_True(result[5][1] == 110.0f, "result[5][1] == 110.0f");
    UtAssert_True(result[6][1] == 110.0f, "result[6][1] == 110.0f");
    UtAssert_True(result[7][1] == 110.0f, "result[7][1] == 110.0f");
    UtAssert_True(result[8][1] == 110.0f, "result[8][1] == 110.0f");
    UtAssert_True(result[9][1] == 110.0f, "result[9][1] == 110.0f");

    UtAssert_True(result[0][2] == 165.0f, "result[0][2] == 165.0f");
    UtAssert_True(result[1][2] == 165.0f, "result[1][2] == 165.0f");
    UtAssert_True(result[2][2] == 165.0f, "result[2][2] == 165.0f");
    UtAssert_True(result[3][2] == 165.0f, "result[3][2] == 165.0f");
    UtAssert_True(result[4][2] == 165.0f, "result[4][2] == 165.0f");
    UtAssert_True(result[5][2] == 165.0f, "result[5][2] == 165.0f");
    UtAssert_True(result[6][2] == 165.0f, "result[6][2] == 165.0f");
    UtAssert_True(result[7][2] == 165.0f, "result[7][2] == 165.0f");
    UtAssert_True(result[8][2] == 165.0f, "result[8][2] == 165.0f");
    UtAssert_True(result[9][2] == 165.0f, "result[9][2] == 165.0f");

    UtAssert_True(result[0][3] == 220.0f, "result[0][3] == 220.0f");
    UtAssert_True(result[1][3] == 220.0f, "result[1][3] == 220.0f");
    UtAssert_True(result[2][3] == 220.0f, "result[2][3] == 220.0f");
    UtAssert_True(result[3][3] == 220.0f, "result[3][3] == 220.0f");
    UtAssert_True(result[4][3] == 220.0f, "result[4][3] == 220.0f");
    UtAssert_True(result[5][3] == 220.0f, "result[5][3] == 220.0f");
    UtAssert_True(result[6][3] == 220.0f, "result[6][3] == 220.0f");
    UtAssert_True(result[7][3] == 220.0f, "result[7][3] == 220.0f");
    UtAssert_True(result[8][3] == 220.0f, "result[8][3] == 220.0f");
    UtAssert_True(result[9][3] == 220.0f, "result[9][3] == 220.0f");

    UtAssert_True(result[0][4] == 275.0f, "result[0][4] == 275.0f");
    UtAssert_True(result[1][4] == 275.0f, "result[1][4] == 275.0f");
    UtAssert_True(result[2][4] == 275.0f, "result[2][4] == 275.0f");
    UtAssert_True(result[3][4] == 275.0f, "result[3][4] == 275.0f");
    UtAssert_True(result[4][4] == 275.0f, "result[4][4] == 275.0f");
    UtAssert_True(result[5][4] == 275.0f, "result[5][4] == 275.0f");
    UtAssert_True(result[6][4] == 275.0f, "result[6][4] == 275.0f");
    UtAssert_True(result[7][4] == 275.0f, "result[7][4] == 275.0f");
    UtAssert_True(result[8][4] == 275.0f, "result[8][4] == 275.0f");
    UtAssert_True(result[9][4] == 275.0f, "result[9][4] == 275.0f");

    UtAssert_True(result[0][5] == 330.0f, "result[0][5] == 330.0f");
    UtAssert_True(result[1][5] == 330.0f, "result[1][5] == 330.0f");
    UtAssert_True(result[2][5] == 330.0f, "result[2][5] == 330.0f");
    UtAssert_True(result[3][5] == 330.0f, "result[3][5] == 330.0f");
    UtAssert_True(result[4][5] == 330.0f, "result[4][5] == 330.0f");
    UtAssert_True(result[5][5] == 330.0f, "result[5][5] == 330.0f");
    UtAssert_True(result[6][5] == 330.0f, "result[6][5] == 330.0f");
    UtAssert_True(result[7][5] == 330.0f, "result[7][5] == 330.0f");
    UtAssert_True(result[8][5] == 330.0f, "result[8][5] == 330.0f");
    UtAssert_True(result[9][5] == 330.0f, "result[9][5] == 330.0f");
}


void Test_Matrix10F10_Mult_10F6_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {0.873176, 0.732066, -0.368210, 0.646684, -0.915820, -0.807261, 0.645939, -0.367210, -0.004736, 0.644576},
        {-0.094670, 0.019256, 0.653762, -0.815309, -0.755441, -0.822297, -0.633216, -0.387372, 0.160633, -0.396080},
        {0.459291, -0.555773, -0.989628, 0.019551, 0.195636, 0.609553, -0.669585, -0.580829, 0.080164, -0.729710},
        {0.762405, -0.251151, -0.154987, 0.085122, -0.587020, -0.090162, 0.290389, -0.491303, 0.819343, 0.667657},
        {0.543770, 0.733176, 0.052859, -0.379463, -0.353219, 0.288928, -0.543518, -0.157303, -0.165638, 0.477322},
        {0.217053, -0.937754, 0.421905, -0.710436, 0.973265, -0.413381, 0.208329, 0.249413, -0.326202, -0.764305},
        {-0.315854, 0.909539, -0.398580, 0.695183, 0.241242, 0.442258, 0.518533, -0.640682, -0.608579, -0.726849},
        {0.614576, 0.378506, 0.949585, 0.399747, 0.958334, -0.433958, 0.823250, 0.600092, 0.706838, 0.531344},
        {-0.561661, -0.442934, -0.591566, 0.370350, -0.678574, -0.890098, -0.944547, 0.746368, -0.443681, 0.076410},
        {0.177046, -0.347198, -0.703109, -0.434237, -0.254061, 0.244077, 0.462116, -0.134458, -0.091395, -0.096399}
    );

    math::Matrix10F6 B (
        {-0.302807, -0.372902, 0.234974, 0.802742, -0.851663, 0.360124},
        {-0.373574, -0.579475, -0.130218, 0.094659, 0.198125, -0.132042},
        {0.027839, -0.381930, 0.050702, 0.497699, 0.787400, 0.158275},
        {-0.829383, 0.669738, -0.420153, 0.867644, 0.412956, -0.979168},
        {0.477380, 0.646908, -0.322682, 0.893885, 0.774531, 0.504544},
        {0.265631, 0.638028, 0.208507, -0.208660, 0.913719, 0.993998},
        {-0.387319, -0.350530, -0.851129, 0.046600, 0.211731, -0.289953},
        {0.711604, 0.985251, 0.110824, 0.282019, 0.520618, 0.483855},
        {-0.654988, 0.814336, -0.116884, 0.016749, 0.997917, -0.884535},
        {-0.907109, 0.376671, 0.788078, -0.045115, -0.239732, -0.876897}
    );

    math::Matrix10F6 expected (
        {-2.829203, -1.632868, -0.135274, 0.395252, -2.282091, -2.664196},
        {0.360494, -1.963020, 0.588363, -1.078086, -1.154427, -0.131944},
        {0.735532, 0.510186, 0.106965, -0.272547, -0.753178, 1.249695},
        {-2.120517, -0.126975, 0.467640, -0.062379, -0.859724, -1.818078},
        {-0.440147, -0.865670, 1.209331, -0.267046, -0.919206, 0.397353},
        {2.244134, -0.189435, -0.621129, 0.744356, 0.075956, 2.063585},
        {-0.197972, -0.935582, -1.504600, 0.226785, 0.356568, 0.299025},
        {-1.127179, 0.878030, -0.722474, 2.491279, 1.874817, -1.057115},
        {0.569791, 0.667133, 0.772200, -0.731132, -1.533640, -0.866716},
        {0.232859, -0.300939, -0.107026, -0.909040, -0.966533, 0.504261}
    );

    math::Matrix10F6 result;
    result.Zero();

    result = A * B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 6; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}


void Test_Matrix10F10_Mult_Scaler(void)
{
    math::Matrix10F10 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F10 result;
    
    result = matrixA * 2.0f;

    UtAssert_True(result[0][0] == 2.0f, "result[0][0] == 2.0f");
    UtAssert_True(result[1][0] == 2.0f, "result[1][0] == 2.0f");
    UtAssert_True(result[2][0] == 2.0f, "result[2][0] == 2.0f");
    UtAssert_True(result[3][0] == 2.0f, "result[3][0] == 2.0f");
    UtAssert_True(result[4][0] == 2.0f, "result[4][0] == 2.0f");
    UtAssert_True(result[5][0] == 2.0f, "result[5][0] == 2.0f");
    UtAssert_True(result[6][0] == 2.0f, "result[6][0] == 2.0f");
    UtAssert_True(result[7][0] == 2.0f, "result[7][0] == 2.0f");
    UtAssert_True(result[8][0] == 2.0f, "result[8][0] == 2.0f");
    UtAssert_True(result[9][0] == 2.0f, "result[9][0] == 2.0f");

    UtAssert_True(result[0][1] == 4.0f, "result[0][1] == 4.0f");
    UtAssert_True(result[1][1] == 4.0f, "result[1][1] == 4.0f");
    UtAssert_True(result[2][1] == 4.0f, "result[2][1] == 4.0f");
    UtAssert_True(result[3][1] == 4.0f, "result[3][1] == 4.0f");
    UtAssert_True(result[4][1] == 4.0f, "result[4][1] == 4.0f");
    UtAssert_True(result[5][1] == 4.0f, "result[5][1] == 4.0f");
    UtAssert_True(result[6][1] == 4.0f, "result[6][1] == 4.0f");
    UtAssert_True(result[7][1] == 4.0f, "result[7][1] == 4.0f");
    UtAssert_True(result[8][1] == 4.0f, "result[8][1] == 4.0f");
    UtAssert_True(result[9][1] == 4.0f, "result[9][1] == 4.0f");

    UtAssert_True(result[0][2] == 6.0f, "result[0][2] == 6.0f");
    UtAssert_True(result[1][2] == 6.0f, "result[1][2] == 6.0f");
    UtAssert_True(result[2][2] == 6.0f, "result[2][2] == 6.0f");
    UtAssert_True(result[3][2] == 6.0f, "result[3][2] == 6.0f");
    UtAssert_True(result[4][2] == 6.0f, "result[4][2] == 6.0f");
    UtAssert_True(result[5][2] == 6.0f, "result[5][2] == 6.0f");
    UtAssert_True(result[6][2] == 6.0f, "result[6][2] == 6.0f");
    UtAssert_True(result[7][2] == 6.0f, "result[7][2] == 6.0f");
    UtAssert_True(result[8][2] == 6.0f, "result[8][2] == 6.0f");
    UtAssert_True(result[9][2] == 6.0f, "result[9][2] == 6.0f");

    UtAssert_True(result[0][3] == 8.0f, "result[0][3] == 8.0f");
    UtAssert_True(result[1][3] == 8.0f, "result[1][3] == 8.0f");
    UtAssert_True(result[2][3] == 8.0f, "result[2][3] == 8.0f");
    UtAssert_True(result[3][3] == 8.0f, "result[3][3] == 8.0f");
    UtAssert_True(result[4][3] == 8.0f, "result[4][3] == 8.0f");
    UtAssert_True(result[5][3] == 8.0f, "result[5][3] == 8.0f");
    UtAssert_True(result[6][3] == 8.0f, "result[6][3] == 8.0f");
    UtAssert_True(result[7][3] == 8.0f, "result[7][3] == 8.0f");
    UtAssert_True(result[8][3] == 8.0f, "result[8][3] == 8.0f");
    UtAssert_True(result[9][3] == 8.0f, "result[9][3] == 8.0f");

    UtAssert_True(result[0][4] == 10.0f, "result[0][4] == 10.0f");
    UtAssert_True(result[1][4] == 10.0f, "result[1][4] == 10.0f");
    UtAssert_True(result[2][4] == 10.0f, "result[2][4] == 10.0f");
    UtAssert_True(result[3][4] == 10.0f, "result[3][4] == 10.0f");
    UtAssert_True(result[4][4] == 10.0f, "result[4][4] == 10.0f");
    UtAssert_True(result[5][4] == 10.0f, "result[5][4] == 10.0f");
    UtAssert_True(result[6][4] == 10.0f, "result[6][4] == 10.0f");
    UtAssert_True(result[7][4] == 10.0f, "result[7][4] == 10.0f");
    UtAssert_True(result[8][4] == 10.0f, "result[8][4] == 10.0f");
    UtAssert_True(result[9][4] == 10.0f, "result[9][4] == 10.0f");

    UtAssert_True(result[0][5] == 12.0f, "result[0][5] == 12.0f");
    UtAssert_True(result[1][5] == 12.0f, "result[1][5] == 12.0f");
    UtAssert_True(result[2][5] == 12.0f, "result[2][5] == 12.0f");
    UtAssert_True(result[3][5] == 12.0f, "result[3][5] == 12.0f");
    UtAssert_True(result[4][5] == 12.0f, "result[4][5] == 12.0f");
    UtAssert_True(result[5][5] == 12.0f, "result[5][5] == 12.0f");
    UtAssert_True(result[6][5] == 12.0f, "result[6][5] == 12.0f");
    UtAssert_True(result[7][5] == 12.0f, "result[7][5] == 12.0f");
    UtAssert_True(result[8][5] == 12.0f, "result[8][5] == 12.0f");
    UtAssert_True(result[9][5] == 12.0f, "result[9][5] == 12.0f");

    UtAssert_True(result[0][6] == 14.0f, "result[0][6] == 14.0f");
    UtAssert_True(result[1][6] == 14.0f, "result[1][6] == 14.0f");
    UtAssert_True(result[2][6] == 14.0f, "result[2][6] == 14.0f");
    UtAssert_True(result[3][6] == 14.0f, "result[3][6] == 14.0f");
    UtAssert_True(result[4][6] == 14.0f, "result[4][6] == 14.0f");
    UtAssert_True(result[5][6] == 14.0f, "result[5][6] == 14.0f");
    UtAssert_True(result[6][6] == 14.0f, "result[6][6] == 14.0f");
    UtAssert_True(result[7][6] == 14.0f, "result[7][6] == 14.0f");
    UtAssert_True(result[8][6] == 14.0f, "result[8][6] == 14.0f");
    UtAssert_True(result[9][6] == 14.0f, "result[9][6] == 14.0f");

    UtAssert_True(result[0][7] == 16.0f, "result[0][7] == 16.0f");
    UtAssert_True(result[1][7] == 16.0f, "result[1][7] == 16.0f");
    UtAssert_True(result[2][7] == 16.0f, "result[2][7] == 16.0f");
    UtAssert_True(result[3][7] == 16.0f, "result[3][7] == 16.0f");
    UtAssert_True(result[4][7] == 16.0f, "result[4][7] == 16.0f");
    UtAssert_True(result[5][7] == 16.0f, "result[5][7] == 16.0f");
    UtAssert_True(result[6][7] == 16.0f, "result[6][7] == 16.0f");
    UtAssert_True(result[7][7] == 16.0f, "result[7][7] == 16.0f");
    UtAssert_True(result[8][7] == 16.0f, "result[8][7] == 16.0f");
    UtAssert_True(result[9][7] == 16.0f, "result[9][7] == 16.0f");

    UtAssert_True(result[0][8] == 18.0f, "result[0][8] == 18.0f");
    UtAssert_True(result[1][8] == 18.0f, "result[1][8] == 18.0f");
    UtAssert_True(result[2][8] == 18.0f, "result[2][8] == 18.0f");
    UtAssert_True(result[3][8] == 18.0f, "result[3][8] == 18.0f");
    UtAssert_True(result[4][8] == 18.0f, "result[4][8] == 18.0f");
    UtAssert_True(result[5][8] == 18.0f, "result[5][8] == 18.0f");
    UtAssert_True(result[6][8] == 18.0f, "result[6][8] == 18.0f");
    UtAssert_True(result[7][8] == 18.0f, "result[7][8] == 18.0f");
    UtAssert_True(result[8][8] == 18.0f, "result[8][8] == 18.0f");
    UtAssert_True(result[9][8] == 18.0f, "result[9][8] == 18.0f");

    UtAssert_True(result[0][9] == 20.0f, "result[0][9] == 20.0f");
    UtAssert_True(result[1][9] == 20.0f, "result[1][9] == 20.0f");
    UtAssert_True(result[2][9] == 20.0f, "result[2][9] == 20.0f");
    UtAssert_True(result[3][9] == 20.0f, "result[3][9] == 20.0f");
    UtAssert_True(result[4][9] == 20.0f, "result[4][9] == 20.0f");
    UtAssert_True(result[5][9] == 20.0f, "result[5][9] == 20.0f");
    UtAssert_True(result[6][9] == 20.0f, "result[6][9] == 20.0f");
    UtAssert_True(result[7][9] == 20.0f, "result[7][9] == 20.0f");
    UtAssert_True(result[8][9] == 20.0f, "result[8][9] == 20.0f");
    UtAssert_True(result[9][9] == 20.0f, "result[9][9] == 20.0f");
}


void Test_Matrix10F10_Addition(void)
{
    math::Matrix10F10 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    
    math::Matrix10F10 result;
    result.Zero();
    
    result = matrixA + matrixB;

    UtAssert_True(result[0][0] == 2.0f, "result[0][0] == 2.0f");
    UtAssert_True(result[0][1] == 4.0f, "result[0][1] == 4.0f");
    UtAssert_True(result[0][2] == 6.0f, "result[0][2] == 6.0f");
    UtAssert_True(result[0][3] == 8.0f, "result[0][3] == 8.0f");
    UtAssert_True(result[0][4] == 10.0f, "result[0][4] == 10.0f");
    UtAssert_True(result[0][5] == 12.0f, "result[0][5] == 12.0f");
    UtAssert_True(result[0][6] == 14.0f, "result[0][6] == 14.0f");
    UtAssert_True(result[0][7] == 16.0f, "result[0][7] == 16.0f");
    UtAssert_True(result[0][8] == 18.0f, "result[0][8] == 18.0f");
    UtAssert_True(result[0][9] == 20.0f, "result[0][9] == 20.0f");

    UtAssert_True(result[1][0] == 2.0f, "result[1][0] == 2.0f");
    UtAssert_True(result[1][1] == 4.0f, "result[1][1] == 4.0f");
    UtAssert_True(result[1][2] == 6.0f, "result[1][2] == 6.0f");
    UtAssert_True(result[1][3] == 8.0f, "result[1][3] == 8.0f");
    UtAssert_True(result[1][4] == 10.0f, "result[1][4] == 10.0f");
    UtAssert_True(result[1][5] == 12.0f, "result[1][5] == 12.0f");
    UtAssert_True(result[1][6] == 14.0f, "result[1][6] == 14.0f");
    UtAssert_True(result[1][7] == 16.0f, "result[1][7] == 16.0f");
    UtAssert_True(result[1][8] == 18.0f, "result[1][8] == 18.0f");
    UtAssert_True(result[1][9] == 20.0f, "result[1][9] == 20.0f");

    UtAssert_True(result[2][0] == 2.0f, "result[2][0] == 2.0f");
    UtAssert_True(result[2][1] == 4.0f, "result[2][1] == 4.0f");
    UtAssert_True(result[2][2] == 6.0f, "result[2][2] == 6.0f");
    UtAssert_True(result[2][3] == 8.0f, "result[2][3] == 8.0f");
    UtAssert_True(result[2][4] == 10.0f, "result[2][4] == 10.0f");
    UtAssert_True(result[2][5] == 12.0f, "result[2][5] == 12.0f");
    UtAssert_True(result[2][6] == 14.0f, "result[2][6] == 14.0f");
    UtAssert_True(result[2][7] == 16.0f, "result[2][7] == 16.0f");
    UtAssert_True(result[2][8] == 18.0f, "result[2][8] == 18.0f");
    UtAssert_True(result[2][9] == 20.0f, "result[2][9] == 20.0f");

    UtAssert_True(result[3][0] == 2.0f, "result[3][0] == 2.0f");
    UtAssert_True(result[3][1] == 4.0f, "result[3][1] == 4.0f");
    UtAssert_True(result[3][2] == 6.0f, "result[3][2] == 6.0f");
    UtAssert_True(result[3][3] == 8.0f, "result[3][3] == 8.0f");
    UtAssert_True(result[3][4] == 10.0f, "result[3][4] == 10.0f");
    UtAssert_True(result[3][5] == 12.0f, "result[3][5] == 12.0f");
    UtAssert_True(result[3][6] == 14.0f, "result[3][6] == 14.0f");
    UtAssert_True(result[3][7] == 16.0f, "result[3][7] == 16.0f");
    UtAssert_True(result[3][8] == 18.0f, "result[3][8] == 18.0f");
    UtAssert_True(result[3][9] == 20.0f, "result[3][9] == 20.0f");

    UtAssert_True(result[4][0] == 2.0f, "result[4][0] == 2.0f");
    UtAssert_True(result[4][1] == 4.0f, "result[4][1] == 4.0f");
    UtAssert_True(result[4][2] == 6.0f, "result[4][2] == 6.0f");
    UtAssert_True(result[4][3] == 8.0f, "result[4][3] == 8.0f");
    UtAssert_True(result[4][4] == 10.0f, "result[4][4] == 10.0f");
    UtAssert_True(result[4][5] == 12.0f, "result[4][5] == 12.0f");
    UtAssert_True(result[4][6] == 14.0f, "result[4][6] == 14.0f");
    UtAssert_True(result[4][7] == 16.0f, "result[4][7] == 16.0f");
    UtAssert_True(result[4][8] == 18.0f, "result[4][8] == 18.0f");
    UtAssert_True(result[4][9] == 20.0f, "result[4][9] == 20.0f");

    UtAssert_True(result[5][0] == 2.0f, "result[5][0] == 2.0f");
    UtAssert_True(result[5][1] == 4.0f, "result[5][1] == 4.0f");
    UtAssert_True(result[5][2] == 6.0f, "result[5][2] == 5.0f");
    UtAssert_True(result[5][3] == 8.0f, "result[5][3] == 6.0f");
    UtAssert_True(result[5][4] == 10.0f, "result[5][4] == 10.0f");
    UtAssert_True(result[5][5] == 12.0f, "result[5][5] == 12.0f");
    UtAssert_True(result[5][6] == 14.0f, "result[5][6] == 14.0f");
    UtAssert_True(result[5][7] == 16.0f, "result[5][7] == 16.0f");
    UtAssert_True(result[5][8] == 18.0f, "result[5][8] == 18.0f");
    UtAssert_True(result[5][9] == 20.0f, "result[5][9] == 20.0f");
    
    UtAssert_True(result[6][0] == 2.0f, "result[6][0] == 2.0f");
    UtAssert_True(result[6][1] == 4.0f, "result[6][1] == 4.0f");
    UtAssert_True(result[6][2] == 6.0f, "result[6][2] == 6.0f");
    UtAssert_True(result[6][3] == 8.0f, "result[6][3] == 8.0f");
    UtAssert_True(result[6][4] == 10.0f, "result[6][4] == 10.0f");
    UtAssert_True(result[6][5] == 12.0f, "result[6][5] == 12.0f");
    UtAssert_True(result[6][6] == 14.0f, "result[6][6] == 14.0f");
    UtAssert_True(result[6][7] == 16.0f, "result[6][7] == 16.0f");
    UtAssert_True(result[6][8] == 18.0f, "result[6][8] == 18.0f");
    UtAssert_True(result[6][9] == 20.0f, "result[6][9] == 20.0f");

    UtAssert_True(result[7][0] == 2.0f, "result[7][0] == 2.0f");
    UtAssert_True(result[7][1] == 4.0f, "result[7][1] == 4.0f");
    UtAssert_True(result[7][2] == 6.0f, "result[7][2] == 6.0f");
    UtAssert_True(result[7][3] == 8.0f, "result[7][3] == 8.0f");
    UtAssert_True(result[7][4] == 10.0f, "result[7][4] == 10.0f");
    UtAssert_True(result[7][5] == 12.0f, "result[7][5] == 12.0f");
    UtAssert_True(result[7][6] == 14.0f, "result[7][6] == 14.0f");
    UtAssert_True(result[7][7] == 16.0f, "result[7][7] == 16.0f");
    UtAssert_True(result[7][8] == 18.0f, "result[7][8] == 18.0f");
    UtAssert_True(result[7][9] == 20.0f, "result[7][9] == 20.0f");
    
    UtAssert_True(result[8][0] == 2.0f, "result[8][0] == 2.0f");
    UtAssert_True(result[8][1] == 4.0f, "result[8][1] == 4.0f");
    UtAssert_True(result[8][2] == 6.0f, "result[8][2] == 6.0f");
    UtAssert_True(result[8][3] == 8.0f, "result[8][3] == 8.0f");
    UtAssert_True(result[8][4] == 10.0f, "result[8][4] == 10.0f");
    UtAssert_True(result[8][5] == 12.0f, "result[8][5] == 12.0f");
    UtAssert_True(result[8][6] == 14.0f, "result[8][6] == 14.0f");
    UtAssert_True(result[8][7] == 16.0f, "result[8][7] == 16.0f");
    UtAssert_True(result[8][8] == 18.0f, "result[8][8] == 18.0f");
    UtAssert_True(result[8][9] == 20.0f, "result[8][9] == 20.0f");

    UtAssert_True(result[9][0] == 2.0f, "result[9][0] == 2.0f");
    UtAssert_True(result[9][1] == 4.0f, "result[9][1] == 4.0f");
    UtAssert_True(result[9][2] == 6.0f, "result[9][2] == 6.0f");
    UtAssert_True(result[9][3] == 8.0f, "result[9][3] == 8.0f");
    UtAssert_True(result[9][4] == 10.0f, "result[9][4] == 10.0f");
    UtAssert_True(result[9][5] == 12.0f, "result[9][5] == 12.0f");
    UtAssert_True(result[9][6] == 14.0f, "result[9][6] == 14.0f");
    UtAssert_True(result[9][7] == 16.0f, "result[9][7] == 16.0f");
    UtAssert_True(result[9][8] == 18.0f, "result[9][8] == 18.0f");
    UtAssert_True(result[9][9] == 20.0f, "result[9][9] == 20.0f");
}


void Test_Matrix10F10_Addition_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {0.179666, 0.144571, 0.747482, -0.722892, -0.925839, -0.457412, 0.168106, 0.968630, 0.634842, 0.516967},
        {0.056125, 0.725200, -0.942587, -0.001594, -0.984500, 0.252873, -0.003418, -0.142864, -0.524193, 0.881262},
        {-0.002672, -0.264325, 0.037265, 0.309501, 0.519310, 0.667355, -0.785511, 0.163071, -0.551418, 0.873829},
        {-0.109458, -0.605451, 0.524236, 0.021206, 0.321386, -0.697930, -0.397675, -0.163126, -0.855118, 0.666390},
        {-0.507523, -0.123070, 0.909000, 0.842746, -0.164934, 0.123438, 0.308745, -0.196633, -0.172482, -0.432825},
        {-0.983191, -0.201888, 0.841957, -0.087203, 0.191870, 0.317164, 0.975524, 0.698010, -0.648346, 0.353546},
        {-0.853064, 0.996708, -0.214448, 0.889954, -0.077199, 0.658908, 0.077461, 0.340994, 0.076359, 0.667246},
        {-0.035521, -0.516563, 0.640894, 0.162324, -0.880917, -0.904260, 0.562704, -0.658502, -0.425704, 0.923991},
        {-0.703051, -0.942352, -0.301119, -0.541107, 0.902601, 0.517083, -0.638108, -0.931732, -0.721571, 0.180325},
        {-0.729673, -0.370774, 0.276857, 0.979410, -0.849365, 0.873644, 0.400936, 0.480219, 0.769611, 0.104613}
    );

    math::Matrix10F10 B (
        {-0.732638, 0.677182, -0.090140, -0.630700, 0.394060, 0.514624, 0.167200, -0.771817, 0.593405, -0.493569},
        {-0.116883, -0.168195, -0.535768, -0.700879, -0.341365, 0.192578, -0.942416, 0.065586, -0.832430, 0.182226},
        {0.603287, -0.917805, 0.164536, 0.794889, -0.392162, 0.317962, -0.752424, 0.196463, 0.994648, 0.938141},
        {0.477347, 0.338530, -0.966380, -0.003603, 0.507891, 0.800017, 0.194538, -0.110735, -0.538464, -0.237566},
        {-0.846312, 0.175984, 0.494335, 0.737161, 0.833833, -0.310350, -0.785475, -0.441792, 0.063995, -0.036555},
        {-0.127824, 0.652017, -0.470956, 0.486490, 0.776529, -0.222457, -0.990262, 0.543860, 0.780890, -0.041994},
        {0.882815, 0.134727, -0.920224, 0.508368, 0.924677, -0.001117, -0.249968, 0.802251, -0.671236, 0.818378},
        {-0.927061, -0.003667, -0.727817, 0.970924, 0.428807, 0.741323, -0.327868, 0.577781, 0.991202, 0.180071},
        {0.214995, 0.317800, 0.134971, -0.257577, -0.187220, 0.976788, 0.012378, -0.354227, -0.962644, 0.706517},
        {0.805240, -0.546397, -0.780105, -0.862507, 0.746282, -0.149149, -0.337957, -0.185482, 0.851464, -0.981568}
    );

    math::Matrix10F10 expected (
        {-0.552972, 0.821753, 0.657341, -1.353592, -0.531778, 0.057211, 0.335306, 0.196814, 1.228248, 0.023397},
        {-0.060758, 0.557005, -1.478355, -0.702473, -1.325865, 0.445451, -0.945834, -0.077278, -1.356623, 1.063488},
        {0.600615, -1.182130, 0.201801, 1.104390, 0.127147, 0.985317, -1.537935, 0.359535, 0.443230, 1.811970},
        {0.367888, -0.266921, -0.442145, 0.017603, 0.829277, 0.102087, -0.203138, -0.273861, -1.393582, 0.428824},
        {-1.353834, 0.052914, 1.403336, 1.579907, 0.668898, -0.186912, -0.476730, -0.638425, -0.108487, -0.469380},
        {-1.111015, 0.450130, 0.371001, 0.399287, 0.968399, 0.094708, -0.014738, 1.241870, 0.132543, 0.311552},
        {0.029751, 1.131435, -1.134672, 1.398322, 0.847479, 0.657792, -0.172508, 1.143245, -0.594877, 1.485624},
        {-0.962582, -0.520230, -0.086924, 1.133249, -0.452110, -0.162937, 0.234836, -0.080721, 0.565497, 1.104062},
        {-0.488056, -0.624551, -0.166148, -0.798685, 0.715381, 1.493870, -0.625730, -1.285959, -1.684215, 0.886842},
        {0.075567, -0.917171, -0.503248, 0.116903, -0.103083, 0.724495, 0.062979, 0.294738, 1.621076, -0.876955}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = A + B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}



void Test_Matrix10F10_Subtraction(void)
{
    math::Matrix10F10 matrixA(
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f}
    );
    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    
    math::Matrix10F10 result;
    result.Zero();

    result = matrixA - matrixB;

    UtAssert_True(result[0][0] == 2.0f, "result[0][0] == 2.0f");
    UtAssert_True(result[0][1] == 4.0f, "result[0][1] == 4.0f");
    UtAssert_True(result[0][2] == 6.0f, "result[0][2] == 6.0f");
    UtAssert_True(result[0][3] == 8.0f, "result[0][3] == 8.0f");
    UtAssert_True(result[0][4] == 10.0f, "result[0][4] == 10.0f");
    UtAssert_True(result[0][5] == 12.0f, "result[0][5] == 12.0f");
    UtAssert_True(result[0][6] == 14.0f, "result[0][6] == 14.0f");
    UtAssert_True(result[0][7] == 16.0f, "result[0][7] == 16.0f");
    UtAssert_True(result[0][8] == 18.0f, "result[0][8] == 18.0f");
    UtAssert_True(result[0][9] == 20.0f, "result[0][9] == 20.0f");

    UtAssert_True(result[1][0] == 2.0f, "result[1][0] == 2.0f");
    UtAssert_True(result[1][1] == 4.0f, "result[1][1] == 4.0f");
    UtAssert_True(result[1][2] == 6.0f, "result[1][2] == 6.0f");
    UtAssert_True(result[1][3] == 8.0f, "result[1][3] == 8.0f");
    UtAssert_True(result[1][4] == 10.0f, "result[1][4] == 10.0f");
    UtAssert_True(result[1][5] == 12.0f, "result[1][5] == 12.0f");
    UtAssert_True(result[1][6] == 14.0f, "result[1][6] == 14.0f");
    UtAssert_True(result[1][7] == 16.0f, "result[1][7] == 16.0f");
    UtAssert_True(result[1][8] == 18.0f, "result[1][8] == 18.0f");
    UtAssert_True(result[1][9] == 20.0f, "result[1][9] == 20.0f");

    UtAssert_True(result[2][0] == 2.0f, "result[2][0] == 2.0f");
    UtAssert_True(result[2][1] == 4.0f, "result[2][1] == 4.0f");
    UtAssert_True(result[2][2] == 6.0f, "result[2][2] == 6.0f");
    UtAssert_True(result[2][3] == 8.0f, "result[2][3] == 8.0f");
    UtAssert_True(result[2][4] == 10.0f, "result[2][4] == 10.0f");
    UtAssert_True(result[2][5] == 12.0f, "result[2][5] == 12.0f");
    UtAssert_True(result[2][6] == 14.0f, "result[2][6] == 14.0f");
    UtAssert_True(result[2][7] == 16.0f, "result[2][7] == 16.0f");
    UtAssert_True(result[2][8] == 18.0f, "result[2][8] == 18.0f");
    UtAssert_True(result[2][9] == 20.0f, "result[2][9] == 20.0f");

    UtAssert_True(result[3][0] == 2.0f, "result[3][0] == 2.0f");
    UtAssert_True(result[3][1] == 4.0f, "result[3][1] == 4.0f");
    UtAssert_True(result[3][2] == 6.0f, "result[3][2] == 6.0f");
    UtAssert_True(result[3][3] == 8.0f, "result[3][3] == 8.0f");
    UtAssert_True(result[3][4] == 10.0f, "result[3][4] == 10.0f");
    UtAssert_True(result[3][5] == 12.0f, "result[3][5] == 12.0f");
    UtAssert_True(result[3][6] == 14.0f, "result[3][6] == 14.0f");
    UtAssert_True(result[3][7] == 16.0f, "result[3][7] == 16.0f");
    UtAssert_True(result[3][8] == 18.0f, "result[3][8] == 18.0f");
    UtAssert_True(result[3][9] == 20.0f, "result[3][9] == 20.0f");

    UtAssert_True(result[4][0] == 2.0f, "result[4][0] == 2.0f");
    UtAssert_True(result[4][1] == 4.0f, "result[4][1] == 4.0f");
    UtAssert_True(result[4][2] == 6.0f, "result[4][2] == 6.0f");
    UtAssert_True(result[4][3] == 8.0f, "result[4][3] == 8.0f");
    UtAssert_True(result[4][4] == 10.0f, "result[4][4] == 10.0f");
    UtAssert_True(result[4][5] == 12.0f, "result[4][5] == 12.0f");
    UtAssert_True(result[4][6] == 14.0f, "result[4][6] == 14.0f");
    UtAssert_True(result[4][7] == 16.0f, "result[4][7] == 16.0f");
    UtAssert_True(result[4][8] == 18.0f, "result[4][8] == 18.0f");
    UtAssert_True(result[4][9] == 20.0f, "result[4][9] == 20.0f");

    UtAssert_True(result[5][0] == 2.0f, "result[5][0] == 2.0f");
    UtAssert_True(result[5][1] == 4.0f, "result[5][1] == 4.0f");
    UtAssert_True(result[5][2] == 6.0f, "result[5][2] == 5.0f");
    UtAssert_True(result[5][3] == 8.0f, "result[5][3] == 6.0f");
    UtAssert_True(result[5][4] == 10.0f, "result[5][4] == 10.0f");
    UtAssert_True(result[5][5] == 12.0f, "result[5][5] == 12.0f");
    UtAssert_True(result[5][6] == 14.0f, "result[5][6] == 14.0f");
    UtAssert_True(result[5][7] == 16.0f, "result[5][7] == 16.0f");
    UtAssert_True(result[5][8] == 18.0f, "result[5][8] == 18.0f");
    UtAssert_True(result[5][9] == 20.0f, "result[5][9] == 20.0f");
    
    UtAssert_True(result[6][0] == 2.0f, "result[6][0] == 2.0f");
    UtAssert_True(result[6][1] == 4.0f, "result[6][1] == 4.0f");
    UtAssert_True(result[6][2] == 6.0f, "result[6][2] == 6.0f");
    UtAssert_True(result[6][3] == 8.0f, "result[6][3] == 8.0f");
    UtAssert_True(result[6][4] == 10.0f, "result[6][4] == 10.0f");
    UtAssert_True(result[6][5] == 12.0f, "result[6][5] == 12.0f");
    UtAssert_True(result[6][6] == 14.0f, "result[6][6] == 14.0f");
    UtAssert_True(result[6][7] == 16.0f, "result[6][7] == 16.0f");
    UtAssert_True(result[6][8] == 18.0f, "result[6][8] == 18.0f");
    UtAssert_True(result[6][9] == 20.0f, "result[6][9] == 20.0f");

    UtAssert_True(result[7][0] == 2.0f, "result[7][0] == 2.0f");
    UtAssert_True(result[7][1] == 4.0f, "result[7][1] == 4.0f");
    UtAssert_True(result[7][2] == 6.0f, "result[7][2] == 6.0f");
    UtAssert_True(result[7][3] == 8.0f, "result[7][3] == 8.0f");
    UtAssert_True(result[7][4] == 10.0f, "result[7][4] == 10.0f");
    UtAssert_True(result[7][5] == 12.0f, "result[7][5] == 12.0f");
    UtAssert_True(result[7][6] == 14.0f, "result[7][6] == 14.0f");
    UtAssert_True(result[7][7] == 16.0f, "result[7][7] == 16.0f");
    UtAssert_True(result[7][8] == 18.0f, "result[7][8] == 18.0f");
    UtAssert_True(result[7][9] == 20.0f, "result[7][9] == 20.0f");
    
    UtAssert_True(result[8][0] == 2.0f, "result[8][0] == 2.0f");
    UtAssert_True(result[8][1] == 4.0f, "result[8][1] == 4.0f");
    UtAssert_True(result[8][2] == 6.0f, "result[8][2] == 6.0f");
    UtAssert_True(result[8][3] == 8.0f, "result[8][3] == 8.0f");
    UtAssert_True(result[8][4] == 10.0f, "result[8][4] == 10.0f");
    UtAssert_True(result[8][5] == 12.0f, "result[8][5] == 12.0f");
    UtAssert_True(result[8][6] == 14.0f, "result[8][6] == 14.0f");
    UtAssert_True(result[8][7] == 16.0f, "result[8][7] == 16.0f");
    UtAssert_True(result[8][8] == 18.0f, "result[8][8] == 18.0f");
    UtAssert_True(result[8][9] == 20.0f, "result[8][9] == 20.0f");

    UtAssert_True(result[9][0] == 2.0f, "result[9][0] == 2.0f");
    UtAssert_True(result[9][1] == 4.0f, "result[9][1] == 4.0f");
    UtAssert_True(result[9][2] == 6.0f, "result[9][2] == 6.0f");
    UtAssert_True(result[9][3] == 8.0f, "result[9][3] == 8.0f");
    UtAssert_True(result[9][4] == 10.0f, "result[9][4] == 10.0f");
    UtAssert_True(result[9][5] == 12.0f, "result[9][5] == 12.0f");
    UtAssert_True(result[9][6] == 14.0f, "result[9][6] == 14.0f");
    UtAssert_True(result[9][7] == 16.0f, "result[9][7] == 16.0f");
    UtAssert_True(result[9][8] == 18.0f, "result[9][8] == 18.0f");
    UtAssert_True(result[9][9] == 20.0f, "result[9][9] == 20.0f");
}


void Test_Matrix10F10_Subtraction_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {-0.280585, 0.358652, 0.875160, -0.244432, -0.672686, -0.996879, -0.326359, 0.793831, 0.845490, -0.851505},
        {0.750725, 0.763608, 0.335869, -0.293064, 0.087447, -0.730769, 0.067280, -0.323202, 0.279664, -0.346842},
        {0.876635, -0.807576, 0.812151, -0.423070, 0.892625, 0.089660, -0.901225, 0.008843, -0.063175, -0.128410},
        {-0.837959, -0.782241, 0.932642, -0.234311, -0.560682, 0.447501, -0.566675, 0.226227, -0.463346, 0.234635},
        {-0.234419, -0.410483, -0.563053, -0.738757, -0.159455, 0.455663, 0.036211, 0.845156, 0.100906, 0.182909},
        {-0.177923, -0.708330, 0.682605, -0.746577, -0.566884, 0.616453, -0.560970, 0.813328, -0.043767, -0.945375},
        {-0.539119, 0.521983, 0.567694, -0.753971, 0.929494, -0.467019, -0.390536, 0.641112, -0.526395, 0.262510},
        {-0.163396, 0.925446, -0.550913, -0.575536, -0.620110, 0.263711, 0.445571, -0.954921, 0.457402, 0.231121},
        {-0.427421, -0.697796, 0.964990, 0.400138, -0.182922, 0.356918, 0.706984, -0.002558, 0.890627, 0.158658},
        {-0.125247, 0.390720, -0.938202, 0.266416, 0.881269, 0.003037, -0.971813, -0.345386, 0.240726, 0.359844}
    );

    math::Matrix10F10 B (
        {0.370077, -0.470577, -0.683725, 0.000685, -0.185449, -0.786095, 0.708685, -0.604233, 0.001060, 0.277068},
        {0.624677, 0.023028, 0.592676, -0.827204, 0.053118, -0.157891, -0.946970, -0.617744, -0.983535, 0.251699},
        {0.185321, -0.019398, -0.569673, 0.038078, 0.487700, 0.539477, -0.006242, 0.862676, -0.994474, 0.961028},
        {-0.756612, -0.401314, -0.490887, 0.121065, 0.146651, 0.006622, 0.172282, -0.951477, 0.601484, -0.991583},
        {0.514681, 0.330061, 0.876548, -0.926783, 0.380076, 0.135288, 0.521703, -0.849442, -0.692335, -0.281295},
        {0.241678, 0.606423, 0.586852, -0.281384, -0.692362, -0.533774, -0.833053, -0.526130, -0.547785, -0.586980},
        {-0.638276, 0.356691, 0.774464, 0.652604, 0.045884, 0.351540, -0.554514, 0.679126, 0.767900, -0.868605},
        {-0.647774, -0.537335, 0.940350, 0.026064, 0.567381, 0.899449, 0.808212, 0.497956, 0.821240, 0.483021},
        {0.398444, 0.227927, 0.179345, -0.581107, -0.352437, 0.388851, 0.608718, 0.892763, 0.791818, 0.204052},
        {-0.697278, 0.063478, -0.716489, 0.089741, 0.561539, 0.363583, -0.210833, -0.256689, 0.341640, 0.409876}
    );

    math::Matrix10F10 expected (
        {-0.650662, 0.829229, 1.558885, -0.245117, -0.487238, -0.210784, -1.035043, 1.398064, 0.844430, -1.128573},
        {0.126048, 0.740580, -0.256806, 0.534139, 0.034329, -0.572878, 1.014251, 0.294542, 1.263199, -0.598541},
        {0.691314, -0.788178, 1.381824, -0.461148, 0.404925, -0.449817, -0.894983, -0.853834, 0.931299, -1.089438},
        {-0.081346, -0.380927, 1.423529, -0.355376, -0.707333, 0.440879, -0.738957, 1.177704, -1.064831, 1.226218},
        {-0.749100, -0.740544, -1.439601, 0.188026, -0.539531, 0.320375, -0.485492, 1.694598, 0.793241, 0.464204},
        {-0.419601, -1.314754, 0.095753, -0.465193, 0.125478, 1.150227, 0.272083, 1.339458, 0.504018, -0.358396},
        {0.099157, 0.165292, -0.206770, -1.406574, 0.883610, -0.818559, 0.163978, -0.038014, -1.294295, 1.131115},
        {0.484378, 1.462782, -1.491262, -0.601599, -1.187491, -0.635739, -0.362641, -1.452877, -0.363838, -0.251900},
        {-0.825865, -0.925723, 0.785645, 0.981245, 0.169515, -0.031934, 0.098266, -0.895321, 0.098809, -0.045394},
        {0.572031, 0.327242, -0.221713, 0.176675, 0.319731, -0.360546, -0.760980, -0.088697, -0.100914, -0.050033}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = A - B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}


void Test_Matrix10F10_Mult_10F10(void)
{
    math::Matrix10F10 matrixA(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = matrixA * matrixB;

    UtAssert_True(result[0][0] == 55.0f, "result[0][0] == 55.0f");
    UtAssert_True(result[0][1] == 110.0f, "result[0][1] == 110.0f");
    UtAssert_True(result[0][2] == 165.0f, "result[0][2] == 165.0f");
    UtAssert_True(result[0][3] == 220.0f, "result[0][3] == 220.0f");
    UtAssert_True(result[0][4] == 275.0f, "result[0][4] == 275.0f");
    UtAssert_True(result[0][5] == 330.0f, "result[0][5] == 330.0f");
    UtAssert_True(result[0][6] == 385.0f, "result[0][6] == 385.0f");
    UtAssert_True(result[0][7] == 440.0f, "result[0][7] == 440.0f");
    UtAssert_True(result[0][8] == 495.0f, "result[0][8] == 495.0f");
    UtAssert_True(result[0][9] == 550.0f, "result[0][9] == 550.0f");

    UtAssert_True(result[1][0] == 55.0f, "result[1][0] == 55.0f");
    UtAssert_True(result[1][1] == 110.0f, "result[1][1] == 110.0f");
    UtAssert_True(result[1][2] == 165.0f, "result[1][2] == 165.0f");
    UtAssert_True(result[1][3] == 220.0f, "result[1][3] == 220.0f");
    UtAssert_True(result[1][4] == 275.0f, "result[1][4] == 275.0f");
    UtAssert_True(result[1][5] == 330.0f, "result[1][5] == 330.0f");
    UtAssert_True(result[1][6] == 385.0f, "result[1][6] == 385.0f");
    UtAssert_True(result[1][7] == 440.0f, "result[1][7] == 440.0f");
    UtAssert_True(result[1][8] == 495.0f, "result[1][8] == 495.0f");
    UtAssert_True(result[1][9] == 550.0f, "result[1][9] == 550.0f");

    UtAssert_True(result[2][0] == 55.0f, "result[2][0] == 55.0f");
    UtAssert_True(result[2][1] == 110.0f, "result[2][1] == 110.0f");
    UtAssert_True(result[2][2] == 165.0f, "result[2][2] == 165.0f");
    UtAssert_True(result[2][3] == 220.0f, "result[2][3] == 220.0f");
    UtAssert_True(result[2][4] == 275.0f, "result[2][4] == 275.0f");
    UtAssert_True(result[2][5] == 330.0f, "result[2][5] == 330.0f");
    UtAssert_True(result[2][6] == 385.0f, "result[2][6] == 385.0f");
    UtAssert_True(result[2][7] == 440.0f, "result[2][7] == 440.0f");
    UtAssert_True(result[2][8] == 495.0f, "result[2][8] == 495.0f");
    UtAssert_True(result[2][9] == 550.0f, "result[2][9] == 550.0f");

    UtAssert_True(result[3][0] == 55.0f, "result[3][0] == 55.0f");
    UtAssert_True(result[3][1] == 110.0f, "result[3][1] == 110.0f");
    UtAssert_True(result[3][2] == 165.0f, "result[3][2] == 165.0f");
    UtAssert_True(result[3][3] == 220.0f, "result[3][3] == 220.0f");
    UtAssert_True(result[3][4] == 275.0f, "result[3][4] == 275.0f");
    UtAssert_True(result[3][5] == 330.0f, "result[3][5] == 330.0f");
    UtAssert_True(result[3][6] == 385.0f, "result[3][6] == 385.0f");
    UtAssert_True(result[3][7] == 440.0f, "result[3][7] == 440.0f");
    UtAssert_True(result[3][8] == 495.0f, "result[3][8] == 495.0f");
    UtAssert_True(result[3][9] == 550.0f, "result[3][9] == 550.0f");

    UtAssert_True(result[4][0] == 55.0f, "result[4][0] == 55.0f");
    UtAssert_True(result[4][1] == 110.0f, "result[4][1] == 110.0f");
    UtAssert_True(result[4][2] == 165.0f, "result[4][2] == 165.0f");
    UtAssert_True(result[4][3] == 220.0f, "result[4][3] == 220.0f");
    UtAssert_True(result[4][4] == 275.0f, "result[4][4] == 275.0f");
    UtAssert_True(result[4][5] == 330.0f, "result[4][5] == 330.0f");
    UtAssert_True(result[4][6] == 385.0f, "result[4][6] == 385.0f");
    UtAssert_True(result[4][7] == 440.0f, "result[4][7] == 440.0f");
    UtAssert_True(result[4][8] == 495.0f, "result[4][8] == 495.0f");
    UtAssert_True(result[4][9] == 550.0f, "result[4][9] == 550.0f");

    UtAssert_True(result[5][0] == 55.0f, "result[5][0] == 55.0f");
    UtAssert_True(result[5][1] == 110.0f, "result[5][1] == 110.0f");
    UtAssert_True(result[5][2] == 165.0f, "result[5][2] == 165.0f");
    UtAssert_True(result[5][3] == 220.0f, "result[5][3] == 220.0f");
    UtAssert_True(result[5][4] == 275.0f, "result[5][4] == 275.0f");
    UtAssert_True(result[5][5] == 330.0f, "result[5][5] == 330.0f");
    UtAssert_True(result[5][6] == 385.0f, "result[5][6] == 385.0f");
    UtAssert_True(result[5][7] == 440.0f, "result[5][7] == 440.0f");
    UtAssert_True(result[5][8] == 495.0f, "result[5][8] == 495.0f");
    UtAssert_True(result[5][9] == 550.0f, "result[5][9] == 550.0f");
    
    UtAssert_True(result[6][0] == 55.0f, "result[6][0] == 55.0f");
    UtAssert_True(result[6][1] == 110.0f, "result[6][1] == 110.0f");
    UtAssert_True(result[6][2] == 165.0f, "result[6][2] == 165.0f");
    UtAssert_True(result[6][3] == 220.0f, "result[6][3] == 220.0f");
    UtAssert_True(result[6][4] == 275.0f, "result[6][4] == 275.0f");
    UtAssert_True(result[6][5] == 330.0f, "result[6][5] == 330.0f");
    UtAssert_True(result[6][6] == 385.0f, "result[6][6] == 385.0f");
    UtAssert_True(result[6][7] == 440.0f, "result[6][7] == 440.0f");
    UtAssert_True(result[6][8] == 495.0f, "result[6][8] == 495.0f");
    UtAssert_True(result[6][9] == 550.0f, "result[6][9] == 550.0f");

    UtAssert_True(result[7][0] == 55.0f, "result[7][0] == 55.0f");
    UtAssert_True(result[7][1] == 110.0f, "result[7][1] == 110.0f");
    UtAssert_True(result[7][2] == 165.0f, "result[7][2] == 165.0f");
    UtAssert_True(result[7][3] == 220.0f, "result[7][3] == 220.0f");
    UtAssert_True(result[7][4] == 275.0f, "result[7][4] == 275.0f");
    UtAssert_True(result[7][5] == 330.0f, "result[7][5] == 330.0f");
    UtAssert_True(result[7][6] == 385.0f, "result[7][6] == 385.0f");
    UtAssert_True(result[7][7] == 440.0f, "result[7][7] == 440.0f");
    UtAssert_True(result[7][8] == 495.0f, "result[7][8] == 495.0f");
    UtAssert_True(result[7][9] == 550.0f, "result[7][9] == 550.0f");
    
    UtAssert_True(result[8][0] == 55.0f, "result[8][0] == 55.0f");
    UtAssert_True(result[8][1] == 110.0f, "result[8][1] == 110.0f");
    UtAssert_True(result[8][2] == 165.0f, "result[8][2] == 165.0f");
    UtAssert_True(result[8][3] == 220.0f, "result[8][3] == 220.0f");
    UtAssert_True(result[8][4] == 275.0f, "result[8][4] == 275.0f");
    UtAssert_True(result[8][5] == 330.0f, "result[8][5] == 330.0f");
    UtAssert_True(result[8][6] == 385.0f, "result[8][6] == 385.0f");
    UtAssert_True(result[8][7] == 440.0f, "result[8][7] == 440.0f");
    UtAssert_True(result[8][8] == 495.0f, "result[8][8] == 495.0f");
    UtAssert_True(result[8][9] == 550.0f, "result[8][9] == 550.0f");

    UtAssert_True(result[9][0] == 55.0f, "result[9][0] == 55.0f");
    UtAssert_True(result[9][1] == 110.0f, "result[9][1] == 110.0f");
    UtAssert_True(result[9][2] == 165.0f, "result[9][2] == 165.0f");
    UtAssert_True(result[9][3] == 220.0f, "result[9][3] == 220.0f");
    UtAssert_True(result[9][4] == 275.0f, "result[9][4] == 275.0f");
    UtAssert_True(result[9][5] == 330.0f, "result[9][5] == 330.0f");
    UtAssert_True(result[9][6] == 385.0f, "result[9][6] == 385.0f");
    UtAssert_True(result[9][7] == 440.0f, "result[9][7] == 440.0f");
    UtAssert_True(result[9][8] == 495.0f, "result[9][8] == 495.0f");
    UtAssert_True(result[9][9] == 550.0f, "result[9][9] == 550.0f");
}



void Test_Matrix10F10_Mult_10F10_Sparse(void)
{
    int i, j = 0;

    math::Matrix10F10 matrixA(
        {0.000000, 0.000000, 0.000000, 0.057048, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.057048, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.682515, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, -0.682515},
        {0.000000, 0.000000, 0.000000, 0.478725, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.478725, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.644076, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, -0.644076},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.015341, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, -0.015341}
    );
    math::Matrix10F10 matrixB(
        {8.025486, 0.000000, 0.000000, 0.000274, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 8.025486, 0.000000, 0.000000, 0.000274, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 4.001574, 0.000000, 0.000000, 0.001984, 0.000000, 0.000000, 0.000000, 3.999728},
        {0.000274, 0.000000, 0.000000, 0.002296, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000274, 0.000000, 0.000000, 0.002296, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.001984, 0.000000, 0.000000, 0.011900, 0.000000, 0.000000, 0.000000, 0.000242},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000004, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000004, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000004, 0.000000},
        {0.000000, 0.000000, 3.999728, 0.000000, 0.000000, 0.000242, 0.000000, 0.000000, 0.000000, 3.999687}
    );

    math::Matrix10F10 expected(
        {0.000016, 0.000000, 0.000000, 0.000131, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000016, 0.000000, 0.000000, 0.000131, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.001260, 0.000000, 0.000000, 0.001189, 0.000000, 0.000000, 0.000000, 0.000028},
        {0.000131, 0.000000, 0.000000, 0.001099, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000131, 0.000000, 0.000000, 0.001099, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.001189, 0.000000, 0.000000, 0.001122, 0.000000, 0.000000, 0.000000, 0.000027},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
        {0.000000, 0.000000, 0.000028, 0.000000, 0.000000, 0.000027, 0.000000, 0.000000, 0.000000, 0.000001}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = matrixA * matrixB;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");
        }
    }
}


void Test_Matrix10F10_Mult_10F10_Random(void)
{
    int i, j = 0;

    math::Matrix10F10 A (
        {0.452948, 0.929453, 0.842306, 0.355999, 0.329895, -0.306065, -0.647885, 0.722080, -0.587544, 0.279602},
        {-0.691942, -0.835140, 0.642385, -0.726119, -0.147096, -0.095589, -0.072547, 0.480662, 0.061523, -0.877248},
        {0.038969, -0.138658, 0.008403, 0.689789, 0.612973, -0.318041, -0.164313, 0.044066, -0.497408, -0.537275},
        {-0.848522, 0.222503, 0.721558, -0.939795, 0.269809, -0.751912, -0.534864, 0.442233, 0.424278, 0.029079},
        {0.460631, -0.411957, -0.743317, -0.784048, -0.116183, 0.963600, -0.577038, 0.117763, 0.886940, 0.026590},
        {-0.574719, 0.503906, 0.483235, -0.675209, -0.932671, -0.360550, 0.990219, 0.391760, 0.510115, -0.742654},
        {-0.776980, 0.468063, 0.626067, 0.310392, -0.201322, 0.333710, 0.240480, -0.226120, 0.446957, -0.440740},
        {-0.101475, -0.661607, -0.084414, -0.258928, -0.047524, -0.657419, 0.548404, 0.990710, 0.629234, 0.998603},
        {-0.131297, -0.454053, 0.152022, -0.549311, 0.161766, -0.641173, 0.509195, 0.093799, -0.468341, -0.545576},
        {0.944580, 0.901562, -0.969141, -0.317679, 0.871896, 0.156580, 0.285337, -0.773026, -0.208677, 0.023482}
    );

    math::Matrix10F10 B (
        {0.231824, -0.882919, -0.905541, -0.407294, -0.415265, -0.192061, -0.025309, 0.016739, -0.811828, 0.469484},
        {-0.330263, -0.953647, -0.882717, -0.215803, 0.493277, 0.189193, -0.562762, -0.676062, -0.574328, -0.281961},
        {-0.450818, -0.193805, 0.010014, -0.835606, 0.652821, 0.151390, 0.248931, -0.960650, 0.858464, 0.107999},
        {-0.027039, 0.592397, -0.551389, 0.649390, 0.362375, 0.144137, 0.414711, -0.524653, 0.916994, 0.017452},
        {0.401054, 0.962462, 0.171429, -0.618303, -0.036966, 0.556488, -0.999888, 0.714112, -0.473123, 0.432509},
        {-0.039983, -0.700817, 0.134110, 0.586253, 0.280155, -0.959068, -0.470871, 0.915910, 0.210859, -0.912422},
        {0.116016, -0.081057, -0.167553, -0.043573, -0.743522, -0.603427, 0.009076, 0.804919, 0.317343, -0.790645},
        {0.661024, -0.572454, 0.564489, -0.343186, 0.596610, 0.906289, 0.244173, -0.377157, 0.705371, 0.078381},
        {0.950619, -0.173952, 0.974223, -0.871648, 0.338080, -0.640112, -0.591303, 0.847490, 0.842984, -0.887705},
        {-0.912226, 0.849553, 0.043689, 0.382538, -0.903287, 0.914781, 0.244685, 0.986827, -0.241957, -0.882019}
    );

    math::Matrix10F10 expected (
        {-0.858213, -0.727731, -1.446981, -0.841608, 1.312643, 2.422035, 0.223311, -2.677320, -0.331815, 1.313502},
        {0.958316, -0.247121, 2.037639, -1.062357, 1.164191, -0.385174, 0.404046, -0.928947, 1.556581, 0.805092},
        {0.318276, 0.935851, -0.686374, 0.109589, 0.524719, 0.679110, 0.073976, -1.229769, 0.020301, 1.674447},
        {0.175274, 0.368144, 1.796663, -2.010444, 1.150680, 1.528680, -0.370225, -1.069784, 0.525336, 0.458446},
        {1.343801, -1.273713, 1.509103, -0.128193, -0.114476, -1.469251, -1.122001, 2.480271, -0.595090, -1.036339},
        {0.677352, -2.135932, 0.764277, -1.257961, 0.832250, -1.240050, 0.294877, -1.107788, 1.538371, -0.995915},
        {-0.014057, -0.467681, 0.384028, -0.277079, 1.411173, -1.094109, -0.340166, -0.709136, 1.749886, -1.031165},
        {0.652980, 1.125818, 1.845513, -0.799892, -1.121551, 1.525951, 0.722736, 1.612940, 1.197985, -1.090740},
        {0.329904, 0.322100, 0.253373, -0.663048, -0.443033, 0.166556, 0.380009, -0.585629, -0.252620, 1.229917},
        {0.012459, -0.489053, -2.001698, 0.020674, -1.448800, -0.586034, -1.906818, 1.637565, -3.423723, 0.191627}
    );

    math::Matrix10F10 result;
    result.Zero();

    result = A * B;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            UtAssert_True(fabs(result[i][j] - expected[i][j]) < 0.00001f, "fabs(result[i][j] - expected[i][j]) < 0.00001f");

        }
    }
}


void Test_Matrix10F10_PlusEquals(void)
{
    int i, j = 0;

    math::Matrix10F10 result(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    result += matrixB;

    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if(0 == j)
            {
                UtAssert_True(result[i][j] == 2.0f, "result[i][j] == 2.0f");
            }
            else if (1 == j)
            {
                UtAssert_True(result[i][j] == 4.0f, "result[i][j] == 4.0f");
            }
            else if (2 == j)
            {
                UtAssert_True(result[i][j] == 6.0f, "result[i][j] == 6.0f");
            }
            else if (3 == j)
            {
                UtAssert_True(result[i][j] == 8.0f, "result[i][j] == 8.0f");
            }
            else if (4 == j)
            {
                UtAssert_True(result[i][j] == 10.0f, "result[i][j] == 10.0f");
            }
            else if (5 == j)
            {
                UtAssert_True(result[i][j] == 12.0f, "result[i][j] == 12.0f");
            }
            else if (6 == j)
            {
                UtAssert_True(result[i][j] == 14.0f, "result[i][j] == 14.0f");
            }
            else if (7 == j)
            {
                UtAssert_True(result[i][j] == 16.0f, "result[i][j] == 16.0f");
            }
            else if (8 == j)
            {
                UtAssert_True(result[i][j] == 18.0f, "result[i][j] == 18.0f");
            }
            else if (9 == j)
            {
                UtAssert_True(result[i][j] == 20.0f, "result[i][j] == 20.0f");
            }
        }
    }
}


void Test_Matrix10F10_MinusEquals(void)
{
    int i, j = 0;

    math::Matrix10F10 result(
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f},
            {3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f}
    );

    math::Matrix10F10 matrixB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );

    result -= matrixB;

    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if(0 == j)
            {
                UtAssert_True(result[i][j] == 2.0f, "result[i][j] == 0.0f");
            }
            else if (1 == j)
            {
                UtAssert_True(result[i][j] == 4.0f, "result[i][j] == 4.0f");
            }
            else if (2 == j)
            {
                UtAssert_True(result[i][j] == 6.0f, "result[i][j] == 6.0f");
            }
            else if (3 == j)
            {
                UtAssert_True(result[i][j] == 8.0f, "result[i][j] == 8.0f");
            }
            else if (4 == j)
            {
                UtAssert_True(result[i][j] == 10.0f, "result[i][j] == 10.0f");
            }
            else if (5 == j)
            {
                UtAssert_True(result[i][j] == 12.0f, "result[i][j] == 12.0f");
            }
            else if (6 == j)
            {
                UtAssert_True(result[i][j] == 14.0f, "result[i][j] == 14.0f");
            }
            else if (7 == j)
            {
                UtAssert_True(result[i][j] == 16.0f, "result[i][j] == 16.0f");
            }
            else if (8 == j)
            {
                UtAssert_True(result[i][j] == 18.0f, "result[i][j] == 18.0f");
            }
            else if (9 == j)
            {
                UtAssert_True(result[i][j] == 20.0f, "result[i][j] == 20.0f");
            }
        }
    }
}
