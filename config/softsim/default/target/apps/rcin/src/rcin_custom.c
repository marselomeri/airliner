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
#include "rcin_events.h"
#include "simlib.h"
#include <time.h>
#include <errno.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

typedef enum {

/** \brief <tt> 'RCIN - ' </tt>
**  \event <tt> 'RCIN - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    RCIN_DEVICE_ERR_EID = RCIN_EVT_CNT,

/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    RCIN_CUSTOM_EVT_CNT

} RCIN_CustomEventIds_t;

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/


CFE_TIME_SysTime_t RCIN_Custom_Get_Time(void);

void RCIN_Custom_InitData(void)
{
}


boolean RCIN_Custom_Init(void)
{
    return TRUE;
}


boolean RCIN_Custom_Measure(PX4_InputRcMsg_t *Measure)
{
    // error Count currently handled outside measure
    //uint16 errorCount = 0;
    int bytesRead = 0;
    boolean returnBool = TRUE;
	uint16 Channel[12];
	uint8 RSSI = 0;
	uint16 ChannelCount = 12;

    /* Null pointer check */
    if (0 == Measure)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN device read null pointer error");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Timestamp */
    Measure->Timestamp = RCIN_Custom_Get_Time();

    SIMLIB_GetRCInputs(Measure->Values, &ChannelCount, &RSSI);

    /* Channel count */
    Measure->ChannelCount = 12;
    Measure->RSSI = RSSI;
    // For now handle outside measure function call.
    //Measure->RcLostFrameCount = errorCount;
    Measure->RcTotalFrameCount = 1;
    Measure->RcPpmFrameLength = 0;
    Measure->RcFailsafe = FALSE;
    Measure->RcLost = FALSE;
    Measure->InputSource = PX4_RC_INPUT_SOURCE_PX4IO_SBUS;
    
end_of_function:
    return returnBool;
}


CFE_TIME_SysTime_t RCIN_Custom_Get_Time(void)
{
    struct timespec ts;
    int returnCode = 0;
    CFE_TIME_SysTime_t Timestamp = {0, 0};

    returnCode = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (-1 == returnCode)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN clock_gettime errno: %i", errno);
        goto end_of_function;
    }

end_of_function:
    return Timestamp;
}


boolean RCIN_Custom_Uninit(void)
{
    return TRUE;
}


boolean RCIN_Custom_Max_Events_Not_Reached(int32 ind)
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


int32 RCIN_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == RCIN_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = RCIN_DEVICE_ERR_EID;
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
