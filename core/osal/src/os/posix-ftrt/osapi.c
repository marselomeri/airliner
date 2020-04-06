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
#define _GNU_SOURCE
#include <pthread.h>

#include <limits.h>
#include <time.h>
#include "osrtm.h"
#include <unistd.h>

/*
** User defined include files
*/
#include "common_types.h"
#include "osapi.h"
#include "osrtm.h"

/*
** Defines
*/
#ifndef SEM_VALUE_MAX
#define SEM_VALUE_MAX INT_MAX
#endif

#define UNINITIALIZED 0
#define MAX_PRIORITY 255
#ifndef PTHREAD_STACK_MIN
   #define PTHREAD_STACK_MIN 8092
#endif

#define OS_API_UNINITIALIZED 0
#define OS_API_INITIALIZED   1

#define OS_SHUTDOWN_MAGIC_NUMBER    0xABADC0DE


/* To remove the "implicit declaration of function ‘pthread_setname_np’" warning. */
extern int pthread_setname_np (pthread_t __target_thread, const char *__name);


/*
** Global data for the API
*/

/*  
** Tables for the properties of objects 
*/
uint32 OS_API_Initialized = OS_API_UNINITIALIZED;

/*tasks */
typedef struct
{
    int       free;
    pthread_t id;
    char      name [OS_MAX_API_NAME];
    int       creator;
    uint32    stack_size;
    uint32    priority;
    void     *delete_hook_pointer;
}OS_task_record_t;
    
/* queues */
typedef struct
{
	uint32	size;
	char buffer[OS_MAX_QUEUE_WIDTH];
}OS_queue_data_t;

typedef struct
{
    int    		free;
    OS_queue_data_t	qData[OS_MAX_QUEUE_DEPTH];
    uint32 		max_size;
    char   		name [OS_MAX_API_NAME];
    int    		creator;
    pthread_cond_t      cv;
    pthread_mutex_t     mut;
    int32	  	head;
    int32   		tail;
    uint32   		width;
    uint32   		depth;
    uint32		queuedCount;
}OS_queue_record_t;

/* Binary Semaphores */
typedef struct
{
    int             free;
    pthread_cond_t  cv;
    pthread_mutex_t mut;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
}OS_bin_sem_record_t;

/*Counting Semaphores */
typedef struct
{
    int             free;
    pthread_cond_t  cv;
    pthread_mutex_t mut;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
}OS_count_sem_record_t;

/* Mutexes */
typedef struct
{
    int             free;
    pthread_mutex_t mut;
    uint32			lock_count;
    char            name [OS_MAX_API_NAME];
    int             creator;
    pthread_t		locked_by;
}OS_mut_sem_record_t;

/* function pointer type */
typedef void (*FuncPtr_t)(void);

/* Tables where the OS object information is stored */
OS_task_record_t    OS_task_table          [OS_MAX_TASKS];
OS_queue_record_t   OS_queue_table         [OS_MAX_QUEUES];
OS_bin_sem_record_t OS_bin_sem_table       [OS_MAX_BIN_SEMAPHORES];
OS_count_sem_record_t OS_count_sem_table   [OS_MAX_COUNT_SEMAPHORES];
OS_mut_sem_record_t OS_mut_sem_table       [OS_MAX_MUTEXES];

pthread_key_t    thread_key;

pthread_mutex_t OS_task_table_mut;
pthread_mutex_t OS_queue_table_mut;
pthread_mutex_t OS_bin_sem_table_mut;
pthread_mutex_t OS_mut_sem_table_mut;
pthread_mutex_t OS_count_sem_table_mut;
pthread_mutex_t OS_timeout_table_mut;

uint32          OS_printf_enabled = TRUE;
volatile uint32 OS_shutdown = FALSE;


/*
** Local Function Prototypes
*/
//void    OS_CompAbsDelayTime( uint32 milli_second , struct timespec * tm);
void    OS_ThreadKillHandler(int sig );
uint32  OS_FindCreator(void);
int32   OS_PriorityRemap(uint32 InputPri);
int     OS_InterruptSafeLock(pthread_mutex_t *lock, sigset_t *set, sigset_t *previous);
void    OS_InterruptSafeUnlock(pthread_mutex_t *lock, sigset_t *previous);



/*---------------------------------------------------------------------------------------
   Name: OS_API_Init

   Purpose: Initialize the tables that the OS API uses to keep track of information
            about objects

   returns: OS_SUCCESS or OS_ERROR
---------------------------------------------------------------------------------------*/
int32 OS_API_Init(void)
{
	return OS_API_InitEx(OS_RUNTIME_MODE_REALTIME);
}

void rek(double test[100])
{
	rek(test);
}

/*---------------------------------------------------------------------------------------
   Name: OS_API_InitEx

   Purpose: Initialize the tables that the OS API uses to keep track of information
            about objects

   returns: OS_SUCCESS or OS_ERROR
---------------------------------------------------------------------------------------*/
int32 OS_API_InitEx(OS_RunTimeModeEnum_t RunMode)
{
   int                 i;
   int                 ret;
   pthread_mutexattr_t mutex_attr ;    
   int32               return_code = OS_SUCCESS;
   struct sched_param  param;
   int                 sched_policy;

   /* Initialize Task Table */

   for(i = 0; i < OS_MAX_TASKS; i++)
   {
        OS_task_table[i].free                = TRUE;
        OS_task_table[i].creator             = UNINITIALIZED;
        OS_task_table[i].delete_hook_pointer = NULL;
        strcpy(OS_task_table[i].name,"");    
    }

    /* Initialize Message Queue Table */

    for(i = 0; i < OS_MAX_QUEUES; i++)
    {
        OS_queue_table[i].free        = TRUE;
        OS_queue_table[i].creator     = UNINITIALIZED;
        strcpy(OS_queue_table[i].name,""); 
    }

    /* Initialize Binary Semaphore Table */

    for(i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
        OS_bin_sem_table[i].free        = TRUE;
        OS_bin_sem_table[i].creator     = UNINITIALIZED;
        strcpy(OS_bin_sem_table[i].name,"");
    }

    /* Initialize Counting Semaphores */
    for(i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
        OS_count_sem_table[i].free        = TRUE;
        OS_count_sem_table[i].creator     = UNINITIALIZED;
        strcpy(OS_count_sem_table[i].name,"");
    }

    /* Initialize Mutex Semaphore Table */
    for(i = 0; i < OS_MAX_MUTEXES; i++)
    {
        OS_mut_sem_table[i].free        = TRUE;
        OS_mut_sem_table[i].creator     = UNINITIALIZED;
        strcpy(OS_mut_sem_table[i].name,"");
    }

   /*
   ** Initialize the module loader
   */
   #ifdef OS_INCLUDE_MODULE_LOADER
      return_code = OS_ModuleTableInit();
      if ( return_code == OS_ERROR )
      {
         return(return_code);
      }
   #endif

   /*
   ** Initialize the Timer API
   */
   return_code = OS_TimerAPIInit();
   if ( return_code == OS_ERROR )
   {
      return(return_code);
   }

   ret = pthread_key_create(&thread_key, NULL );
   if ( ret != 0 )
   {
      #ifdef OS_DEBUG_PRINTF
        printf("Error creating thread key\n");
      #endif
      return_code = OS_ERROR;
      return(return_code);
   }

   /* 
   ** initialize the pthread mutex attribute structure with default values 
   */
   return_code = pthread_mutexattr_init(&mutex_attr); 
   if ( return_code != 0 )
   {
      #ifdef OS_DEBUG_PRINTF
         printf("Error: pthread_mutexattr_init failed\n");
      #endif
      return_code = OS_ERROR;
      return (return_code);
   }

   pthread_mutexattr_setrobust(&mutex_attr, PTHREAD_MUTEX_ROBUST);

   /*
   ** Allow the mutex to use priority inheritance
   */  
   return_code = pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT) ;
   if ( return_code != 0 )
   {
      #ifdef OS_DEBUG_PRINTF
         printf("Error: pthread_mutexattr_setprotocol failed\n");
      #endif
      return_code = OS_ERROR;
      return (return_code);
   }	

   /*
   **  Set the mutex type to ERRORCHECK so deadlocked mutexes due to
   **  terminated tasks can be recovered.
   */
   return_code = pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);
   if ( return_code != 0 )
   {
      #ifdef OS_DEBUG_PRINTF
         printf("Error: pthread_mutexattr_settype failed\n");
      #endif
      return_code = OS_ERROR;
      return (return_code);
   }

   /*
   ** create the mutexes that protect the OSAPI structures 
   ** the function returns on error, since we dont want to go through
   ** the extra trouble of creating and deleting resoruces for nothing
   */   
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_task_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_queue_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_bin_sem_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_count_sem_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_mut_sem_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }
   ret = pthread_mutex_init((pthread_mutex_t *)&OS_timeout_table_mut, &mutex_attr);
   if ( ret != 0 )
   {
      return_code = OS_ERROR;
      return(return_code);
   }

   /*
   ** Test to see if the user is running as root.
   ** root is required to set the scheduling policy, stack, and priority
   */
   if (geteuid() == 0 )
   {
       pthread_attr_t     custom_attr ;
       /*
       ** Set the scheduling policy
       ** On Linux, the schedpolity must be SCHED_FIFO or SCHED_RR to set the priorty
       */
       memset(&custom_attr, 0, sizeof(custom_attr));
       if (pthread_attr_setschedpolicy(&custom_attr, SCHED_FIFO))
       {
           #ifdef OS_DEBUG_PRINTF
               printf("OSAL:  pthread_attr_setschedpolity error in OS_API_InitEx\n");
           #endif
           return(OS_ERROR);
       }
   }

   /*
   ** File system init
   */
   return_code = OS_FS_Init();

   /*
   ** Raise the priority of the current (main) thread so that subsequent
   ** application initialization will complete.  This had previously been
   ** done by the BSP and but it is moved here.
   **
   ** This will only work if the user owning this process has permission
   ** to create real time threads.  Otherwise, the default priority will
   ** be retained.
   **
   ** NOTE - previously this checked that (geteuid() == 0) before even
   ** trying this, however that assumes that only uid 0 will be able to do
   ** this, which is not necessarily true, some linuxes have fine-grained
   ** permissions which could allow a non-root user to do this too.
   */
   ret = pthread_getschedparam(pthread_self(), &sched_policy, &param);
   if (ret == 0)
   {
        sched_policy = SCHED_FIFO;
        param.sched_priority = sched_get_priority_max(sched_policy);
        ret = pthread_setschedparam(pthread_self(), sched_policy, &param);
        if (ret != 0)
        {
        #ifdef OS_DEBUG_PRINTF
        printf("OS_API_Init: Could not set scheduleparam in main thread, error=%d\n",ret);
        #endif
        }
   }
   else
   {
        #ifdef OS_DEBUG_PRINTF
        printf("OS_API_Init: Could not get scheduleparam in main thread, error=%d\n",ret);
        #endif
   }

   if(return_code == OS_SUCCESS)
   {
	   return_code = OS_RtmInit(RunMode);
	   if(return_code == OS_SUCCESS)
	   {
		   OS_API_Initialized = OS_API_INITIALIZED;
	   }
	   else
	   {
		   printf("OSAL:  OS_RtmInit() failed.\n");
	   }
   }

   return(return_code);
}




/*---------------------------------------------------------------------------------------
   Name: OS_ApplicationExit

   Purpose: Indicates that the OSAL application should exit and return control to the OS
         This is intended for e.g. scripted unit testing where the test needs to end
         without user intervention.  This function does not return.

    NOTES: This exits the entire process including tasks that have been created.
       It does not return.  Production embedded code typically would not ever call this.

---------------------------------------------------------------------------------------*/
void OS_ApplicationExit(int32 Status)
{
   if (Status == OS_SUCCESS)
   {
      exit(EXIT_SUCCESS);
   }
   else
   {
      exit(EXIT_FAILURE);
   }
}

/*---------------------------------------------------------------------------------------
   Name: OS_DeleteAllObjects

   Purpose: This task will delete all objects allocated by this instance of OSAL
            May be used during shutdown or by the unit tests to purge all state

   returns: no value
---------------------------------------------------------------------------------------*/
void OS_DeleteAllObjects       (void)
{
    uint32 i;

    for (i = 0; i < OS_MAX_TASKS; ++i)
    {
        OS_TaskDelete(i);
    }
    for (i = 0; i < OS_MAX_QUEUES; ++i)
    {
        OS_QueueDelete(i);
    }
    for (i = 0; i < OS_MAX_MUTEXES; ++i)
    {
        OS_MutSemDelete(i);
    }
    for (i = 0; i < OS_MAX_COUNT_SEMAPHORES; ++i)
    {
        OS_CountSemDelete(i);
    }
    for (i = 0; i < OS_MAX_BIN_SEMAPHORES; ++i)
    {
        OS_BinSemDelete(i);
    }
    for (i = 0; i < OS_MAX_TIMERS; ++i)
    {
        OS_TimerDelete(i);
    }
    for (i = 0; i < OS_MAX_MODULES; ++i)
    {
        OS_ModuleUnload(i);
    }
    for (i = 0; i < OS_MAX_NUM_OPEN_FILES; ++i)
    {
        OS_close(i);
    }
}


/*---------------------------------------------------------------------------------------
   Name: OS_IdleLoop

   Purpose: Should be called after all initialization is done
            This thread may be used to wait for and handle external events
            Typically just waits forever until "OS_shutdown" flag becomes true.

   returns: no value
---------------------------------------------------------------------------------------*/
void OS_IdleLoop()
{
   sigset_t mask;

   /* All signals should be unblocked in this thread while suspended */
   sigemptyset(&mask);

   while (OS_shutdown != OS_SHUTDOWN_MAGIC_NUMBER)
   {
      /* Unblock signals and wait for something to occur */
      //sigsuspend(&mask);
      sleep(1);
   }
}


