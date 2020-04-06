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

/****************************************************************************************
                                    INCLUDE FILES
****************************************************************************************/

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "osconfig.h"
#include "osrtm.h"

/*
** The __USE_UNIX98 is for advanced pthread features on linux
*/
#define __USE_UNIX98
#include <pthread.h>
#include "osrtm.h"
#include <errno.h>
#include "common_types.h"
#include "osapi.h"
#include "osarte.h"
#include <sys/resource.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/syscall.h>

extern int    OS_InterruptSafeLock(pthread_mutex_t *lock, sigset_t *set, sigset_t *previous);
extern void   OS_InterruptSafeUnlock(pthread_mutex_t *lock, sigset_t *previous);

OS_RtmData_t OS_RtmData;


int32 OS_RtmInit(OS_RunTimeModeEnum_t RunMode)
{
    int32 Status = OS_SUCCESS;
    int ret = 0;
    uint32 i = 0;
    int32 ArteReturn = 0;

    /* Initialize internal variables. */
    OS_RtmData.CurrentTime.Time.tv_nsec = 0;
    OS_RtmData.CurrentTime.Time.tv_sec = 0;
    OS_RtmData.CurrentTime.Valid = FALSE;
    OS_RtmData.FrameStartTime.Time.tv_nsec = 0;
    OS_RtmData.FrameStartTime.Time.tv_sec = 0;
    OS_RtmData.FrameStartTime.Valid = FALSE;
    OS_RtmData.StopTime.Time.tv_nsec = 0;
    OS_RtmData.StopTime.Time.tv_sec = 0;
    OS_RtmData.StopTime.Valid = FALSE;
    OS_RtmData.Mode = RunMode;

    if(OS_RtmData.Mode == OS_RUNTIME_MODE_NONREALTIME)
    {
        ArteReturn = OS_ArteInit();
        if(ArteReturn != OS_SUCCESS)
        {
            OS_printf("OSAL:  ARTE failed to initialize  err = '%s'\n", strerror(errno));
            Status = OS_ERROR;
            goto end_of_function;
        }
        OS_RtmData.State = OS_RTM_STATE_NONREALTIME_PRERUN;
    }
    else
    {
        OS_RtmData.State = OS_RTM_STATE_REALTIME;
    }

    /* Clear the Timeout table. */
    for(i = 0; i < OS_MAX_TIMEOUTS; ++i)
    {
        OS_RtmTimeoutRecord_t *Timeout = &OS_RtmData.TimeoutTable[i];
        Timeout->Free = TRUE;
        Timeout->Enabled = FALSE;
        Timeout->CV = 0;
        Timeout->Mut = 0;
        Timeout->Time.tv_sec = 0;
        Timeout->Time.tv_nsec = 0;
        Timeout->TimedOut = FALSE;
        Timeout->Owner = 0;
    }

    /* Create the main RTM conditional variable.  We're going to use this in
     * the various setters and utility functions to signal the main run time
     * executive that a change in the current configuration has occurred so
     * the executive can reevaluate and react to the change.
     */
    ret = pthread_cond_init(&OS_RtmData.CV, 0);
    if(ret != 0)
    {
        OS_printf("OSAL:  Failed to create the RTM CV.  err = '%s'\n", strerror(errno));
        Status = OS_ERROR;
        goto end_of_function;
    }

	/* Create the main RTM mutex to be used with the conditional variable
	 * and to make internal data thread safe.
	 */
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutexattr_settype(&attr, PTHREAD_PRIO_INHERIT);
    ret = pthread_mutex_init(&OS_RtmData.Mut, &attr);
	if(ret != 0)
	{
 	    OS_printf("OSAL:  Failed to create the RTM MUT.  err = '%s'\n", strerror(errno));
        Status = OS_ERROR;
        goto end_of_function;
	}
    ret = pthread_mutex_init(&OS_RtmData.AllocDeallocMut, &attr);
	if(ret != 0)
	{
 	    OS_printf("OSAL:  Failed to create the RTM MUT.  err = '%s'\n", strerror(errno));
        Status = OS_ERROR;
        goto end_of_function;
	}

    if(OS_RtmData.Mode == OS_RUNTIME_MODE_NONREALTIME)
    {
		/* Lastly, create the RTM executive thread.  This thread will block on the
		 * main conditional variable, and release whenever any of the data contained
		 * in the RtmData object has changed, allowing the Run Time Manager to
		 * react accordingly. */
		Status = OS_RtmInitExecTask();
		if(Status != OS_SUCCESS)
		{
			OS_printf("OSAL:  Failed to create the RTM Exec task.  err = '%s'\n", strerror(errno));
			goto end_of_function;
		}
    }

    Status = OS_SUCCESS;

end_of_function:
	return Status;

}



