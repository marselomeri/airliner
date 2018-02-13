#include "nav_take_off.h"


Takeoff::Takeoff(){

}
Takeoff::~Takeoff(){

}

void Takeoff:: Active(PX4_VehicleGlobalPositionMsg_t* pst_ptr){
//	PX4_PositionSetpointTripletMsg_t* pst_ptr = GetPositionSetpointTripletMsg();
//	OS_printf("valid2 %llu\n",pst_ptr->Current.Timestamp);
//	OS_printf("valid2 %f\n",pst_ptr->Previous.Alt );
//	OS_printf("valid2 %lld\n",pst_ptr->Previous.Lat );
//	OS_printf("valid2 %lld\n",pst_ptr->Previous.Lon );
	OS_printf("valid2 %llu\n",pst_ptr->Timestamp );



}