/*---------------------------------------------------------------------------------------
   Name: OS_ApplicationShutdown

   Purpose: Indicates that the OSAL application should perform an orderly shutdown
       of ALL tasks, clean up all resources, and exit the application.

   returns: none

---------------------------------------------------------------------------------------*/
void OS_ApplicationShutdown(uint8 flag)
{
   if (flag == TRUE)
   {
      OS_shutdown = OS_SHUTDOWN_MAGIC_NUMBER;
   }

   /*
    * Raise a signal that is unblocked in OS_IdleLoop(),
    * which should break it out of the sigsuspend() call.
    */
   //kill(getpid(), SIGUSR1);
}



/*
**********************************************************************************
**          TASK API
**********************************************************************************
*/

/*---------------------------------------------------------------------------------------
   Name: OS_TaskCreate

   Purpose: Creates a task and starts running it.

   returns: OS_INVALID_POINTER if any of the necessary pointers are NULL
            OS_ERR_NAME_TOO_LONG if the name of the task is too long to be copied
            OS_ERR_INVALID_PRIORITY if the priority is bad
            OS_ERR_NO_FREE_IDS if there can be no more tasks created
            OS_ERR_NAME_TAKEN if the name specified is already used by a task
            OS_ERROR if the operating system calls fail
            OS_SUCCESS if success
            
    NOTES: task_id is passed back to the user as the ID. stack_pointer is usually null.
           the flags parameter is unused.

---------------------------------------------------------------------------------------*/
int32 OS_TaskCreate (uint32 *task_id, const char *task_name, osal_task_entry function_pointer,
                      uint32 *stack_pointer, uint32 stack_size, uint32 priority,
                      uint32 flags)
{
    int                return_code = 0;
    pthread_attr_t     custom_attr ;
    struct sched_param priority_holder ;
    int                possible_taskid;
    int                i;
    uint32             local_stack_size;
    int                ret;  
    int                os_priority;
    int                inheritsched;
    sigset_t           previous;
    sigset_t           mask;
    
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check for NULL pointers */    
    if( (task_name == NULL) || (function_pointer == NULL) || (task_id == NULL) )
    {
        return OS_INVALID_POINTER;
    }
    
    /* we don't want to allow names too long*/
    /* if truncated, two names might be the same */
    if (strlen(task_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Check for bad priority */
    if (priority > MAX_PRIORITY)
    {
        return OS_ERR_INVALID_PRIORITY;
    }

    /* Change OSAL priority into a priority that will work for this OS */
    os_priority = OS_PriorityRemap(priority);
    
    /* Check Parameters */
    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous); 

    for(possible_taskid = 0; possible_taskid < OS_MAX_TASKS; possible_taskid++)
    {
        if (OS_task_table[possible_taskid].free == TRUE)
        {
            break;
        }
    }

    /* Check to see if the id is out of bounds */
    if( possible_taskid >= OS_MAX_TASKS || OS_task_table[possible_taskid].free != TRUE)
    {
        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */ 
    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if ((OS_task_table[i].free == FALSE) &&
           ( strcmp((char*) task_name, OS_task_table[i].name) == 0)) 
        {       
            OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
            return OS_ERR_NAME_TAKEN;
        }
    }
    
    /* 
    ** Set the possible task Id to not free so that
    ** no other task can try to use it 
    */
    OS_task_table[possible_taskid].free = FALSE;
    
    if ( stack_size < PTHREAD_STACK_MIN )
    {
       local_stack_size = PTHREAD_STACK_MIN;
    }
    else
    {
        local_stack_size = stack_size;
    }

    /*
    ** Initialize the pthread_attr structure. 
    ** The structure is used to set the stack and priority
    */
    memset(&custom_attr, 0, sizeof(custom_attr));
    if(pthread_attr_init(&custom_attr))
    {  
        OS_task_table[possible_taskid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        
        #ifdef OS_DEBUG_PRINTF
           printf("pthread_attr_init error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
		  perror("pthread_attr_init");
        #endif
        return(OS_ERROR); 
    }

    /* Set in thread to the detached state so Valgrind memcheck doesn't
     * complain about lost records.
     */
    if(pthread_attr_setdetachstate(&custom_attr, PTHREAD_CREATE_DETACHED))
    {
        OS_printf("OSAL:  pthread_attr_setdetachstate error in OS_TaskCreate.  %i\n", errno);
        return(OS_ERROR);
    }

    /*
    ** Test to see if the user is running as root.
    ** root is required to set the scheduling policy, stack, and priority
    */
    if (geteuid() == 0 )
    {
       /*
       ** Set the scheduling inherit attribute to EXPLICIT
       */
       inheritsched = PTHREAD_EXPLICIT_SCHED;
       return_code = pthread_attr_setinheritsched(&custom_attr, inheritsched);
       if ( return_code < 0 )
       {
           #ifdef OS_DEBUG_PRINTF
               printf("pthread_attr_setinheritsched error in OS_TaskCreate, Task ID = %d, errno = %s\n",
                      possible_taskid,strerror(errno));
           #endif
           return(OS_ERROR);
       }

       /*
       ** Set the Stack Size
       */
       if (pthread_attr_setstacksize(&custom_attr, (size_t)local_stack_size ))
       {
          #ifdef OS_DEBUG_PRINTF
             printf("pthread_attr_setstacksize error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
          #endif
          return(OS_ERROR);
       }

       /*
       ** Set the scheduling policy 
       ** On Linux, the schedpolity must be SCHED_FIFO or SCHED_RR to set the priorty
       */
       if (pthread_attr_setschedpolicy(&custom_attr, SCHED_FIFO))
       {
          #ifdef OS_DEBUG_PRINTF
             printf("pthread_attr_setschedpolity error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
          #endif
          return(OS_ERROR);
       }

       /* 
       ** Set priority 
       */
       memset(&priority_holder, 0, sizeof(priority_holder));
       priority_holder.sched_priority = os_priority;
       ret = pthread_attr_setschedparam(&custom_attr,&priority_holder);
       if(ret !=0)
       {
          #ifdef OS_DEBUG_PRINTF
             printf("pthread_attr_setschedparam error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
          #endif
          return(OS_ERROR);
       }

    } /* End if user is root */

    /*
    ** Create thread
    */
    return_code = pthread_create(&(OS_task_table[possible_taskid].id),
                                 &custom_attr,
                                 (void* (*)(void*))function_pointer,
                                 (void *)0);
    if (return_code != 0)
    {
        OS_task_table[possible_taskid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 
        #ifdef OS_DEBUG_PRINTF
           printf("pthread_create error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
        #endif
        return(OS_ERROR);
    }

    /* Set thread name so its easier to identify in the debugger.  No need to
     * check for errors.  If it fails, just keep going.  No big deal. */
    pthread_setname_np(OS_task_table[possible_taskid].id, task_name);


    return_code = pthread_attr_destroy(&custom_attr);
    if (return_code !=0)
    {
       OS_task_table[possible_taskid].free = TRUE;
       OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 
       #ifdef OS_DEBUG_PRINTF
          printf("pthread_attr_destroy error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
       #endif
       return(OS_ERROR);
    }

    /*
    ** Assign the task ID
    */
    memcpy(task_id, &possible_taskid, sizeof(possible_taskid));

    /* 
    ** Initialize the table entries 
    */
    OS_task_table[possible_taskid].free = FALSE;
    strcpy(OS_task_table[*task_id].name, (char*) task_name);
    OS_task_table[possible_taskid].creator = OS_FindCreator();
    OS_task_table[possible_taskid].stack_size = stack_size;
    /* Use the abstracted priority, not the OS one */
    OS_task_table[possible_taskid].priority = priority;

    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 

    return OS_SUCCESS;
}/* end OS_TaskCreate */


/*--------------------------------------------------------------------------------------
     Name: OS_TaskDelete

    Purpose: Deletes the specified Task and removes it from the OS_task_table.

    returns: OS_ERR_INVALID_ID if the ID given to it is invalid
             OS_ERROR if the OS delete call fails
             OS_SUCCESS if success
---------------------------------------------------------------------------------------*/
int32 OS_TaskDelete (uint32 task_id)
{    
    int       ret;
    FuncPtr_t FunctionPointer;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /*
    ** Check to see if the task_id given is valid
    */
    if (task_id >= OS_MAX_TASKS || OS_task_table[task_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /*
    ** Call the thread Delete hook if there is one.
    */
    if ( OS_task_table[task_id].delete_hook_pointer != NULL)
    {
       FunctionPointer = (FuncPtr_t)(OS_task_table[task_id].delete_hook_pointer);
       (*FunctionPointer)();
    }

    /*
    ** Try to delete the task
    */
    ret = pthread_cancel(OS_task_table[task_id].id);
    if (ret != 0)
    {
        #ifdef OS_DEBUG_PRINTF
           printf("FAILED PTHREAD CANCEL %d, %d \n",ret, ESRCH);
        #endif
        return OS_ERROR;
    }

    /*
    ** Now that the task is deleted, remove its
    ** "presence" in OS_task_table
    */
    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous);

    OS_task_table[task_id].free = TRUE;
    strcpy(OS_task_table[task_id].name, "");
    OS_task_table[task_id].creator = UNINITIALIZED;
    OS_task_table[task_id].stack_size = UNINITIALIZED;
    OS_task_table[task_id].priority = UNINITIALIZED;
    OS_task_table[task_id].id = UNINITIALIZED;
    OS_task_table[task_id].delete_hook_pointer = NULL;

    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);

    return OS_SUCCESS;
    
}/* end OS_TaskDelete */

/*--------------------------------------------------------------------------------------
     Name: OS_TaskExit

    Purpose: Exits the calling task and removes it from the OS_task_table.

    returns: Nothing 
---------------------------------------------------------------------------------------*/

void OS_TaskExit()
{
    uint32    task_id;
    sigset_t  previous;
    sigset_t  mask;

    task_id = OS_TaskGetId();

    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous); 
    OS_task_table[task_id].free = TRUE;
    strcpy(OS_task_table[task_id].name, "");
    OS_task_table[task_id].creator = UNINITIALIZED;
    OS_task_table[task_id].stack_size = UNINITIALIZED;
    OS_task_table[task_id].priority = UNINITIALIZED;
    OS_task_table[task_id].id = UNINITIALIZED;
    OS_task_table[task_id].delete_hook_pointer = NULL;
    
    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 

    pthread_exit(NULL);

}/*end OS_TaskExit */
/*---------------------------------------------------------------------------------------
   Name: OS_TaskDelay

   Purpose: Delay a task for specified amount of milliseconds

   returns: OS_ERROR if sleep fails or millisecond = 0
            OS_SUCCESS if success
---------------------------------------------------------------------------------------*/
int32 OS_TaskDelay(uint32 millisecond )
{
    struct timespec waittime;
    uint32          ms = millisecond;
    int             sleepstat;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

	waittime.tv_sec  = ms / 1000;
	waittime.tv_nsec = (ms % 1000) * 1000000;

	/*
	** Do not allow signals to interrupt nanosleep until the requested time
	*/
	do
	{
		sleepstat = OS_NanoSleep(&waittime, &waittime);
	}
	while( sleepstat == -1 && errno == EINTR );

	if ( sleepstat == -1 )
	{
	   return(OS_ERROR);
	}
	else
	{
	   return OS_SUCCESS;
	}
}/* end OS_TaskDelay */

/*---------------------------------------------------------------------------------------
   Name: OS_TaskSetPriority

   Purpose: Sets the given task to a new priority

    returns: OS_ERR_INVALID_ID if the ID passed to it is invalid
             OS_ERR_INVALID_PRIORITY if the priority is greater than the max 
             allowed
             OS_ERROR if the OS call to change the priority fails
             OS_SUCCESS if success
---------------------------------------------------------------------------------------*/
int32 OS_TaskSetPriority (uint32 task_id, uint32 new_priority)
{
    int       os_priority;
    int       ret;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if(task_id >= OS_MAX_TASKS || OS_task_table[task_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if (new_priority > MAX_PRIORITY)
    {
        return OS_ERR_INVALID_PRIORITY;
    }
   
    /* Change OSAL priority into a priority that will work for this OS */
    os_priority = OS_PriorityRemap(new_priority);

    if (geteuid() == 0 )
    {
       /* 
       ** Set priority
       */
       ret = pthread_setschedprio(OS_task_table[task_id].id, os_priority);
       if( ret != 0 )
       {
          #ifdef OS_DEBUG_PRINTF
             printf("pthread_setschedprio err in OS_TaskSetPriority, Task ID = %lu, prio = %d, errno = %s\n",
                        task_id,os_priority ,strerror(errno));
          #endif
          return(OS_ERROR);
       }
    }

    /* Use the abstracted priority, not the OS one */
    /* Change the priority in the table as well */
    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous);
    OS_task_table[task_id].priority = new_priority;
    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);

   return OS_SUCCESS;
} /* end OS_TaskSetPriority */


/*---------------------------------------------------------------------------------------
   Name: OS_TaskRegister
  
   Purpose: Registers the calling task id with the task by adding the var to the tcb
            It searches the OS_task_table to find the task_id corresponding to the tcb_id
            
   Returns: OS_ERR_INVALID_ID if there the specified ID could not be found
            OS_ERROR if the OS call fails
            OS_SUCCESS if success
---------------------------------------------------------------------------------------*/
int32 OS_TaskRegister (void)
{
    int          i;
    int          ret;
    uint32       task_id;
    pthread_t    pthread_id;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* 
    ** Get PTHREAD Id
    */
    pthread_id = pthread_self();

    /*
    ** Look our task ID in table 
    */
    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous);
    for(i = 0; i < OS_MAX_TASKS; i++)
    {
       if(OS_task_table[i].id == pthread_id)
       {
          break;
       }
    }
    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
    task_id = i;

    if(task_id == OS_MAX_TASKS)
    {
        return OS_ERR_INVALID_ID;
    }

    /*
    ** Add pthread variable
    */
    ret = pthread_setspecific(thread_key, (void *)task_id);
    if ( ret != 0 )
    {
       #ifdef OS_DEBUG_PRINTF
          printf("OS_TaskRegister Failed during pthread_setspecific function\n");
       #endif
       return(OS_ERROR);
    }

    return OS_SUCCESS;
}/* end OS_TaskRegister */

/*---------------------------------------------------------------------------------------
   Name: OS_TaskGetId

   Purpose: This function returns the #defined task id of the calling task

   Notes: The OS_task_key is initialized by the task switch if AND ONLY IF the 
          OS_task_key has been registered via OS_TaskRegister(..).  If this is not 
          called prior to this call, the value will be old and wrong.
---------------------------------------------------------------------------------------*/
uint32 OS_TaskGetId (void)
{ 
   void*   task_id;
   int     task_id_int;
   uint32   task_key;
   task_key = 0;
   
   task_id = (void *)pthread_getspecific(thread_key);

   memcpy(& task_id_int,&task_id, sizeof(uint32));
   task_key = task_id_int & 0xFFFF;
   
   return task_key;
}/* end OS_TaskGetId */

/*--------------------------------------------------------------------------------------
    Name: OS_TaskGetIdByName

    Purpose: This function tries to find a task Id given the name of a task

    Returns: OS_INVALID_POINTER if the pointers passed in are NULL
             OS_ERR_NAME_TOO_LONG if th ename to found is too long to begin with
             OS_ERR_NAME_NOT_FOUND if the name wasn't found in the table
             OS_SUCCESS if SUCCESS
---------------------------------------------------------------------------------------*/

int32 OS_TaskGetIdByName (uint32 *task_id, const char *task_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if (task_id == NULL || task_name == NULL)
    {
       return OS_INVALID_POINTER;
    }
    
    /* 
    ** we don't want to allow names too long because they won't be found at all 
    */
    if (strlen(task_name) >= OS_MAX_API_NAME)
    {
       return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if((OS_task_table[i].free != TRUE) &&
                (strcmp(OS_task_table[i].name,(char*) task_name) == 0 ))
        {
            *task_id = i;
            return OS_SUCCESS;
        }
    }
    /* The name was not found in the table,
    **  or it was, and the task_id isn't valid anymore 
    */
    return OS_ERR_NAME_NOT_FOUND;

}/* end OS_TaskGetIdByName */            

/*---------------------------------------------------------------------------------------
    Name: OS_TaskGetInfo

    Purpose: This function will pass back a pointer to structure that contains 
             all of the relevant info (creator, stack size, priority, name) about the 
             specified task. 

    Returns: OS_ERR_INVALID_ID if the ID passed to it is invalid
             OS_INVALID_POINTER if the task_prop pointer is NULL
             OS_SUCCESS if it copied all of the relevant info over
 
---------------------------------------------------------------------------------------*/
int32 OS_TaskGetInfo (uint32 task_id, OS_task_prop_t *task_prop)  
{
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* put the info into the stucture */
    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous);

    /* 
    ** Check to see that the id given is valid 
    */
    if (task_id >= OS_MAX_TASKS || OS_task_table[task_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        return OS_ERR_INVALID_ID;
    }

    if( task_prop == NULL)
    {
        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        return OS_INVALID_POINTER;
    }

    task_prop -> creator =    OS_task_table[task_id].creator;
    task_prop -> stack_size = OS_task_table[task_id].stack_size;
    task_prop -> priority =   OS_task_table[task_id].priority;
    task_prop -> OStask_id =  (uint32) OS_task_table[task_id].id;
    
    strcpy(task_prop-> name, OS_task_table[task_id].name);

    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 
    
    return OS_SUCCESS;
    
} /* end OS_TaskGetInfo */

/*--------------------------------------------------------------------------------------
     Name: OS_TaskInstallDeleteHandler

    Purpose: Installs a handler for when the task is deleted.

    returns: status
---------------------------------------------------------------------------------------*/

int32 OS_TaskInstallDeleteHandler(osal_task_entry function_pointer)
{
    uint32    task_id;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    task_id = OS_TaskGetId();

    if ( task_id >= OS_MAX_TASKS )
    {
       return(OS_ERR_INVALID_ID);
    }

    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous); 

    if ( OS_task_table[task_id].free != FALSE )
    {
       /* 
       ** Somehow the calling task is not registered 
       */
       OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 
       return(OS_ERR_INVALID_ID);
    }

    /*
    ** Install the pointer
    */
    OS_task_table[task_id].delete_hook_pointer = function_pointer;    
    
    OS_InterruptSafeUnlock(&OS_task_table_mut, &previous); 

    return(OS_SUCCESS);
    
}/*end OS_TaskInstallDeleteHandler */



/* ---------------------- POSIX MESSAGE QUEUE IMPLEMENTATION ------------------------- */
/*---------------------------------------------------------------------------------------
   Name: OS_QueueCreate

 Purpose: Create a message queue which can be refered to by name or ID

 Returns: OS_INVALID_POINTER if a pointer passed in is NULL
 OS_ERR_NAME_TOO_LONG if the name passed in is too long
 OS_ERR_NO_FREE_IDS if there are already the max queues created
 OS_ERR_NAME_TAKEN if the name is already being used on another queue
 OS_ERROR if the OS create call fails
 OS_SUCCESS if success

 Notes: the flags parameter is unused.
 ---------------------------------------------------------------------------------------*/
int32 OS_QueueCreate (uint32 *queue_id, const char *queue_name, uint32 queue_depth,
                      uint32 data_size, uint32 flags)
{
	int						ret;
    int                     i;
    uint32                  possible_qid;
    sigset_t                previous;
    sigset_t                mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */

    if ( queue_id == NULL || queue_name == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* we don't want to allow names too long*/
    /* if truncated, two names might be the same */

    if (strlen(queue_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Ensure the queue depth isn't larger than our maximum depth. */
    if(queue_depth > OS_MAX_QUEUE_DEPTH) {
    	return OS_QUEUE_INVALID_SIZE;
    }

    /* Ensure the queue depth isn't zero. */
    if(queue_depth == 0) {
    	return OS_QUEUE_INVALID_SIZE;
    }

    OS_InterruptSafeLock(&OS_queue_table_mut, &mask, &previous);

    for(possible_qid = 0; possible_qid < OS_MAX_QUEUES; possible_qid++)
    {
        if (OS_queue_table[possible_qid].free == TRUE)
            break;
    }

    if( possible_qid >= OS_MAX_QUEUES || OS_queue_table[possible_qid].free != TRUE)
    {
        OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_QUEUES; i++)
    {
        if ((OS_queue_table[i].free == FALSE) &&
            strcmp ((char*) queue_name, OS_queue_table[i].name) == 0)
        {
            OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /* Set the possible task Id to not free so that
     * no other task can try to use it */
    *queue_id = possible_qid;

    OS_queue_table[*queue_id].free = FALSE;

    ret = pthread_cond_init(&(OS_queue_table[*queue_id].cv), NULL);
	if ( ret != 0 )
	{
        OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);
        return OS_ERROR;
	}

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutexattr_settype(&attr, PTHREAD_PRIO_INHERIT);
	ret = pthread_mutex_init((pthread_mutex_t *)&(OS_queue_table[*queue_id].mut), &attr);
    if ( ret < 0 )
    {
        OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);
        return OS_ERROR;
    }

    OS_queue_table[*queue_id].free = FALSE;
    OS_queue_table[*queue_id].max_size = data_size;
    strcpy( OS_queue_table[*queue_id].name, (char*) queue_name);
    OS_queue_table[*queue_id].creator = OS_FindCreator();
    OS_queue_table[*queue_id].width = data_size;
    OS_queue_table[*queue_id].depth = queue_depth;
    OS_queue_table[*queue_id].head = -1;
    OS_queue_table[*queue_id].tail = -1;
    OS_queue_table[*queue_id].queuedCount = 0;

    OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);

    return OS_SUCCESS;

}/* end OS_QueueCreate */



/*--------------------------------------------------------------------------------------
 Name: OS_QueueDelete

 Purpose: Deletes the specified message queue.

 Returns: OS_ERR_INVALID_ID if the id passed in does not exist
 OS_ERROR if the OS call to delete the queue fails
 OS_SUCCESS if success

 Notes: If There are messages on the queue, they will be lost and any subsequent
 calls to QueueGet or QueuePut to this queue will result in errors
 ---------------------------------------------------------------------------------------*/
int32 OS_QueueDelete (uint32 queue_id)
{
	int			ret;
    sigset_t   	previous;
    sigset_t   	mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
        ret = OS_ERROR;
        goto end_of_function;
    }

    OS_InterruptSafeLock(&OS_queue_table_mut, &mask, &previous);

    /* Check to see if the queue_id given is valid */

    if (queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);
        ret = OS_ERR_INVALID_ID;
        goto end_of_function;
    }

    OS_queue_table[queue_id].free = TRUE;
    strcpy(OS_queue_table[queue_id].name, "");
    OS_queue_table[queue_id].creator = UNINITIALIZED;
    OS_queue_table[queue_id].max_size = 0;
    OS_queue_table[queue_id].head = -1;
    OS_queue_table[queue_id].tail = -1;

    /* Destroy the conditional variable. */
    ret = pthread_cond_destroy(&(OS_queue_table[queue_id].cv));

    OS_InterruptSafeUnlock(&OS_queue_table_mut, &previous);

    ret = OS_SUCCESS;

end_of_function:
    return ret;

} /* end OS_QueueDelete */



/*---------------------------------------------------------------------------------------
 Name: OS_QueueGet

 Purpose: Receive a message on a message queue.  Will pend or timeout on the receive.
 Returns: OS_ERR_INVALID_ID if the given ID does not exist
 OS_ERR_INVALID_POINTER if a pointer passed in is NULL
 OS_QUEUE_EMPTY if the Queue has no messages on it to be recieved
 OS_QUEUE_TIMEOUT if the timeout was OS_PEND and the time expired
 OS_QUEUE_INVALID_SIZE if the size of the buffer passed in is not big enough for the
                                  maximum size message
 OS_SUCCESS if success
 ---------------------------------------------------------------------------------------*/
int32 OS_QueueGet (uint32 queue_id, void *data, uint32 size, uint32 *size_copied, int32 timeout)
{
    struct timespec ts;
    int				ret = 0;
    sigset_t   		previous;
    sigset_t   		mask;
    int32 			headIndex;
    OS_queue_data_t *qData = 0;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    OS_InterruptSafeLock(&OS_queue_table[queue_id].mut, &mask, &previous);

    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
    {
    	OS_printf("Bug encountered (4)\n");
    	exit(-1);
    }
    /*
    ** Check Parameters
    */
    if(queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
        return OS_ERR_INVALID_ID;
    }
    else if( (data == NULL) || (size_copied == NULL) )
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
        return OS_INVALID_POINTER;
    }
    else if( size < OS_queue_table[queue_id].max_size )
    {
        /*
        ** The buffer that the user is passing in is potentially too small
        ** RTEMS will just copy into a buffer that is too small
        */
        *size_copied = 0;
	    OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
        return OS_QUEUE_INVALID_SIZE;
    }

    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
    {
    	OS_printf("Bug encountered (4)\n");
    	exit(-1);
    }
    if(OS_queue_table[queue_id].head == -1)
    {
	    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
	    {
	    	OS_printf("Bug encountered (4)\n");
	    	exit(-1);
	    }
    	if (timeout == OS_PEND)
    	{
    		/*
    		 ** A signal can interrupt the pthread_cond_wait call, so the call has to be done with
    		 ** a loop
    		 */
		    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
		    {
		    	OS_printf("Bug encountered (4)\n");
		    	exit(-1);
		    }
    		do
    		{
    			ret = pthread_cond_wait(&OS_queue_table[queue_id].cv, &OS_queue_table[queue_id].mut);
    			if(ret != 0)
    			{
    				*size_copied = 0;
    			    OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
    				return OS_ERROR;
    			}
    		} while ((OS_queue_table[queue_id].head == -1) && (OS_queue_table[queue_id].free != 1));

    		if(OS_queue_table[queue_id].free == 1)
    		{
				*size_copied = 0;
			    OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
				return OS_ERR_INVALID_ID;
    		}
    	}
    	else if (timeout == OS_CHECK)
    	{
        	/* The queue is empty so return 0. */
            *size_copied = 0;
			OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
			return OS_QUEUE_EMPTY;
    	}
    	else /* timeout */
    	{
		    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
		    {
		    	OS_printf("Bug encountered (4)\n");
		    	exit(-1);
		    }
    		//OS_CompAbsDelayTime( timeout , &ts) ;
    		while ((OS_queue_table[queue_id].head == -1) && (ret != ETIMEDOUT))
			{
    		    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
    		    {
    		    	OS_printf("Bug encountered (4)\n");
    		    	exit(-1);
    		    }
				ret = OS_RtmCondTimedWait(&OS_queue_table[queue_id].cv, &OS_queue_table[queue_id].mut, timeout*1000);
    		    if(OS_queue_table[queue_id].mut.__data.__owner == 0)
    		    {
    		    	OS_printf("Bug encountered (5)\n");
    		    	exit(-1);
    		    }
			};
    		if((ret != 0) && (ret != ETIMEDOUT))
			{
				*size_copied = 0;
				OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
				return OS_ERROR;
			}

			if(ret == ETIMEDOUT)
			{
				*size_copied = 0;
				OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
				return OS_QUEUE_TIMEOUT;
			}
        }
    }

	/* The queue is not empty.  Pop an object from the head. */
	headIndex = OS_queue_table[queue_id].head;
	qData = &OS_queue_table[queue_id].qData[headIndex];
	memcpy(data, &qData->buffer[0], qData->size);
	if(qData->size != size)
	{
		*size_copied = 0;
		OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
		OS_printf("OS_QueueGet ---  OS_QUEUE_INVALID_SIZE\n");
		return OS_QUEUE_INVALID_SIZE;
	}

	*size_copied = qData->size;

	/* Check to see if there are more objects in the queue. */
	if(OS_queue_table[queue_id].tail == headIndex)
	{
		/* There are no more objects in the queue.  Set the queue to empty
		 * by setting the head to -1.
		 */
		OS_queue_table[queue_id].head = -1;
	}
	else
	{
		/* There are more objects in the queue.  Move the head to the next
		 * object. */
		if((headIndex + 1) >= OS_queue_table[queue_id].depth)
		{
			/* The head is at the end of the array.  Move it back to the
			 * beginning.
			 */
			OS_queue_table[queue_id].head = 0;
		}
		else
		{
			OS_queue_table[queue_id].head++;
		}
	}

        OS_queue_table[queue_id].queuedCount--;
	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);

	return OS_SUCCESS;
} /* end OS_QueueGet */



/*---------------------------------------------------------------------------------------
 Name: OS_QueuePut

 Purpose: Put a message on a message queue.

 Returns: OS_ERR_INVALID_ID if the queue id passed in is not a valid queue
 OS_INVALID_POINTER if the data pointer is NULL
 OS_QUEUE_FULL if the queue cannot accept another message
 OS_ERROR if the OS call returns an error
 OS_SUCCESS if SUCCESS

 Notes: The flags parameter is not used.  The message put is always configured to
 immediately return an error if the receiving message queue is full.
 ---------------------------------------------------------------------------------------*/
int32 OS_QueuePut (uint32 queue_id, const void *data, uint32 size, uint32 flags)
{
    sigset_t   		previous;
    sigset_t   		mask;
    OS_queue_data_t *qData;
    int				ret;

	//pthread_t tid = pthread_self();
	//char threadName[100];
	//pthread_getname_np(tid, threadName);

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    if(queue_id >= OS_MAX_QUEUES == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    OS_InterruptSafeLock(&OS_queue_table[queue_id].mut, &mask, &previous);

    /*
    ** Check Parameters
    */
    if(OS_queue_table[queue_id].free == TRUE)
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
        return OS_ERR_INVALID_ID;
    }

    if (data == NULL)
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
        return OS_INVALID_POINTER;
    }

    if(size > OS_queue_table[queue_id].width)
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
    	return OS_QUEUE_INVALID_SIZE;
    }

    /* Check if queue is full. */
    if(OS_queue_table[queue_id].queuedCount >= OS_queue_table[queue_id].depth)
    {
    	OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);
    	return OS_QUEUE_FULL;
    }

    if(OS_queue_table[queue_id].head == -1)
    {
    	OS_queue_table[queue_id].head = 0;
    	OS_queue_table[queue_id].tail = 0;
    }
    else
    {
        /* Determine where to move the tail. */
        if(OS_queue_table[queue_id].tail >= (OS_queue_table[queue_id].depth - 1))
	{
	    /* The tail is at the end of the array.  Move it back to the beginning. */
	    OS_queue_table[queue_id].tail = 0;
	}
	else
	{
	    OS_queue_table[queue_id].tail++;
	}
    }

    /* Copy the data to the new tail object. */
    qData = &OS_queue_table[queue_id].qData[OS_queue_table[queue_id].tail];
    memcpy(&qData->buffer, data, size);
    qData->size = size;
    OS_queue_table[queue_id].queuedCount++;
    ret = pthread_cond_signal(&OS_queue_table[queue_id].cv);
    OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);

    if(ret < 0)
    {
    	return OS_ERROR;
    }

    return OS_SUCCESS;

} /* end OS_QueuePut */


