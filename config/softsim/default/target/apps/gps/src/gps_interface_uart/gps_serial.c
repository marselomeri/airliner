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
#include "gps_serial.h"
#include "gps_perfids.h"
#include "../gps_parser_ubx/gps_ubx_msg.h"
#include "../gps_parser_ubx/gps_parser_ubx_common.h"
#include "msg_ids.h"

#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
GPS_AppCustomData_t GPS_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/


void GPS_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&GPS_AppCustomData, sizeof(GPS_AppCustomData));
    //GPS_AppCustomData.Baud = GPS_SERIAL_IO_SPEED;
    GPS_Parser_Reset();
        /* Set all non-zero values */
    GPS_AppCustomData.ContinueFlag          = TRUE;
    GPS_AppCustomData.Priority              = GPS_STREAMING_TASK_PRIORITY;
    GPS_AppCustomData.StreamingTask         = GPS_Stream_Task;
}


boolean GPS_Custom_Init()
{
    boolean returnBool = TRUE;
    int32 returnCode = 0;
    int32 Status = CFE_SUCCESS;

    //GPS_AppCustomData.DeviceFd = open(GPS_SERIAL_DEVICE_PATH, O_RDWR | O_NOCTTY);
    //if (GPS_AppCustomData.DeviceFd < 0) 
    //{
        //CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"GPS Device open errno: %i", errno);
        //returnBool = FALSE;
        //goto end_of_function;
    //}
    
    Status = OS_MutSemCreate(&GPS_AppCustomData.MutexPosition, GPS_MUTEX_POS, 0);
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS mutex create failed in custom init");
        returnBool = FALSE;
        goto end_of_function;
    }
    Status = OS_MutSemCreate(&GPS_AppCustomData.MutexSatInfo, GPS_MUTEX_SAT, 0);
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS mutex create failed in custom init");
        returnBool = FALSE;
        goto end_of_function;
    }
    /* End mutex creation */

    /* Configure all the message rates */
    returnBool = GPS_Custom_Configure();
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device set configuration error");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Create the streaming task */
    returnCode = CFE_ES_CreateChildTask(
            &GPS_AppCustomData.ChildTaskID,
            GPS_STREAMING_TASK_NAME,
            GPS_AppCustomData.StreamingTask,
            0,
            CFE_ES_DEFAULT_STACK_SIZE,
            GPS_AppCustomData.Priority,
            0);
    if(CFE_SUCCESS != returnCode)
    {
        GPS_AppCustomData.ContinueFlag = FALSE;
        returnBool = FALSE;
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS create streaming task failed");
        goto end_of_function;
    }
    else
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_INITIALIZED;
    }
    
end_of_function:
    return returnBool;
}


boolean GPS_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    /* Delete the child task */
    CFE_ES_DeleteChildTask(GPS_AppCustomData.ChildTaskID);
    /* Set streaming task loop flag to stop */
    GPS_AppCustomData.ContinueFlag = FALSE;
    /* Set app state to initialized */
    GPS_AppCustomData.Status = GPS_CUSTOM_INITIALIZED;

    returnCode = close(GPS_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


int32 GPS_Custom_Receive(uint8 *Buffer, uint32 Length, uint32 Timeout)
{
    int32 returnCode = 0;
    int32 bytesRead = 0;

    /* Null check */
    if(0 == Buffer)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS receive null pointer");
        goto end_of_function;
    }
    /* Wait for GPS data */
    returnCode = GPS_Custom_Select(0, 1000 * Timeout);
    if (returnCode <= 0)
    {
        /* Select timeout or error */
        goto end_of_function;
    }
    /* Select returned > 0, data is ready to be read, wait for more
     * data to be available before calling read */
    usleep(GPS_WAIT_BEFORE_READ * 1000);
    
    /* Read GPS data */
    bytesRead = read(GPS_AppCustomData.DeviceFd, Buffer, Length);
    if (bytesRead <= 0)
    {
        /* Read failed */
        goto end_of_function;
    }

end_of_function:

    return bytesRead;
}


