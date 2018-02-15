#ifndef MATRIX6F6_HPP
#define MATRIX6F6_HPP

#include "cfe.h"
#include "Vector6F.hpp"

namespace math
{

class Matrix6F6
{
private:
	static const int SIZE = 6;
	Vector6F data[SIZE];
	Vector6F nan[SIZE];
    void getCofactor(const Matrix6F6 &mat, Matrix6F6 &temp, int p, int q, int n);
    float DeterminantRecursive(const Matrix6F6 &mat, int n);
    

public:
	Matrix6F6(Vector6F m0, Vector6F m1, Vector6F m2, Vector6F m3,
               Vector6F m4, Vector6F m5);
	~Matrix6F6();
	Vector6F& operator [] (uint32 i);
	Vector6F operator [] (uint32 i) const;
    Matrix6F6 operator+(const Matrix6F6 &matIn) const;
    Matrix6F6 Inversed(void);
    Matrix6F6 Identity(void);
    float Determinant(void);
    void Zero(void);
	Matrix6F6();

protected:

};

}

#endif
