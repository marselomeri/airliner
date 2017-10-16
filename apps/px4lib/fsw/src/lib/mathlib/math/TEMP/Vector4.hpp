/****************************************************************************
 *
 *   Copyright (C) 2013 PX4 Development Team. All rights reserved.
 *   Author: Anton Babushkin <anton.babushkin@me.com>
 *           Pavel Kirienko <pavel.kirienko@gmail.com>
 *           Lorenz Meier <lm@inf.ethz.ch>
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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 ****************************************************************************/

/**
 * @file Vector4.hpp
 *
 * Vector class
 */

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <math.h>
#include "eigen_math.h"

#define VECTOR_ELEMENT_NUM 4

namespace math
{

class Vector4
{
public:
	/**
	 * vector data
	 */
	float data[VECTOR_ELEMENT_NUM];

	/**
	 * struct for using arm_math functions, represents column vector
	 */
	eigen_matrix_instance arm_col;


	/**
	 * trivial ctor
	 * initializes elements to zero
	 */
	Vector4();

	virtual ~Vector4() {};

	/**
	 * copy ctor
	 */
	Vector4(const Vector4 &v);

	/**
	 * setting ctor
	 */
	Vector4(const float d[VECTOR_ELEMENT_NUM]);

	/**
	 * set data
	 */
	void set(const float d[VECTOR_ELEMENT_NUM]);

	/**
	 * access to elements by index
	 */
	float &operator()(const unsigned int i);

	/**
	 * access to elements by index
	 */
	float operator()(const unsigned int i) const;

	/**
	 * get vector size
	 */
	unsigned int get_size() const;

	/**
	 * test for equality
	 */
	bool operator ==(const Vector4 &v) const;

	/**
	 * test for inequality
	 */
	bool operator !=(const Vector4 &v) const;

	/**
	 * set to value
	 */
	const Vector4 &operator =(const Vector4 &v);

	/**
	 * negation
	 */
	const Vector4 operator -(void) const;

	/**
	 * addition
	 */
	const Vector4 operator +(const Vector4 &v) const;

	/**
	 * subtraction
	 */
	const Vector4 operator -(const Vector4 &v) const;

	/**
	 * uniform scaling
	 */
	const Vector4 operator *(const float num) const;

	/**
	 * uniform scaling
	 */
	const Vector4 operator /(const float num) const;

	/**
	 * addition
	 */
	const Vector4 &operator +=(const Vector4 &v);

	/**
	 * subtraction
	 */
	const Vector4 &operator -=(const Vector4 &v);

	/**
	 * uniform scaling
	 */
	const Vector4 &operator *=(const float num);

	/**
	 * uniform scaling
	 */
	const Vector4 &operator /=(const float num);

	/**
	 * dot product
	 */
	float operator *(const Vector4 &v) const;

	/**
	 * element by element multiplication
	 */
	const Vector4 emult(const Vector4 &v) const;

	/**
	 * element by element division
	 */
	const Vector4 edivide(const Vector4 &v) const;

	/**
	 * gets the length of this vector squared
	 */
	float length_squared() const;

	/**
	 * gets the length of this vector
	 */
	float length() const;

	/**
	 * normalizes this vector
	 */
	void normalize();

	/**
	 * returns the normalized version of this vector
	 */
	Vector4 normalized();

	/**
	 * set zero vector
	 */
	void zero(void);

	void print(void);
};

}

#endif // VECTOR4_HPP
