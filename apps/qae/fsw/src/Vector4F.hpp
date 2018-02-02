#ifndef VECTOR4F_HPP
#define VECTOR4F_HPP

#include "cfe.h"

namespace math
{

class Vector4F
{
private:

public:
    Vector4F();
    Vector4F(float m1, float m2, float m3, float m4);
    ~Vector4F();
    float& operator [] (uint32 i);
    float operator [] (uint32 i) const;
    float Length(void) const;
    float LengthSquared(void) const;
    void Zero(void);
    Vector4F operator+(const Vector4F &vecIn);
    Vector4F operator-(const Vector4F &vecIn);
    Vector4F operator*(const float scalar);
    Vector4F operator/(const float scalar);
    float operator*(const Vector4F &vecIn);
    Vector4F operator-() const;

protected:
    static const int SIZE = 4;
    float data[SIZE];
    float nan;

};

}

#endif
