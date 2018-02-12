#ifndef MATRIX10F1_HPP
#define MATRIX10F1_HPP


#include "cfe.h"
#include "Vector10F.hpp"
#include "Vector1F.hpp"
#include "Matrix1F10.hpp"

namespace math
{

/* Forward declare 1F10 */
class Matrix1F10;

class Matrix10F1
{
private:
    static const int SIZE = 10;
    Vector1F data[SIZE];
    Vector1F nan[SIZE];

public:
    Matrix10F1();
    Matrix10F1(Vector10F m0);
    ~Matrix10F1();
    Vector1F& operator [] (uint32 i);
    Vector1F operator [] (uint32 i) const;
    Matrix1F10 Transpose(void);
    void Zero(void);

protected:

};

}

#endif
