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

/*
** The __USE_UNIX98 is for advanced pthread features on linux
*/
#define __USE_UNIX98
#include <pthread.h>

#include "common_types.h"
#include "osapi.h"

#include <sys/types.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/signal.h>
#include <sys/errno.h>
#include "osrtm.h"

/****************************************************************************************
                                EXTERNAL FUNCTION PROTOTYPES
****************************************************************************************/

extern uint32 OS_FindCreator(void);
extern int    OS_InterruptSafeLock(pthread_mutex_t *lock, sigset_t *set, sigset_t *previous);
extern void   OS_InterruptSafeUnlock(pthread_mutex_t *lock, sigset_t *previous);
extern int32  OS_PriorityRemap(uint32 InputPri);

extern pthread_mutex_t OS_task_table_mut;


/****************************************************************************************
                                INTERNAL FUNCTION PROTOTYPES
****************************************************************************************/

void  OS_TimespecToUsec(struct timespec time_spec, uint32 *usecs);
void  OS_UsecToTimespec(uint32 usecs, struct timespec *time_spec);

/****************************************************************************************
                                     DEFINES
****************************************************************************************/

/*
** The timers use the RT Signals. The system that this code was developed
** and tested on has 32 available RT signals ( SIGRTMIN -> SIGRTMAX ).
** OS_MAX_TIMERS should not be set to more than this number.
*/
#define OS_STARTING_SIGNAL  (SIGRTMAX-1)

/*
** Since the API is storing the timer values in a 32 bit integer as Microseconds, 
** there is a limit to the number of seconds that can be represented.
*/
#define MAX_SECS_IN_USEC 4293

#define UNINITIALIZED 0

/****************************************************************************************
                                    LOCAL TYPEDEFS 
****************************************************************************************/

typedef struct 
{
   uint32              free;
   char                name[OS_MAX_API_NAME];
   uint32              creator;
   uint32              start_time;
   uint32              interval_time;
   uint32              accuracy;
   OS_TimerCallback_t  callback_ptr;
   uint32              host_timerid;
   pthread_t 		   nonrealtime_pthread;
   pthread_cond_t  	   cv;
   pthread_mutex_t     mut;
   boolean			   isSet;
} OS_timer_record_t;

/****************************************************************************************
                                   GLOBAL DATA
****************************************************************************************/

OS_timer_record_t OS_timer_table[OS_MAX_TIMERS];
uint32           os_clock_accuracy;

/*
** The Mutex for protecting the above table
*/
pthread_mutex_t    OS_timer_table_mut;

/****************************************************************************************
                                INITIALIZATION FUNCTION
****************************************************************************************/
int32  OS_TimerAPIInit ( void )
{
   int    i;   
   int    status;
   struct timespec clock_resolution;
   int32  return_code = OS_SUCCESS;

   /*
   ** Initialize and mark all timers as available
   */
    for ( i = 0; i < OS_MAX_TIMERS; i++ )
    {
	    int ret = 0;
        OS_timer_table[i].free      = TRUE;
        OS_timer_table[i].isSet     = FALSE;
        OS_timer_table[i].creator   = UNINITIALIZED;
        strcpy(OS_timer_table[i].name,"");

        ret = pthread_cond_init(&(OS_timer_table[i].cv), NULL);
  	    if ( ret < 0 )
  	    {
            return OS_ERROR;
  	    }

  	    pthread_mutexattr_t attr;
    	pthread_mutexattr_init(&attr);
    	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    	pthread_mutexattr_settype(&attr, PTHREAD_PRIO_INHERIT);
    	ret = pthread_mutex_init((pthread_mutex_t *)&(OS_timer_table[i].mut), &attr);
        if ( ret < 0 )
        {
            return OS_ERROR;
        }
    }

   /*
   ** get the resolution of the realtime clock
   */
   status = clock_getres(CLOCK_REALTIME, &clock_resolution);
   if ( status < 0 )
   {
      return_code = OS_ERROR;
   }  
   else
   { 
      /*
      ** Convert to microseconds
      */
      OS_TimespecToUsec(clock_resolution, &os_clock_accuracy);
   
      /*
      ** Create the Timer Table mutex
      */
  	  pthread_mutexattr_t attr;
  	  pthread_mutexattr_init(&attr);
  	  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  	  pthread_mutexattr_settype(&attr, PTHREAD_PRIO_INHERIT);
      status = pthread_mutex_init((pthread_mutex_t *) & OS_timer_table_mut, &attr);
      if ( status < 0 )
      {
         return_code = OS_ERROR;
      }
   }
   return(return_code);

}

