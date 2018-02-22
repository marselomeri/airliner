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

#include "Matrix6F10_test.hpp"
#include <math/Matrix6F10.hpp>
#include <math/Vector10F.hpp>
#include <math/Vector6F.hpp>

#include "utassert.h"
#include <float.h>


void Test_Matrix6F10_Constructor(void)
{
	math::Matrix6F10 matrix(
			{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			{2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f},
			{3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f},
			{4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f},
			{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
            {6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f}
	);

	/* Verify results */
	UtAssert_True(matrix[0][0] == 1.0f, "matrix[0][0] == 1.0f");
	UtAssert_True(matrix[1][0] == 2.0f, "matrix[1][0] == 2.0f");
	UtAssert_True(matrix[2][0] == 3.0f, "matrix[2][0] == 3.0f");
	UtAssert_True(matrix[3][0] == 4.0f, "matrix[3][0] == 4.0f");
	UtAssert_True(matrix[4][0] == 5.0f, "matrix[4][0] == 5.0f");
	UtAssert_True(matrix[5][0] == 6.0f, "matrix[5][0] == 6.0f");

	UtAssert_True(matrix[0][1] == 1.0f, "matrix[0][1] == 1.0f");
	UtAssert_True(matrix[1][1] == 2.0f, "matrix[1][1] == 2.0f");
	UtAssert_True(matrix[2][1] == 3.0f, "matrix[2][1] == 3.0f");
	UtAssert_True(matrix[3][1] == 4.0f, "matrix[3][1] == 4.0f");
	UtAssert_True(matrix[4][1] == 5.0f, "matrix[4][1] == 5.0f");
	UtAssert_True(matrix[5][1] == 6.0f, "matrix[5][1] == 6.0f");
    
	UtAssert_True(matrix[0][2] == 1.0f, "matrix[0][0] == 1.0f");
	UtAssert_True(matrix[1][2] == 2.0f, "matrix[1][1] == 2.0f");
	UtAssert_True(matrix[2][2] == 3.0f, "matrix[2][2] == 3.0f");
	UtAssert_True(matrix[3][2] == 4.0f, "matrix[3][3] == 4.0f");
	UtAssert_True(matrix[4][2] == 5.0f, "matrix[4][4] == 5.0f");
	UtAssert_True(matrix[5][2] == 6.0f, "matrix[5][5] == 6.0f");

	UtAssert_True(matrix[0][3] == 1.0f, "matrix[0][3] == 1.0f");
	UtAssert_True(matrix[1][3] == 2.0f, "matrix[1][3] == 2.0f");
	UtAssert_True(matrix[2][3] == 3.0f, "matrix[2][3] == 3.0f");
	UtAssert_True(matrix[3][3] == 4.0f, "matrix[3][3] == 4.0f");
	UtAssert_True(matrix[4][3] == 5.0f, "matrix[4][3] == 5.0f");
	UtAssert_True(matrix[5][3] == 6.0f, "matrix[5][3] == 6.0f");
    
	UtAssert_True(matrix[0][4] == 1.0f, "matrix[0][4] == 1.0f");
	UtAssert_True(matrix[1][4] == 2.0f, "matrix[1][4] == 2.0f");
	UtAssert_True(matrix[2][4] == 3.0f, "matrix[2][4] == 3.0f");
	UtAssert_True(matrix[3][4] == 4.0f, "matrix[3][4] == 4.0f");
	UtAssert_True(matrix[4][4] == 5.0f, "matrix[4][4] == 5.0f");
	UtAssert_True(matrix[5][4] == 6.0f, "matrix[5][4] == 6.0f");
    
	UtAssert_True(matrix[0][5] == 1.0f, "matrix[0][5] == 1.0f");
	UtAssert_True(matrix[1][5] == 2.0f, "matrix[1][5] == 2.0f");
	UtAssert_True(matrix[2][5] == 3.0f, "matrix[2][5] == 3.0f");
	UtAssert_True(matrix[3][5] == 4.0f, "matrix[3][5] == 4.0f");
	UtAssert_True(matrix[4][5] == 5.0f, "matrix[4][5] == 5.0f");
	UtAssert_True(matrix[5][5] == 6.0f, "matrix[5][5] == 6.0f");

	UtAssert_True(matrix[0][6] == 1.0f, "matrix[0][6] == 1.0f");
	UtAssert_True(matrix[1][6] == 2.0f, "matrix[1][6] == 2.0f");
	UtAssert_True(matrix[2][6] == 3.0f, "matrix[2][6] == 3.0f");
	UtAssert_True(matrix[3][6] == 4.0f, "matrix[3][6] == 4.0f");
	UtAssert_True(matrix[4][6] == 5.0f, "matrix[4][6] == 5.0f");
	UtAssert_True(matrix[5][6] == 6.0f, "matrix[5][6] == 6.0f");

	UtAssert_True(matrix[0][7] == 1.0f, "matrix[0][7] == 1.0f");
	UtAssert_True(matrix[1][7] == 2.0f, "matrix[1][7] == 2.0f");
	UtAssert_True(matrix[2][7] == 3.0f, "matrix[2][7] == 3.0f");
	UtAssert_True(matrix[3][7] == 4.0f, "matrix[3][7] == 4.0f");
	UtAssert_True(matrix[4][7] == 5.0f, "matrix[4][7] == 5.0f");
	UtAssert_True(matrix[5][7] == 6.0f, "matrix[5][7] == 6.0f");

	UtAssert_True(matrix[0][8] == 1.0f, "matrix[0][8] == 1.0f");
	UtAssert_True(matrix[1][8] == 2.0f, "matrix[1][8] == 2.0f");
	UtAssert_True(matrix[2][8] == 3.0f, "matrix[2][8] == 3.0f");
	UtAssert_True(matrix[3][8] == 4.0f, "matrix[3][8] == 4.0f");
	UtAssert_True(matrix[4][8] == 5.0f, "matrix[4][8] == 5.0f");
	UtAssert_True(matrix[5][8] == 6.0f, "matrix[5][8] == 6.0f");

	UtAssert_True(matrix[0][9] == 1.0f, "matrix[0][9] == 1.0f");
	UtAssert_True(matrix[1][9] == 2.0f, "matrix[1][9] == 2.0f");
	UtAssert_True(matrix[2][9] == 3.0f, "matrix[2][9] == 3.0f");
	UtAssert_True(matrix[3][9] == 4.0f, "matrix[3][9] == 4.0f");
	UtAssert_True(matrix[4][9] == 5.0f, "matrix[4][9] == 5.0f");
	UtAssert_True(matrix[5][9] == 6.0f, "matrix[5][9] == 6.0f");

}


void Test_Matrix6F10_IndexOutOfBounds(void)
{
    /* Note row column reversed in constructor */
	math::Matrix6F10 matrix(
			{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			{2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f},
			{3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f},
			{4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f},
			{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
            {6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f}
	);

	/* Verify results */
	UtAssert_True(isnan(matrix[6][0]), "matrix[6][0] == NAN");
	UtAssert_True(isnan(matrix[0][10]), "matrix[0][10] == NAN");
}


void Test_Matrix6F10_Mult_10F(void)
{
	math::Matrix6F10 matrixA(
			{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			{2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f},
			{3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f},
			{4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f},
			{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
            {6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f}
	);
    
    math::Vector10F vectorB(
            {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f}
    );
    
    math::Vector6F result;
    result.Zero();
    
    result = matrixA * vectorB;

    UtAssert_True(result[0] == 55.0f, "result[0] == 55.0f");
	UtAssert_True(result[1] == 110.0f, "result[1] == 110.0f");
	UtAssert_True(result[2] == 165.0f, "result[2] == 165.0f");
	UtAssert_True(result[3] == 220.0f, "result[3] == 220.0f");
	UtAssert_True(result[4] == 275.0f, "result[4] == 275.0f");
	UtAssert_True(result[5] == 330.0f, "result[5] == 330.0f");
}


void Test_Matrix6F10_Mult_10F6(void)
{
	math::Matrix6F10 matrixA(
			{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			{2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f},
			{3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f},
			{4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f},
			{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
            {6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f}
	);
    
    math::Matrix10F6 matrixB(
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
    
    math::Matrix6F6 result;
    result.Zero();
    
    result = matrixA * matrixB;

    UtAssert_True(result[0][0] == 10.0f, "result[0][0] == 10.0f");
	UtAssert_True(result[1][0] == 20.0f, "result[1][0] == 20.0f");
	UtAssert_True(result[2][0] == 30.0f, "result[2][0] == 30.0f");
	UtAssert_True(result[3][0] == 40.0f, "result[3][0] == 40.0f");
	UtAssert_True(result[4][0] == 50.0f, "result[4][0] == 50.0f");
	UtAssert_True(result[5][0] == 60.0f, "result[5][0] == 60.0f");

    UtAssert_True(result[0][1] == 20.0f, "result[0][1] == 20.0f");
	UtAssert_True(result[1][1] == 40.0f, "result[1][1] == 40.0f");
	UtAssert_True(result[2][1] == 60.0f, "result[2][1] == 60.0f");
	UtAssert_True(result[3][1] == 80.0f, "result[3][1] == 80.0f");
	UtAssert_True(result[4][1] == 100.0f, "result[4][1] == 100.0f");
	UtAssert_True(result[5][1] == 120.0f, "result[5][1] == 120.0f");

    UtAssert_True(result[0][2] == 30.0f, "result[0][2] == 30.0f");
	UtAssert_True(result[1][2] == 60.0f, "result[1][2] == 60.0f");
	UtAssert_True(result[2][2] == 90.0f, "result[2][2] == 90.0f");
	UtAssert_True(result[3][2] == 120.0f, "result[3][2] == 120.0f");
	UtAssert_True(result[4][2] == 150.0f, "result[4][2] == 150.0f");
	UtAssert_True(result[5][2] == 180.0f, "result[5][2] == 180.0f");

    UtAssert_True(result[0][3] == 40.0f, "result[0][3] == 40.0f");
	UtAssert_True(result[1][3] == 80.0f, "result[1][3] == 80.0f");
	UtAssert_True(result[2][3] == 120.0f, "result[2][3] == 120.0f");
	UtAssert_True(result[3][3] == 160.0f, "result[3][3] == 160.0f");
	UtAssert_True(result[4][3] == 200.0f, "result[4][3] == 200.0f");
	UtAssert_True(result[5][3] == 240.0f, "result[5][3] == 240.0f");

    UtAssert_True(result[0][4] == 50.0f, "result[0][4] == 50.0f");
	UtAssert_True(result[1][4] == 100.0f, "result[1][4] == 100.0f");
	UtAssert_True(result[2][4] == 150.0f, "result[2][4] == 150.0f");
	UtAssert_True(result[3][4] == 200.0f, "result[3][4] == 200.0f");
	UtAssert_True(result[4][4] == 250.0f, "result[4][4] == 250.0f");
	UtAssert_True(result[5][4] == 300.0f, "result[5][4] == 300.0f");

    UtAssert_True(result[0][5] == 60.0f, "result[0][5] == 60.0f");
	UtAssert_True(result[1][5] == 120.0f, "result[1][5] == 120.0f");
	UtAssert_True(result[2][5] == 180.0f, "result[2][5] == 180.0f");
	UtAssert_True(result[3][5] == 240.0f, "result[3][5] == 240.0f");
	UtAssert_True(result[4][5] == 300.0f, "result[4][5] == 300.0f");
	UtAssert_True(result[5][5] == 360.0f, "result[5][5] == 360.0f");
}


void Test_Matrix6F10_Mult_10F10(void)
{
	math::Matrix6F10 matrixA(
			{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			{2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f},
			{3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f},
			{4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f},
			{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
            {6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f}
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
    
    math::Matrix6F10 result;
    result.Zero();
    
    result = matrixA * matrixB;

    UtAssert_True(result[0][0] == 10.0f, "result[0][0] == 10.0f");
	UtAssert_True(result[1][0] == 20.0f, "result[1][0] == 20.0f");
	UtAssert_True(result[2][0] == 30.0f, "result[2][0] == 30.0f");
	UtAssert_True(result[3][0] == 40.0f, "result[3][0] == 40.0f");
	UtAssert_True(result[4][0] == 50.0f, "result[4][0] == 50.0f");
	UtAssert_True(result[5][0] == 60.0f, "result[5][0] == 60.0f");

    UtAssert_True(result[0][1] == 20.0f, "result[0][1] == 20.0f");
	UtAssert_True(result[1][1] == 40.0f, "result[1][1] == 40.0f");
	UtAssert_True(result[2][1] == 60.0f, "result[2][1] == 60.0f");
	UtAssert_True(result[3][1] == 80.0f, "result[3][1] == 80.0f");
	UtAssert_True(result[4][1] == 100.0f, "result[4][1] == 100.0f");
	UtAssert_True(result[5][1] == 120.0f, "result[5][1] == 120.0f");

    UtAssert_True(result[0][2] == 30.0f, "result[0][2] == 30.0f");
	UtAssert_True(result[1][2] == 60.0f, "result[1][2] == 60.0f");
	UtAssert_True(result[2][2] == 90.0f, "result[2][2] == 90.0f");
	UtAssert_True(result[3][2] == 120.0f, "result[3][2] == 120.0f");
	UtAssert_True(result[4][2] == 150.0f, "result[4][2] == 150.0f");
	UtAssert_True(result[5][2] == 180.0f, "result[5][2] == 180.0f");

    UtAssert_True(result[0][3] == 40.0f, "result[0][3] == 40.0f");
	UtAssert_True(result[1][3] == 80.0f, "result[1][3] == 80.0f");
	UtAssert_True(result[2][3] == 120.0f, "result[2][3] == 120.0f");
	UtAssert_True(result[3][3] == 160.0f, "result[3][3] == 160.0f");
	UtAssert_True(result[4][3] == 200.0f, "result[4][3] == 200.0f");
	UtAssert_True(result[5][3] == 240.0f, "result[5][3] == 240.0f");

    UtAssert_True(result[0][4] == 50.0f, "result[0][4] == 50.0f");
	UtAssert_True(result[1][4] == 100.0f, "result[1][4] == 100.0f");
	UtAssert_True(result[2][4] == 150.0f, "result[2][4] == 150.0f");
	UtAssert_True(result[3][4] == 200.0f, "result[3][4] == 200.0f");
	UtAssert_True(result[4][4] == 250.0f, "result[4][4] == 250.0f");
	UtAssert_True(result[5][4] == 300.0f, "result[5][4] == 300.0f");

    UtAssert_True(result[0][5] == 60.0f, "result[0][5] == 60.0f");
	UtAssert_True(result[1][5] == 120.0f, "result[1][5] == 120.0f");
	UtAssert_True(result[2][5] == 180.0f, "result[2][5] == 180.0f");
	UtAssert_True(result[3][5] == 240.0f, "result[3][5] == 240.0f");
	UtAssert_True(result[4][5] == 300.0f, "result[4][5] == 300.0f");
	UtAssert_True(result[5][5] == 360.0f, "result[5][5] == 360.0f");

    UtAssert_True(result[0][6] == 70.0f, "result[0][6] == 70.0f");
	UtAssert_True(result[1][6] == 140.0f, "result[1][6] == 140.0f");
	UtAssert_True(result[2][6] == 210.0f, "result[2][6] == 210.0f");
	UtAssert_True(result[3][6] == 280.0f, "result[3][6] == 280.0f");
	UtAssert_True(result[4][6] == 350.0f, "result[4][6] == 350.0f");
	UtAssert_True(result[5][6] == 420.0f, "result[5][6] == 420.0f");

    UtAssert_True(result[0][7] == 80.0f, "result[0][7] == 80.0f");
	UtAssert_True(result[1][7] == 160.0f, "result[1][7] == 160.0f");
	UtAssert_True(result[2][7] == 240.0f, "result[2][7] == 240.0f");
	UtAssert_True(result[3][7] == 320.0f, "result[3][7] == 320.0f");
	UtAssert_True(result[4][7] == 400.0f, "result[4][7] == 400.0f");
	UtAssert_True(result[5][7] == 480.0f, "result[5][7] == 480.0f");

    UtAssert_True(result[0][8] == 90.0f, "result[0][8] == 90.0f");
	UtAssert_True(result[1][8] == 180.0f, "result[1][8] == 180.0f");
	UtAssert_True(result[2][8] == 270.0f, "result[2][8] == 270.0f");
	UtAssert_True(result[3][8] == 360.0f, "result[3][8] == 360.0f");
	UtAssert_True(result[4][8] == 450.0f, "result[4][8] == 450.0f");
	UtAssert_True(result[5][8] == 540.0f, "result[5][8] == 540.0f");

    UtAssert_True(result[0][9] == 100.0f, "result[0][9] == 100.0f");
	UtAssert_True(result[1][9] == 200.0f, "result[1][9] == 200.0f");
	UtAssert_True(result[2][9] == 300.0f, "result[2][9] == 300.0f");
	UtAssert_True(result[3][9] == 400.0f, "result[3][9] == 400.0f");
	UtAssert_True(result[4][9] == 500.0f, "result[4][9] == 500.0f");
	UtAssert_True(result[5][9] == 600.0f, "result[5][9] == 600.0f");
}





