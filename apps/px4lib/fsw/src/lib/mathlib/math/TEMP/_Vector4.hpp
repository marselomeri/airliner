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
 * @file Vector.hpp
 *
 * Vector class
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdio.h>
#include <math.h>
#include <string.h>

#include <platforms/ros/eigen_math.h>

#include <platforms/px4_defines.h>

#define VECTOR_ELEMENT_NUM

namespace math
{

class Vector4;

class Vector4Base
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
	Vector4Base() :
		data{},
		arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
	{

	}

	virtual ~VectorBase() {};

	/**
	 * copy ctor
	 */
	Vector4Base(const VectorBase4Base &v) :
		arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
	{
		memcpy(data, v.data, sizeof(data));
	}

	/**
	 * setting ctor
	 */
	Vector4Base(const float d[VECTOR_ELEMENT_NUM]) :
		arm_col{VECTOR_ELEMENT_NUM, 1, &data[0]}
	{
		memcpy(data, d, sizeof(data));
	}

	/**
	 * set data
	 */
	void set(const float d[VECTOR_ELEMENT_NUM]) {
		memcpy(data, d, sizeof(data));
	}

	/**
	 * access to elements by index
	 */
	float &operator()(const unsigned int i) {
		return data[i];
	}

	/**
	 * access to elements by index
	 */
	float operator()(const unsigned int i) const {
		return data[i];
	}

	/**
	 * get vector size
	 */
	unsigned int get_size() const {
		return VECTOR_ELEMENT_NUM;
	}

	/**
	 * test for equality
	 */
	bool operator ==(const Vector4 &v) const {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			if (data[i] != v.data[i])
				return false;

		return true;
	}

	/**
	 * test for inequality
	 */
	bool operator !=(const Vector4 &v) const {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			if (data[i] != v.data[i])
				return true;

		return false;
	}

	/**
	 * set to value
	 */
	const Vector4 &operator =(const Vector4 &v) {
		memcpy(data, v.data, sizeof(data));
		return *static_cast<const Vector4*>(this);
	}

	/**
	 * negation
	 */
	const Vector4 operator -(void) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = -data[i];

		return res;
	}

	/**
	 * addition
	 */
	const Vector4 operator +(const Vector4 &v) const {
		Vector4 res;

		for (unsigned int i = 0; i < Vector4Base; i++)
			res.data[i] = data[i] + v.data[i];

		return res;
	}

	/**
	 * subtraction
	 */
	const Vector4 operator -(const Vector4 &v) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = data[i] - v.data[i];

		return res;
	}

	/**
	 * uniform scaling
	 */
	const Vector4 operator *(const float num) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = data[i] * num;

		return res;
	}

	/**
	 * uniform scaling
	 */
	const Vector4 operator /(const float num) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = data[i] / num;

		return res;
	}

	/**
	 * addition
	 */
	const Vector4 &operator +=(const Vector4 &v) {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			data[i] += v.data[i];

		return *static_cast<const Vector4*>(this);
	}

	/**
	 * subtraction
	 */
	const Vector4 &operator -=(const Vector4 &v) {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			data[i] -= v.data[i];

		return *static_cast<const Vector4*>(this);
	}

	/**
	 * uniform scaling
	 */
	const Vector4 &operator *=(const float num) {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			data[i] *= num;

		return *static_cast<const Vector4*>(this);
	}

	/**
	 * uniform scaling
	 */
	const Vector4 &operator /=(const float num) {
		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			data[i] /= num;

		return *static_cast<const Vector4*>(this);
	}

	/**
	 * dot product
	 */
	float operator *(const Vector4 &v) const {
		float res = 0.0f;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res += data[i] * v.data[i];

		return res;
	}

	/**
	 * element by element multiplication
	 */
	const Vector4 emult(const Vector4 &v) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = data[i] * v.data[i];

		return res;
	}

	/**
	 * element by element division
	 */
	const Vector4 edivide(const Vector4 &v) const {
		Vector4 res;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res.data[i] = data[i] / v.data[i];

		return res;
	}

	/**
	 * gets the length of this vector squared
	 */
	float length_squared() const {
		float res = 0.0f;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res += data[i] * data[i];

		return res;
	}

	/**
	 * gets the length of this vector
	 */
	float length() const {
		float res = 0.0f;

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			res += data[i] * data[i];

		return sqrtf(res);
	}

	/**
	 * normalizes this vector
	 */
	void normalize() {
		*this /= length();
	}

	/**
	 * returns the normalized version of this vector
	 */
	Vector4 normalized() const {
		return *this / length();
	}

	/**
	 * set zero vector
	 */
	void zero(void) {
		memset(data, 0, sizeof(data));
	}

	void print(void) {
		OS_printf("[ ");

		for (unsigned int i = 0; i < VECTOR_ELEMENT_NUM; i++)
			OS_printf("%.3f\t", (double)data[i]);

		OS_printf("]\n");
	}
};


