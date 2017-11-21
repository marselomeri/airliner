#include "bat_app.h"
#include <unistd.h>

#define BAT_VOLTAGE_PATH "/sys/bus/iio/devices/iio:device0/in_voltage8_raw"
#define BAT_BATTERY1_V_DIV   (0.00694783573f)


int32 BAT::InitDevice(void)
{
	int32 ret = CFE_SUCCESS;
	FILE *FD;

	FD = fopen(BAT_VOLTAGE_PATH, "r");

	if (FD == NULL)
	{
		ret = -1;
	}
	else
	{
		fclose(FD);
	}

	return ret;
}


void BAT::CloseDevice(void)
{
}


int32 BAT::ReadDevice(float &Voltage, float &Current)
{
	int32 ret = CFE_SUCCESS;
	FILE *FD;

	FD = fopen(BAT_VOLTAGE_PATH, "r");

	if (FD == NULL)
	{
		Voltage = 0.0f;
		Current = 0.0f;
		ret = -1;
	}
	else
	{
		int ret_tmp = fscanf(FD, "%f", (float*)&Voltage);
		if(ret_tmp < 0)
		{
			ret = ret_tmp;
		}

		fclose(FD);
	}

	usleep(100000);

	Voltage *= BAT_BATTERY1_V_DIV;
	Current = 0.0f;

	return ret;
}