int32 OS_RtmInitExecTask(void)
{
	int32			   Status = OS_ERROR;
    pthread_attr_t     custom_attr;
    struct sched_param priority_holder;
    int                ret = 0;
    int                inheritsched = 0;

    /*
    ** Initialize the pthread_attr structure.
    ** The structure is used to set the stack and priority
    */
    memset(&custom_attr, 0, sizeof(custom_attr));
    if(pthread_attr_init(&custom_attr))
    {
        OS_printf("OSAL:  pthread_attr_init error in OS_RtmInitExecTask. %i\n", errno);
        Status = OS_ERROR;
        goto end_of_function;
    }

    /* Set in thread to the detached state so Valgrind memcheck doesn't
     * complain about lost records.
     */
    if(pthread_attr_setdetachstate(&custom_attr, PTHREAD_CREATE_DETACHED))
    {
        OS_printf("OSAL:  pthread_attr_setdetachstate error in OS_RtmInitExecTask.  %i\n", errno);
        Status = OS_ERROR;
        goto end_of_function;
    }

    if(pthread_attr_setguardsize(&custom_attr, 1000000))
    {
        OS_printf("OSAL:  pthread_attr_setguardsize error in OS_RtmInitExecTask.  %i\n", errno);
        Status = OS_ERROR;
        goto end_of_function;
    }

    /*
    ** Test to see if the user is running as root.
    ** root is required to set the scheduling policy, stack, and priority
    */
    if (geteuid() == 0 )
    {
//       /*
//       ** Set the scheduling inherit attribute to EXPLICIT
//       */
//       inheritsched = PTHREAD_EXPLICIT_SCHED;
//       ret = pthread_attr_setinheritsched(&custom_attr, inheritsched);
//       if ( ret < 0 )
//       {
//    	   OS_printf("OSAL:  pthread_attr_setinheritsched error in OS_RtmInitExecTask.  err = '%s'\n", strerror(errno));
//           Status = OS_ERROR;
//           goto end_of_function;
//       }
//
//       /*
//       ** Set the Stack Size
//       */
//       if (pthread_attr_setstacksize(&custom_attr, OS_RUNTIME_MANAGER_EXEC_TASK_STACK_SIZE))
//       {
//           OS_printf("OSAL:  pthread_attr_setstacksize error in OS_RtmInitExecTask.  errno = %u  '%s'\n", errno, strerror(errno));
//           Status = OS_ERROR;
//           goto end_of_function;
//       }

//       /*
//       ** Set priority
//       */
//       memset(&priority_holder, 0, sizeof(priority_holder));
//       priority_holder.sched_priority = OS_RUNTIME_MANAGER_EXEC_TASK_PRIORITY;
//       ret = pthread_attr_setschedparam(&custom_attr, &priority_holder);
//       if(ret !=0)
//       {
//    	   OS_printf("OSAL:  pthread_attr_setschedparam error in OS_RtmInitExecTask.  ret = %i  errno = %u  '%s'\n", ret, errno, strerror(errno));
//           Status = OS_ERROR;
//           goto end_of_function;
//       }
    } /* End if user is root */

    /*
    ** Create thread
    */
    ret = pthread_create(&OS_RtmData.ExecTaskID,
                                 &custom_attr,
								 OS_RtmExecTask,
                                 0);
    if (ret != 0)
    {
    	OS_printf("OSAL:  pthread_create error in OS_RtmInitExecTask.  err = '%s'\n", strerror(errno));
        Status = OS_ERROR;
        goto end_of_function;
    }

    ret = pthread_attr_destroy(&custom_attr);
    if (ret !=0)
    {
    	OS_printf("OSAL:  pthread_attr_destroy error in OS_RtmInitExecTask.  err = '%s'\n", strerror(errno));
        Status = OS_ERROR;
        goto end_of_function;
    }

    Status = OS_SUCCESS;

end_of_function:
    return Status;

}



