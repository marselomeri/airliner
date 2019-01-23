/****************************************************************************
*
*   Copyright (c) 2019 Windhover Labs, L.L.C. All rights reserved.
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
#include "sg33bl_events.h"
#include "sg33bl_perfids.h"
#include "sg33bl_platform_cfg.h"
#include "sg33bl_map.h"
#include "sg33bl_custom.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <time.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'SG33BL - ' </tt>
**  \event <tt> 'SG33BL - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    SG33BL_DEVICE_ERR_EID = SG33BL_EVT_CNT,

/** \brief <tt> 'SG33BL - ' </tt>
**  \event <tt> 'SG33BL - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    SG33BL_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    SG33BL_CUSTOM_EVT_CNT
} SG33BL_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
SG33BL_AppCustomData_t SG33BL_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/
boolean SG33BL_Custom_Set_Baud(const uint32 Baud);
boolean SG33BL_Custom_Max_Events_Not_Reached(int32 ind);
uint8 SG33BL_Compute_Checksum(SG33BL_Packet_t *Packet);
boolean SG33BL_Valid_Checksum(SG33BL_Packet_t *Packet);
int32 SG33BL_Custom_Select(uint32 TimeoutSec, uint32 TimeoutUSec);

/************************************************************************
** Function Definitions
*************************************************************************/

void SG33BL_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&SG33BL_AppCustomData, sizeof(SG33BL_AppCustomData));
}


boolean SG33BL_Custom_Init()
{
    boolean returnBool = TRUE;
    uint16 productNum = 0;
    uint16 productVer = 0;
    uint16 firmwareVer = 0;
    uint16 serialSub = 0;
    uint16 serialMain = 0;
    uint16 speed = 0;
    uint16 value = 0;
    
    SG33BL_AppCustomData.Status = SG33BL_CUSTOM_INITIALIZED;

end_of_function:
    return returnBool;
}


boolean SG33BL_Custom_Deinit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    return returnBool;
}


boolean SG33BL_Custom_Max_Events_Not_Reached(int32 ind)
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


int32 SG33BL_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == SG33BL_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = SG33BL_DEVICE_ERR_EID;
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


boolean SG33BL_Custom_Write(uint8 Addr, uint16 Value)
{
    SG33BL_Packet_t packet = {0};
    boolean returnBool = TRUE;
    int bytesWritten = 0;

end_of_function:
    return returnBool;
}


boolean SG33BL_Custom_Read(uint8 Addr, uint16 *Value)
{
    SG33BL_Packet_t inPacket = {0};
    SG33BL_Normal_Read_t outPacket = {0};
    uint8   *BytePtr  = (uint8 *)&inPacket;
    boolean returnBool = TRUE;
    int bytes, i = 0;
    uint8 startIndex = 0;
    char buffer[32] = {0};
    char tempBuffer;
    int32 returnCode = 0;
    boolean completePacket = FALSE;


end_of_function:
    return returnBool;
}


uint8 SG33BL_Compute_Checksum(SG33BL_Packet_t *PktPtr)
{
   uint16   PktLen   = sizeof(SG33BL_Packet_t) - 2;
   uint8   *BytePtr  = (uint8 *)PktPtr;
   uint8    CheckSum = 0;


   return CheckSum % 0x100;
}


boolean SG33BL_Valid_Checksum(SG33BL_Packet_t *PktPtr)
{
    if(SG33BL_Compute_Checksum(PktPtr) == PktPtr->checksum)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


boolean SG33BL_Custom_Set_Baud(const uint32 Baud)
{
    int speed = 0;
    int termios_state = 0;
    boolean returnBool = TRUE;
    struct termios uart_config;
    int returnVal = 0;


end_of_function:

    return returnBool;
}


int32 SG33BL_Custom_Select(uint32 TimeoutSec, uint32 TimeoutUSec)
{
    int32 returnCode = 0;
    uint32 maxFd = 0;
    uint32 retryAttempts = 0;
    fd_set fds;
    struct timeval timeValue;
    maxFd = 0;
    returnCode = 0;
    const uint32 maxRetryAttempts = 5;


    return returnCode;
}