int32 GPS_Custom_Select(const uint32 TimeoutSec, const uint32 TimeoutUSec)
{
    int32 returnCode = 0;
    uint32 maxFd = 0;
    uint32 retryAttempts = 0;
    fd_set fds;
    struct timeval timeValue;
    maxFd = 0;
    returnCode = 0;

    while(retryAttempts != GPS_MAX_RETRY_ATTEMPTS)
    {
        /* Set the timeout */
        timeValue.tv_sec = TimeoutSec;
        timeValue.tv_usec = TimeoutUSec;
    
        /* Initialize the set */
        FD_ZERO(&fds);
    
        FD_SET(GPS_AppCustomData.DeviceFd, &fds);
        
        /* Get the greatest fd value for select() */
        maxFd = GPS_AppCustomData.DeviceFd; 
    
        //CFE_ES_PerfLogEntry(GPS_DEVICE_GET_PERF_ID);
        /* Wait for RC data */
        returnCode = select(maxFd + 1, &fds, 0, 0, &timeValue);
        //CFE_ES_PerfLogExit(GPS_DEVICE_GET_PERF_ID);

        /* select() wasn't successful */
        if (-1 == returnCode)
        {
            /* select was interrupted, try again */
            if (EINTR == errno)
            {
                CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select was interrupted");
                usleep(GPS_MAX_RETRY_SLEEP_USEC);
                retryAttempts++;
                continue;
            }
            else
            {
                /* select returned an error other than EINTR */
                CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select() returned errno: %i", errno);
                break;
            }
        }
        /* select timed out */
        if (0 == returnCode)
        {
            CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select() timed out");
            break;
        } 
        /* select() returned and data is ready to be read */
        if(returnCode > 0)
        {
            break;
        }
    } /* end while loop*/

    return returnCode;
}


void GPS_Stream_Task(void)
{
    uint32 iStatus = -1;
    boolean returnBool = FALSE;
    
    iStatus = CFE_ES_RegisterChildTask();
    
    if (iStatus == CFE_SUCCESS)
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_STREAMING;
        while (GPS_AppCustomData.ContinueFlag == TRUE)
        {
            returnBool = GPS_Custom_Read_and_Parse(GPS_PACKET_TIMEOUT);
            if(returnBool == FALSE)
            {
                /* TODO remove me*/
                OS_printf("GPS parse and read failed\n");
            }
        }
    }

    /* Streaming task is exiting so set app flag to initialized */
    GPS_AppCustomData.Status = GPS_CUSTOM_INITIALIZED;
    CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
        "GPS receive task exited with task status (0x%08lX)", iStatus);

    /* The child task was successfully registered so exit from it */
    if (iStatus == CFE_SUCCESS)
    {
        CFE_ES_ExitChildTask();
    }
}