/*--------------------------------------------------------------------------------------
    Name: OS_QueueGetIdByName

    Purpose: This function tries to find a queue Id given the name of the queue. The
             id of the queue is passed back in queue_id

    Returns: OS_INVALID_POINTER if the name or id pointers are NULL
             OS_ERR_NAME_TOO_LONG the name passed in is too long
             OS_ERR_NAME_NOT_FOUND the name was not found in the table
             OS_SUCCESS if success
             
---------------------------------------------------------------------------------------*/

int32 OS_QueueGetIdByName (uint32 *queue_id, const char *queue_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if(queue_id == NULL || queue_name == NULL)
    {
       return OS_INVALID_POINTER;
    }
    
    /* a name too long wouldn't have been allowed in the first place
     * so we definitely won't find a name too long*/
 
    if (strlen(queue_name) >= OS_MAX_API_NAME)
    {
       return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_QUEUES; i++)
    {
        if (OS_queue_table[i].free != TRUE &&
           (strcmp(OS_queue_table[i].name, (char*) queue_name) == 0 ))
        {
            *queue_id = i;
            return OS_SUCCESS;
        }
    }

    /* The name was not found in the table,
     *  or it was, and the queue_id isn't valid anymore */
    return OS_ERR_NAME_NOT_FOUND;

}/* end OS_QueueGetIdByName */

