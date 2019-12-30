/*
 ** cFE includes
 */
#include <string.h>
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */

/*
 ** Types and prototypes for this module
 */
#include "cfe_psp.h"

/*
 ** PSP Specific defines
 */
#include "cfe_psp_config.h"

#define CFE_PSP_CDS_SIZE            CFE_ES_CDS_SIZE
#define CFE_PSP_RESET_AREA_SIZE     CFE_ES_RESET_AREA_SIZE
#define CFE_PSP_USER_RESERVED_SIZE  CFE_ES_USER_RESERVED_SIZE

/*
 ** Internal prototypes for this module
 */
int32 CFE_PSP_InitCDS(uint32 RestartType);
int32 CFE_PSP_InitResetArea(uint32 RestartType);
int32 CFE_PSP_InitVolatileDiskMem(uint32 RestartType);
int32 CFE_PSP_InitUserReservedArea(uint32 RestartType);


/*
 ** Global variables
 */
uint8 CFE_PSP_CDS[CFE_PSP_CDS_SIZE];
uint8 CFE_PSP_ResetArea[CFE_PSP_RESET_AREA_SIZE];
uint8 CFE_PSP_UserReservedArea[CFE_PSP_USER_RESERVED_SIZE];


int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    int32 return_code;

    if (SizeOfCDS == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *SizeOfCDS = CFE_PSP_CDS_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}



int32 CFE_PSP_WriteToCDS(void *PtrToDataToWrite, uint32 CDSOffset,
        uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32 return_code;

    if (PtrToDataToWrite == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE)
                && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = &CFE_PSP_CDS[CDSOffset];
            memcpy(CopyPtr, (char *) PtrToDataToWrite, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}



int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset,
        uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32 return_code;

    if (PtrToDataToRead == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE)
                && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = &CFE_PSP_CDS[CDSOffset];
            memcpy((char *) PtrToDataToRead, CopyPtr, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}



int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    int32 return_code;

    if (SizeOfResetArea == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        uint8 *ptr = CFE_PSP_ResetArea;
        memcpy(PtrToResetArea, &ptr, sizeof(PtrToResetArea));
        *SizeOfResetArea = CFE_PSP_RESET_AREA_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}



int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea,
        uint32 *SizeOfUserArea)
{
    int32 return_code;

    if (SizeOfUserArea == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        uint8 *ptr = CFE_PSP_UserReservedArea;
        memcpy(PtrToUserArea, &ptr, sizeof(PtrToUserArea));
        *SizeOfUserArea = CFE_PSP_USER_RESERVED_SIZE;
        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}



int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    int32 return_code;

    if (SizeOfVolDisk == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        memset(&(PtrToVolDisk), 0, sizeof(PtrToVolDisk));
        *SizeOfVolDisk = 0;
        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}



int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    int32 return_code;

    if (RestartType == CFE_ES_PROCESSOR_RESET)
    {
        return_code = CFE_PSP_InitCDS( CFE_ES_PROCESSOR_RESET);
        return_code = CFE_PSP_InitResetArea( CFE_ES_PROCESSOR_RESET);
        return_code = CFE_PSP_InitVolatileDiskMem( CFE_ES_PROCESSOR_RESET);
        return_code = CFE_PSP_InitUserReservedArea( CFE_ES_PROCESSOR_RESET);
    }
    else
    {
        return_code = CFE_PSP_InitCDS( CFE_ES_POWERON_RESET);
        return_code = CFE_PSP_InitResetArea( CFE_ES_POWERON_RESET);
        return_code = CFE_PSP_InitVolatileDiskMem( CFE_ES_POWERON_RESET);
        return_code = CFE_PSP_InitUserReservedArea( CFE_ES_POWERON_RESET);
    }

    return return_code;
}

int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment,
        uint32 *SizeOfKernelSegment)
{
    OS_printf("%s\n", __FUNCTION__);

	return -1;
}

int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment,
        uint32 *SizeOfCFESegment)
{
    OS_printf("%s\n", __FUNCTION__);

	return -1;
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
    memset(&(CFE_PSP_CDS[0]), 0, sizeof(CFE_PSP_CDS));

    return CFE_PSP_SUCCESS;
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
    memset(&(CFE_PSP_ResetArea[0]), 0, sizeof(CFE_PSP_ResetArea));

    return CFE_PSP_SUCCESS;
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
    int32 return_code;

    /*
     ** Here, we want to clear out the volatile ram disk contents
     ** on a power on reset
     */

    return_code = CFE_PSP_SUCCESS;
    return return_code;

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
    memset(&(CFE_PSP_UserReservedArea[0]), 0, sizeof(CFE_PSP_CDS));

    return CFE_PSP_SUCCESS;

}