boolean GPS_Custom_Read_and_Parse(const uint32 timeout)
{
    boolean returnBool = TRUE;
    uint32 i = 0;
    uint32 j = 0;
    uint16 satCount = 0;
    int32 bytesRead = 0;
    uint8 from_gps_data[GPS_READ_BUFFER_SIZE];
    boolean done = FALSE;
    
    bytesRead = GPS_Custom_Receive(&from_gps_data[0], 
            sizeof(from_gps_data), timeout);

    if (bytesRead < 0)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    for(i = 0;  i < bytesRead; ++i)
    {
        GPS_DeviceMessage_t message;
        GPS_ParserStatus_t status;

        if(GPS_ParseChar(from_gps_data[i], &message, &status, &done))
        {
            /* If parsechar completed a message... */
            if(TRUE == done)
            {
                /* Copy message to the CVT */
                CFE_SB_MsgId_t msgID = CFE_SB_GetMsgId((CFE_SB_Msg_t*)&message);
                switch(msgID)
                {
                    case GPS_NAV_DOP_MID:
                    {
                        GPS_NAV_DOP_t *msgIn = (GPS_NAV_DOP_t*) CFE_SB_GetUserData((CFE_SB_Msg_t*)&message);
                        OS_MutSemTake(GPS_AppCustomData.MutexPosition);
                        /* from cm to m */
                        GPS_AppCustomData.GpsPositionMsg.HDOP = msgIn->hDOP * 0.01f;
                        /* from cm to m */
                        GPS_AppCustomData.GpsPositionMsg.VDOP = msgIn->vDOP * 0.01f;
                        OS_MutSemGive(GPS_AppCustomData.MutexPosition);
                        break;
                    }
                    case GPS_NAV_NAVPVT_MID:
                    {
                        GPS_NAV_PVT_t *msgIn = (GPS_NAV_PVT_t*) CFE_SB_GetUserData((CFE_SB_Msg_t*)&message);
                        OS_MutSemTake(GPS_AppCustomData.MutexPosition);
                        /* Check if position fix flag is good */
                        if ((msgIn->flags & GPS_NAV_PVT_FLAGS_GNSSFIXOK) == 1)
                        {
                            uint8 carr_soln = msgIn->flags >> 6;
                            GPS_AppCustomData.GpsPositionMsg.FixType = msgIn->fixType;

                            if (msgIn->flags & GPS_NAV_PVT_FLAGS_DIFFSOLN)
                            {
                                /* DGPS */
                                GPS_AppCustomData.GpsPositionMsg.FixType = 4;
                            }

                            if (carr_soln == 1)
                            {
                                /* Float RTK */
                                GPS_AppCustomData.GpsPositionMsg.FixType = 5;

                            }
                            else if (carr_soln == 2)
                            {
                                /* Fixed RTK */
                                GPS_AppCustomData.GpsPositionMsg.FixType = 6;
                            }

                            GPS_AppCustomData.GpsPositionMsg.VelNedValid = TRUE;
                        }
                        else
                        {
                            GPS_AppCustomData.GpsPositionMsg.FixType = 0;
                            GPS_AppCustomData.GpsPositionMsg.VelNedValid = FALSE;
                        }

                        GPS_AppCustomData.GpsPositionMsg.SatellitesUsed = 
                                msgIn->numSV;

                        GPS_AppCustomData.GpsPositionMsg.Lat = 
                                msgIn->lat;
                        GPS_AppCustomData.GpsPositionMsg.Lon = 
                                msgIn->lon;
                        GPS_AppCustomData.GpsPositionMsg.Alt = 
                                msgIn->hMSL;

                        GPS_AppCustomData.GpsPositionMsg.EpH = 
                                (float)msgIn->hAcc * 1e-3f;
                        GPS_AppCustomData.GpsPositionMsg.EpV = 
                                (float)msgIn->vAcc * 1e-3f;
                        GPS_AppCustomData.GpsPositionMsg.SVariance = 
                                (float)msgIn->sAcc * 1e-3f;

                        GPS_AppCustomData.GpsPositionMsg.Vel_m_s = 
                                (float)msgIn->gSpeed * 1e-3f;

                        GPS_AppCustomData.GpsPositionMsg.Vel_n_m_s = 
                                (float)msgIn->velN * 1e-3f;
                        GPS_AppCustomData.GpsPositionMsg.Vel_e_m_s = 
                                (float)msgIn->velE * 1e-3f;
                        GPS_AppCustomData.GpsPositionMsg.Vel_d_m_s = 
                                (float)msgIn->velD * 1e-3f;

                        GPS_AppCustomData.GpsPositionMsg.COG = 
                                (float)msgIn->headMot * M_DEG_TO_RAD_F * 1e-5f;
                        GPS_AppCustomData.GpsPositionMsg.CVariance = 
                                (float)msgIn->headAcc * M_DEG_TO_RAD_F * 1e-5f;

                        //Check if time and date fix flags are good
                        if ((msgIn->valid & GPS_NAV_PVT_VALID_VALIDDATE)
                            && (msgIn->valid & GPS_NAV_PVT_VALID_VALIDTIME)
                            && (msgIn->valid & GPS_NAV_PVT_VALID_FULLYRESOLVED)) 
                        {
                            /* convert to unix timestamp */
                            struct tm timeinfo;
                            timeinfo.tm_year = msgIn->year - 1900;
                            timeinfo.tm_mon  = msgIn->month - 1;
                            timeinfo.tm_mday = msgIn->day;
                            timeinfo.tm_hour = msgIn->hour;
                            timeinfo.tm_min  = msgIn->min;
                            timeinfo.tm_sec  = msgIn->sec;

                            time_t epoch     = mktime(&timeinfo);

                            if (epoch > GPS_EPOCH_SECS)
                            {
                                // FMUv2+ boards have a hardware RTC, but GPS helps us to configure it
                                // and control its drift. Since we rely on the HRT for our monotonic
                                // clock, updating it from time to time is safe.

                                struct timespec ts;
                                ts.tv_sec = epoch;
                                ts.tv_nsec = msgIn->nano;

                                //setClock(ts);

                                GPS_AppCustomData.GpsPositionMsg.TimeUtcUsec = ((uint64)epoch) * 1000000ULL;
                                GPS_AppCustomData.GpsPositionMsg.TimeUtcUsec += msgIn->nano / 1000;
                            }
                            else
                            {
                                GPS_AppCustomData.GpsPositionMsg.TimeUtcUsec = 0;
                            }
                        }
                        
                        GPS_AppCustomData.GpsPositionMsg.Timestamp = GPS_Custom_Get_Time();
                        //GPS_AppCustomData.LastTimeStamp = GPS_AppCustomData.GpsPositionMsg.Timestamp;

                        /* TODO position and velocity update rate functions
                         * and a reset function */
                        GPS_AppCustomData.RateCountVel++;
                        GPS_AppCustomData.RateCountLatLon++;
                        GPS_AppCustomData.GotPosllh = TRUE;
                        GPS_AppCustomData.GotVelned = TRUE;
                        
                        /* TODO verify this for NAV-PVT */
                        //GPS_AppCustomData.GpsPositionMsg.TimestampTimeRelative = 0;

                        OS_MutSemGive(GPS_AppCustomData.MutexPosition);
                        break;
                    }
                    case GPS_NAV_SVINFO_MID:
                    {

                        GPS_NAV_SVINFO_Combined_t *msgIn = (GPS_NAV_SVINFO_Combined_t*) CFE_SB_GetUserData((CFE_SB_Msg_t*)&message);
                        
                        OS_MutSemTake(GPS_AppCustomData.MutexSatInfo);
                        
                        GPS_AppCustomData.GpsSatInfoMsg.Count = msgIn->svinfo.numCh;
                        satCount = GPS_AppCustomData.GpsSatInfoMsg.Count;

                        if(GPS_AppCustomData.GpsSatInfoMsg.Count > PX4_SAT_INFO_MAX_SATELLITES)
                        {
                            CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                                    "GPS sat count %hhu > max buffer length %hhu", 
                                    GPS_AppCustomData.GpsSatInfoMsg.Count,
                                    PX4_SAT_INFO_MAX_SATELLITES);
                            satCount = PX4_SAT_INFO_MAX_SATELLITES;
                        }
                        for(j = 0; j< satCount; j++)
                        {
                            GPS_AppCustomData.GpsSatInfoMsg.Used[j] = 
                                    (uint8)(msgIn->numCh[j].flags & 0x01);
                            GPS_AppCustomData.GpsSatInfoMsg.SNR[j] = 
                                    (uint8)(msgIn->numCh[j].cno);
                                    
                            GPS_AppCustomData.GpsSatInfoMsg.Elevation[j] =
                                    (uint8)(msgIn->numCh[j].elev);
                            GPS_AppCustomData.GpsSatInfoMsg.Azimuth[j] =
                                    (uint8)((float)msgIn->numCh[j].azim * 255.0f / 360.0f);
                            GPS_AppCustomData.GpsSatInfoMsg.SVID[j] =
                                    (uint8)(msgIn->numCh[j].svid);
                        }
                        
                        GPS_AppCustomData.GpsSatInfoMsg.Timestamp = GPS_Custom_Get_Time();
                        
                        OS_MutSemGive(GPS_AppCustomData.MutexSatInfo);
                        break;
                    }
                    case GPS_ACK_NAK_MID:
                    {
                        break;
                    }
                    case GPS_ACK_ACK_MID:
                    {
                        break;
                    }
                    case GPS_CFG_PRT_MID:
                    {
                        break;
                    }
                    case GPS_CFG_MSG_MID:
                    {
                        break;
                    }
                    case GPS_CFG_RATE_MID:
                    {
                        break;
                    }
                    case GPS_CFG_SBAS_MID:
                    {
                        break;
                    }
                    case GPS_CFG_NAV5_MID:
                    {
                        break;
                    }
                    case GPS_MON_HW_MID:
                    {
                        OS_MutSemTake(GPS_AppCustomData.MutexPosition);
                        GPS_MON_HW_t *msgIn = (GPS_MON_HW_t*) CFE_SB_GetUserData((CFE_SB_Msg_t*)&message);

                        GPS_AppCustomData.GpsPositionMsg.NoisePerMs = msgIn->noisePerMS;
                        GPS_AppCustomData.GpsPositionMsg.JammingIndicator = msgIn->jamInd;
                        
                        OS_MutSemGive(GPS_AppCustomData.MutexPosition);
                        break;
                    }
                    default:
                    {
                        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                                "GPS parser received unexpected message");
                    }
                }
            }
        }
    }