/*---------------------------------------------------------------------------------------
    Name: OS_QueueGetInfo

    Purpose: This function will pass back a pointer to structure that contains 
             all of the relevant info (name and creator) about the specified queue. 

    Returns: OS_INVALID_POINTER if queue_prop is NULL
             OS_ERR_INVALID_ID if the ID given is not  a valid queue
             OS_SUCCESS if the info was copied over correctly
---------------------------------------------------------------------------------------*/
int32 OS_QueueGetInfo (uint32 queue_id, OS_queue_prop_t *queue_prop)  
{
    sigset_t   previous;
    sigset_t   mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check to see that the id given is valid */
    
    if (queue_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }
    
    if (queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /* put the info into the stucture */
    OS_InterruptSafeLock(&OS_queue_table[queue_id].mut, &mask, &previous);

    queue_prop -> creator =   OS_queue_table[queue_id].creator;
    strcpy(queue_prop -> name, OS_queue_table[queue_id].name);

    OS_InterruptSafeUnlock(&OS_queue_table[queue_id].mut, &previous);

    return OS_SUCCESS;
    
} /* end OS_QueueGetInfo */

/****************************************************************************************
                                  SEMAPHORE API
****************************************************************************************/

/*---------------------------------------------------------------------------------------
   Name: OS_BinSemCreate

   Purpose: Creates a binary semaphore with initial value specified by
            sem_initial_value and name specified by sem_name. sem_id will be 
            returned to the caller
            
   Returns: OS_INVALID_POINTER if sen name or sem_id are NULL
            OS_ERR_NAME_TOO_LONG if the name given is too long
            OS_ERR_NO_FREE_IDS if all of the semaphore ids are taken
            OS_ERR_NAME_TAKEN if this is already the name of a binary semaphore
            OS_SEM_FAILURE if the OS call failed
            OS_SUCCESS if success
            

   Notes: options is an unused parameter 
---------------------------------------------------------------------------------------*/
int32 OS_BinSemCreate (uint32 *sem_id, const char *sem_name, uint32 sem_initial_value,
                        uint32 options)
{
    uint32              possible_semid;
    uint32              i;
    int                 Status;
    pthread_mutexattr_t mutex_attr;    
    sigset_t            previous;
    sigset_t            mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* 
    ** Check Parameters 
    */
    if (sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }
    
    /* 
    ** Check for maximum name length 
    */
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Lock table */
    OS_InterruptSafeLock(&OS_bin_sem_table_mut, &mask, &previous); 

    for (possible_semid = 0; possible_semid < OS_MAX_BIN_SEMAPHORES; possible_semid++)
    {
        if (OS_bin_sem_table[possible_semid].free == TRUE)    
            break;
    }

    if((possible_semid >= OS_MAX_BIN_SEMAPHORES) ||  
       (OS_bin_sem_table[possible_semid].free != TRUE))
    {
        OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 
        return OS_ERR_NO_FREE_IDS;
    }
    
    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
        if ((OS_bin_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_bin_sem_table[i].name) == 0)
        {
            OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 
            return OS_ERR_NAME_TAKEN;
        }
    }  

    /* 
    ** Check to make sure the value is 0 or 1 
    */
    if (sem_initial_value < 0)
    {
        sem_initial_value = 0;
    }
    else if ( sem_initial_value > 1 )
    {
        sem_initial_value = 1;
    }

    /* 
    ** Initialize the pthread mutex attribute structure with default values 
    */
    errno = 0;
    Status = pthread_mutexattr_init(&mutex_attr);
    if ( Status == 0 )
    {
       /*
       ** Use priority inheritance
       */
       Status = pthread_mutexattr_setprotocol(&mutex_attr,PTHREAD_PRIO_INHERIT);
       if ( Status == 0 )
       {
           /*
           **  Set the mutex type to ERRORCHECK so deadlocked mutexes due to
           **  terminated tasks can be recovered.
           */
           Status = pthread_mutexattr_settype(&mutex_attr,PTHREAD_MUTEX_ERRORCHECK);
           if ( Status == 0 )
           {
			  /*
			  ** Initialize the mutex that is used with the condition variable
			  */
			  Status = pthread_mutex_init(&(OS_bin_sem_table[possible_semid].mut), &mutex_attr);
			  if( Status == 0 )
			  {
				 /*
				 ** Initialize the condition variable
				 */
				 Status = pthread_cond_init(&(OS_bin_sem_table[possible_semid].cv), NULL);
				 if ( Status == 0 )
				 {
					/*
					** fill out the proper OSAL table fields
					*/
					*sem_id = possible_semid;

					strcpy(OS_bin_sem_table[*sem_id].name , (char*) sem_name);
					OS_bin_sem_table[*sem_id].creator = OS_FindCreator();

					OS_bin_sem_table[*sem_id].max_value = 1;
					OS_bin_sem_table[*sem_id].current_value = sem_initial_value;
					OS_bin_sem_table[*sem_id].free = FALSE;

					/* Unlock table */
					OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);

					return OS_SUCCESS;
				 }
				 else
				 {
					OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);
					#ifdef OS_DEBUG_PRINTF
					   printf("Error: pthread_cond_init failed\n");
					#endif
					return (OS_SEM_FAILURE);
				 }
			  }
			  else
			  {
				 OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);
				 #ifdef OS_DEBUG_PRINTF
					printf("Error: pthread_mutex_init failed\n");
				 #endif
				 return (OS_SEM_FAILURE);
			  }
           }
           else
           {
               OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);
               #ifdef OS_DEBUG_PRINTF
                  printf("Error: pthread_mutexattr_settype recursion failed\n");
               #endif
               return (OS_SEM_FAILURE);
           }
      }
      else
      {
          OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 
          #ifdef OS_DEBUG_PRINTF
             printf("Error: pthread_mutexattr_setprotocol failed\n");
          #endif
          return (OS_SEM_FAILURE);
      }
   }
   else
   {
      OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 
      #ifdef OS_DEBUG_PRINTF
         printf("Error: pthread_mutexattr_init failed\n");
      #endif
      return (OS_SEM_FAILURE);
   }
            
}/* end OS_BinSemCreate */