void OS_RtmProcessTimeouts(void)
{
	OS_RtmTimeoutRecord_t *timeout = 0;
    sigset_t	previous;
    sigset_t   	mask;
    uint32 i = 0;

    //OS_InterruptSafeLock(&OS_RtmData.AllocDeallocMut, &mask, &previous);
	timeout = OS_RtmGetNextTimeout();
	while(timeout != 0)
	{
		if(OS_RtmData.State == OS_RTM_STATE_NONREALTIME_PRERUN)
		{
			struct timespec remaining;

			/* Wait the actual wall time defined in the timeout object. */
			nanosleep(&timeout->Time, &remaining);

			/* Now that we slept a bit, notify the thread thats pending on
			 * the timeout remove the timeout from the list with
			 * OS_RtmExpireTimeout().
			 */
			OS_RtmExpireTimeout(timeout);
		}
		else
		{
			/* We must be in the RUN state.  Rather than wait for the
			 * actual wall time, we're going to collapse time by moving
			 * the simulated current time to whatever the timeout is, and
			 * immediately expire the timeout.
			 */
			if(OS_RtmIsTimeoutExpired(timeout))
			{
				struct timespec currentTime;

				/* Now that we simulated a sleep, notify the thread thats
				 * pending on the timeout remove the timeout from the list
				 * with OS_RtmExpireTimeout().
				 */
				OS_RtmExpireTimeout(timeout);
			}
			else
			{
				timeout = 0;
				break;
			}
		}

		timeout = OS_RtmGetNextTimeout();
	}

    //OS_InterruptSafeUnlock(&OS_RtmData.AllocDeallocMut, &previous);
}



void OS_RtmDisplayDebugInfo(void)
{
	uint32 i = 0;

	OS_printf("Mut: %u\n", OS_RtmData.Mut.__data.__owner);
	OS_printf("AllocDeallocMut: %u\n", OS_RtmData.AllocDeallocMut.__data.__owner);
	OS_printf("FrameStartTime.Valid: %u\n", OS_RtmData.FrameStartTime.Valid);
	OS_printf("FrameStartTime.Time: %lu.%lu\n", OS_RtmData.FrameStartTime.Time.tv_sec, OS_RtmData.FrameStartTime.Time.tv_nsec);
	OS_printf("CurrentTime.Valid: %u\n", OS_RtmData.CurrentTime.Valid);
	OS_printf("CurrentTime.Time: %lu.%lu\n", OS_RtmData.CurrentTime.Time.tv_sec, OS_RtmData.CurrentTime.Time.tv_nsec);
	OS_printf("StopTime.Valid: %u\n", OS_RtmData.StopTime.Valid);
	OS_printf("StopTime.Time: %lu.%lu\n", OS_RtmData.StopTime.Time.tv_sec, OS_RtmData.StopTime.Time.tv_nsec);
	OS_printf("MajorFrameLength: %lu\n", OS_RtmData.MajorFrameLength);
	OS_printf("MinorFrameLength: %lu\n", OS_RtmData.MinorFrameLength);
	OS_printf("MinorFramesPerMajorFrame: %lu\n", OS_RtmData.MinorFramesPerMajorFrame);
	OS_printf("Mode: %u\n", OS_RtmData.Mode);
	OS_printf("State: %u\n", OS_RtmData.State);
	OS_printf("CurrentMinorFrame: %lu\n", OS_RtmData.CurrentMinorFrame);

	for(i = 0; i < 5; ++i)
	{
		OS_printf("OS_RtmData.TimeoutTable[%lu]:\n", i);
		OS_printf("        Free: %u\n", OS_RtmData.TimeoutTable[i].Free);
		OS_printf("     Enabled: %u\n", OS_RtmData.TimeoutTable[i].Enabled);
		OS_printf("          CV: %p\n", OS_RtmData.TimeoutTable[i].CV);
		OS_printf("         Mut: %p\n", OS_RtmData.TimeoutTable[i].Mut);
		if(OS_RtmData.TimeoutTable[i].Mut != 0)
			OS_printf("  Mut(Owner): %u\n", OS_RtmData.TimeoutTable[i].Mut->__data.__owner);
		OS_printf("        Time: %lu.%lu\n", OS_RtmData.TimeoutTable[i].Time.tv_sec, OS_RtmData.TimeoutTable[i].Time.tv_nsec);
		OS_printf("    TimedOut: %u\n", OS_RtmData.TimeoutTable[i].TimedOut);
		OS_printf("       Owner: %u\n", OS_RtmData.TimeoutTable[i].Owner);
	}
}



