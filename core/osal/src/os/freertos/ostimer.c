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

#include "FreeRTOS.h"
#include "semphr.h"
#include "osapi.h"
#include <timers.h>
#include <string.h>



#define UNINITIALIZED 0



typedef struct
{
   uint32              free;
   char                name[OS_MAX_API_NAME];
   uint32              creator;
   uint32              start_time;
   uint32              interval_time;
   OS_TimerCallback_t  callback_ptr;
   TimerHandle_t       handle;
   osalbool            isStarted;

} OS_timer_record_t;


OS_timer_record_t OS_timer_table[OS_MAX_TIMERS];

SemaphoreHandle_t OS_timer_table_mut;


/*
** Timer Signal Handler.
** The purpose of this function is to convert the FreeRTOS timer ID to the
** OSAL timer ID and pass it to the User defined callback.
*/
void OS_TimerSignalHandler( TimerHandle_t xTimer )
{
   uint32 tid;

   for(tid = 0; tid < OS_MAX_TIMERS; tid++)
   {
       if (OS_timer_table[tid].handle == xTimer)
       {
           if(OS_timer_table[tid].callback_ptr != 0)
           {
        	   (OS_timer_table[tid].callback_ptr)(tid);
           }
       }
   }
}


int32 OS_TimerAPIInit(void)
{
    int i;

    /*
    ** Mark all timers as available
    */
    for (i = 0; i < OS_MAX_TIMERS; i++)
    {
        OS_timer_table[i].free      = TRUE;
        OS_timer_table[i].creator   = UNINITIALIZED;
        strcpy(OS_timer_table[i].name, "");
        OS_timer_table[i].callback_ptr = 0;
        OS_timer_table[i].handle = 0;
        OS_timer_table[i].interval_time = 0;
        OS_timer_table[i].start_time = 0;
        OS_timer_table[i].isStarted = FALSE;
    }

    OS_timer_table_mut = xSemaphoreCreateMutex();
    if ( OS_timer_table_mut == NULL )
    {
        return OS_ERROR;
    }
    else
    {
        return OS_SUCCESS;
    }
}