/****************************************************************************************
                                INTERNAL FUNCTIONS
****************************************************************************************/
void OS_RtmDisplayDebugInfo(void);

/*
** Timer Signal Handler.
** The purpose of this function is to convert the POSIX signal number to the 
** OSAL signal number and pass it to the User defined signal handler.
*/
void OS_TimerSignalHandler(int signum)
{
    sigset_t previous;
    sigset_t mask;
    uint32   timer_id = 0;

    timer_id = OS_STARTING_SIGNAL - signum;

    if ( timer_id  < OS_MAX_TIMERS )
    {
    	OS_InterruptSafeLock(&OS_timer_table_mut, &mask, &previous);
        if ( OS_timer_table[timer_id].free == FALSE )
        {
            (OS_timer_table[timer_id].callback_ptr)(timer_id);
        }
        OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
    }
}

void OS_TimerNonrealtimeHandler(uint32 timer_id)
{
    sigset_t previous;
    sigset_t mask;
    int		 ret;

    OS_timer_record_t *timer = &OS_timer_table[timer_id];

	OS_InterruptSafeLock(&timer->mut, &mask, &previous);
	while(1)
	{
	    if(timer->mut.__data.__owner == 0)
	    {
	    	OS_printf("Bug encountered (2)\n");
	    	exit(-1);
	    }
		uint32 micros = timer->start_time + timer->interval_time;
		do
		{
		    if(timer->mut.__data.__owner == 0)
		    {
		    	OS_printf("Bug encountered (3)\n");
		    	exit(-1);
		    }

		    //OS_printf("1\n");
			//OS_RtmDisplayDebugInfo();
		    //OS_printf("2\n");
			ret = OS_RtmCondTimedWait(&timer->cv, &timer->mut, micros);
		    //OS_printf("3\n");
			//OS_RtmDisplayDebugInfo();
		    //OS_printf("4\n");
		} while (ret != ETIMEDOUT);

        timer->start_time = 0;

        (OS_timer_table[timer_id].callback_ptr)(timer_id);
	}
	OS_InterruptSafeUnlock(&timer->mut, &previous);
}
 
/******************************************************************************
 **  Function:  OS_UsecToTimespec
 **
 **  Purpose:  Convert Microseconds to a POSIX timespec structure.
 **
 */
void OS_UsecToTimespec(uint32 usecs, struct timespec *time_spec)
{
	
   if ( usecs < 1000000 )
   {
      time_spec->tv_nsec = (usecs * 1000);
      time_spec->tv_sec = 0;
   }
   else
   {
      time_spec->tv_sec = usecs / 1000000;
      time_spec->tv_nsec = (usecs % 1000000) * 1000;
   }
	
}

/******************************************************************************
 **  Function:  OS_TimespecToUsec
 **
 **  Purpose:  Convert a POSIX timespec structure to microseconds
 **
 */
void  OS_TimespecToUsec(struct timespec time_spec, uint32 *usecs)
{
   if ( (*usecs) < 1000000 )
   {
      *usecs = time_spec.tv_nsec / 1000;
   }
   else
   {
      /*
      ** Need to account for maximum number of seconds that will fit in the 
      ** 32 bit usec integer
      */
      if ( time_spec.tv_sec > MAX_SECS_IN_USEC )
      {
         time_spec.tv_sec = MAX_SECS_IN_USEC;
      }
      *usecs = (time_spec.tv_sec * 1000000 ) + (time_spec.tv_nsec / 1000 );
   }
}



/****************************************************************************************
                                   Timer API
****************************************************************************************/

