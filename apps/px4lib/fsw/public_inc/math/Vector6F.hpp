#ifndef VECTOR6F_HPP
#define VECTOR6F_HPP

#include "cfe.h"

namespace math
{

class Vector6F
{
private:
	static const int SIZE = 6;
	float data[SIZE];
	float nan;

public:
	Vector6F();
	Vector6F(float A, float B, float C, float D, float E, float F);
	~Vector6F();
	float& operator [] (uint32 i);
	float operator [] (uint32 i) const;
	float Length(void) const;
	void Zero(void);
	Vector6F operator+(const Vector6F &vecIn);
    //Vector6F operator+=(const Vector6F &vecIn);
	Vector6F operator-(const Vector6F &vecIn);
	Vector6F operator-(const Vector6F &vecIn) const;
	//Vector6F operator%(const Vector6F &vecIn);
	Vector6F operator*(const float scalar);
	Vector6F operator/(const float scalar);
	float operator*(const Vector6F &vecIn);
	Vector6F operator-() const;
    Vector6F pow(const float scalar) const;
	Vector6F EMult(const Vector6F &vecIn);
	void Constrain(uint32 i, float min, float max);
	Vector6F Normalized(void);
	void Normalize(void);
	const Vector6F EDivide(const Vector6F &v) const;

protected:

};

}

#endif
