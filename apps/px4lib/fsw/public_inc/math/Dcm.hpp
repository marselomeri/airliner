#ifndef DCM_HPP
#define DCM_HPP

#include "cfe.h"
#include "Matrix3F3.hpp"
#include "Quaternion.hpp"

#define M_DEG_TO_RAD_F		(0.01745329251994329576f)

namespace math
{

class Dcm : public Matrix3F3
{

private:

public:
	Dcm();
	Dcm(Quaternion q);
    
	~Dcm();

protected:

};

}

#endif
