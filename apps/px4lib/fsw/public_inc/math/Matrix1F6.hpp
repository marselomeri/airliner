#ifndef MATRIX1F6_HPP
#define MATRIX1F6_HPP


#include "cfe.h"
#include "Vector6F.hpp"
#include "Matrix1F1.hpp"
#include "Matrix6F1.hpp"

namespace math
{

/* Forward declare 6F*/
class Vector6F;
/* Forward declare 6F1 */
//class Matrix6F1;

class Matrix1F6
{
private:
    static const int ROWS = 1;
    static const int COLS = 6;
    Vector6F data[ROWS];
    Vector6F nan;

public:
    Matrix1F6();
    Matrix1F6(Vector6F m0);
    ~Matrix1F6();
    Vector6F& operator [] (uint32 i);
    Vector6F operator [] (uint32 i) const;
    Matrix1F1 operator*(const Matrix6F1 &matIn);
    void Zero(void);

protected:

};

}

#endif