class Vector4 : public Vector4Base
{
public:
	Vector4() : Vector4Base() {}

	Vector4(const Vector4 &v) : Vector4Base(v) {}

	Vector4(const float d[VECTOR_ELEMENT_NUM]) : Vector4Base(d) {}

	/**
	 * set to value
	 */
	const Vector4 &operator =(const Vector4 &v) {
		memcpy(this->data, v.data, sizeof(this->data));
		return *this;
	}
};

class Vector2 : public VectorBase<2>
{
public:
	Vector() : VectorBase<2>() {}

	// simple copy is 1.6 times faster than memcpy
	Vector(const Vector<2> &v) : VectorBase<2>() {
		data[0] = v.data[0];
		data[1] = v.data[1];
	}

	Vector(const float d[2]) : VectorBase<2>() {
		data[0] = d[0];
		data[1] = d[1];
	}

	Vector(const float x, const float y) : VectorBase<2>() {
		data[0] = x;
		data[1] = y;
	}

	/**
	 * set data
	 */
	void set(const float d[2]) {
		data[0] = d[0];
		data[1] = d[1];
	}
#if defined(__PX4_ROS)
	/**
	 * set data from boost::array
	 */
	void set(const boost::array<float, 2ul> d) {
	set(static_cast<const float*>(d.data()));
	}
#endif
	/**
	 * set to value
	 */
	const Vector<2> &operator =(const Vector<2> &v) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		return *this;
	}

	float operator %(const Vector<2> &v) const {
		return data[0] * v.data[1] - data[1] * v.data[0];
	}
};

template <>
class __EXPORT Vector<3> : public VectorBase<3>
{
public:
	Vector() : VectorBase<3>() {}

	// simple copy is 1.6 times faster than memcpy
	Vector(const Vector<3> &v) : VectorBase<3>() {
		for (unsigned int i = 0; i < 3; i++)
			data[i] = v.data[i];
	}

	Vector(const float d[3]) : VectorBase<3>() {
		for (unsigned int i = 0; i < 3; i++)
			data[i] = d[i];
	}

	Vector(const float x, const float y, const float z) : VectorBase<3>() {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}
#if defined(__PX4_ROS)
	/**
	 * set data from boost::array
	 */
	void set(const boost::array<float, 3ul> d) {
	set(static_cast<const float*>(d.data()));
	}
#endif

	/**
	 * set data
	 */
	void set(const float d[3]) {
		for (unsigned int i = 0; i < 3; i++)
			data[i] = d[i];
	}

	/**
	 * set to value
	 */
	const Vector<3> &operator =(const Vector<3> &v) {
		for (unsigned int i = 0; i < 3; i++)
			data[i] = v.data[i];

		return *this;
	}

	Vector<3> operator %(const Vector<3> &v) const {
		return Vector<3>(
			       data[1] * v.data[2] - data[2] * v.data[1],
			       data[2] * v.data[0] - data[0] * v.data[2],
			       data[0] * v.data[1] - data[1] * v.data[0]
		       );
	}
};

template <>
class __EXPORT Vector<4> : public VectorBase<4>
{
public:
	Vector() : VectorBase() {}

	Vector(const Vector<4> &v) : VectorBase<4>() {
		for (unsigned int i = 0; i < 4; i++)
			data[i] = v.data[i];
	}

	Vector(const float d[4]) : VectorBase<4>() {
		for (unsigned int i = 0; i < 4; i++)
			data[i] = d[i];
	}

	Vector(const float x0, const float x1, const float x2, const float x3) : VectorBase() {
		data[0] = x0;
		data[1] = x1;
		data[2] = x2;
		data[3] = x3;
	}
#if defined(__PX4_ROS)
	/**
	 * set data from boost::array
	 */
	void set(const boost::array<float, 4ul> d) {
	set(static_cast<const float*>(d.data()));
	}
#endif

	/**
	 * set data
	 */
	void set(const float d[4]) {
		for (unsigned int i = 0; i < 4; i++)
			data[i] = d[i];
	}

	/**
	 * set to value
	 */
	const Vector<4> &operator =(const Vector<4> &v) {
		for (unsigned int i = 0; i < 4; i++)
			data[i] = v.data[i];

		return *this;
	}
};

}

#endif // VECTOR_HPP
