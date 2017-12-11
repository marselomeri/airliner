/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "ms5611_spi.h"
#include "ms5611_events.h"
#include "ms5611_perfids.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

typedef enum {
	MS5611_CUSTOM_UNINITIALIZED = 0;
	MS5611_CUSTOM_D1_CONV       = 1;
	MS5611_CUSTOM_D2_CONV       = 2;
} MS5611_Custom_State_t;



typedef enum {

/** \brief <tt> 'MS5611 - ' </tt>
**  \event <tt> 'MS5611 - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    MS5611_DEVICE_ERR_EID = MS5611_EVT_CNT,

/** \brief <tt> 'MS5611 - ' </tt>
**  \event <tt> 'MS5611 - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    MS5611_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    MS5611_CUSTOM_EVT_CNT
} MS5611_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
MS5611_AppCustomData_t MS5611_AppCustomData;
struct spi_ioc_transfer MS5611_SPI_Xfer[2];

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

void MS5611_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&MS5611_AppCustomData, sizeof(MS5611_AppCustomData));
}


boolean MS5611_Custom_Init()
{
    return TRUE;
}


boolean MS5611_Custom_Uninit(void)
{
    return TRUE;
}


boolean MS5611_ReadPROM(uint8 Addr, uint16 *returnVal)
{
	*returnVal = 1;

    return TRUE;
}


boolean MS5611_D1Conversion(void)
{
    return TRUE;
}


boolean MS5611_D2Conversion(void)
{
    return TRUE;
}


boolean MS5611_ReadADCResult(uint32 *returnVal)
{
    return TRUE;
}


boolean MS5611_Custom_Max_Events_Not_Reached(int32 ind)
{
    if ((ind < CFE_EVS_MAX_EVENT_FILTERS) && (ind > 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


int32 MS5611_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == MS5611_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = MS5611_DEVICE_ERR_EID;
        EventTbl[customEventCount++].Mask    = CFE_EVS_FIRST_16_STOP;
    }
    else
    {
        customEventCount = -1;
        goto end_of_function;
    }
    
end_of_function:

    return customEventCount;
}