/******************************************************************************
**  Function:  OS_TimerCreate
**
**  Purpose:  Create a new OSAL Timer
**
**  Arguments:
**
**  Return:
*/
int32 OS_TimerCreate(uint32 *timer_id, const char *timer_name, uint32 *clock_accuracy, OS_TimerCallback_t  callback_ptr)
{
   uint32    possible_tid;
   int32     i;
   sigset_t  previous;
   sigset_t  mask;

   int                status;
   struct  sigaction  sig_act;
   struct  sigevent   evp;

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
   OS_InterruptSafeLock(&OS_timer_table_mut, &mask, &previous);
    
   for(possible_tid = 0; possible_tid < OS_MAX_TIMERS; possible_tid++)
   {
      if (OS_timer_table[possible_tid].free == TRUE)
         break;
   }


   if( possible_tid >= OS_MAX_TIMERS || OS_timer_table[possible_tid].free != TRUE)
   {
        OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
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
            OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
            return OS_ERR_NAME_TAKEN;
       }
   }

   /*
   ** Verify callback parameter
   */
   if (callback_ptr == NULL ) 
   {
      OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
      return OS_TIMER_ERR_INVALID_ARGS;
   }    

   /* 
   ** Set the possible timer Id to not free so that
   ** no other task can try to use it 
   */
   OS_timer_table[possible_tid].free = FALSE;
   OS_timer_table[possible_tid].isSet = FALSE;
   OS_timer_table[possible_tid].creator = OS_FindCreator();
   strncpy(OS_timer_table[possible_tid].name, timer_name, OS_MAX_API_NAME);
   OS_timer_table[possible_tid].start_time = 0;
   OS_timer_table[possible_tid].interval_time = 0;

   OS_timer_table[possible_tid].callback_ptr = callback_ptr;

   /*
   **  Initialize the sigaction and sigevent structures for the handler.
   */
   memset((void *)&sig_act, 0, sizeof(sig_act));
   sigemptyset(&sig_act.sa_mask);
   sig_act.sa_handler = OS_TimerSignalHandler;
//   sig_act.sa_flags = SA_RESTART;

   memset((void *)&evp, 0, sizeof(evp));
   evp.sigev_notify = SIGEV_SIGNAL; 
   evp.sigev_signo = OS_STARTING_SIGNAL - possible_tid;

   if(OS_RtmGetRunMode() == OS_RUNTIME_MODE_REALTIME)
   {
	   /*
	    ** Create the timer
	    */
	   status = timer_create(CLOCK_REALTIME, &evp, (timer_t *)&(OS_timer_table[possible_tid].host_timerid));
	   if (status < 0)
	   {
		   OS_timer_table[possible_tid].free = TRUE;
		   OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
		   return ( OS_TIMER_ERR_UNAVAILABLE);
	   }

	   /*
	    ** Set the signal action for the timer
	    */
	   sigaction(OS_STARTING_SIGNAL - possible_tid, &(sig_act), 0);
    }
   
    /*
    ** Return the clock accuracy to the user
    */
    *clock_accuracy = os_clock_accuracy;

    /*
    ** Return timer ID
    */
    *timer_id = possible_tid;

    OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);

    return OS_SUCCESS;
}

