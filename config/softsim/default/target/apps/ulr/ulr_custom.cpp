#include "ulr_app.h"
#include <unistd.h>

int32 ULR::InitDevice(void)
{
	return 0;
}


int32 ULR::ReadDevice(uint8 *Buffer, uint32 *Size)
{
	*Size = 0;

	sleep(1);	

	return 0;
}