end_of_function:
    return returnBool;
}


//boolean GPS_Custom_WaitForAck(const uint16 msg, const uint32 timeout)
//{
    //uint32 i = 0;
    //int32 bytesRead = 0;
    //uint8 from_gps_data[GPS_READ_BUFFER_SIZE];
    //boolean done = FALSE;
    //boolean timedOut = FALSE;
    //boolean returnBool = FALSE;
    //uint64 timeStamp = 0;
    //uint64 startTime = 0;

    ///* Set the ack state to waiting */
    //GPS_AppCustomData.AckState = GPS_ACK_WAITING;
    ///* Set the message we're looking for */
    //GPS_AppCustomData.AckWaitingMsg = msg;
    ///* Set the received ack boolean to false */
    //GPS_AppCustomData.AckWaitingRcvd = FALSE;

    ///* Get the start time */
    //startTime = GPS_Custom_Get_Time_Uint64();
    //if(0 == startTime)
    //{
        //goto end_of_function;
    //}

    ///* while we haven't timed out keep looking for the message */
    //while(FALSE == timedOut)
    //{
        ///* Get the loop iteration time */
        //timeStamp = GPS_Custom_Get_Time_Uint64();
        //if(0 == timeStamp)
        //{
            //goto end_of_function;
        //}
        
        ///* If we've timed out out set the flag to true */
        //if(timeStamp >= startTime + timeout * 1000)
        //{
            //timedOut = TRUE;
        //}

        //returnBool = GPS_Custom_Read_and_Parse(GPS_PACKET_TIMEOUT); 
        //if(TRUE == returnBool && FALSE == timedOut)
        //{
            ///* TODO move to read and parse message decode */
            //if(GPS_AppCustomData.AckState == GPS_ACK_GOT_ACK &&
               //GPS_AppCustomData.AckWaitingRcvd == TRUE)
            //{
                //returnBool = TRUE;
                //goto end_of_function;
            //}
            //if(GPS_AppCustomData.AckState == GPS_ACK_GOT_NAK &&
               //GPS_AppCustomData.AckWaitingRcvd == TRUE)
            //{
                //returnBool = FALSE;
                //goto end_of_function;
            //}
        //}
    //}

