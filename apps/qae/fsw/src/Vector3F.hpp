#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include "cfe.h"

namespace math
{

class Vector3F
{
private:

protected:
	static const int SIZE = 3;
	float data[SIZE];
	float nan;

public:
	Vector3F();
	Vector3F(float X, float Y, float Z);
	~Vector3F();
	float& operator [] (uint32 i);
	float operator [] (uint32 i) const;
	float Length(void) const;
    float LengthSquared(void) const;
	void Zero(void);
	const Vector3F operator+(const Vector3F &vecIn) const;
	const Vector3F operator-(const Vector3F &vecIn) const;
	const Vector3F operator%(const Vector3F &vecIn) const;
	const Vector3F operator*(const float scalar) const;
	const Vector3F operator/(const float scalar) const;
	float operator*(const Vector3F &vecIn) const;
	const Vector3F operator-() const;
	const Vector3F EMult(const Vector3F &vecIn) const;
    const Vector3F EDivide(const Vector3F &v) const;
	void Constrain(uint32 i, float min, float max);
    Vector3F Normalized(void);
	void Normalize(void);
};

}

#endif