/******************************************************************************
**  Function:  OS_TimerSet
**
**  Purpose:  
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 OS_TimerSet(uint32 timer_id, uint32 start_time, uint32 interval_time)
{
   int    status;
   struct itimerspec timeout;
   sigset_t	previous;
   sigset_t   	mask;

   /* 
   ** Check to see if the timer_id given is valid 
   */
   if (timer_id >= OS_MAX_TIMERS || OS_timer_table[timer_id].free == TRUE)
   {
      return OS_ERR_INVALID_ID;
   }

   /*
   ** Round up the accuracy of the start time and interval times 
   */
   if (( start_time > 0 ) && ( start_time < os_clock_accuracy ))
   {
      start_time = os_clock_accuracy;
   }
 
   if (( interval_time > 0) && ( interval_time < os_clock_accuracy ))
   {
      interval_time = os_clock_accuracy;
   }

   OS_timer_record_t *timer = &OS_timer_table[timer_id];

   /*
   ** Save the start and interval times 
   */
   timer->start_time = start_time;
   timer->interval_time = interval_time;

   /*
   ** Convert from Microseconds to timespec structures
   */
   OS_UsecToTimespec(start_time, &(timeout.it_value));
   OS_UsecToTimespec(interval_time, &(timeout.it_interval));

   if(OS_RtmGetRunMode() == OS_RUNTIME_MODE_REALTIME)
   {
	   /*
	   ** Program the real timer
	   */
	   status = timer_settime((timer_t)(timer->host_timerid),
                             0,              /* Flags field can be zero */
                             &timeout,       /* struct itimerspec */
		            		 0);         /* Oldvalue */
	   if (status < 0)
	   {
		   return ( OS_TIMER_ERR_INTERNAL);
	   }
   }
   else
   {
	   /* Check to see if the timer has ever been set. */
	   if(timer->isSet == TRUE)
	   {
		   /* Timer has already been set.  Just replenish it. */
		   OS_RtmReplishTimeoutByCV(&timer->cv, interval_time);
	   }
	   else
	   {
		   /* Timer has never been set.  Create the handler thread.
		    */
           timer->isSet = TRUE;
           timer->start_time = 0;

		   pthread_attr_t     custom_attr ;
		   struct sched_param priority_holder ;
	       int return_code = 0;
	       OS_task_prop_t taskProp;

	       uint32 callerTaskID = OS_TaskGetId();
	       OS_TaskGetInfo(callerTaskID, &taskProp);

		   /*
		    ** Initialize the pthread_attr structure.
		    ** The structure is used to set the stack and priority
		    */
		   memset(&custom_attr, 0, sizeof(custom_attr));
		   if(pthread_attr_init(&custom_attr))
		   {
		       OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);

		       #ifdef OS_DEBUG_PRINTF
		           printf("pthread_attr_init error in OS_TimerCreate, Timer ID = %d\n", possible_tid);
		       	   perror("pthread_attr_init");
		       #endif
		       return(OS_ERROR);
		   }

		   /* Set in thread to the detached state so Valgrind memcheck doesn't
		    * complain about lost records.
		    */
		   if(pthread_attr_setdetachstate(&custom_attr, PTHREAD_CREATE_DETACHED))
		   {
		       OS_printf("OSAL:  pthread_attr_setdetachstate error in OS_TimerCreate.  %i\n", errno);
		       return(OS_ERROR);
		   }

		   /*
		   ** Test to see if the user is running as root.
		   ** root is required to set the scheduling policy, stack, and priority
		   */
		   if (geteuid() == 0 )
		   {
	//            int inheritsched = PTHREAD_EXPLICIT_SCHED;
	//
	//            /*
	//	        ** Set the scheduling inherit attribute to EXPLICIT
	//	        */
	//	        return_code = pthread_attr_setinheritsched(&custom_attr, inheritsched);
	//	        if ( return_code < 0 )
	//	        {
	//	            #ifdef OS_DEBUG_PRINTF
	//	                printf("pthread_attr_setinheritsched error in OS_TimerCreate, Timer ID = %d, errno = %s\n",
	//	                    possible_tid,strerror(errno));
	//	            #endif
	//		        OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
	//	            return(OS_ERROR);
	//	        }
	//
	//	        /*
	//	        ** Set the scheduling policy
	//	        ** On Linux, the schedpolicy must be SCHED_FIFO or SCHED_RR to set the priorty
	//	        */
	//	        if (pthread_attr_setschedpolicy(&custom_attr, SCHED_FIFO))
	//	        {
	//	            #ifdef OS_DEBUG_PRINTF
	//	                printf("pthread_attr_setschedpolity error in OS_TimerCreate, Timer ID = %d\n", possible_tid);
	//	            #endif
	//	            OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
	//	            return(OS_ERROR);
	//	        }
	//
	//	        /*
	//	        ** Set priority
	//	        */
	//	        int32 osPriority = OS_PriorityRemap(taskProp.priority);
	//	        memset(&priority_holder, 0, sizeof(priority_holder));
	//	        priority_holder.sched_priority = osPriority;
	//	        return_code = pthread_attr_setschedparam(&custom_attr, &priority_holder);
	//	        if(return_code !=0)
	//	        {
	//	            #ifdef OS_DEBUG_PRINTF
	//	                printf("pthread_attr_setschedparam error in OS_TimerCreate, Timer ID = %d\n", possible_tid);
	//	            #endif
	//	            OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
	//	            return(OS_ERROR);
	//	        }
	       } /* End if user is root */

		   /*
		   ** Create thread
		   */
		   return_code = pthread_create(&timer->nonrealtime_pthread,
		                                &custom_attr,
		                                (void* (*)(void*))OS_TimerNonrealtimeHandler,
		                                (void *)timer_id);
		   if (return_code != 0)
		   {
		       OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
		       #ifdef OS_DEBUG_PRINTF
		          printf("pthread_create error in OS_TimerCreate, Timer ID = %d\n", possible_tid);
		       #endif
		       return(OS_ERROR);
		   }

		   return_code = pthread_attr_destroy(&custom_attr);
		   if (return_code !=0)
		   {
		       OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
		       #ifdef OS_DEBUG_PRINTF
		          printf("pthread_attr_destroy error in OS_TimerCreate, Timer ID = %d\n", possible_tid);
		       #endif
		       return(OS_ERROR);
		   }
	   }
	   /* Yield to let the */
   }

   return OS_SUCCESS;
}