void* OS_RtmExecTask(void *args)
{
	uint32 i = 0;
    sigset_t	previous;
    sigset_t   	mask;
	struct timespec timeToWait;

    OS_InterruptSafeLock(&OS_RtmData.Mut, &mask, &previous);

    /* Initialize the state machine to PRERUN.  This tells the state
     * machine to not evaluate whether the timeout expires in the current
     * frame.  In the PRERUN state, it waits the actual wall time.  In
     * the RUN state, it immediately "times out" the next timeout if its
     * within the current frame.
     */
    OS_RtmData.State = OS_RTM_STATE_NONREALTIME_PRERUN;

	while(1)
	{
		i++;
		if(i > 10000)
		{
			OS_printf("\n\nDeadlock detected.  Displaying RTM debug info.\n");
			OS_RtmDisplayDebugInfo();
			i=0;
			exit(-1);
		}
		/* Always see if we have timeouts to process before we go to sleep
		 * and wait for things to change.
		 */
		OS_RtmProcessTimeouts();

		/* Wait for something to change, but include a timeout just in
		 * case. */
		clock_gettime(CLOCK_REALTIME, &timeToWait);
		OS_RtmTimeAddMicroseconds(&timeToWait, 1000);
        pthread_cond_timedwait(&OS_RtmData.CV, &OS_RtmData.Mut, &timeToWait);
		OS_RtmProcessTimeouts();

		/* Now that we processed all the timeouts, lets respond to whatever
		 * else has changed.
		 */
        if(OS_RtmData.State == OS_RTM_STATE_NONREALTIME_STEP_NEXT_FRAME)
        {
        	i = 0;

        	/* Scheduler has signaled it is ready to step to the next
        	 * frame.  First, transition the state machine to RUN so
        	 * a future change doesn't immediately cause us to step to the
        	 * next frame.  Scheduler will command us back to the state
        	 * when its ready. */
            OS_RtmData.State = OS_RTM_STATE_NONREALTIME_RUN;

            /* Step to the next frame.  This function will release when the
             * external sync source, i.e. ARTE, has completed its cycle and
             * has signaled Airliner to step to the next frame.
             */
    		OS_RtmStepNextFrame();
        }
	}
}



boolean OS_RtmIsTimeoutExpired(OS_RtmTimeoutRecord_t *timeout)
{
    boolean		expired = FALSE;

	if(OS_RtmIsTimeLTE(&timeout->Time, &OS_RtmData.StopTime.Time))
	{
		expired = TRUE;
	}
	else
	{
		expired = FALSE;
	}

    return expired;
}



