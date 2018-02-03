#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector4F.hpp"
#include "Vector3F.hpp"
#include "Matrix3F3.hpp"
#include "Matrix4F4.hpp"

namespace math
{

class Quaternion : public Vector4F
{
public:

public:
	Quaternion(float a, float b, float c, float d);
	Quaternion(const Matrix3F3 &mat);
	~Quaternion();
	Matrix3F3 RotationMatrix(void) const;
    Vector3F Imaginary(void);
    const Quaternion operator*(const Quaternion &q) const;
    Quaternion operator/(const Quaternion &q) const;
    Vector3F Conjugate(const Vector3F &v) const;
    const Quaternion Derivative(const Vector3F &w);

protected:
	Quaternion();
};

}

#endif
