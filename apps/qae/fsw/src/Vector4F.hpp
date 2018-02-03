#ifndef VECTOR4F_HPP
#define VECTOR4F_HPP

#include "cfe.h"

namespace math
{

class Vector4F
{
private:

protected:
    static const int SIZE = 4;
    float data[SIZE];
    float nan;

public:
    Vector4F();
    Vector4F(float m1, float m2, float m3, float m4);
    ~Vector4F();
    float& operator [] (uint32 i);
    float operator [] (uint32 i) const;
    float Length(void) const;
    float LengthSquared(void) const;
    void Zero(void);
    const Vector4F operator+(const Vector4F &vecIn) const;
    const Vector4F operator-(const Vector4F &vecIn) const;
    const Vector4F operator*(const float scalar) const;
    const Vector4F operator/(const float scalar) const;
    float operator*(const Vector4F &vecIn) const;
    const Vector4F operator-() const;
    const Vector4F & operator=(const Vector4F &v);
    const Vector4F EMult(const Vector4F &vecIn) const;
    void Normalize(void);
    Vector4F Normalized(void) const;

};

}

#endif
