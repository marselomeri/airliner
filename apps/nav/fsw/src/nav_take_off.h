#ifndef NAV_TAKEOFF_H
#define NAV_TAKEOFF_H

#include "nav_app.h"

class Takeoff{

public:
	Takeoff();
	~Takeoff();
	 void Launch();
	void Active(PX4_VehicleGlobalPositionMsg_t*);
	 void Kill();

private:
	void SetTakeoffPosition();

};

#endif
