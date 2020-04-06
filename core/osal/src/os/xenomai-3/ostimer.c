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

#include "osapi.h"



int32  OS_TimerAPIInit          (void)
{
	return OS_SUCCESS;
}



int32 OS_TimeBaseCreate         (uint32 *timer_id, const char *timebase_name, OS_TimerSync_t external_sync)
{
	return OS_ERROR;
}



int32 OS_TimeBaseSet            (uint32 timer_id, uint32 start_time, uint32 interval_time)
{
	return OS_ERROR;
}



int32 OS_TimeBaseDelete         (uint32 timer_id)
{
	return OS_ERROR;
}



int32 OS_TimeBaseGetIdByName    (uint32 *timer_id, const char *timebase_name)
{
	return OS_ERROR;
}



int32 OS_TimerCreate            (uint32 *timer_id, const char *timer_name, uint32 *clock_accuracy, OS_TimerCallback_t callback_ptr)
{
	return OS_ERROR;
}



int32 OS_TimerAdd               (uint32 *timer_id, const char *timer_name, uint32 timebase_id, OS_ArgCallback_t  callback_ptr, void *callback_arg)
{
	return OS_ERROR;
}



int32 OS_TimerSet               (uint32 timer_id, uint32 start_time, uint32 interval_time)
{
	return OS_ERROR;
}



int32 OS_TimerDelete            (uint32 timer_id)
{
	return OS_ERROR;
}



int32 OS_TimerGetIdByName       (uint32 *timer_id, const char *timer_name)
{
	return OS_ERROR;
}



int32 OS_TimerGetInfo           (uint32  timer_id, OS_timer_prop_t *timer_prop)
{
	return OS_ERROR;
}


