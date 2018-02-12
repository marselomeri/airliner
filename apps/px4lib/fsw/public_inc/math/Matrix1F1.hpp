#ifndef MATRIX1F1_HPP
#define MATRIX1F1_HPP


#include "cfe.h"
#include "Vector1F.hpp"

namespace math
{

class Matrix1F1
{
private:
    static const int SIZE = 1;
    Vector1F data[SIZE];
    Vector1F nan[SIZE];

public:
    Matrix1F1();
    Matrix1F1(Vector1F m0);
    ~Matrix1F1();
    Vector1F& operator [] (uint32 i);
    Vector1F operator [] (uint32 i) const;
    //Matrix1F1 Transpose(void);
    void Zero(void);

protected:

};

}

#endif
