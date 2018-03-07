#ifndef MATRIX6F1_HPP
#define MATRIX6F1_HPP


#include "cfe.h"
#include "Vector6F.hpp"
#include "Vector1F.hpp"


namespace math
{

class Matrix6F1
{
private:
    static const int SIZE = 6;
    Vector1F data[SIZE];
    Vector1F nan[SIZE];

public:
    Matrix6F1();
    Matrix6F1(Vector1F m0, Vector1F m1, Vector1F m2, Vector1F m3, Vector1F m4, Vector1F m5);
    ~Matrix6F1();
    Vector1F& operator [] (uint32 i);
    Vector1F operator [] (uint32 i) const;
    void Zero(void);

protected:

};

}

#endif