/*--------------------------------------------------------------------------------------
     Name: OS_BinSemDelete

    Purpose: Deletes the specified Binary Semaphore.

    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid binary semaphore
             OS_SEM_FAILURE the OS call failed
             OS_SUCCESS if success
    
    Notes: Since we can't delete a semaphore which is currently locked by some task 
           (as it may ber crucial to completing the task), the semaphore must be full to
           allow deletion.
---------------------------------------------------------------------------------------*/
int32 OS_BinSemDelete (uint32 sem_id)
{
    sigset_t            previous;
    sigset_t            mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check to see if this sem_id is valid */
    if (sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock table */
    OS_InterruptSafeLock(&OS_bin_sem_table_mut, &mask, &previous); 
   
    /* Remove the Id from the table, and its name, so that it cannot be found again */
    pthread_mutex_destroy(&(OS_bin_sem_table[sem_id].mut));
    pthread_cond_destroy(&(OS_bin_sem_table[sem_id].cv));
    OS_bin_sem_table[sem_id].free = TRUE;
    strcpy(OS_bin_sem_table[sem_id].name , "");
    OS_bin_sem_table[sem_id].creator = UNINITIALIZED;
    OS_bin_sem_table[sem_id].max_value = 0;
    OS_bin_sem_table[sem_id].current_value = 0;

    /* Unlock table */
    OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 
   
    return OS_SUCCESS;

}/* end OS_BinSemDelete */


/*---------------------------------------------------------------------------------------
    Name: OS_BinSemGive

    Purpose: The function  unlocks the semaphore referenced by sem_id by performing
             a semaphore unlock operation on that semaphore.If the semaphore value 
             resulting from this operation is positive, then no threads were blocked             
             waiting for the semaphore to become unlocked; the semaphore value is
             simply incremented for this semaphore.

    
    Returns: OS_SEM_FAILURE the semaphore was not previously  initialized or is not
             in the array of semaphores defined by the system
             OS_ERR_INVALID_ID if the id passed in is not a binary semaphore
             OS_SUCCESS if success
                
---------------------------------------------------------------------------------------*/
int32 OS_BinSemGive ( uint32 sem_id )
{
    int       ret;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_BIN_SEMAPHORES)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock the mutex ( not the table! ) */
    ret = OS_InterruptSafeLock(&(OS_bin_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
        return(OS_SEM_FAILURE);
    }

    /* Check Parameters */
    if(OS_bin_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
        return OS_ERR_INVALID_ID;
    }
    
    /* 
    ** If the sem value is not full ( 1 ) then increment it.
    */
    if ( OS_bin_sem_table[sem_id].current_value  < OS_bin_sem_table[sem_id].max_value )
    {
         OS_bin_sem_table[sem_id].current_value ++;
         pthread_cond_signal(&(OS_bin_sem_table[sem_id].cv));
    }
    OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
    return (OS_SUCCESS);

}/* end OS_BinSemGive */

/*---------------------------------------------------------------------------------------
    Name: OS_BinSemFlush

    Purpose: The function unblocks all tasks pending on the specified semaphore. However,
             this function does not change the state of the semaphore.

    
    Returns: OS_SEM_FAILURE the semaphore was not previously  initialized or is not
             in the array of semaphores defined by the system
             OS_ERR_INVALID_ID if the id passed in is not a binary semaphore
             OS_SUCCESS if success

---------------------------------------------------------------------------------------*/
int32 OS_BinSemFlush (uint32 sem_id)
{
    uint32    ret_val;
    int32     ret = 0;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if(sem_id >= OS_MAX_BIN_SEMAPHORES)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock the mutex ( not the table! ) */
    ret = OS_InterruptSafeLock(&(OS_bin_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
        return(OS_SEM_FAILURE);
    }

    /* Check Parameters */
    if(OS_bin_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
        return OS_ERR_INVALID_ID;
    }

    /* 
    ** Release all threads waiting on the binary semaphore 
    */
    ret = pthread_cond_broadcast(&(OS_bin_sem_table[sem_id].cv));
    if ( ret == 0 )
    {
       ret_val = OS_SUCCESS ;
       OS_bin_sem_table[sem_id].current_value = OS_bin_sem_table[sem_id].max_value;
    }
    else
    {
       ret_val = OS_SEM_FAILURE;
    }
    OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);

    return(ret_val);

}/* end OS_BinSemFlush */

/*---------------------------------------------------------------------------------------
    Name:    OS_BinSemTake

    Purpose: The locks the semaphore referenced by sem_id by performing a 
             semaphore lock operation on that semaphore.If the semaphore value 
             is currently zero, then the calling thread shall not return from 
             the call until it either locks the semaphore or the call is 
             interrupted by a signal.

    Return:  OS_ERR_INVALID_ID the Id passed in is not a valid binary semaphore
             OS_SEM_FAILURE if the OS call failed
             OS_SUCCESS if success
             
----------------------------------------------------------------------------------------*/
int32 OS_BinSemTake ( uint32 sem_id )
{
    uint32    ret_val;
    int       ret;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check parameters */
    if(sem_id >= OS_MAX_BIN_SEMAPHORES )
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock the mutex */
	ret = OS_InterruptSafeLock(&(OS_bin_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
        return(OS_SEM_FAILURE);
    }

    /* Check parameters */ 
    if(OS_bin_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
        return OS_ERR_INVALID_ID;
    }
 
    /*
    ** If the value is less than the max (1) 
    ** wait until it is available
    ** If the value is max (1), then grab the resource without waiting
    */
    if ( OS_bin_sem_table[sem_id].current_value < OS_bin_sem_table[sem_id].max_value )
    {
        /*
        ** Wait on the condition variable. Calling this function unlocks the mutex and
        ** re-aquires the mutex when the function returns. This allows the function that
        ** calls the pthread_cond_signal or pthread_cond_broadcast to aquire the mutex
        */
        ret = pthread_cond_wait(&(OS_bin_sem_table[sem_id].cv),&(OS_bin_sem_table[sem_id].mut));
        if ( ret == 0 )
        {
            /*
            ** Decrement the counter
            */
            OS_bin_sem_table[sem_id].current_value--;

            ret_val = OS_SUCCESS;
        }
        else
        {
            ret_val = OS_SEM_FAILURE;
        }

    }
    else
    {
        /*
        ** Decrement the counter
        */
        OS_bin_sem_table[sem_id].current_value--;

        ret_val = OS_SUCCESS;
    }

    /* Unlock the mutex */
    OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
    
    return (ret_val);

}/* end OS_BinSemTake */

/*---------------------------------------------------------------------------------------
    Name: OS_BinSemTimedWait
    
    Purpose: The function locks the semaphore referenced by sem_id . However,
             if the semaphore cannot be locked without waiting for another process
             or thread to unlock the semaphore , this wait shall be terminated when 
             the specified timeout ,msecs, expires.

    Returns: OS_SEM_TIMEOUT if semaphore was not relinquished in time
             OS_SUCCESS if success
             OS_SEM_FAILURE the semaphore was not previously initialized or is not
             in the array of semaphores defined by the system
             OS_ERR_INVALID_ID if the ID passed in is not a valid semaphore ID

----------------------------------------------------------------------------------------*/
int32 OS_BinSemTimedWait ( uint32 sem_id, uint32 msecs )
{
    int              ret = 0;
    int32            ret_val;
    //struct timespec  ts;
    sigset_t         previous;
    sigset_t         mask;

    if(sem_id >= OS_MAX_BIN_SEMAPHORES)
    {
    	ret_val = OS_ERR_INVALID_ID;
    	goto end_of_function;
    }

    /* Lock the mutex */
    ret = OS_InterruptSafeLock(&(OS_bin_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
    	ret_val = OS_SEM_FAILURE;
    	goto end_of_function;
    }

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	ret_val = OS_ERROR;
    	goto end_of_function;
    }

    if(OS_bin_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
    	ret_val = OS_ERR_INVALID_ID;
    	goto end_of_function;
    }

    /*
    ** Compute an absolute time for the delay
    */
    //OS_CompAbsDelayTime(msecs, &ts);

 
    /*
    ** If the value is less than the max (1) 
    ** wait until it is available
    ** If the value is max (1), then grab the resource
    */
    while( (OS_bin_sem_table[sem_id].current_value <= 0) && (ret != ETIMEDOUT))
    {
		/*
		** Wait on the condition variable. Calling this function unlocks the mutex and
		** re-aquires the mutex when the function returns. This allows the function that
		** calls the pthread_cond_signal or pthread_cond_broadcast to acquire the mutex
		*/
		ret = OS_RtmCondTimedWait(&(OS_bin_sem_table[sem_id].cv), &(OS_bin_sem_table[sem_id].mut), msecs*1000);
    }

	if ( ret == ETIMEDOUT )
	{
		ret_val = OS_SEM_TIMEOUT;
	}
	else if(ret != 0)
	{
		ret_val = OS_SEM_FAILURE;
	}
    else
    {
		/* Decrement the counter */
		OS_bin_sem_table[sem_id].current_value--;

		ret_val = OS_SUCCESS;
    }


end_of_function:
	/* Unlock the mutex */
	OS_InterruptSafeUnlock(&(OS_bin_sem_table[sem_id].mut), &previous);
    return ret_val;
}
/*--------------------------------------------------------------------------------------
    Name: OS_BinSemGetIdByName

    Purpose: This function tries to find a binary sem Id given the name of a bin_sem
             The id is returned through sem_id

    Returns: OS_INVALID_POINTER is semid or sem_name are NULL pointers
             OS_ERR_NAME_TOO_LONG if the name given is to long to have been stored
             OS_ERR_NAME_NOT_FOUND if the name was not found in the table
             OS_SUCCESS if success
             
---------------------------------------------------------------------------------------*/
int32 OS_BinSemGetIdByName (uint32 *sem_id, const char *sem_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check parameters */
    if (sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* 
    ** a name too long wouldn't have been allowed in the first place
    ** so we definitely won't find a name too long
    */
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
       return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
        if (OS_bin_sem_table[i].free != TRUE &&
                (strcmp (OS_bin_sem_table[i].name , (char*) sem_name) == 0))
        {
            *sem_id = i;
            return OS_SUCCESS;
        }
    }
    /* 
    ** The name was not found in the table,
    ** or it was, and the sem_id isn't valid anymore 
    */
    return OS_ERR_NAME_NOT_FOUND;
    
}/* end OS_BinSemGetIdByName */
/*---------------------------------------------------------------------------------------
    Name: OS_BinSemGetInfo

    Purpose: This function will pass back a pointer to structure that contains 
             all of the relevant info( name and creator) about the specified binary
             semaphore.
             
    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid semaphore 
             OS_INVALID_POINTER if the bin_prop pointer is null
             OS_SUCCESS if success
---------------------------------------------------------------------------------------*/

int32 OS_BinSemGetInfo (uint32 sem_id, OS_bin_sem_prop_t *bin_prop)  
{
    sigset_t    previous;
    sigset_t    mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* put the info into the stucture */
    OS_InterruptSafeLock(&OS_bin_sem_table_mut, &mask, &previous);

    /* Check parameters */
    if (sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);
        return OS_ERR_INVALID_ID;
    }
    if (bin_prop == NULL)
    {
        OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous);
        return OS_INVALID_POINTER;
    }

    bin_prop ->creator =    OS_bin_sem_table[sem_id].creator;
    bin_prop -> value = OS_bin_sem_table[sem_id].current_value ;
    strcpy(bin_prop-> name, OS_bin_sem_table[sem_id].name);
    
    OS_InterruptSafeUnlock(&OS_bin_sem_table_mut, &previous); 

    return OS_SUCCESS;
    
} /* end OS_BinSemGetInfo */

/*---------------------------------------------------------------------------------------
   Name: OS_CountSemCreate

   Purpose: Creates a counting semaphore with initial value specified by
            sem_initial_value and name specified by sem_name. sem_id will be 
            returned to the caller
            
   Returns: OS_INVALID_POINTER if sen name or sem_id are NULL
            OS_ERR_NAME_TOO_LONG if the name given is too long
            OS_ERR_NO_FREE_IDS if all of the semaphore ids are taken
            OS_ERR_NAME_TAKEN if this is already the name of a counting semaphore
            OS_SEM_FAILURE if the OS call failed
            OS_INVALID_SEM_VALUE if the semaphore value is too high
            OS_SUCCESS if success
            

   Notes: options is an unused parameter 
---------------------------------------------------------------------------------------*/
int32 OS_CountSemCreate (uint32 *sem_id, const char *sem_name, uint32 sem_initial_value,
                        uint32 options)
{
    uint32              possible_semid;
    uint32              i;
    int                 Status;
    pthread_mutexattr_t mutex_attr;    
    sigset_t            previous;
    sigset_t            mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* 
    ** Check Parameters 
    */
    if (sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }
    
    /* 
    ** Check for maximum name length 
    */
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* 
    ** Check to make sure the value is between 0 and SEM_VALUE_MAX 
    */
    if (sem_initial_value < 0)
    {
        sem_initial_value = 0;
    }
    if ( sem_initial_value > SEM_VALUE_MAX )
    {
        return OS_INVALID_SEM_VALUE;
    }

    /* Lock table */
    OS_InterruptSafeLock(&OS_count_sem_table_mut, &mask, &previous); 

    for (possible_semid = 0; possible_semid < OS_MAX_COUNT_SEMAPHORES; possible_semid++)
    {
        if (OS_count_sem_table[possible_semid].free == TRUE)    
            break;
    }

    if((possible_semid >= OS_MAX_COUNT_SEMAPHORES) ||  
       (OS_count_sem_table[possible_semid].free != TRUE))
    {
        OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 
        return OS_ERR_NO_FREE_IDS;
    }
    
    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
        if ((OS_count_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_count_sem_table[i].name) == 0)
        {
            OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 
            return OS_ERR_NAME_TAKEN;
        }
    }  

    /* 
    ** Initialize the pthread mutex attribute structure with default values 
    */
    errno = 0;
    Status = pthread_mutexattr_init(&mutex_attr);
    if ( Status == 0 )
    {
       /*
       ** Use priority inheritance
       */
       Status = pthread_mutexattr_setprotocol(&mutex_attr,PTHREAD_PRIO_INHERIT);
       if ( Status == 0 )
       {
           /*
           **  Set the mutex type to ERRORCHECK so deadlocked mutexes due to
           **  terminated tasks can be recovered.
           */
           Status = pthread_mutexattr_settype(&mutex_attr,PTHREAD_MUTEX_ERRORCHECK);
           if ( Status == 0 )
           {
			  /*
			  ** Initialize the mutex that is used with the condition variable
			  */
			  Status = pthread_mutex_init(&(OS_count_sem_table[possible_semid].mut), &mutex_attr);
			  if( Status == 0 )
			  {
				 /*
				 ** Initialize the condition variable
				 */
				 Status = pthread_cond_init(&(OS_count_sem_table[possible_semid].cv), NULL);
				 if ( Status == 0 )
				 {
					/*
					** fill out the proper OSAL table fields
					*/
					*sem_id = possible_semid;

					strcpy(OS_count_sem_table[*sem_id].name , (char*) sem_name);
					OS_count_sem_table[*sem_id].creator = OS_FindCreator();

					OS_count_sem_table[*sem_id].max_value = SEM_VALUE_MAX;
					OS_count_sem_table[*sem_id].current_value = sem_initial_value;
					OS_count_sem_table[*sem_id].free = FALSE;

					/* Unlock table */
					OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous);

					return OS_SUCCESS;
				 }
				 else
				 {
					OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous);
					#ifdef OS_DEBUG_PRINTF
					   printf("Error: pthread_cond_init failed\n");
					#endif
					return (OS_SEM_FAILURE);
				 }
			  }
			  else
			  {
				 OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous);
				 #ifdef OS_DEBUG_PRINTF
					printf("Error: pthread_mutex_init failed\n");
				 #endif
				 return (OS_SEM_FAILURE);
			  }
           }
           else
           {
               OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous);
               #ifdef OS_DEBUG_PRINTF
                  printf("Error: pthread_mutexattr_settype failed\n");
               #endif
               return (OS_SEM_FAILURE);
           }
      }
      else
      {
          OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 
          #ifdef OS_DEBUG_PRINTF
             printf("Error: pthread_mutexattr_setprotocol failed\n");
          #endif
          return (OS_SEM_FAILURE);
      }
   }
   else
   {
      OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 
      #ifdef OS_DEBUG_PRINTF
         printf("Error: pthread_mutexattr_init failed\n");
      #endif
      return (OS_SEM_FAILURE);
   }

}/* end OS_CountSemCreate */

