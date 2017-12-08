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
/*************************************************************************
**
** Include section
**
**************************************************************************/

#include "cfe.h"
#include "gps_serial.h"
//#include "GPS_events.h"
//#include "GPS_msgids.h"
#include "gps_parser_ubx_cfg.h"

/*************************************************************************
**
** Macro definitions
**
**************************************************************************/

#define GPS_PARSER_CFG_CFG_MSG_LENGTH1    (12)
#define GPS_PARSER_CFG_CFG_MSG_LENGTH2    (13)
#define GPS_PARSER_CFG_NAV5_MSG_LENGTH    (36)
#define GPS_PARSER_CFG_SBAS_MSG_LENGTH    (8)
#define GPS_PARSER_CFG_TMODE3_MSG_LENGTH  (40)
#define GPS_PARSER_CFG_PRT_MSG_LENGTH     (20)
#define GPS_PARSER_CFG_MSG_MSG_LENGTH1     (8)
#define GPS_PARSER_CFG_MSG_MSG_LENGTH2     (8)

/*************************************************************************
**
** Type definitions
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Imported data
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Exported data
**
**************************************************************************/



/*************************************************************************
**
** File data
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
** Local function prototypes
**************************************************************************/
void GPS_Cfg_ParseChar_CFG(uint8 byte, GPS_DeviceMessage_t* message)
{
    if(GPS_AppCustomData.ParserStatus.MsgLength != GPS_PARSER_CFG_CFG_MSG_LENGTH1 ||
       GPS_PARSER_CFG_CFG_MSG_LENGTH2)
    {
        GPS_AppCustomData.ParserStatus.ParseError++;
        CFE_EVS_SendEvent(GPS_INIT_DEVICE_PARSER_ERR_EID, CFE_EVS_ERROR,
                      "Received CFG message with incorrect length (%u).", GPS_AppCustomData.ParserStatus.MsgLength);
        GPS_Parser_Reset();
    }
    else
    {
        GPS_CFG_CFG_t *payload = (void*)CFE_SB_GetUserData((CFE_SB_MsgPtr_t)message);
        switch(GPS_AppCustomData.ParserStatus.PayloadCursor)
        {
        case 0:
        {
            CFE_SB_MsgId_t sbMsgID = GPS_TranslateMsgID(GPS_AppCustomData.ParserStatus.ClassID, GPS_AppCustomData.ParserStatus.MsgID);
            uint16 sbHdrSize = CFE_SB_MsgHdrSize(sbMsgID);
            uint16 sbTotalMsgSize = sbHdrSize + GPS_AppCustomData.ParserStatus.MsgLength;
            CFE_SB_InitMsg(message, sbMsgID, sbTotalMsgSize, TRUE);

            payload->clearMask = byte;
            break;
        }

        case 1:
            payload->clearMask += byte << 8;
            break;

        case 2:
            payload->clearMask += byte << 16;
            break;

        case 3:
            payload->clearMask += byte << 24;
            break;

        case 4:
            payload->saveMask = byte;
            break;

        case 5:
            payload->saveMask += byte << 8;
            break;

        case 6:
            payload->saveMask += byte << 16;
            break;

        case 7:
            payload->saveMask += byte << 24;
            break;

        case 8:
            payload->loadMask = byte;
            break;

        case 9:
            payload->loadMask += byte << 8;
            break;

        case 10:
            payload->loadMask += byte << 16;
            break;

        case 11:
            payload->loadMask += byte << 24;
            break;

        case 12:
            payload->deviceMask = byte;
            GPS_Parser_StateChange(GPS_PARSE_STATE_GOT_PAYLOAD);
            break;

        default:
            GPS_Parser_Reset();
            return;
        }
    }
}


/************************/
/*  End of File Comment */
/************************/

