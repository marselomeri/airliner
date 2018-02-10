
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
        Quaternion();
        Quaternion(float a, float b, float c, float d);
	    Quaternion(float roll, float pitch, float yaw);
	    Quaternion(const Matrix3F3 &mat);
	    ~Quaternion();
	    Matrix3F3 RotationMatrix(void) const;
        Vector3F Imaginary(void);
        Vector3F ToEuler(void) const;
	    void copyTo(float (&dst)[4]);
        const Quaternion operator*(const float scalar) const;
        const Quaternion & operator=(const Quaternion &q);
        const Quaternion operator+(const Quaternion &vecIn) const;
        const Quaternion operator-(const Quaternion &vecIn) const;
        const Quaternion operator*(const Quaternion &q) const;
        Quaternion operator/(const Quaternion &q) const;
        Vector3F Conjugate(const Vector3F &v) const;
        Vector3F ConjugateInversed(const Vector3F &v) const;
        void FromDCM(const Matrix3F3 &dcm);
        void FromYaw(float yaw);
        const Quaternion Derivative(const Vector3F &w);
    
    protected:

};

}

#endif
