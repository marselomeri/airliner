#include "bat_app.h"


int32 BAT::InitDevice(void)
{
	return 0;
}


void BAT::CloseDevice(void)
{
}


int32 BAT::ReadDevice(float &Voltage, float &Current)
{
	Voltage = 0.0f;
	Current = 0.0f;

	OS_TaskDelay(100);

	return 0;
}
