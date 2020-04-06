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

/*
**  Include Files
*/


/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */

/*
**  System Include Files
*/
#include <stdio.h>
#include <stdlib.h>

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"


/******************* Macro Definitions ***********************/

#define CFE_PSP_TIMER_TICKS_PER_SECOND       1000000     /* Resolution of the least significant 32 bits of the 64 bit
                                                           time stamp returned by OS_BSPGet_Timebase in timer ticks per second.
                                                           The timer resolution for accuracy should not be any slower than 1000000
                                                           ticks per second or 1 us per tick */
#define CFE_PSP_TIMER_LOW32_ROLLOVER         1000000     /* The number that the least significant 32 bits of the 64 bit
                                                           time stamp returned by OS_BSPGet_Timebase rolls over.  If the lower 32
                                                           bits rolls at 1 second, then the OS_BSP_TIMER_LOW32_ROLLOVER will be 1000000.
                                                           if the lower 32 bits rolls at its maximum value (2^32) then
                                                           OS_BSP_TIMER_LOW32_ROLLOVER will be 0. */

/******************************************************************************
**  Function:  CFE_PSP_GetTime()
**
**  Purpose: Gets the value of the time from the hardware
**
**  Arguments: LocalTime - where the time is returned through
******************************************************************************/

void CFE_PSP_GetTime( OS_time_t *LocalTime)
{

    /* since we don't have a hardware register to access like the mcp750,
     * we use a call to the OS to get the time */

    OS_GetLocalTime(LocalTime);

}/* end CFE_PSP_GetLocalTime */



/******************************************************************************
**  Function:  CFE_PSP_Get_Timer_Tick()
**
**  Purpose:
**    Provides a common interface to system clock tick. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**  OS system clock ticks per second
*/
uint32 CFE_PSP_Get_Timer_Tick(void)
{
   /* SUB -add function call code*/
   return (0);
}

/******************************************************************************
**  Function:  CFE_PSP_GetTimerTicksPerSecond()
**
**  Purpose:
**    Provides the resolution of the least significant 32 bits of the 64 bit
**    time stamp returned by OS_BSPGet_Timebase in timer ticks per second.
**    The timer resolution for accuracy should not be any slower than 1000000
**    ticks per second or 1 us per tick
**
**  Arguments:
**
**  Return:
**    The number of timer ticks per second of the time stamp returned
**    by CFE_PSP_Get_Timebase
*/
uint32 CFE_PSP_GetTimerTicksPerSecond(void)
{
    return(CFE_PSP_TIMER_TICKS_PER_SECOND);
}

/******************************************************************************
**  Function:  CFE_PSP_GetTimerLow32Rollover()
**
**  Purpose:
**    Provides the number that the least significant 32 bits of the 64 bit
**    time stamp returned by CFE_PSP_Get_Timebase rolls over.  If the lower 32
**    bits rolls at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000.
**    if the lower 32 bits rolls at its maximum value (2^32) then
**    CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
**
**  Arguments:
**
**  Return:
**    The number that the least significant 32 bits of the 64 bit time stamp
**    returned by CFE_PSP_Get_Timebase rolls over.
*/
uint32 CFE_PSP_GetTimerLow32Rollover(void)
{
    return(CFE_PSP_TIMER_LOW32_ROLLOVER);
}

/******************************************************************************
**  Function:  CFE_PSP_Get_Timebase()
**
**  Purpose:
**    Provides a common interface to system timebase. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**  Timebase register value
*/
void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32* Tbl)
{
   OS_time_t        time;

   OS_GetLocalTime(&time);
   *Tbu = time.seconds;
   *Tbl = time.microsecs;
}

/******************************************************************************
**  Function:  CFE_PSP_Get_Dec()
**
**  Purpose:
**    Provides a common interface to decrementer counter. This routine
**    is in the PSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**  Timebase register value
*/

uint32 CFE_PSP_Get_Dec(void)
{
   /* SUB -add function call code*/
   return(0);
}

