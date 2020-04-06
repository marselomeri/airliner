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

void 	OS_RtmSetCurrentTime(const struct timespec *t);
void 	OS_RtmGetCurrentTime(struct timespec *t);
void 	OS_RtmSetStopTime(const struct timespec *t);
void 	OS_RtmGetStopTime(struct timespec *t);
void 	OS_RtmTimeAddMicroseconds(struct timespec *t, uint32 m);
int 	OS_RtmCondTimedWait(pthread_cond_t *cond, pthread_mutex_t *mutex, uint32 microseconds);
void    OS_RtmAdvanceStopTime(uint32 microseconds);
OS_RunTimeModeEnum_t OS_RtmGetRunMode(void);
int32   OS_RtmReplishTimeoutByCV(pthread_cond_t* cv, uint32 microseconds);
void    OS_RtmHoldTime(void);

#endif
