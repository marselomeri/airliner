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
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
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
