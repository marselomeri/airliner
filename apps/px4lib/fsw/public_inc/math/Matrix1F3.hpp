#ifndef MATRIX1F3_HPP
#define MATRIX1F3_HPP

#include "cfe.h"
#include "Vector3F.hpp"

#define M_DEG_TO_RAD_F		(0.01745329251994329576f)

namespace math
{

class Vector3F;

class Matrix1F3
{
public:

private:
	static const int SIZE = 1;
	Vector3F nan;

public:
	Matrix1F3(Vector3F m0);

	~Matrix1F3();
	Vector3F& operator [] (uint32 i);
	Vector3F operator [] (uint32 i) const;
	Matrix1F3();
	float operator*(const Vector3F &vecIn);
	void Zero(void);

protected:
	Vector3F data[SIZE];

};

}

#endif