/*--------------------------------------------------------------------------------------
     Name: OS_CountSemDelete

    Purpose: Deletes the specified Countary Semaphore.

    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid counting semaphore
             OS_SEM_FAILURE the OS call failed
             OS_SUCCESS if success
    
    Notes: Since we can't delete a semaphore which is currently locked by some task 
           (as it may ber crucial to completing the task), the semaphore must be full to
           allow deletion.
---------------------------------------------------------------------------------------*/
int32 OS_CountSemDelete (uint32 sem_id)
{
    sigset_t            previous;
    sigset_t            mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check to see if this sem_id is valid */
    if (sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock table */
    OS_InterruptSafeLock(&OS_count_sem_table_mut, &mask, &previous); 
   
    /* Remove the Id from the table, and its name, so that it cannot be found again */
    pthread_mutex_destroy(&(OS_count_sem_table[sem_id].mut));
    pthread_cond_destroy(&(OS_count_sem_table[sem_id].cv));
    OS_count_sem_table[sem_id].free = TRUE;
    strcpy(OS_count_sem_table[sem_id].name , "");
    OS_count_sem_table[sem_id].creator = UNINITIALIZED;
    OS_count_sem_table[sem_id].max_value = 0;
    OS_count_sem_table[sem_id].current_value = 0;

    /* Unlock table */
    OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 
   
    return OS_SUCCESS;

}/* end OS_CountSemDelete */

/*---------------------------------------------------------------------------------------
    Name: OS_CountSemGive

    Purpose: The function  unlocks the semaphore referenced by sem_id by performing
             a semaphore unlock operation on that semaphore.If the semaphore value 
             resulting from this operation is positive, then no threads were blocked             
             waiting for the semaphore to become unlocked; the semaphore value is
             simply incremented for this semaphore.

    
    Returns: OS_SEM_FAILURE the semaphore was not previously  initialized or is not
             in the array of semaphores defined by the system
             OS_ERR_INVALID_ID if the id passed in is not a counting semaphore
             OS_SUCCESS if success
                
---------------------------------------------------------------------------------------*/
int32 OS_CountSemGive ( uint32 sem_id )
{
    int       ret;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock the mutex ( not the table! ) */    
    ret = OS_InterruptSafeLock(&(OS_count_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
       return(OS_SEM_FAILURE);
    }
    
    /* 
    ** If the sem value is less than or equal to 0, there are waiters.
    ** If the count is from 1 to max, there are no waiters
    */
    if ( OS_count_sem_table[sem_id].current_value  <= 0 )
    {
         OS_count_sem_table[sem_id].current_value ++;
         pthread_cond_signal(&(OS_count_sem_table[sem_id].cv));
    }
    else if ( OS_count_sem_table[sem_id].current_value  < OS_count_sem_table[sem_id].max_value )
    {
         OS_count_sem_table[sem_id].current_value ++;
    }

    OS_InterruptSafeUnlock(&(OS_count_sem_table[sem_id].mut), &previous);

    return (OS_SUCCESS);

}/* end OS_CountSemGive */

/*---------------------------------------------------------------------------------------
    Name:    OS_CountSemTake

    Purpose: The locks the semaphore referenced by sem_id by performing a 
             semaphore lock operation on that semaphore.If the semaphore value 
             is currently zero, then the calling thread shall not return from 
             the call until it either locks the semaphore or the call is 
             interrupted by a signal.

    Return:  OS_ERR_INVALID_ID the Id passed in is not a valid counting semaphore
             OS_SEM_FAILURE if the OS call failed
             OS_SUCCESS if success
             
----------------------------------------------------------------------------------------*/
int32 OS_CountSemTake ( uint32 sem_id )
{
    uint32    ret_val;
    int       ret;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check parameters */ 
    if(sem_id >= OS_MAX_COUNT_SEMAPHORES  || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }
        
    /* Lock the mutex */    
    ret = OS_InterruptSafeLock(&(OS_count_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
       return(OS_SEM_FAILURE);
    }
 
    /*
    ** If the value is <= 0, then wait until the semaphore is available 
    ** If the value is > 1, then grab the resource without waiting
    */
    if ( OS_count_sem_table[sem_id].current_value <= 0 )
    {
       /*
       ** Wait on the condition variable. Calling this function unlocks the mutex and 
       ** re-aquires the mutex when the function returns. This allows the function that
       ** calls the pthread_cond_signal or pthread_cond_broadcast to aquire the mutex
       */
       ret = pthread_cond_wait(&(OS_count_sem_table[sem_id].cv),&(OS_count_sem_table[sem_id].mut));
       if ( ret == 0 )
       {
          ret_val = OS_SUCCESS;
          /*
          ** Decrement the counter
          */
          OS_count_sem_table[sem_id].current_value --;
       }
       else
       {
           ret_val = OS_SEM_FAILURE;
       }

    }
    else /* Grab the sem */
    {
       OS_count_sem_table[sem_id].current_value --;
       ret_val = OS_SUCCESS;
    }

    /* Unlock the mutex */
    OS_InterruptSafeUnlock(&(OS_count_sem_table[sem_id].mut), &previous);
    
    return (ret_val);

}/* end OS_CountSemTake */

/*---------------------------------------------------------------------------------------
    Name: OS_CountSemTimedWait
    
    Purpose: The function locks the semaphore referenced by sem_id . However,
             if the semaphore cannot be locked without waiting for another process
             or thread to unlock the semaphore , this wait shall be terminated when 
             the specified timeout ,msecs, expires.

    Returns: OS_SEM_TIMEOUT if semaphore was not relinquished in time
             OS_SUCCESS if success
             OS_SEM_FAILURE the semaphore was not previously initialized or is not
             in the array of semaphores defined by the system
             OS_ERR_INVALID_ID if the ID passed in is not a valid semaphore ID

----------------------------------------------------------------------------------------*/
int32 OS_CountSemTimedWait ( uint32 sem_id, uint32 msecs )
{
    int              ret;
    uint32           ret_val;
    //struct timespec  ts;
    sigset_t         previous;
    sigset_t         mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if( (sem_id >= OS_MAX_COUNT_SEMAPHORES) || (OS_count_sem_table[sem_id].free == TRUE) )
    {
       return OS_ERR_INVALID_ID;
    }

    /*
    ** Compute an absolute time for the delay
    */
    //OS_CompAbsDelayTime(msecs, &ts);

    /* Lock the mutex */    
    ret = OS_InterruptSafeLock(&(OS_count_sem_table[sem_id].mut), &mask, &previous);
    if ( ret != 0 )
    {
       return(OS_SEM_FAILURE);
    }
 
    /*
    ** If the value is <= 0, then wait until the semaphore is available 
    ** If the value is > 1, then grab the resource without waiting
    */
    while( (OS_count_sem_table[sem_id].current_value <= 0) && (ret != ETIMEDOUT))
    {
		/*
		** Wait on the condition variable. Calling this function unlocks the mutex and
		** re-aquires the mutex when the function returns. This allows the function that
		** calls the pthread_cond_signal or pthread_cond_broadcast to acquire the mutex
		*/
		ret = OS_RtmCondTimedWait(&(OS_count_sem_table[sem_id].cv), &(OS_count_sem_table[sem_id].mut), msecs*1000);
    }

	if ( ret == ETIMEDOUT )
	{
		ret_val = OS_SEM_TIMEOUT;
	}
	else if(ret != 0)
	{
		ret_val = OS_SEM_FAILURE;
	}
    else
    {
		/* Decrement the counter */
    	OS_count_sem_table[sem_id].current_value--;

		ret_val = OS_SUCCESS;
    }

    /* Unlock the mutex */
    OS_InterruptSafeUnlock(&(OS_count_sem_table[sem_id].mut), &previous);

    return ret_val;
}

/*--------------------------------------------------------------------------------------
    Name: OS_CountSemGetIdByName

    Purpose: This function tries to find a counting sem Id given the name of a count_sem
             The id is returned through sem_id

    Returns: OS_INVALID_POINTER is semid or sem_name are NULL pointers
             OS_ERR_NAME_TOO_LONG if the name given is to long to have been stored
             OS_ERR_NAME_NOT_FOUND if the name was not found in the table
             OS_SUCCESS if success
             
---------------------------------------------------------------------------------------*/
int32 OS_CountSemGetIdByName (uint32 *sem_id, const char *sem_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if (sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* 
    ** a name too long wouldn't have been allowed in the first place
    ** so we definitely won't find a name too long
    */    
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
        if (OS_count_sem_table[i].free != TRUE &&
                (strcmp (OS_count_sem_table[i].name , (char*) sem_name) == 0))
        {
            *sem_id = i;
            return OS_SUCCESS;
        }
    }
    /* 
    ** The name was not found in the table,
    ** or it was, and the sem_id isn't valid anymore 
    */
    return OS_ERR_NAME_NOT_FOUND;
    
}/* end OS_CountSemGetIdByName */
/*---------------------------------------------------------------------------------------
    Name: OS_CountSemGetInfo

    Purpose: This function will pass back a pointer to structure that contains 
             all of the relevant info( name and creator) about the specified counting
             semaphore.
             
    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid semaphore 
             OS_INVALID_POINTER if the count_prop pointer is null
             OS_SUCCESS if success
---------------------------------------------------------------------------------------*/

int32 OS_CountSemGetInfo (uint32 sem_id, OS_count_sem_prop_t *count_prop)  
{
    sigset_t    previous;
    sigset_t    mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* 
    ** Check to see that the id given is valid 
    */
    if (sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if (count_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /*
    ** Lock
    */
    OS_InterruptSafeLock(&OS_count_sem_table_mut, &mask, &previous); 
    
    /* put the info into the stucture */
    count_prop -> value = OS_count_sem_table[sem_id].current_value;
    
    count_prop -> creator =    OS_count_sem_table[sem_id].creator;
    strcpy(count_prop-> name, OS_count_sem_table[sem_id].name);
   
    /*
    ** Unlock
    */ 
    OS_InterruptSafeUnlock(&OS_count_sem_table_mut, &previous); 

    return OS_SUCCESS;
    
} /* end OS_CountSemGetInfo */
/****************************************************************************************
                                  MUTEX API
****************************************************************************************/


/*---------------------------------------------------------------------------------------
    Name: OS_MutSemCreate

    Purpose: Creates a mutex semaphore initially full.

    Returns: OS_INVALID_POINTER if sem_id or sem_name are NULL
             OS_ERR_NAME_TOO_LONG if the sem_name is too long to be stored
             OS_ERR_NO_FREE_IDS if there are no more free mutex Ids
             OS_ERR_NAME_TAKEN if there is already a mutex with the same name
             OS_SEM_FAILURE if the OS call failed
             OS_SUCCESS if success
    
    Notes: the options parameter is not used in this implementation

---------------------------------------------------------------------------------------*/
int32 OS_MutSemCreate (uint32 *sem_id, const char *sem_name, uint32 options)
{
    int                 return_code;
    pthread_mutexattr_t mutex_attr ;    
    uint32              possible_semid;
    uint32              i;      
    sigset_t            previous;
    sigset_t            mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if (sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }
    
    /* we don't want to allow names too long*/
    /* if truncated, two names might be the same */
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    OS_InterruptSafeLock(&OS_mut_sem_table_mut, &mask, &previous);

    for (possible_semid = 0; possible_semid < OS_MAX_MUTEXES; possible_semid++)
    {
        if (OS_mut_sem_table[possible_semid].free == TRUE)    
            break;
    }
    
    if( (possible_semid == OS_MAX_MUTEXES) ||
        (OS_mut_sem_table[possible_semid].free != TRUE) )
    {
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */

    for (i = 0; i < OS_MAX_MUTEXES; i++)
    {
        if ((OS_mut_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_mut_sem_table[i].name) == 0)
        {
            OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /* Set the free flag to false to make sure no other task grabs it */
    OS_mut_sem_table[possible_semid].free = FALSE;

    /* Set the lock count to 0 and set the locked_by property to 0 */
    OS_mut_sem_table[possible_semid].lock_count = 0;
    OS_mut_sem_table[possible_semid].locked_by = 0;

    /* 
    ** initialize the attribute with default values 
    */
    return_code = pthread_mutexattr_init(&mutex_attr); 
    if ( return_code != 0 )
    {
        /* Since the call failed, set free back to true */
        OS_mut_sem_table[possible_semid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
 
       
        #ifdef OS_DEBUG_PRINTF  
           printf("Error: Mutex could not be created. pthread_mutexattr_init failed ID = %lu\n",possible_semid);
        #endif
        return OS_SEM_FAILURE;
    }

    return_code = pthread_mutexattr_setrobust(&mutex_attr, PTHREAD_MUTEX_ROBUST);
    if ( return_code != 0 )
    {
        /* Since the call failed, set free back to true */
        OS_mut_sem_table[possible_semid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);

        #ifdef OS_DEBUG_PRINTF
           printf("Error: Mutex could not be created. pthread_mutexattr_setrobust failed ID = %lu\n", possible_semid);
        #endif
        return OS_SEM_FAILURE;
    }

    /*
    ** Allow the mutex to use priority inheritance  
    */  
    return_code = pthread_mutexattr_setprotocol(&mutex_attr,PTHREAD_PRIO_INHERIT) ;
    if ( return_code != 0 )
    {
        /* Since the call failed, set free back to true */
        OS_mut_sem_table[possible_semid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);

        #ifdef OS_DEBUG_PRINTF  
           printf("Error: Mutex could not be created. pthread_mutexattr_setprotocol failed ID = %lu\n",possible_semid);
        #endif
        return OS_SEM_FAILURE;    
    }	
    /*
    **  Set the mutex type to ERRORCHECK so a thread can do nested locks
    */
    return_code = pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);
    if ( return_code != 0 )
    {
        /* Since the call failed, set free back to true */
        OS_mut_sem_table[possible_semid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);

        #ifdef OS_DEBUG_PRINTF
           printf("Error: Mutex could not be created. pthread_mutexattr_settype failed ID = %lu\n",possible_semid);
        #endif
       return OS_SEM_FAILURE;
    }

    /* 
    ** create the mutex 
    ** upon successful initialization, the state of the mutex becomes initialized and unlocked 
    */
    return_code =  pthread_mutex_init((pthread_mutex_t *) &OS_mut_sem_table[possible_semid].mut,&mutex_attr);
    if ( return_code != 0 )
    {
        /* Since the call failed, set free back to true */
        OS_mut_sem_table[possible_semid].free = TRUE;
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);

        #ifdef OS_DEBUG_PRINTF  
           printf("Error: Mutex could not be created. ID = %lu\n",possible_semid);
        #endif
       return OS_SEM_FAILURE;
    }
    else
    {
       /*
       ** Mark mutex as initialized
       */
       *sem_id = possible_semid;

       strcpy(OS_mut_sem_table[*sem_id].name, (char*) sem_name);
       OS_mut_sem_table[*sem_id].free = FALSE;
       OS_mut_sem_table[*sem_id].creator = OS_FindCreator();
    
       OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);

       return OS_SUCCESS;
    }

}/* end OS_MutexSemCreate */

/*--------------------------------------------------------------------------------------
     Name: OS_MutSemDelete

    Purpose: Deletes the specified Mutex Semaphore.
    
    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid mutex
             OS_SEM_FAILURE if the OS call failed
             OS_SUCCESS if success

    Notes: The mutex must be full to take it, so we have to check for fullness

---------------------------------------------------------------------------------------*/

int32 OS_MutSemDelete (uint32 sem_id)
{
    int32     ret_val = OS_ERROR;
    int       status=-1;
    sigset_t  previous;
    sigset_t  mask;

    OS_InterruptSafeLock(&OS_mut_sem_table_mut, &mask, &previous);

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	ret_val = OS_ERROR;
    	goto end_of_function;
    }

    /* Check to see if this sem_id is valid   */
    if (sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
    	ret_val = OS_ERR_INVALID_ID;
    	goto end_of_function;
    }

    status = pthread_mutex_destroy( &(OS_mut_sem_table[sem_id].mut)); /* 0 = success */
    
    if( status != 0)
    {
    	ret_val = OS_SEM_FAILURE;
    	goto end_of_function;
    }
    /* Delete its presence in the table */

    OS_mut_sem_table[sem_id].free = TRUE;
    strcpy(OS_mut_sem_table[sem_id].name , "");
    OS_mut_sem_table[sem_id].creator = UNINITIALIZED;

    ret_val = OS_SUCCESS;

end_of_function:
	OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
	return ret_val;
}/* end OS_MutSemDelete */

/*---------------------------------------------------------------------------------------
    Name: OS_MutSemGive

    Purpose: The function releases the mutex object referenced by sem_id.The 
             manner in which a mutex is released is dependent upon the mutex's type 
             attribute.  If there are threads blocked on the mutex object referenced by 
             mutex when this function is called, resulting in the mutex becoming 
             available, the scheduling policy shall determine which thread shall 
             acquire the mutex.

    Returns: OS_SUCCESS if success
             OS_SEM_FAILURE if the semaphore was not previously  initialized 
             OS_ERR_INVALID_ID if the id passed in is not a valid mutex

---------------------------------------------------------------------------------------*/

int32 OS_MutSemGive ( uint32 sem_id )
{
    int32     ret_val = OS_ERROR;
    sigset_t  previous;
    sigset_t  mask;

    OS_InterruptSafeLock(&OS_mut_sem_table_mut, &mask, &previous);

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	ret_val = OS_ERROR;
    	goto end_of_function;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
    	ret_val = OS_ERR_INVALID_ID;
    	goto end_of_function;
    }

    /* We can't use recursive mutexes so we need to simulate recursive
     * locks here.  First, check to see if it is even locked.
     */
    if(OS_mut_sem_table[sem_id].lock_count == 0)
    {
    	/* This isn't locked.  Return an error. */
    	ret_val = OS_ERROR;
    	goto end_of_function;
    }
    else
    {
    	/* This is locked.  Check to see who the locker is. */
    	if(OS_mut_sem_table[sem_id].locked_by != pthread_self())
    	{
    		/* The caller doesn't have the lock.  Return an error. */
        	ret_val = OS_ERROR;
        	goto end_of_function;
    	}
    	else
    	{
    		/* The caller does have the lock.  Decrement the lock count. */
    		OS_mut_sem_table[sem_id].lock_count--;

    		/* If the lock count is back down to zero, go ahead and unlock
    		 * the mutex.
    		 */
    		if(OS_mut_sem_table[sem_id].lock_count == 0)
    		{
    		    ret_val = pthread_mutex_unlock(&(OS_mut_sem_table[sem_id].mut));
    		    if(ret_val == EPERM)
    		    {
    				#ifdef OS_DEBUG_PRINTF
    				   printf("Task would deadlock--nested mutex call!\n");
    				#endif
    		    	ret_val = OS_SUCCESS;
    		    	goto end_of_function;
    		    }
    		}
	    	ret_val = OS_SUCCESS;
	    	goto end_of_function;
    	}
    }

end_of_function:
    OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
    return ret_val;
} /* end OS_MutSemGive */

/*---------------------------------------------------------------------------------------
    Name: OS_MutSemTake

    Purpose: The mutex object referenced by sem_id shall be locked by calling this
             function. If the mutex is already locked, the calling thread shall
             block until the mutex becomes available. This operation shall return
             with the mutex object referenced by mutex in the locked state with the              
             calling thread as its owner.

    Returns: OS_SUCCESS if success
             OS_SEM_FAILURE if the semaphore was not previously initialized or is 
             not in the array of semaphores defined by the system
             OS_ERR_INVALID_ID the id passed in is not a valid mutex
---------------------------------------------------------------------------------------*/
int32 OS_MutSemTake ( uint32 sem_id )
{
    int32     ret_val = OS_ERROR;
    int status;
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    OS_InterruptSafeLock(&OS_mut_sem_table_mut, &mask, &previous);
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
		ret_val = OS_ERROR;
		goto end_of_function;
    }

    /* 
    ** Check Parameters
    */  
    if(sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
        OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
		ret_val = OS_ERR_INVALID_ID;
		goto end_of_function;
    }

    OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous);
  	status = pthread_mutex_lock(&(OS_mut_sem_table[sem_id].mut));
 	if ( status == EDEADLK )
   	{
    	/* We're using ERRORCHECK mutexes, so this is because the caller
    	 * called OS_MutSemTake again.  We're supporting recursive mutexes
    	 * so this is ok.  Just increment the lock count.
    	 */
		OS_mut_sem_table[sem_id].lock_count++;
		ret_val = OS_SUCCESS;
		goto end_of_function;
    }
    else if(status == EOWNERDEAD)
    {
    	/* We're using ERRORCHECK mutexes, so this is because the lock owner
    	 * terminated, either purposely or harshly.  The next call will
    	 * return the mutex back to a useful state so we can attempt the lock
    	 * again.
    	 */
    	pthread_mutex_consistent(&(OS_mut_sem_table[sem_id].mut));
    	status = pthread_mutex_lock(&(OS_mut_sem_table[sem_id].mut));
    	if ( status == EDEADLK )
    	{
    		ret_val = OS_SUCCESS;
    		goto end_of_function;
    	}
    	else if(status != 0)
    	{
    		/* Something bad happened */
    		ret_val = OS_SEM_FAILURE;
    		goto end_of_function;
    	}
    	else
    	{
        	/* We're using ERRORCHECK mutexes.  Since we had to call
        	 * pthread_mutex_consistent on this mutex, we know this is the
        	 * first time the caller has locked this mutex.  Set the lock
        	 * count to 1 and the owner equal to the caller.
        	 */
    		OS_mut_sem_table[sem_id].lock_count = 1;
    		OS_mut_sem_table[sem_id].locked_by = pthread_self();
        	ret_val = OS_SUCCESS;
        	goto end_of_function;
    	}
    }
    else if(status != 0)
    {
    	/* Something bad happened. */
    	OS_printf("OS_MutSemTake:  pthread_mutex_lock(lock) returned %i\n", status);
    	ret_val = OS_SEM_FAILURE;
    	goto end_of_function;
    }
	else
	{
    	/* We're using ERRORCHECK mutexes.  Since we did not get a EDEADLK
    	 * return, we know this is the first time the caller has locked this
    	 * mutex.  Set the lock count to 1 and the owner equal to the caller.
    	 */
		OS_mut_sem_table[sem_id].lock_count = 1;
		OS_mut_sem_table[sem_id].locked_by = pthread_self();
    	ret_val = OS_SUCCESS;
    	goto end_of_function;
	}

end_of_function:
	return ret_val;
}
/*--------------------------------------------------------------------------------------
    Name: OS_MutSemGetIdByName

    Purpose: This function tries to find a mutex sem Id given the name of a mut_sem
             The id is returned through sem_id

    Returns: OS_INVALID_POINTER is semid or sem_name are NULL pointers
             OS_ERR_NAME_TOO_LONG if the name given is to long to have been stored
             OS_ERR_NAME_NOT_FOUND if the name was not found in the table
             OS_SUCCESS if success
             
---------------------------------------------------------------------------------------*/
int32 OS_MutSemGetIdByName (uint32 *sem_id, const char *sem_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    if(sem_id == NULL || sem_name == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* 
    ** Check parameters 
    */ 
    if (strlen(sem_name) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    for (i = 0; i < OS_MAX_MUTEXES; i++)
    {
        if ((OS_mut_sem_table[i].free != TRUE) &&
           (strcmp (OS_mut_sem_table[i].name, (char*) sem_name) == 0) )
        {
            *sem_id = i;
            return OS_SUCCESS;
        }
    }
    
    /* 
    ** The name was not found in the table,
    **  or it was, and the sem_id isn't valid anymore 
    */
    return OS_ERR_NAME_NOT_FOUND;

}/* end OS_MutSemGetIdByName */

/*---------------------------------------------------------------------------------------
    Name: OS_MutSemGetInfo

    Purpose: This function will pass back a pointer to structure that contains 
             all of the relevant info( name and creator) about the specified mutex
             semaphore.
             
    Returns: OS_ERR_INVALID_ID if the id passed in is not a valid semaphore 
             OS_INVALID_POINTER if the mut_prop pointer is null
             OS_SUCCESS if success
---------------------------------------------------------------------------------------*/

int32 OS_MutSemGetInfo (uint32 sem_id, OS_mut_sem_prop_t *mut_prop)  
{
    sigset_t  previous;
    sigset_t  mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check to see that the id given is valid */
    
    if (sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if (mut_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }
    
    /* put the info into the stucture */    
    
    OS_InterruptSafeLock(&OS_mut_sem_table_mut, &mask, &previous); 

    mut_prop -> creator =   OS_mut_sem_table[sem_id].creator;
    strcpy(mut_prop-> name, OS_mut_sem_table[sem_id].name);

    OS_InterruptSafeUnlock(&OS_mut_sem_table_mut, &previous); 
    
    return OS_SUCCESS;
    
} /* end OS_BinSemGetInfo */


/****************************************************************************************
                                    INT API
****************************************************************************************/

/*---------------------------------------------------------------------------------------
** Name: OS_IntAttachHandler
**
** Purpose:
**      The call associates a specified C routine to a specified interrupt   
**      number.Upon occurring of the InterruptNumber , the InerruptHandler 
**      routine will be called and passed the parameter. 
**
** Assumptions and Notes:
**
** Parameters:
**      InterruptNumber : The Interrupt Number that will cause the start of
**                        the ISR
**      InerruptHandler : The ISR associatd with this interrupt
**      parameter :The parameter that is passed to the ISR
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**     OS_SUCCESS on success
**     OS_INVALID_POINTER if the Interrupt handler pointer is NULL
---------------------------------------------------------------------------------------*/
int32 OS_IntAttachHandler  (uint32 InterruptNumber, osal_task_entry InterruptHandler, int32 parameter)
{
    if (InterruptHandler == NULL)
    {
        return OS_INVALID_POINTER;
    }
    return(OS_ERR_NOT_IMPLEMENTED);
}

/*---------------------------------------------------------------------------------------
** Name: OS_IntUnlock
** Purpose:
**      Enable the interrupts. 
**
** Assumptions and Notes:
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/
int32 OS_IntUnlock (int32 IntLevel)
{
    return(OS_ERR_NOT_IMPLEMENTED);
}

/*---------------------------------------------------------------------------------------
** Name: OS_Intlock
** Purpose:
**      Disable the interrupts. 
**
** Assumptions and Notes:
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/
int32 OS_IntLock ( void ) 
{
    return(OS_ERR_NOT_IMPLEMENTED) ;
}
/*---------------------------------------------------------------------------------------
** Name: OS_IntEnable
** Purpose:
**      Enables interrupts through Level 
**
** Assumptions and Notes:
**
** Parameters:
**              Level - the interrupts to enable
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/
int32 OS_IntEnable(int32 Level)
{
    return(OS_ERR_NOT_IMPLEMENTED);
}

/*---------------------------------------------------------------------------------------
** Name: OS_IntDisable
** Purpose:
**      Disables interrupts through Level 
**
** Assumptions and Notes:
**
** Parameters:
**              Level - the interrupts to disable
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/

int32 OS_IntDisable(int32 Level)
{
    return(OS_ERR_NOT_IMPLEMENTED);
}

/*---------------------------------------------------------------------------------------
   Name: OS_HeapGetInfo

   Purpose: Return current info on the heap

   Parameters:

---------------------------------------------------------------------------------------*/
int32 OS_HeapGetInfo       (OS_heap_prop_t *heap_prop)
{
    if (heap_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }
    /*
    ** Not implemented yet
    */
    return (OS_ERR_NOT_IMPLEMENTED);
}
/*---------------------------------------------------------------------------------------
** Name: OS_Tick2Micros
**
** Purpose:
** This function returns the duration of a system tick in micro seconds.
**
** Assumptions and Notes:
**
** Parameters: None
**
** Global Inputs: None
**
** Global Outputs: None
**
**
**
** Return Values: duration of a system tick in microseconds
---------------------------------------------------------------------------------------*/
int32 OS_Tick2Micros (void)
{
   /* 
   ** sysconf(_SC_CLK_TCK) returns ticks/second.
   */
   return ((int32)(1000000) / sysconf(_SC_CLK_TCK));
}

/*---------------------------------------------------------------------------------------
** Name: OS_Milli2Ticks
**
** Purpose:
** This function accepts a time interval in milliseconds, as an input and 
** returns the tick equivalent  for this time period. The tick value is 
**  rounded up.
**
** Assumptions and Notes:
**
** Parameters:
**      milli_seconds : the time interval ,in milli second , to be translated
**                      to ticks
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: the number of ticks rounded up.
---------------------------------------------------------------------------------------*/
int32 OS_Milli2Ticks(uint32 milli_seconds)
{
    uint32 num_of_ticks;
    uint32 tick_duration_usec;

    tick_duration_usec = OS_Tick2Micros();
    num_of_ticks = ((milli_seconds * 1000) + tick_duration_usec - 1)/tick_duration_usec;

    return(num_of_ticks);
}
/*---------------------------------------------------------------------------------------
 * Name: OS_GetLocalTime
 * 
 * Purpose: This functions get the local time of the machine its on
 * ------------------------------------------------------------------------------------*/

int32 OS_GetLocalTime(OS_time_t *time_struct)
{
   int             Status;
   int32           ReturnCode;
   struct timespec time;

    if (time_struct == NULL)
    {
       return OS_INVALID_POINTER;
    }

    Status = clock_gettime(CLOCK_REALTIME, &time);

    if (Status == 0)
    {
        time_struct -> seconds = time.tv_sec;
        time_struct -> microsecs = time.tv_nsec / 1000;
        ReturnCode = OS_SUCCESS;
    }
    else
    {
        printf("Error calling clock_gettime!\n");
        ReturnCode = OS_ERROR;
    }

    return ReturnCode;

}/* end OS_GetLocalTime */

/*---------------------------------------------------------------------------------------
 * Name: OS_SetLocalTime
 * 
 * Purpose: This functions set the local time of the machine its on
 * ------------------------------------------------------------------------------------*/

int32 OS_SetLocalTime(OS_time_t *time_struct)
{
    int             Status;
    int32           ReturnCode;
    struct timespec time;

    if (time_struct == NULL)
    {
       return OS_INVALID_POINTER;
    }

    /* Check to see if we're running as root.  Only root has access to change
     * the local time.
     */
    if (geteuid() != 0 ) {
    	/* We are not running as root.  Return Not Implemented since we can't
    	 * the time.
    	 */
    	return OS_ERR_NOT_IMPLEMENTED;
    }

    time.tv_sec = time_struct -> seconds;
    time.tv_nsec = (time_struct -> microsecs * 1000);

    Status = clock_settime(CLOCK_REALTIME, &time);
    printf("%u\n", errno);
    if (Status == 0)
    {
        ReturnCode = OS_SUCCESS;
    }
    else
    {
        ReturnCode = OS_ERROR;
    }
    
    return ReturnCode;

} /*end OS_SetLocalTime */

/*---------------------------------------------------------------------------------------
** Name: OS_SetMask
** Purpose:
**      Set the masking register to mask and unmask interrupts 
**
** Assumptions and Notes:
**
** Parameters:
**      MaskSetting :the value to be written into the mask register
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/
int32 OS_SetMask ( uint32 MaskSetting ) 
{
    return(OS_SUCCESS) ;
}

/*--------------------------------------------------------------------------------------
** Name: OS_GetMask
** Purpose:
**      Read and report the setting of the cpu mask register.
**
** Assumptions and Notes:
**
** Parameters:
**      MaskSettingPtr : pointer to a location where the function store the
**                               reading of the cpu mask register.
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: 
**      OS_SUCCESS
---------------------------------------------------------------------------------------*/
int32 OS_GetMask ( uint32 * MaskSettingPtr ) 
{
    return(OS_SUCCESS) ;
}
/*--------------------------------------------------------------------------------------
 * uint32 FindCreator
 * purpose: Finds the creator of the calling thread
---------------------------------------------------------------------------------------*/
uint32 OS_FindCreator(void)
{
    pthread_t    pthread_id;
    uint32 i;  
   
    pthread_id = pthread_self();
    /* 
    ** Get PTHREAD Id
    */

    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if (pthread_equal(pthread_id, OS_task_table[i].id) != 0 )
        {
            break;
        }
    }

    return i;
}

/*---------------------------------------------------------------------------------------
** Name: OS_CompAbsDelayTime
**
** Purpose:
** This function accept time interval, msecs, as an input and 
** computes the absolute time at which this time interval will expire. 
** The absolute time is programmed into a struct.
**
** Assumptions and Notes:
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: OS_SUCCESS, 
---------------------------------------------------------------------------------------*/
//void  OS_CompAbsDelayTime( uint32 msecs, struct timespec * tm)
//{
//    clock_gettime( CLOCK_REALTIME,  tm );
//
//    /* add the delay to the current time */
//    tm->tv_sec  += (time_t) (msecs / 1000) ;
//    /* convert residue ( msecs )  to nanoseconds */
//    tm->tv_nsec +=  (msecs % 1000) * 1000000L ;
//
//    if(tm->tv_nsec  >= 1000000000L )
//    {
//        tm->tv_nsec -= 1000000000L ;
//        tm->tv_sec ++ ;
//    }
//}
/* ---------------------------------------------------------------------------
 * Name: OS_printf 
 * 
 * Purpose: This function abstracts out the printf type statements. This is 
 *          useful for using OS- specific thats that will allow non-polled
 *          print statements for the real time systems. 
 ---------------------------------------------------------------------------*/
void OS_printf( const char *String, ...)
{
    va_list     ptr;
    char msg_buffer [OS_BUFFER_SIZE];

    if ( OS_printf_enabled == TRUE )
    {
       va_start(ptr,String);
       vsnprintf(&msg_buffer[0], (size_t)OS_BUFFER_SIZE, String, ptr);
       va_end(ptr);
    
       msg_buffer[OS_BUFFER_SIZE -1] = '\0';
       printf("%s", &msg_buffer[0]);
       fflush(stdout);
    }

    
}/* end OS_printf*/

/* ---------------------------------------------------------------------------
 * Name: OS_printf_disable
 * 
 * Purpose: This function disables the output to the UART from OS_printf.  
 *
 ---------------------------------------------------------------------------*/
void OS_printf_disable(void)
{
   OS_printf_enabled = FALSE;
}/* end OS_printf_disable*/

/* ---------------------------------------------------------------------------
 * Name: OS_printf_enable
 * 
 * Purpose: This function enables the output to the UART through OS_printf.  
 *
 ---------------------------------------------------------------------------*/
void OS_printf_enable(void)
{
   OS_printf_enabled = TRUE;
}/* end OS_printf_enable*/

/*---------------------------------------------------------------------------------------
 *  Name: OS_GetErrorName()
---------------------------------------------------------------------------------------*/
int32 OS_GetErrorName(int32 error_num, os_err_name_t * err_name)
{
    os_err_name_t local_name;
    uint32        return_code = OS_SUCCESS;

    if ( err_name == NULL )
    {
       return(OS_INVALID_POINTER);
    }

    switch (error_num)
    {
        case OS_SUCCESS:
            strcpy(local_name,"OS_SUCCESS"); break;
        case OS_ERROR:
            strcpy(local_name,"OS_ERROR"); break;
        case OS_INVALID_POINTER:
            strcpy(local_name,"OS_INVALID_POINTER"); break;
        case OS_ERROR_ADDRESS_MISALIGNED:
            strcpy(local_name,"OS_ADDRESS_MISALIGNED"); break;
        case OS_ERROR_TIMEOUT:
            strcpy(local_name,"OS_ERROR_TIMEOUT"); break;
        case OS_INVALID_INT_NUM:
            strcpy(local_name,"OS_INVALID_INT_NUM"); break;
        case OS_SEM_FAILURE:
            strcpy(local_name,"OS_SEM_FAILURE"); break;
        case OS_SEM_TIMEOUT:
            strcpy(local_name,"OS_SEM_TIMEOUT"); break;
        case OS_QUEUE_EMPTY:
            strcpy(local_name,"OS_QUEUE_EMPTY"); break;
        case OS_QUEUE_FULL:
            strcpy(local_name,"OS_QUEUE_FULL"); break;
        case OS_QUEUE_TIMEOUT:
            strcpy(local_name,"OS_QUEUE_TIMEOUT"); break;
        case OS_QUEUE_INVALID_SIZE:
            strcpy(local_name,"OS_QUEUE_INVALID_SIZE"); break;
        case OS_QUEUE_ID_ERROR:
            strcpy(local_name,"OS_QUEUE_ID_ERROR"); break;
        case OS_ERR_NAME_TOO_LONG:
            strcpy(local_name,"OS_ERR_NAME_TOO_LONG"); break;
        case OS_ERR_NO_FREE_IDS:
            strcpy(local_name,"OS_ERR_NO_FREE_IDS"); break;
        case OS_ERR_NAME_TAKEN:
            strcpy(local_name,"OS_ERR_NAME_TAKEN"); break;
        case OS_ERR_INVALID_ID:
            strcpy(local_name,"OS_ERR_INVALID_ID"); break;
        case OS_ERR_NAME_NOT_FOUND:
            strcpy(local_name,"OS_ERR_NAME_NOT_FOUND"); break;
        case OS_ERR_SEM_NOT_FULL:
            strcpy(local_name,"OS_ERR_SEM_NOT_FULL"); break;
        case OS_ERR_INVALID_PRIORITY:
            strcpy(local_name,"OS_ERR_INVALID_PRIORITY"); break;

        default: strcpy(local_name,"ERROR_UNKNOWN");
                 return_code = OS_ERROR;
    }

    strcpy((char*) err_name, local_name);

    return return_code;
}
/*----------------------------------------------------------------------------
 * Name: OS_PriorityRemap
 *
 * Purpose: Remaps the OSAL priority into one that is viable for this OS
----------------------------------------------------------------------------*/

int32 OS_PriorityRemap(uint32 InputPri)
{
    int OutputPri;
    int pmax = sched_get_priority_max( SCHED_FIFO );
    int pmin = sched_get_priority_min( SCHED_FIFO );
    int prange = abs((pmax - pmin)  +1);
    int numbins, offset;
    int IsMinNegative = 0;
    int MinNegOffset = 0;
    int IsMaxNegative = 0;
    int MaxNegOffset = 0;
    int InputRev;

    /* If an end point is negative, adjust the range upward so that there is no negative */
    if (pmin < 0)
    {
        IsMinNegative = 1;
        MinNegOffset = -pmin;
        pmin += MinNegOffset;
        pmax += MinNegOffset;
    } 

    if (pmax < 0)
    {
        IsMaxNegative = 1;
        MaxNegOffset = -pmax;
        pmin += MaxNegOffset;
        pmax += MaxNegOffset;
    }

    /* calculate the number of 'bins' to map the OSAL priorities into.
     * Since the Underlying OS will have AT MOST as many priority levels as
     * the OSAL (256 values), then we will be pigeon-holing a larger range 
     * (OSAL priorities) into a small range (OS priorities), or the ranges are
     * equal, which is OK too.
     */

    numbins = MAX_PRIORITY/prange;

    /* If we are more than half way to making a new bin, add another one */
   if (MAX_PRIORITY % prange > prange/2)
   {
      numbins++;
   } 
    

    /* Since the OSAL priorities have 0 as the highest and 255 as the lowest,
     * we need to reverse this so that the numerically higher number is a higher priority
     * to work with the OS's
     */

     InputRev = MAX_PRIORITY - InputPri;
       
     /* calculate the offset from the min value */
     offset = InputRev / numbins ;
          
     OutputPri = pmin + offset ;  

     /* take care of extraneous cases at ends, if they occur. */
     if (OutputPri > pmax)
     {
         OutputPri = pmax;
     }

     if ( OutputPri < pmin)
     {
            OutputPri = pmin;
     }

     /* if an end point was negative, shift it back */
     if (IsMinNegative == 1)
     {
         OutputPri -= MinNegOffset;
     }

     if (IsMaxNegative == 1)
     {
         OutputPri -= MaxNegOffset;
     }


    return OutputPri;
}/*end OS_PriortyRemap*/

/* ---------------------------------------------------------------------------
 * Name: OS_ThreadKillHandler
 * 
 * Purpose: This function allows for a task to be deleted when OS_TaskDelete
 * is called  
----------------------------------------------------------------------------*/

void    OS_ThreadKillHandler(int sig)
{
    pthread_exit(NULL);

}/*end OS_ThreadKillHandler */


/*
**
**   Name: OS_FPUExcSetMask
**
**   Purpose: This function sets the FPU exception mask
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions.
*/
int32 OS_FPUExcSetMask(uint32 mask)
{
    /*
    ** Not implemented in linux.
    */
    return(OS_SUCCESS);
}

/*
**
**   Name: OS_FPUExcGetMask
**
**   Purpose: This function gets the FPU exception mask
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions.
*/
int32 OS_FPUExcGetMask(uint32 *mask)
{
    /*
    ** Not implemented in linux.
    */
    return(OS_SUCCESS);
}

/*
**
**   Name: OS_InterruptSafeLock
**
**   Purpose: This function masks signals and locks a mutex for mutual exclusion 
**
*/
int OS_InterruptSafeLock(pthread_mutex_t *lock, sigset_t *set, sigset_t *previous)
{
    /* Block all signals */
    sigfillset(set);

    if (pthread_sigmask(SIG_SETMASK, set, previous) == 0) 
    {
        /* Acquire the lock */
    	int rc = pthread_mutex_lock(lock);
    	if(rc == EOWNERDEAD)
    	{
    		pthread_mutex_consistent(lock);

    		rc = pthread_mutex_lock(lock);

    		OS_printf("pthread_mutex_lock() returned error\n");
    	}
    	else if(rc != 0)
    	{
    		OS_printf("OS_InterruptSafeLock:  pthread_mutex_lock(lock) returned %i\n", rc);
    	}
    	return rc;
    } 
    else 
    {
    	printf("OOPS!\n");
        return EINVAL;
    }
}

/*
**
**   Name: OS_InterruptSafeUnlock
**
**   Purpose: This function unlocks the mutex and restores the signal mask 
**
*/
void OS_InterruptSafeUnlock(pthread_mutex_t *lock, sigset_t *previous)
{
    /* Release the lock */
	int rc = pthread_mutex_unlock(lock);
	if(rc != 0)
	{
		OS_printf("OS_InterruptSafeUnlock:  pthread_mutex_unlock(lock, previous) returned %i\n", rc);
	}

    /* Restore previous signals */
    pthread_sigmask(SIG_SETMASK, previous, 0);
}


