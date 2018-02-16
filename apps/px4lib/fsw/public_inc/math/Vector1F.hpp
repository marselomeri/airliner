#ifndef VECTOR1F_HPP
#define VECTOR1F_HPP

#include "cfe.h"

namespace math
{

class Vector1F
{
private:
	static const int SIZE = 1;
	float data[SIZE];
	float nan;

public:
	Vector1F();
	Vector1F(float A);
	~Vector1F();
	float& operator [] (uint32 i);
	float operator [] (uint32 i) const;
	float Length(void) const;
	void Zero(void);
	Vector1F operator+(const Vector1F &vecIn);
    Vector1F operator+=(const Vector1F &vecIn);
	Vector1F operator-(const Vector1F &vecIn);
	Vector1F operator-(const Vector1F &vecIn) const;
	Vector1F operator*(const float scalar);
	Vector1F operator/(const float scalar);
	Vector1F pow(const float scalar) const;
	float operator*(const Vector1F &vecIn);
	Vector1F operator-() const;
	Vector1F EMult(const Vector1F &vecIn);
	void Constrain(uint32 i, float min, float max);
	Vector1F Normalized(void);
	void Normalize(void);
	const Vector1F EDivide(const Vector1F &v) const;

protected:

};

}

#endif
