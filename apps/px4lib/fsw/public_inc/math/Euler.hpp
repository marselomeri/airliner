#ifndef EULER_HPP
#define EULER_HPP

#include "cfe.h"
#include "Vector3F.hpp"
#include "Quaternion.hpp"
#include "Matrix3F3.hpp"


namespace math
{

class Euler : public Vector3F
{

public:
	Euler();
	Euler(Matrix3F3 dcm);
	~Euler();


protected:

};

}

#endif
