#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include "cfe.h"

namespace math
{

class Vector3F
{
private:
	static const int SIZE = 3;
	float data[SIZE];
	float nan;

public:
	Vector3F(float X, float Y, float Z);
	~Vector3F();
	float& operator [] (uint32 i);
	float operator [] (uint32 i) const;
	float length(void) const;
	void zero(void);
	Vector3F operator+(const Vector3F &vecIn);
	Vector3F operator-(const Vector3F &vecIn);
	Vector3F operator%(const Vector3F &vecIn);
	Vector3F operator*(const float scalar);
	Vector3F operator/(const float scalar);
	float operator*(const Vector3F &vecIn);
	Vector3F operator-() const;
	Vector3F();

protected:

};

}

#endif
