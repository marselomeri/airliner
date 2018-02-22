#ifndef MATRIX1F10_HPP
#define MATRIX1F10_HPP


#include "cfe.h"
#include "Vector10F.hpp"
#include "Matrix10F10.hpp"
#include "Matrix10F1.hpp"
#include "Matrix1F1.hpp"
#include "Vector1F.hpp"

namespace math
{

/* Forward declare 10F1 */
class Matrix10F1;
/* Forward declare 10F10 */
class Matrix10F10;

class Matrix1F10
{
private:
    static const int ROWS = 1;
    static const int COLS = 10;
    Vector10F data[ROWS];
    Vector10F nan;

public:
    Matrix1F10();
    Matrix1F10(Vector10F m0);
    ~Matrix1F10();
    Vector10F& operator [] (uint32 i);
    Vector10F operator [] (uint32 i) const;
    Matrix1F10 operator*(const Matrix10F10 &matIn);
    Matrix1F1 operator*(const Matrix10F1 & matIn);
    Vector1F operator*(const Vector10F &vecIn);
    Matrix10F1 Transpose(void);
    void Zero(void);

protected:

};

}

#endif
