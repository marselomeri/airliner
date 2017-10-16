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
 * @file Vector4Base.hpp
 *
 * Vector class
 */

#include <math.h>
#include "Vector4Base.hpp"
#include <string.h>

using namespace math;

Vector4Base::Vector4Base() :
		data{},
		arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
	{

	};

/**
 * copy ctor
 */
Vector4Base::Vector4Base(const Vector4Base &v) :
	arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
{
	memcpy(data, v.data, sizeof(data));
}

/**
 * setting ctor
 */
Vector4Base::Vector4Base(const float d[VECTOR_ELEMENT_NUM]) :
	arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
{
	memcpy(data, d, sizeof(data));
}

/**
 * set data
 */
void Vector4Base::set(const float d[VECTOR_ELEMENT_NUM]) {
	memcpy(data, d, sizeof(data));
}

/**
 * access to elements by index
 */
float &Vector4Base::operator()(const unsigned int i) {
	return data[i];
}

/**
 * access to elements by index
 */
float Vector4Base::operator()(const unsigned int i) const {
	return data[i];
}

/**
 * get vector size
 */
unsigned int Vector4Base::get_size() const {
	return VECTOR_ELEMENT_NUM;
}

/**
 * test for equality
 */
bool Vector4Base::operator ==(const Vector4 &v) const {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		if (data[i] != v.data[i])
			return false;

	return true;
}

/**
 * test for inequality
 */
bool Vector4Base::operator !=(const Vector4 &v) const {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		if (data[i] != v.data[i])
			return true;

	return false;
}

/**
 * set to value
 */
const Vector4 &Vector4Base::operator =(const Vector4 &v) {
	memcpy(data, v.data, sizeof(data));
	return *static_cast<const Vector4*>(this);
}

/**
 * negation
 */
const Vector4 Vector4Base::operator -(void) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = -data[i];

	return res;
}

/**
 * addition
 */
const Vector4 Vector4Base::operator +(const Vector4 &v) const {
	Vector4 res;

	for (unsigned int i = 0; i < Vector4Base; i++)
		res.data[i] = data[i] + v.data[i];

	return res;
}

/**
 * subtraction
 */
const Vector4 Vector4Base::operator -(const Vector4 &v) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = data[i] - v.data[i];

	return res;
}

/**
 * uniform scaling
 */
const Vector4 Vector4Base::operator *(const float num) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = data[i] * num;

	return res;
}

/**
 * uniform scaling
 */
const Vector4 Vector4Base::operator /(const float num) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = data[i] / num;

	return res;
}

/**
 * addition
 */
const Vector4 &Vector4Base::operator +=(const Vector4 &v) {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		data[i] += v.data[i];

	return *static_cast<const Vector4*>(this);
}

/**
 * subtraction
 */
const Vector4 &Vector4Base::operator -=(const Vector4 &v) {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		data[i] -= v.data[i];

	return *static_cast<const Vector4*>(this);
}

/**
 * uniform scaling
 */
const Vector4 &Vector4Base::operator *=(const float num) {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		data[i] *= num;

	return *static_cast<const Vector4*>(this);
}

/**
 * uniform scaling
 */
const Vector4 &Vector4Base::operator /=(const float num) {
	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		data[i] /= num;

	return *static_cast<const Vector4*>(this);
}

/**
 * dot product
 */
float Vector4Base::operator *(const Vector4 &v) const {
	float res = 0.0f;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res += data[i] * v.data[i];

	return res;
}

/**
 * element by element multiplication
 */
const Vector4 Vector4Base::emult(const Vector4 &v) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = data[i] * v.data[i];

	return res;
}

/**
 * element by element division
 */
const Vector4 Vector4Base::edivide(const Vector4 &v) const {
	Vector4 res;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res.data[i] = data[i] / v.data[i];

	return res;
}

/**
 * gets the length of this vector squared
 */
float Vector4Base::length_squared() const {
	float res = 0.0f;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res += data[i] * data[i];

	return res;
}

/**
 * gets the length of this vector
 */
float Vector4Base::length() const {
	float res = 0.0f;

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		res += data[i] * data[i];

	return sqrtf(res);
}

/**
 * normalizes this vector
 */
void Vector4Base::normalize() {
	*this /= length();
}

/**
 * returns the normalized version of this vector
 */
Vector4 Vector4Base::normalized() const {
	return *this / length();
}

/**
 * set zero vector
 */
void Vector4Base::zero(void) {
	memset(data, 0, sizeof(data));
}

void Vector4Base::print(void) {
	OS_printf("[ ");

	for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
		OS_printf("%.3f\t", (double)data[i]);

	OS_printf("]\n");
}
