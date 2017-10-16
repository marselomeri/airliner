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

#include "Vector4F_test.hpp"
#include "Vector4F.hpp"

#include "utassert.h"
#include <float.h>


void Test_Vector4F_Constructor(void)
{
	math::Vector4F vector(1.0f, 2.0f, 3.0f, 4.0f);

	/* Verify results */
	UtAssert_True(vector[0] == 1.0f, "vector[0] == 1.0f");
	UtAssert_True(vector[1] == 2.0f, "vector[1] == 2.0f");
	UtAssert_True(vector[2] == 3.0f, "vector[2] == 3.0f");
	UtAssert_True(vector[3] == 4.0f, "vector[3] == 4.0f");
}


void Test_Vector4F_IndexOutOfBounds(void)
{
	math::Vector4F vector(1.0f, 2.0f, 3.0f, 4.0f);

	/* Verify results */
	UtAssert_True(vector[0] == 1.0f, "vector[0] == 1.0f");
	UtAssert_True(vector[1] == 2.0f, "vector[1] == 2.0f");
	UtAssert_True(vector[2] == 3.0f, "vector[2] == 3.0f");
	UtAssert_True(vector[3] == 4.0f, "vector[3] == 4.0f");
	UtAssert_True(isnan(vector[4]), "vector[4] == nan");
}


void Test_Vector4F_ArrayOperator(void)
{
	math::Vector4F vector(1.5f, 2.5f, 3.5f, 4.5f);
	float nanResult = vector[4];

    UtAssert_True(vector[0] == 1.5f, "vector[0] == 1.5f");
    UtAssert_True(vector[1] == 2.5f, "vector[1] == 2.5f");
    UtAssert_True(vector[2] == 3.5f, "vector[2] == 3.5f");
    UtAssert_True(vector[3] == 4.5f, "vector[3] == 4.5f");
    UtAssert_True(isnan(vector[4]), "vector[4] == NAN");

    UtAssert_True(1.5f == vector[0], "1.5f == vector[0]");
    UtAssert_True(2.5f == vector[1], "2.5f == vector[1]");
    UtAssert_True(3.5f == vector[2], "3.5f == vector[2]");
    UtAssert_True(4.5f == vector[3], "4.5f == vector[3]");
    UtAssert_True(isnan(nanResult), "NAN == vector[4]");
}


void Test_Vector4F_NegateOperator(void)
{
	/* vectorActual = vectorA - vectorB */
	math::Vector4F vectorA(1.5f, -2.5f, -3.5f, 4.5f);
	math::Vector4F vectorActual = -vectorA;

	/* Verify results */
	UtAssert_True(vectorActual[0] == -1.5, "vectorActual[0] == vectorA[0] - vectorB[0]");
	UtAssert_True(vectorActual[1] == 2.5, "vectorActual[1] == vectorA[1] - vectorB[1]");
	UtAssert_True(vectorActual[2] == 3.5, "vectorActual[2] == vectorA[2] - vectorB[2]");
	UtAssert_True(vectorActual[3] == -4.5, "vectorActual[3] == vectorA[3] - vectorB[3]");
}