void OS_RtmExpireTimeout(OS_RtmTimeoutRecord_t *Timeout)
{
    sigset_t	previous;
    sigset_t   	mask;
    struct timespec currentTime;

    /* The following conditional is a temporary kludge to fix a concurrency
     * bug causing a mutex to get partially deleted.
     */
    if(Timeout->Mut == 0)
    {
		/* Timeout was signaled by another source.  Ignore this timeout. */
    }
    else
    {
		pthread_mutex_lock(Timeout->Mut);
	    if(Timeout->CV == 0)
	    {
			/* Timeout was signaled by another source.  Ignore this timeout. */
	    	OS_printf("BUG DETECTED 2\n");
	    }
	    else
	    {
	    	Timeout->TimedOut = TRUE;
	    	pthread_cond_signal(Timeout->CV);
	    }
    	pthread_mutex_unlock(Timeout->Mut);
    }
}



OS_RtmTimeoutRecord_t* OS_RtmGetNextTimeout(void)
{
	uint32 i = 0;

	OS_RtmTimeoutRecord_t *Timeout = 0;

	for(i = 0; i < OS_MAX_TIMEOUTS; ++i)
	{
		if(OS_RtmData.TimeoutTable[i].Free == FALSE)
		{
			if(OS_RtmData.TimeoutTable[i].Enabled == TRUE)
			{
				if(OS_RtmData.TimeoutTable[i].TimedOut == FALSE)
				{
					/* If this is the first one, flag this as the next timeout. */
					if(Timeout == 0)
					{
						Timeout = &OS_RtmData.TimeoutTable[i];
					}
					else
					{
						/* Look to see if this is going to happen earlier. */
						if(OS_RtmIsTimeLT(&OS_RtmData.TimeoutTable[i].Time, &Timeout->Time))
						{
							/* This is going to happen earlier.  This is the new
							 * "next" timeout.
							 */
							Timeout = &OS_RtmData.TimeoutTable[i];
						}
					}
				}
			}
		}
	}

	return Timeout;
}



void OS_RtmTimeAddMicroseconds(struct timespec *t, uint32 m)
{
	if(t != 0)
	{
		if((t != 0) && (m != 0))
		{
			t->tv_sec = t->tv_sec + (m / 1000000);
			t->tv_nsec = t->tv_nsec + ((m % 1000000) * 1000);

			if(t->tv_nsec >= 1000000000)
			{
				t->tv_nsec -= 1000000000;
				t->tv_sec++;
			}
		}
	}
}



boolean OS_RtmIsTimeGTECurrentTime(const struct timespec *t1)
{
	boolean result;
	struct timespec currentTime = {};

	clock_gettime(CLOCK_REALTIME, &currentTime);

	result = OS_RtmIsTimeGTE(t1, &currentTime);

	return result;
}



