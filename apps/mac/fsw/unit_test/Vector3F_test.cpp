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

#include "Vector3F_test.hpp"
#include "Vector3F.hpp"

#include "utassert.h"
#include <float.h>


void Test_Vector3F_Constructor(void)
{
	math::Vector3F vector(1.0f, 2.0f, 3.0f);

	/* Verify results */
	UtAssert_True(vector[0] == 1.0f, "vector[0] == 1.0f");
	UtAssert_True(vector[1] == 2.0f, "vector[1] == 2.0f");
	UtAssert_True(vector[2] == 3.0f, "vector[2] == 3.0f");
}


void Test_Vector3F_IndexOutOfBounds(void)
{
	math::Vector3F vector(1.0f, 2.0f, 3.0f);

	/* Verify results */
	UtAssert_True(vector[0] == 1.0f, "vector[0] == 1.0f");
	UtAssert_True(vector[1] == 2.0f, "vector[1] == 2.0f");
	UtAssert_True(vector[2] == 3.0f, "vector[2] == 3.0f");
	UtAssert_True(isnan(vector[3]), "vector[3] == nan");
}


void Test_Vector3F_Length(void)
{
	math::Vector3F vector(1.5f, 2.5f, 3.5f);
	float expectedLength = sqrtf((1.5f)*(1.5f) + (2.5f)*(2.5f) + (3.5f)*(3.5f));
    float actualLength = 4.555217f;

	/* Verify results */
    UtAssert_True(fabs(expectedLength - actualLength) <= FLT_EPSILON, "vector.Length() == expectedLength");
}


void Test_Vector3F_ArrayOperator(void)
{
	math::Vector3F vector(1.5f, 2.5f, 3.5f);
	float nanResult = vector[3];

    UtAssert_True(vector[0] == 1.5f, "vector[0] == 1.5f");
    UtAssert_True(vector[1] == 2.5f, "vector[1] == 2.5f");
    UtAssert_True(vector[2] == 3.5f, "vector[2] == 3.5f");
    UtAssert_True(isnan(vector[3]), "vector[3] == NAN");

    UtAssert_True(1.5f == vector[0], "1.5f == vector[0]");
    UtAssert_True(2.5f == vector[1], "2.5f == vector[1]");
    UtAssert_True(3.5f == vector[2], "3.5f == vector[2]");
    UtAssert_True(isnan(nanResult), "NAN == vector[3]");

}


void Test_Vector3F_AdditionOperator(void)
{
	/* vectorActual = vectorA + vectorB */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(10.5f, 20.5f, 30.5f);
	math::Vector3F vectorActual = vectorA + vectorB;

	/* Verify results */
	UtAssert_True(vectorActual[0] == 12.0, "vectorActual[0] == vectorA[0] + vectorB[0]");
	UtAssert_True(vectorActual[1] == 23.0, "vectorActual[1] == vectorA[1] + vectorB[1]");
	UtAssert_True(vectorActual[2] == 34.0, "vectorActual[2] == vectorA[2] + vectorB[2]");
}


void Test_Vector3F_SubtractionOperator(void)
{
	/* vectorActual = vectorA - vectorB */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(10.5f, 20.5f, 30.5f);
	math::Vector3F vectorActual = vectorA - vectorB;

	/* Verify results */
	UtAssert_True(vectorActual[0] == -9.0, "vectorActual[0] == vectorA[0] - vectorB[0]");
	UtAssert_True(vectorActual[1] == -18.0, "vectorActual[1] == vectorA[1] - vectorB[1]");
	UtAssert_True(vectorActual[2] == -27.0, "vectorActual[2] == vectorA[2] - vectorB[2]");
}


void Test_Vector3F_CrossProductOperator(void)
{
	/* vectorActual = vectorA % vectorB */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(10.5f, 20.5f, 30.5f);
	math::Vector3F vectorActual = vectorA % vectorB;
	math::Vector3F vectorExpected;

	/* Verify results */
	vectorExpected[0] = 4.5;
	vectorExpected[1] = -9.0;
	vectorExpected[2] = 4.5;

	UtAssert_True(vectorExpected[0] == vectorActual[0], "[0] vectorExpected == vectorA % vectorB");
	UtAssert_True(vectorExpected[1] == vectorActual[1], "[1] vectorExpected == vectorA % vectorB");
	UtAssert_True(vectorExpected[2] == vectorActual[2], "[2] vectorExpected == vectorA % vectorB");
}