/******************************************************************************
**  Function:  OS_TimerDelete
**
**  Purpose: 
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 OS_TimerDelete(uint32 timer_id)
{
    int status;
    sigset_t	previous;
    sigset_t   	mask;

    /*
    ** Check to see if the timer_id given is valid
    */
    OS_InterruptSafeLock(&OS_timer_table_mut, &mask, &previous);
    if (timer_id >= OS_MAX_TIMERS || OS_timer_table[timer_id].free == TRUE)
    {
	    OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
        return OS_ERR_INVALID_ID;
    }

    /*
    ** Delete the timer
    */

    if(OS_RtmGetRunMode() == OS_RUNTIME_MODE_REALTIME)
    {
	    status = timer_delete((timer_t)(OS_timer_table[timer_id].host_timerid));
	    OS_timer_table[timer_id].free = TRUE;
	    if (status < 0)
	    {
		    OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
		    return ( OS_TIMER_ERR_INTERNAL);
	    }
    }
    else
    {

    }

    OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);
    return OS_SUCCESS;
}

/***********************************************************************************
**
**    Name: OS_TimerGetIdByName
**
**    Purpose: This function tries to find a Timer Id given the name 
**             The id is returned through timer_id
**
**    Returns: OS_INVALID_POINTER if timer_id or timer_name are NULL pointers
**             OS_ERR_NAME_TOO_LONG if the name given is to long to have been stored
**             OS_ERR_NAME_NOT_FOUND if the name was not found in the table
**             OS_SUCCESS if success
**             
*/
int32 OS_TimerGetIdByName (uint32 *timer_id, const char *timer_name)
{
    uint32 i;

    if (timer_id == NULL || timer_name == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* 
    ** a name too long wouldn't have been allowed in the first place
    ** so we definitely won't find a name too long
    */
    if (strlen(timer_name) > OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_TIMERS; i++)
    {
        if (OS_timer_table[i].free != TRUE &&
                (strcmp (OS_timer_table[i].name , (char*) timer_name) == 0))
        {
            *timer_id = i;
            return OS_SUCCESS;
        }
    }
   
    /* 
    ** The name was not found in the table,
    **  or it was, and the sem_id isn't valid anymore 
    */
    return OS_ERR_NAME_NOT_FOUND;
    
}/* end OS_TimerGetIdByName */

/***************************************************************************************
**    Name: OS_TimerGetInfo
**
**    Purpose: This function will pass back a pointer to structure that contains 
**             all of the relevant info( name and creator) about the specified timer.
**             
**    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid timer 
**             OS_INVALID_POINTER if the timer_prop pointer is null
**             OS_SUCCESS if success
*/
int32 OS_TimerGetInfo (uint32 timer_id, OS_timer_prop_t *timer_prop)  
{
    sigset_t  previous;
    sigset_t  mask;

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
    OS_InterruptSafeLock(&OS_timer_table_mut, &mask, &previous);

    timer_prop ->creator       = OS_timer_table[timer_id].creator;
    strcpy(timer_prop-> name, OS_timer_table[timer_id].name);
    timer_prop ->start_time    = OS_timer_table[timer_id].start_time;
    timer_prop ->interval_time = OS_timer_table[timer_id].interval_time;
    timer_prop ->accuracy      = OS_timer_table[timer_id].accuracy;
    
    OS_InterruptSafeUnlock(&OS_timer_table_mut, &previous);

    return OS_SUCCESS;
    
} /* end OS_TimerGetInfo */


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