//end_of_function:

//return returnBool;
//}


boolean GPS_Custom_Configure(void)
{
    boolean returnBool = TRUE;

end_of_function:

    return returnBool;
}


boolean GPS_Custom_SendMessageRate(const uint16 msg, const uint8 rate)
{
    GPS_Payload_TX_CFG_Rate_Msg_t rateMsgConfig;
    memset(&rateMsgConfig, 0, sizeof(rateMsgConfig));
    rateMsgConfig.msg = msg;
    rateMsgConfig.rate = rate;
    
    return GPS_Custom_SendMessage(GPS_MESSAGE_CFG_MSG, 
                (uint8 *)&rateMsgConfig, sizeof(rateMsgConfig));
    
}


boolean GPS_Custom_Measure_PositionMsg(PX4_VehicleGpsPositionMsg_t *Measure)
{
    boolean returnBool = TRUE;
    /* Null check */
    if(0 == Measure)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS measure dump message null pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    OS_MutSemTake(GPS_AppCustomData.MutexPosition);
    memcpy(Measure, &GPS_AppCustomData.GpsPositionMsg, 
            sizeof(GPS_AppCustomData.GpsPositionMsg));
    OS_MutSemGive(GPS_AppCustomData.MutexPosition);

end_of_function:

    return returnBool;
}


boolean GPS_Custom_Measure_SatInfoMsg(PX4_SatelliteInfoMsg_t *Measure)
{
    boolean returnBool = TRUE;
    /* Null check */
    if(0 == Measure)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS measure dump message null pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    OS_MutSemTake(GPS_AppCustomData.MutexSatInfo);
    memcpy(Measure, &GPS_AppCustomData.GpsSatInfoMsg, 
            sizeof(GPS_AppCustomData.GpsSatInfoMsg));
    OS_MutSemGive(GPS_AppCustomData.MutexSatInfo);

end_of_function:

    return returnBool;
}
