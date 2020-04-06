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

#ifndef OSRTM_H
#define OSRTM_H

#include "common_types.h"
#include <pthread.h>
#include "osapi-os-rtm.h"
#include "osapi.h"

/*timeouts */
typedef struct
{
    boolean   	    Free;
    boolean	    Enabled;
    pthread_cond_t  *CV;
    pthread_mutex_t *Mut;
    struct timespec Time;
    boolean	    TimedOut;
    pid_t           Owner;
} OS_RtmTimeoutRecord_t;


typedef enum
{
	OS_RTM_STATE_REALTIME 				 = 0,
	OS_RTM_STATE_NONREALTIME_PRERUN			 = 1,
	OS_RTM_STATE_NONREALTIME_STEP_NEXT_FRAME         = 2,
	OS_RTM_STATE_NONREALTIME_RUN			 = 3
} OS_RunTimeStateEnum_t;


typedef struct
{
    struct timespec Time;
    boolean Valid;
} OS_RtmNRTTime_t;


typedef struct
{
	uint32			      ExecTaskID;
	pthread_cond_t        CV;
	pthread_mutex_t       Mut;
    pthread_mutex_t       AllocDeallocMut;
	OS_RtmNRTTime_t	      FrameStartTime;
	OS_RtmNRTTime_t       CurrentTime;
	OS_RtmNRTTime_t       StopTime;
	uint32			      MajorFrameLength;
	uint32                MinorFrameLength;
	uint32			      MinorFramesPerMajorFrame;
	OS_RunTimeModeEnum_t  Mode;
	OS_RunTimeStateEnum_t State;
	uint32			      CurrentMinorFrame;
	OS_RtmTimeoutRecord_t TimeoutTable[OS_MAX_TIMEOUTS];
} OS_RtmData_t;


int32   OS_RtmInit(OS_RunTimeModeEnum_t RunMode);
void* 	OS_RtmExecTask(void *Args);
int32 	OS_RtmInitExecTask(void);
OS_RtmTimeoutRecord_t* OS_RtmGetNextTimeout(void);
boolean OS_RtmIsTimeoutExpired(OS_RtmTimeoutRecord_t *Timeout);
void    OS_RtmStepNextFrame(void);
void 	OS_RtmExpireTimeout(OS_RtmTimeoutRecord_t *Timeout);
boolean OS_RtmIsTimeGTE(const struct timespec *t1, const struct timespec *t2);
boolean OS_RtmIsTimeLT(const struct timespec *t1, const struct timespec *t2);
boolean OS_RtmIsTimeLTE(const struct timespec *t1, const struct timespec *t2);
OS_RtmTimeoutRecord_t* OS_RtmAllocTimeoutRecord(void);
void 	OS_RtmFreeTimeoutRecord(OS_RtmTimeoutRecord_t* timeout);
boolean OS_RtmIsTimeGTECurrentTime(const struct timespec *t1);
int     OS_NanoSleep(const struct timespec *requested_time, struct timespec *remaining);
int     OS_RtmCondTimedWait(pthread_cond_t *cond, pthread_mutex_t *mutex, uint32 usec);
void    OS_RtmTimeAddMicroseconds(struct timespec *t, uint32 m);
int32   OS_RtmReplishTimeoutByCV(pthread_cond_t* cv, uint32 microseconds);

extern OS_RtmData_t OS_RtmData;

#endif