int32 OS_TimerCreate(uint32 *timer_id, const char *timer_name, uint32 *clock_accuracy, OS_TimerCallback_t callback_ptr)
{
    uint32    possible_tid;
    int32     i;

    if ( timer_id == NULL || timer_name == NULL || clock_accuracy == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /*
    ** we don't want to allow names too long
    ** if truncated, two names might be the same
    */
    if (strlen(timer_name) > OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Check Parameters
    */
    xSemaphoreTakeRecursive(OS_timer_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);
    for(possible_tid = 0; possible_tid < OS_MAX_TIMERS; possible_tid++)
    {
        if (OS_timer_table[possible_tid].free == TRUE)
        {
            break;
        }
    }

    if( possible_tid >= OS_MAX_TIMERS || OS_timer_table[possible_tid].free != TRUE)
    {
        xSemaphoreGiveRecursive(OS_timer_table_mut);
        return OS_ERR_NO_FREE_IDS;
    }

    /*
    ** Check to see if the name is already taken
    */
    for (i = 0; i < OS_MAX_TIMERS; i++)
    {
        if ((OS_timer_table[i].free == FALSE) &&
            strcmp ((char*) timer_name, OS_timer_table[i].name) == 0)
        {
            xSemaphoreGiveRecursive(OS_timer_table_mut);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /*
    ** Verify callback parameter
    */
    if (callback_ptr == NULL )
    {
        xSemaphoreGiveRecursive(OS_timer_table_mut);
        return OS_TIMER_ERR_INVALID_ARGS;
    }

    /*
    ** Set the possible timer Id to not free so that
    ** no other task can try to use it
    */
    OS_timer_table[possible_tid].free = FALSE;
    //OS_timer_table[possible_tid].creator = OS_FindCreator();
    strncpy(OS_timer_table[possible_tid].name, timer_name, OS_MAX_API_NAME);
    OS_timer_table[possible_tid].start_time = 0;
    OS_timer_table[possible_tid].interval_time = 0;
    OS_timer_table[possible_tid].callback_ptr = callback_ptr;
    OS_timer_table[possible_tid].isStarted = FALSE;
    OS_timer_table[possible_tid].handle = 0;

    /*
    ** Return the clock accuracy to the user
    */
    *clock_accuracy = (uint32)1000 / (uint32)configTICK_RATE_HZ;

    /*
    ** Return timer ID
    */
    *timer_id = possible_tid;
    xSemaphoreGiveRecursive(OS_timer_table_mut);

    return OS_SUCCESS;
}



int32 OS_TimerSet(uint32 timer_id, uint32 start_time, uint32 interval_time)
{
    int startTicks = pdMS_TO_TICKS(start_time);
    int intervalTicks = pdMS_TO_TICKS(interval_time);

    /*
    ** Check to see if the timer_id given is valid
    */
    if (timer_id >= OS_MAX_TIMERS || OS_timer_table[timer_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    xSemaphoreTakeRecursive(OS_timer_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /*
    ** Save the start and interval times
    */
    OS_timer_table[timer_id].start_time = start_time;
    OS_timer_table[timer_id].interval_time = interval_time;

    xSemaphoreGiveRecursive(OS_timer_table_mut);

    if(OS_timer_table[timer_id].isStarted == FALSE)
    {
    	OS_timer_table[timer_id].handle = xTimerCreate(
                                                       OS_timer_table[timer_id].name,
                                                       intervalTicks,
                                                       TRUE,
													   (void *) 0,
													   OS_TimerSignalHandler);
    	if(OS_timer_table[timer_id].handle == NULL)
    	{
            return OS_ERROR;
    	}

    	OS_timer_table[timer_id].isStarted = TRUE;

    	if(xTimerStart(OS_timer_table[timer_id].handle, startTicks) != pdPASS)
    	{
            return OS_ERROR;
        }
    }
    else
    {
    	if(xTimerChangePeriod(OS_timer_table[timer_id].handle, intervalTicks, startTicks) != pdPASS)
    	{
            return OS_ERROR;
        }
    }

    return OS_SUCCESS;
}



int32 OS_TimerDelete(uint32 timer_id)
{
    /*
    ** Check to see if the timer_id given is valid
    */
    if (timer_id >= OS_MAX_TIMERS || OS_timer_table[timer_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    xSemaphoreTakeRecursive(OS_timer_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    if(OS_timer_table[timer_id].isStarted == TRUE)
    {
        if(xTimerDelete(OS_timer_table[timer_id].handle, 0) != 	pdPASS)
        {
            xSemaphoreGiveRecursive(OS_timer_table_mut);

            return OS_ERROR;
        }
    }

    OS_timer_table[timer_id].free = TRUE;
    strncpy(OS_timer_table[timer_id].name, "", OS_MAX_API_NAME);
    OS_timer_table[timer_id].start_time = 0;
    OS_timer_table[timer_id].interval_time = 0;
    OS_timer_table[timer_id].callback_ptr = 0;
    OS_timer_table[timer_id].isStarted = FALSE;
    OS_timer_table[timer_id].handle = 0;

    xSemaphoreGiveRecursive(OS_timer_table_mut);

    return OS_SUCCESS;
}



int32 OS_TimerGetInfo(uint32  timer_id, OS_timer_prop_t *timer_prop)
{
    /*
    ** Check to see that the id given is valid
    */
    if (timer_id >= OS_MAX_TIMERS || OS_timer_table[timer_id].free == TRUE)
    {
       return OS_ERR_INVALID_ID;
    }

    if (timer_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /*
    ** put the info into the stucture
    */
    xSemaphoreTakeRecursive(OS_timer_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    timer_prop ->creator       = OS_timer_table[timer_id].creator;
    strcpy(timer_prop-> name, OS_timer_table[timer_id].name);
    timer_prop ->start_time    = OS_timer_table[timer_id].start_time;
    timer_prop ->interval_time = OS_timer_table[timer_id].interval_time;
    timer_prop ->accuracy      = (uint32)1000 / (uint32)configTICK_RATE_HZ;

    xSemaphoreGiveRecursive(OS_timer_table_mut);

    return OS_SUCCESS;
}



/****************************************************************
 * TIME BASE API
 *
 * This is not implemented by this OSAL, so return "OS_ERR_NOT_IMPLEMENTED"
 * for all calls defined by this API.  This is necessary for forward
 * compatibility (runtime code can check for this return code and use
 * an alternative API where appropriate).
 */

int32 OS_TimeBaseCreate(uint32 *timer_id, const char *timebase_name, OS_TimerSync_t external_sync)
{
    return OS_ERR_NOT_IMPLEMENTED;
}

int32 OS_TimeBaseSet(uint32 timer_id, uint32 start_time, uint32 interval_time)
{
    return OS_ERR_NOT_IMPLEMENTED;
}

int32 OS_TimeBaseDelete(uint32 timer_id)
{
    return OS_ERR_NOT_IMPLEMENTED;
}

int32 OS_TimeBaseGetIdByName (uint32 *timer_id, const char *timebase_name)
{
    return OS_ERR_NOT_IMPLEMENTED;
}

int32 OS_TimerAdd(uint32 *timer_id, const char *timer_name, uint32 timebase_id, OS_ArgCallback_t  callback_ptr, void *callback_arg)
{
    return OS_ERR_NOT_IMPLEMENTED;
}