void Test_Vector3F_ScalarMultiplyOperator(void)
{
	/* actual = vectorA * scalar */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	float scalar = 10.5f;
	math::Vector3F vectorActual = vectorA * scalar;
	math::Vector3F vectorExpected;

	/* Verify results */
	vectorExpected[0] = 15.75;
	vectorExpected[1] = 26.25;
	vectorExpected[2] = 36.75;

	UtAssert_True(vectorExpected[0] == vectorActual[0], "[0] vectorExpected == vectorA * scalar");
	UtAssert_True(vectorExpected[1] == vectorActual[1], "[1] vectorExpected == vectorA * scalar");
	UtAssert_True(vectorExpected[2] == vectorActual[2], "[2] vectorExpected == vectorA * scalar");
}


void Test_Vector3F_ScalarDivOperator(void)
{
	/* actual = vectorA / scalar */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	float scalar = 10.5f;
	math::Vector3F vectorActual = vectorA / scalar;
	math::Vector3F vectorExpected;

	/* Verify results */
	vectorExpected[0] = 0.142857f;
	vectorExpected[1] = 0.238095f;
	vectorExpected[2] = 0.333333f;

	UtAssert_True(fabs(vectorActual[0] - vectorExpected[0]) <= 0.00001, "[0] vectorExpected == vectorA / scalar");
	UtAssert_True(fabs(vectorActual[1] - vectorExpected[1]) <= 0.00001, "[1] vectorExpected == vectorA / scalar");
	UtAssert_True(fabs(vectorActual[2] - vectorExpected[2]) <= 0.00001, "[2] vectorExpected == vectorA / scalar");
}


void Test_Vector3F_DotProductOperator(void)
{
	/* actual = vectorA * vectorB */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(10.5f, 20.5f, 30.5f);
	float actual = vectorA * vectorB;
	float expected = 173.75;

	/* Verify results */
	UtAssert_True(actual == expected, "expected == vectorA * vectorB");
}


void Test_Vector3F_EMult(void)
{
	/* actual = vectorA / scalar */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(10.5f, 20.5f, 30.5f);
	math::Vector3F vectorActual = vectorA.EMult(vectorB);
	math::Vector3F vectorExpected;

	/* Verify results */
	vectorExpected[0] = 15.75f;
	vectorExpected[1] = 51.25f;
	vectorExpected[2] = 106.75f;

	UtAssert_True(fabs(vectorActual[0] - vectorExpected[0]) <= 0.00001, "[0] vectorExpected == vectorA.EMult(vectorB)");
	UtAssert_True(fabs(vectorActual[1] - vectorExpected[1]) <= 0.00001, "[1] vectorExpected == vectorA.EMult(vectorB)");
	UtAssert_True(fabs(vectorActual[2] - vectorExpected[2]) <= 0.00001, "[2] vectorExpected == vectorA.EMult(vectorB)");
}


void Test_Vector3F_Constrain(void)
{
	/* actual = vectorA / scalar */
	math::Vector3F vectorA(1.5f, 2.5f, 3.5f);
	math::Vector3F vectorB(-1.5f, -2.5f, -3.5f);
	math::Vector3F vectorAExpected;
	math::Vector3F vectorBExpected;

	vectorA.Constrain(0, 0.5, 1.0);
	vectorA.Constrain(1, 1.5, 2.7);
	vectorA.Constrain(2, 2.5, 3.0);

	vectorB.Constrain(0, -1.0, -0.5);
	vectorB.Constrain(1, -2.7, -1.5);
	vectorB.Constrain(2, -3.0, -2.5);

	/* Verify results */
	vectorAExpected[0] = 1.0f;
	vectorAExpected[1] = 2.5f;
	vectorAExpected[2] = 3.0f;

	vectorBExpected[0] = -1.0f;
	vectorBExpected[1] = -2.5f;
	vectorBExpected[2] = -3.0f;

	UtAssert_True(fabs(vectorA[0] - vectorAExpected[0]) <= 0.00001, "[0] vectorAExpected == vectorA.Constrain(0, min, max)");
	UtAssert_True(fabs(vectorA[1] - vectorAExpected[1]) <= 0.00001, "[1] vectorAExpected == vectorA.Constrain(1, min, max)");
	UtAssert_True(fabs(vectorA[2] - vectorAExpected[2]) <= 0.00001, "[2] vectorAExpected == vectorA.Constrain(2, min, max)");

	UtAssert_True(fabs(vectorB[0] - vectorBExpected[0]) <= 0.00001, "[0] vectorBExpected == vectorB.Constrain(0, min, max)");
	UtAssert_True(fabs(vectorB[1] - vectorBExpected[1]) <= 0.00001, "[1] vectorBExpected == vectorB.Constrain(1, min, max)");
	UtAssert_True(fabs(vectorB[2] - vectorBExpected[2]) <= 0.00001, "[2] vectorBExpected == vectorB.Constrain(2, min, max)");
}


