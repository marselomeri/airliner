#include "ulr_app.h"
#include <sys/stat.h>
#include <fcntl.h>

typedef struct
{
	int FD;
} ULR_CustomData_t;

ULR_CustomData_t ULR_CustomData;

int32 ULR::InitDevice(void)
{
	int32 iStatus = CFE_SUCCESS;
	struct termios uart_config;

	OS_printf("ULR::InitDevice\n");

	ULR_CustomData.FD = open(ULR_CUSTOM_PORT_PATH, O_RDWR | O_NOCTTY);
	if (ULR_CustomData.FD < 0)
	{
		iStatus = -1;
		goto end_of_function;
	}



end_of_function:
	return iStatus;
}


int32 ULR::ReadDevice(void)
{
	OS_printf("ULR::ReadDevice\n");

	return 0;
}

