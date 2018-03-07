#ifndef MATRIX10F1_HPP
#define MATRIX10F1_HPP


#include "cfe.h"
#include "Vector10F.hpp"
#include "Vector1F.hpp"
#include "Matrix1F10.hpp"
#include "Matrix1F1.hpp"
#include "Matrix10F10.hpp"

namespace math
{

/* Forward declare 1F10 */
class Matrix1F10;
/* Forward declare 10F10 */
class Matrix10F10;

class Matrix10F1
{
private:
    static const int SIZE = 10;
    Vector1F data[SIZE];
    Vector1F nan[SIZE];

public:
    Matrix10F1();
    Matrix10F1(Vector1F m0, Vector1F m1, Vector1F m2, Vector1F m3, Vector1F m4,
               Vector1F m5, Vector1F m6, Vector1F m7, Vector1F m8, Vector1F m9);
    ~Matrix10F1();
    Vector1F& operator [] (uint32 i);
    Vector1F operator [] (uint32 i) const;
    Matrix10F1 operator*(const Matrix1F1 & matIn);
    Matrix10F10 operator*(const Matrix1F10 & matIn);
    Matrix10F1 operator*(const Vector1F & vecIn);
    Vector10F ToVector(void);
    Matrix1F10 Transpose(void);
    void Zero(void);

protected:

};

}

#endif
