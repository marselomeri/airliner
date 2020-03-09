/*
 ** cFE includes
 */
#include <string.h>
#include "common_types.h"
#include "osapi.h"
#include "cfe_psp.h"
#include "cfe_psp_config.h"



int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_WriteToCDS(void *PtrToDataToWrite, uint32 CDSOffset,
        uint32 NumBytes)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset,
        uint32 NumBytes)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea,
        uint32 *SizeOfUserArea)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment,
        uint32 *SizeOfKernelSegment)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment,
        uint32 *SizeOfCFESegment)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



/******************************************************************************
 **  Function: CFE_PSP_InitCDS
 **
 **  Purpose: This function is used by the ES startup code to initialize the
 **            Critical Data store area
 **
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */
int32 CFE_PSP_InitCDS(uint32 RestartType)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



/******************************************************************************
 **  Function: CFE_PSP_InitESResetArea
 **
 **  Purpose:
 **    This function is used by the ES startup code to initialize the
 **     ES Reset Area.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */
int32 CFE_PSP_InitResetArea(uint32 RestartType)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



/******************************************************************************
 **  Function: CFE_PSP_InitVolatileDiskMem
 **
 **  Purpose:
 **   This function is used by the ES startup code to initialize the memory
 **   used by the volatile disk. On a desktop/posix platform this is currently
 **   a no-op, because the volatile disk is being mapped to the desktop.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */
int32 CFE_PSP_InitVolatileDiskMem(uint32 RestartType)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;

}




/******************************************************************************
 **  Function: CFE_PSP_InitUserReservedArea
 **
 **  Purpose:
 **    This function is used by the ES startup code to initialize the
 **      ES user reserved area.
 **
 **  Arguments:
 **    (none)
 **
 **  Return:
 **    (none)
 */
int32 CFE_PSP_InitUserReservedArea(uint32 RestartType)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}
