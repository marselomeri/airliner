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

#include "Matrix4F4_test.hpp"
#include <math/Matrix4F4.hpp>

#include "utassert.h"
#include <float.h>


void Test_Matrix4F4_Constructor(void)
{
	math::Matrix4F4 matrix(
			{1.0f, 2.0f, 3.0f, 4.0f},
			{5.0f, 6.0f, 7.0f, 8.0f},
			{9.0f, 10.0f, 11.0f, 12.0f},
			{13.0f, 14.0f, 15.0f, 16.0f}
	);

	/* Verify results */
	UtAssert_True(matrix[0][0] == 1.0f, "matrix[0][0] == 1.0f");
	UtAssert_True(matrix[0][1] == 2.0f, "matrix[0][1] == 2.0f");
	UtAssert_True(matrix[0][2] == 3.0f, "matrix[0][2] == 3.0f");
	UtAssert_True(matrix[0][3] == 4.0f, "matrix[0][3] == 4.0f");
	UtAssert_True(matrix[1][0] == 5.0f, "matrix[1][0] == 5.0f");
	UtAssert_True(matrix[1][1] == 6.0f, "matrix[1][1] == 6.0f");
	UtAssert_True(matrix[1][2] == 7.0f, "matrix[1][2] == 7.0f");
	UtAssert_True(matrix[1][3] == 8.0f, "matrix[1][3] == 8.0f");
	UtAssert_True(matrix[2][0] == 9.0f, "matrix[2][0] == 9.0f");
	UtAssert_True(matrix[2][1] == 10.0f, "matrix[2][1] == 10.0f");
	UtAssert_True(matrix[2][2] == 11.0f, "matrix[2][2] == 11.0f");
	UtAssert_True(matrix[2][3] == 12.0f, "matrix[2][3] == 12.0f");
	UtAssert_True(matrix[3][0] == 13.0f, "matrix[3][0] == 13.0f");
	UtAssert_True(matrix[3][1] == 14.0f, "matrix[3][1] == 14.0f");
	UtAssert_True(matrix[3][2] == 15.0f, "matrix[3][2] == 15.0f");
	UtAssert_True(matrix[3][3] == 16.0f, "matrix[3][3] == 16.0f");
}


void Test_Matrix4F4_IndexOutOfBounds(void)
{
	math::Matrix4F4 matrix(
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.0f, 6.0f, 7.0f, 8.0f},
		{9.0f, 10.0f, 11.0f, 12.0f},
		{13.0f, 14.0f, 15.0f, 16.0f}
	);

	/* Verify results */
	UtAssert_True(isnan(matrix[3][4]), "matrix[3][4] == NAN");
	UtAssert_True(isnan(matrix[4][0]), "matrix[4][0] == NAN");
}


void Test_Matrix4F4_ArrayOperator(void)
{
	math::Matrix4F4 matrix(
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.0f, 6.0f, 7.0f, 8.0f},
		{9.0f, 10.0f, 11.0f, 12.0f},
		{13.0f, 14.0f, 15.0f, 16.0f}
	);
	float nanResultA = matrix[4][0];
	float nanResultB = matrix[3][4];

    UtAssert_True(isnan(matrix[4][0]), "matrix[4][0] == NAN");
    UtAssert_True(isnan(matrix[3][4]), "matrix[3][4] == NAN");

    UtAssert_True(isnan(nanResultA), "NAN == matrix[4][0]");
    UtAssert_True(isnan(nanResultB), "NAN == matrix[3][4]");
}


void Test_Matrix4F4_NegateOperator(void)
{
//	/* vectorActual = vectorA - vectorB */
//	math::Matrix4F4 vectorA(1.5f, 2.5f, 3.5f, 4.5f);
//	math::Matrix4F4 vectorActual = -vectorA;
//
//	/* Verify results */
//	UtAssert_True(vectorActual[0] == -9.0, "vectorActual[0] == vectorA[0] - vectorB[0]");
//	UtAssert_True(vectorActual[1] == -18.0, "vectorActual[1] == vectorA[1] - vectorB[1]");
//	UtAssert_True(vectorActual[2] == -27.0, "vectorActual[2] == vectorA[2] - vectorB[2]");
//	UtAssert_True(vectorActual[3] == -27.0, "vectorActual[3] == vectorA[3] - vectorB[3]");
}