boolean OS_RtmIsTimeGTE(const struct timespec *t1, const struct timespec *t2)
{

	if((t1 != 0) && (t2 != 0))
	{
		if(t1->tv_sec == t2->tv_sec)
		{
			if(t1->tv_nsec >= t2->tv_nsec)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if(t1->tv_sec >= t2->tv_sec)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}



boolean OS_RtmIsTimeLT(const struct timespec *t1, const struct timespec *t2)
{
	if((t1 != 0) && (t2 != 0))
	{
		if(t1->tv_sec == t2->tv_sec)
		{
			if(t1->tv_nsec < t2->tv_nsec)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if(t1->tv_sec < t2->tv_sec)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}



boolean OS_RtmIsTimeLTE(const struct timespec *t1, const struct timespec *t2)
{
	if((t1 != 0) && (t2 != 0))
	{
		if(t1->tv_sec == t2->tv_sec)
		{
			if(t1->tv_nsec <= t2->tv_nsec)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if(t1->tv_sec <= t2->tv_sec)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}



void OS_RtmSetCurrentTime(const struct timespec *t)
{
    sigset_t	previous;
    sigset_t   	mask;

	memcpy(&OS_RtmData.CurrentTime.Time, t, sizeof(OS_RtmData.CurrentTime.Time));
	OS_RtmData.CurrentTime.Valid = TRUE;

    pthread_cond_broadcast(&OS_RtmData.CV);

}



void OS_RtmGetCurrentTime(struct timespec *t)
{
    sigset_t	previous;
    sigset_t   	mask;

	if(OS_RtmData.State == OS_RTM_STATE_REALTIME)
	{
		clock_gettime(CLOCK_REALTIME, t);
	}
	else
	{
		memcpy(t, &OS_RtmData.CurrentTime.Time, sizeof(OS_RtmData.CurrentTime.Time));
	}
}



void OS_RtmSetStopTime(const struct timespec *t)
{
    sigset_t	previous;
    sigset_t   	mask;

	memcpy(&OS_RtmData.StopTime.Time, t, sizeof(OS_RtmData.StopTime.Time));
	OS_RtmData.StopTime.Valid = TRUE;

    pthread_cond_broadcast(&OS_RtmData.CV);

}



int32  OS_RtmEngageStepMode(void)
{
    sigset_t	    previous;
    sigset_t   	    mask;
	struct timespec t;

	int32 Status = OS_ERROR;

	if(OS_RtmData.Mode == OS_RUNTIME_MODE_NONREALTIME)
	{
		OS_RtmGetCurrentTime(&t);
		OS_RtmTimeAddMicroseconds(&t, OS_RtmData.MinorFrameLength);
		OS_RtmSetStopTime(&t);
		OS_RtmData.State = OS_RTM_STATE_NONREALTIME_RUN;
		pthread_mutex_lock(&OS_RtmData.Mut);
		pthread_cond_broadcast(&OS_RtmData.CV);
		pthread_mutex_unlock(&OS_RtmData.Mut);
		Status = OS_SUCCESS;
	}

	return Status;
}



int OS_RtmCondTimedWait(pthread_cond_t *cond, pthread_mutex_t *mutex, uint32 usec)
{
    sigset_t	previous;
    sigset_t   	mask;
	int 		ret = 0;
	OS_RtmTimeoutRecord_t *timeout = 0;

	if(OS_RtmData.State == OS_RTM_STATE_REALTIME)
	{
		struct timespec time;

		clock_gettime(CLOCK_REALTIME, &time);

		OS_RtmTimeAddMicroseconds(&time, usec);
		ret = pthread_cond_timedwait(cond, mutex, &time);

		if(OS_RtmIsTimeGTECurrentTime(&time) == FALSE)
		{
			ret = ETIMEDOUT;
		}

	    return ret;
	}
	else
	{
		timeout = OS_RtmAllocTimeoutRecord();

		/* Check to see if we found one. */
		if(timeout == 0)
		{
			/* We didn't find one.  Unlock and return an error. */
			OS_printf("OSAL:  OS_RtmAllocTimeoutRecord() failed to return a record.  Exiting\n");
			exit(-1);
		}

		/* We got one.  Get the current time, add the relative timed wait to it,
		 * and set the timeout with that absolute time.
		 */
		timeout->Owner = syscall(SYS_gettid);
		OS_RtmGetCurrentTime(&timeout->Time);
		OS_RtmTimeAddMicroseconds(&timeout->Time, usec);
		timeout->CV = cond;
		timeout->Mut = mutex;
		timeout->TimedOut = FALSE;

//		pthread_mutex_lock(&OS_RtmData.Mut);
//		pthread_cond_broadcast(&OS_RtmData.CV);
//		pthread_mutex_unlock(&OS_RtmData.Mut);
		ret = pthread_cond_wait(timeout->CV, timeout->Mut);
		if(timeout->TimedOut == TRUE)
		{
			ret = ETIMEDOUT;
		}

		OS_RtmFreeTimeoutRecord(timeout);

		return ret;
	}
}



OS_RtmTimeoutRecord_t* OS_RtmAllocTimeoutRecord(void)
{
	uint32 		i = 0;
	OS_RtmTimeoutRecord_t *timeout = 0;
    sigset_t	previous;
    sigset_t   	mask;

    OS_InterruptSafeLock(&OS_RtmData.AllocDeallocMut, &mask, &previous);

	/* Find an available record. */
	for(i = 0; i < OS_MAX_TIMEOUTS; ++i)
	{
		if(OS_RtmData.TimeoutTable[i].Free == TRUE)
		{
			/* Found one.  Save the record off and break out. */
			timeout = &OS_RtmData.TimeoutTable[i];
			break;
		}
	}

	if(timeout != 0)
	{
		timeout->TimedOut = FALSE;
		timeout->Enabled = TRUE;
		timeout->Free = FALSE;
		timeout->CV = 0;
		timeout->Mut = 0;
	}

    OS_InterruptSafeUnlock(&OS_RtmData.AllocDeallocMut, &previous);

	return timeout;
}



void OS_RtmFreeTimeoutRecord(OS_RtmTimeoutRecord_t* timeout)
{
    sigset_t	previous;
    sigset_t   	mask;

    OS_InterruptSafeLock(&OS_RtmData.AllocDeallocMut, &mask, &previous);

	if(timeout != 0)
	{
		timeout->TimedOut = FALSE;
		timeout->Enabled = FALSE;
		timeout->Free = TRUE;
		timeout->CV = 0;
		timeout->Mut = 0;
	}

    OS_InterruptSafeUnlock(&OS_RtmData.AllocDeallocMut, &previous);
}



/* Shared OSAL function */
OS_RunTimeModeEnum_t OS_RtmGetRunMode(void)
{
	return OS_RtmData.Mode;
}



/* Shared OSAL function */
int32 OS_RtmReplishTimeoutByCV(pthread_cond_t* cv, uint32 microseconds)
{
    sigset_t	previous;
    sigset_t   	mask;
    int32		Status = OS_ERROR;
	uint32 		i = 0;

    OS_InterruptSafeLock(&OS_RtmData.Mut, &mask, &previous);

	for(i = 0; i < OS_MAX_TIMEOUTS; ++i)
	{
		OS_RtmTimeoutRecord_t *timeout = &OS_RtmData.TimeoutTable[i];
		if(timeout->Free == FALSE)
		{
			if(timeout->CV == cv)
			{
				OS_RtmGetCurrentTime(&timeout->Time);

				OS_RtmTimeAddMicroseconds(&timeout->Time, microseconds);

			    pthread_cond_broadcast(&OS_RtmData.CV);

			    Status = OS_SUCCESS;
			}
		}
	}

    OS_InterruptSafeUnlock(&OS_RtmData.Mut, &previous);

    return Status;
}



/* Shared OSAL function */
int OS_NanoSleep(const struct timespec *requested_time, struct timespec *remaining)
{
	int rc = 0;

	if((OS_RtmData.State == OS_RTM_STATE_REALTIME)
			|| (OS_RtmData.State == OS_RTM_STATE_NONREALTIME_PRERUN))
	{
		rc = nanosleep(requested_time, remaining);
	}
	else
	{
		pthread_cond_t cond;
		pthread_mutex_t mutex;
		pthread_mutexattr_t attr;

		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutexattr_settype(&attr, PTHREAD_PRIO_INHERIT);

		pthread_cond_init(&cond, 0);
		pthread_mutexattr_init(&attr);
		pthread_mutex_init(&mutex, &attr);
		uint32 micros = (requested_time->tv_sec * 1000000) + (requested_time->tv_nsec / 1000);

		pthread_mutex_lock(&mutex);
		do
		{
			rc = OS_RtmCondTimedWait(&cond, &mutex, micros);
		} while (rc != ETIMEDOUT);
		pthread_mutex_unlock(&mutex);

		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);

	}

	return rc;
}



/* Public function */
void OS_RtmSetMajorAndMinorFrame(uint32 MajorFrameLength, uint32 MinorFramesPerMajorFrame)
{
	OS_RtmData.MajorFrameLength = MajorFrameLength;
	OS_RtmData.MinorFramesPerMajorFrame = MinorFramesPerMajorFrame;
	OS_RtmData.MinorFrameLength = OS_RtmData.MajorFrameLength / OS_RtmData.MinorFramesPerMajorFrame;
}



void OS_RtmStepNextFrame(void)
{
    sigset_t        previous;
    sigset_t        mask;
    static uint32          arteMinorFrame = 0;
    uint32          arteFrameCount = 0;
    uint32          frameDelta;
    struct timespec newFrameStartTime;
    struct timespec newStopTime;
    uint32          usToAdvance;
    int32           returnCode = 0;

    /* Step the external source to the next frame. */
    returnCode = OS_ArteStepNext(&arteFrameCount, &arteMinorFrame);
    if(returnCode < 0)
    {
    	/* ARTE failed.  No sense on staying alive.  Inform the user and exit.
    	 */
        OS_printf("\nOSAL: OS_ArteStepNext() failed.  Exiting Airliner\n");
        exit(0);
    }
//    arteMinorFrame++;
    if(arteMinorFrame >= OS_RtmData.MinorFramesPerMajorFrame)
    {
    	arteMinorFrame = 0;
    }

    /* Determine how many frames we should advance.  This should be 1, unless
     * we missed a message or two, but we also have to account for rollover.
     * Assume that we cannot lose more than a major frames worth of messages.
     */
    if(arteMinorFrame > OS_RtmData.CurrentMinorFrame)
    {
    	/* No roll over detected. */
        frameDelta = arteMinorFrame - OS_RtmData.CurrentMinorFrame;
    }
    else
    {
    	/* Roll over detected. */
    	frameDelta = OS_RtmData.MinorFramesPerMajorFrame -
    			OS_RtmData.CurrentMinorFrame + arteMinorFrame;
    }

    /* Set the minor frame. */
    OS_RtmData.CurrentMinorFrame = arteMinorFrame;

    /* Calculate the number of microseconds to advance the time. */
    usToAdvance = frameDelta * OS_RtmData.MinorFrameLength;

    /* Set the new frame start time. */
    OS_RtmTimeAddMicroseconds(&OS_RtmData.FrameStartTime.Time, usToAdvance);

    /* Calculate and set the new stop time. */
    OS_RtmData.StopTime.Time.tv_sec = OS_RtmData.FrameStartTime.Time.tv_sec;
    OS_RtmData.StopTime.Time.tv_nsec = OS_RtmData.FrameStartTime.Time.tv_nsec;
    OS_RtmData.StopTime.Valid = TRUE;
    OS_RtmTimeAddMicroseconds(&OS_RtmData.StopTime.Time, OS_RtmData.MinorFrameLength);

	//OS_printf("Starting Frame %u\n", OS_RtmData.CurrentMinorFrame);

    /* Set the new current time. */
    OS_RtmSetCurrentTime(&OS_RtmData.FrameStartTime.Time);
}



/* Public function */
uint32 OS_RtmGetCurrentMinorFrame(void)
{
    return OS_RtmData.CurrentMinorFrame;
}



/* Public function */
void  OS_RtmEndFrame(void)
{
    sigset_t	previous;
    sigset_t   	mask;

    OS_InterruptSafeLock(&OS_RtmData.Mut, &mask, &previous);
    if(OS_RtmData.Mode == OS_RUNTIME_MODE_NONREALTIME)
    {
    	//OS_printf("End of Frame %u\n", OS_RtmData.CurrentMinorFrame);
    	OS_RtmData.State = OS_RTM_STATE_NONREALTIME_STEP_NEXT_FRAME;
    	pthread_cond_broadcast(&OS_RtmData.CV);
    }
    else
    {
    	OS_RtmData.CurrentMinorFrame++;
    	if(OS_RtmData.CurrentMinorFrame >= OS_RtmData.MinorFramesPerMajorFrame)
    	{
    		/* Roll over */
    		OS_RtmData.CurrentMinorFrame = 0;
    	}
    }
    OS_InterruptSafeUnlock(&OS_RtmData.Mut, &previous);
}
