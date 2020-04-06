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

#include <native/task.h>
#include <native/mutex.h>
#include <rtdk.h>
#include <unistd.h>
#include <sys/mman.h>

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

/*tasks */
typedef struct
{
    int       free;
    RT_TASK   id;
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
	char    buffer[OS_MAX_QUEUE_WIDTH];
}OS_queue_data_t;

typedef struct
{
    int    			free;
    OS_queue_data_t	qData[OS_MAX_QUEUE_DEPTH];
    uint32 			max_size;
    char   			name [OS_MAX_API_NAME];
    int    			creator;
    //pthread_cond_t  cv;
    int32	  		head;
    int32   		tail;
    uint32   		width;
    uint32   		depth;
}OS_queue_record_t;

/* Binary Semaphores */
typedef struct
{
    int             free;
    RT_MUTEX		id;
    //pthread_cond_t  cv;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
}OS_bin_sem_record_t;

/*Counting Semaphores */
typedef struct
{
    int             free;
    RT_MUTEX		id;
    //pthread_cond_t  cv;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
}OS_count_sem_record_t;

/* Mutexes */
typedef struct
{
    int             free;
    RT_MUTEX 		id;
    char            name [OS_MAX_API_NAME];
    int             creator;
}OS_mut_sem_record_t;

/* function pointer type */
typedef void (*FuncPtr_t)(void);

/* Tables where the OS object information is stored */
OS_task_record_t      OS_task_table          [OS_MAX_TASKS];
OS_queue_record_t     OS_queue_table         [OS_MAX_QUEUES];
OS_bin_sem_record_t   OS_bin_sem_table       [OS_MAX_BIN_SEMAPHORES];
OS_count_sem_record_t OS_count_sem_table     [OS_MAX_COUNT_SEMAPHORES];
OS_mut_sem_record_t   OS_mut_sem_table       [OS_MAX_MUTEXES];

pthread_mutex_t OS_task_table_mut;
pthread_mutex_t OS_queue_table_mut;
pthread_mutex_t OS_bin_sem_table_mut;
pthread_mutex_t OS_mut_sem_table_mut;
pthread_mutex_t OS_count_sem_table_mut;
pthread_mutex_t OS_timeout_table_mut;

uint32          OS_printf_enabled = TRUE;
volatile uint32 OS_shutdown = FALSE;
uint32 OS_API_Initialized = OS_API_UNINITIALIZED;


int32  OS_PriorityRemap(uint32 InputPri);
uint32 OS_FindCreator(void);


int32 OS_API_Init (OS_RunTimeModeEnum_t Mode)
{
	int                 i;
	int                 ret;
	//pthread_mutexattr_t mutex_attr ;
	int32               return_code = OS_SUCCESS;

	/* Restrict this memory from being paged to the swap area. */
	mlockall(MCL_CURRENT | MCL_FUTURE);

	/* Initialize the real time printing library. */
	rt_print_auto_init(1);

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

    OS_API_Initialized = OS_API_INITIALIZED;

	return OS_SUCCESS;
}



void OS_IdleLoop (void)
{
	while (OS_shutdown != OS_SHUTDOWN_MAGIC_NUMBER)
	{
		/* Unblock signals and wait for something to occur */
		//sigsuspend(&mask);
		sleep(1);
	}
}



void OS_DeleteAllObjects       (void)
{
	uint32 i = 0;

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

    OS_API_Initialized = OS_API_UNINITIALIZED;
}



void OS_ApplicationShutdown         (uint8 flag)
{
	if (flag == TRUE)
	{
		OS_shutdown = OS_SHUTDOWN_MAGIC_NUMBER;
	}
}



int32 OS_TaskCreate            (uint32 *task_id, const char *task_name,
                                osal_task_entry function_pointer,
                                uint32 *stack_pointer,
                                uint32 stack_size,
                                uint32 priority, uint32 flags)
{
    int                return_code = 0;
    int                possible_taskid;
    int                i;
    uint32             local_stack_size;
    int                ret;
    int                os_priority;
    int                inheritsched;
    //sigset_t           previous;
    //sigset_t           mask;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
        printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
    	return OS_ERROR;
    }

    /* Check for NULL pointers */
    if( (task_name == NULL) || (function_pointer == NULL) || (task_id == NULL) )
    {
        printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
        return OS_INVALID_POINTER;
    }

    /* we don't want to allow names too long*/
    /* if truncated, two names might be the same */
    if (strlen(task_name) >= OS_MAX_API_NAME)
    {
        printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Check for bad priority */
    if (priority > MAX_PRIORITY)
    {
        printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
        return OS_ERR_INVALID_PRIORITY;
    }

    /* Change OSAL priority into a priority that will work for this OS */
    os_priority = OS_PriorityRemap(priority);

    /* Check Parameters */
//    OS_InterruptSafeLock(&OS_task_table_mut, &mask, &previous);

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
//        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if ((OS_task_table[i].free == FALSE) &&
           ( strcmp((char*) task_name, OS_task_table[i].name) == 0))
        {
//            OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
            printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
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
    ** Create thread
    */
    return_code = rt_task_create(&(OS_task_table[possible_taskid].id),
    		task_name, local_stack_size, os_priority, 0);
    if (return_code != 0)
    {
        OS_task_table[possible_taskid].free = TRUE;
//        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        #ifdef OS_DEBUG_PRINTF
           printf("rt_task_create in OS_TaskCreate, Task ID = %d\n", possible_taskid);
        #endif
           printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
           printf("priority = %u  task_name = '%s'  %i %u %s\n", os_priority, task_name, return_code, errno, strerror(errno));
        return(OS_ERROR);
    }

    return_code = rt_task_start(&(OS_task_table[possible_taskid].id),
    		(void(*)(void *arg))function_pointer, (void *)0);
    if (return_code != 0)
    {
        OS_task_table[possible_taskid].free = TRUE;
//        OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);
        #ifdef OS_DEBUG_PRINTF
           printf("rt_task_start in OS_TaskCreate, Task ID = %d\n", possible_taskid);
        #endif
           printf("%s %s %u\n", __FILE__, __FUNCTION__, __LINE__);
        return(OS_ERROR);
    }

    /*
    ** Assign the task ID
    */
    *task_id = possible_taskid;

    /*
    ** Initialize the table entries
    */
    OS_task_table[possible_taskid].free = FALSE;
    strcpy(OS_task_table[*task_id].name, (char*) task_name);
    OS_task_table[possible_taskid].creator = OS_FindCreator();
    OS_task_table[possible_taskid].stack_size = stack_size;
    /* Use the abstracted priority, not the OS one */
    OS_task_table[possible_taskid].priority = priority;

    //OS_InterruptSafeUnlock(&OS_task_table_mut, &previous);

    return OS_SUCCESS;
}



int32 OS_TaskDelete            (uint32 task_id)
{
	return OS_ERROR;
}



void OS_TaskExit               (void)
{

}



int32 OS_TaskInstallDeleteHandler(osal_task_entry function_pointer)
{
	return OS_ERROR;
}



int32 OS_TaskDelay             (uint32 millisecond)
{
	return OS_ERROR;
}



int32 OS_TaskSetPriority       (uint32 task_id, uint32 new_priority)
{
	return OS_ERROR;
}



int32 OS_TaskRegister          (void)
{
	return OS_ERROR;
}



uint32 OS_TaskGetId            (void)
{
	return OS_ERROR;
}



int32 OS_TaskGetIdByName       (uint32 *task_id, const char *task_name)
{
	return OS_ERROR;
}



int32 OS_TaskGetInfo           (uint32 task_id, OS_task_prop_t *task_prop)
{
	return OS_ERROR;
}




/*
** Message Queue API
*/

/*
** Queue Create now has the Queue ID returned to the caller.
*/
int32 OS_QueueCreate           (uint32 *queue_id, const char *queue_name,
                                uint32 queue_depth, uint32 data_size, uint32 flags)
{
	return OS_ERROR;
}



int32 OS_QueueDelete           (uint32 queue_id)
{
	return OS_ERROR;
}



int32 OS_QueueGet              (uint32 queue_id, void *data, uint32 size,
                                uint32 *size_copied, int32 timeout)
{
	return OS_ERROR;
}



int32 OS_QueuePut              (uint32 queue_id, const void *data, uint32 size,
                                uint32 flags)
{
	return OS_ERROR;
}



int32 OS_QueueGetIdByName      (uint32 *queue_id, const char *queue_name)
{
	return OS_ERROR;
}



int32 OS_QueueGetInfo          (uint32 queue_id, OS_queue_prop_t *queue_prop)
{
	return OS_ERROR;
}




/*
** Semaphore API
*/

int32 OS_BinSemCreate          (uint32 *sem_id, const char *sem_name,
                                uint32 sem_initial_value, uint32 options)
{
	return OS_ERROR;
}



int32 OS_BinSemFlush            (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_BinSemGive            (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_BinSemTake            (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_BinSemTimedWait       (uint32 sem_id, uint32 msecs)
{
	return OS_ERROR;
}



int32 OS_BinSemDelete          (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_BinSemGetIdByName     (uint32 *sem_id, const char *sem_name)
{
	return OS_ERROR;
}



int32 OS_BinSemGetInfo         (uint32 sem_id, OS_bin_sem_prop_t *bin_prop)
{
	return OS_ERROR;
}




int32 OS_CountSemCreate          (uint32 *sem_id, const char *sem_name,
                                uint32 sem_initial_value, uint32 options)
{
	return OS_ERROR;
}



int32 OS_CountSemGive            (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_CountSemTake            (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_CountSemTimedWait       (uint32 sem_id, uint32 msecs)
{
	return OS_ERROR;
}



int32 OS_CountSemDelete          (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_CountSemGetIdByName     (uint32 *sem_id, const char *sem_name)
{
	return OS_ERROR;
}



int32 OS_CountSemGetInfo         (uint32 sem_id, OS_count_sem_prop_t *count_prop)
{
	return OS_ERROR;
}



int32 OS_MutSemCreate           (uint32 *sem_id, const char *sem_name, uint32 options)
{
	return OS_ERROR;
}



int32 OS_MutSemGive             (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_MutSemTake             (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_MutSemDelete           (uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_MutSemGetIdByName      (uint32 *sem_id, const char *sem_name)
{
	return OS_ERROR;
}



int32 OS_MutSemGetInfo          (uint32 sem_id, OS_mut_sem_prop_t *mut_prop)
{
	return OS_ERROR;
}



int32 OS_Milli2Ticks           (uint32 milli_seconds)
{
	return OS_ERROR;
}



int32 OS_Tick2Micros           (void)
{
	return OS_ERROR;
}



int32  OS_GetLocalTime         (OS_time_t *time_struct)
{
	return OS_ERROR;
}



int32  OS_SetLocalTime         (OS_time_t *time_struct)
{
	return OS_ERROR;
}



int32 OS_ExcAttachHandler      (uint32 ExceptionNumber,
                                void (*ExceptionHandler)(uint32, const void *,uint32),
                                int32 parameter)
{
	return OS_ERROR;
}



int32 OS_ExcEnable             (int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_ExcDisable            (int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_FPUExcAttachHandler   (uint32 ExceptionNumber, void * ExceptionHandler ,
                                 int32 parameter)
{
	return OS_ERROR;
}



int32 OS_FPUExcEnable          (int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_FPUExcDisable         (int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_FPUExcSetMask         (uint32 mask)
{
	return OS_ERROR;
}



int32 OS_FPUExcGetMask         (uint32 *mask)
{
	return OS_ERROR;
}



int32 OS_IntAttachHandler  (uint32 InterruptNumber, osal_task_entry InterruptHandler, int32 parameter)
{
	return OS_ERROR;
}



int32 OS_IntUnlock         (int32 IntLevel)
{
	return OS_ERROR;
}



int32 OS_IntLock           (void)
{
	return OS_ERROR;
}



int32 OS_IntEnable         (int32 Level)
{
	return OS_ERROR;
}



int32 OS_IntDisable        (int32 Level)
{
	return OS_ERROR;
}



int32 OS_IntSetMask        (uint32 mask)
{
	return OS_ERROR;
}



int32 OS_IntGetMask        (uint32 *mask)
{
	return OS_ERROR;
}



int32 OS_IntAck             (int32 InterruptNumber)
{
	return OS_ERROR;
}



int32 OS_ShMemInit          (void)
{
	return OS_ERROR;
}



int32 OS_ShMemCreate        (uint32 *Id, uint32 NBytes, const char* SegName)
{
	return OS_ERROR;
}



int32 OS_ShMemSemTake       (uint32 Id)
{
	return OS_ERROR;
}



int32 OS_ShMemSemGive       (uint32 Id)
{
	return OS_ERROR;
}



int32 OS_ShMemAttach        (cpuaddr * Address, uint32 Id)
{
	return OS_ERROR;
}



int32 OS_ShMemGetIdByName   (uint32 *ShMemId, const char *SegName )
{
	return OS_ERROR;
}



int32 OS_HeapGetInfo       (OS_heap_prop_t *heap_prop)
{
	return OS_ERROR;
}



int32 OS_GetErrorName      (int32 error_num, os_err_name_t* err_name)
{
	return OS_ERROR;
}



void OS_printf( const char *string, ...)
{
}



void OS_printf_disable(void)
{
}



void OS_printf_enable(void)
{
}



void OS_ApplicationExit(int32 Status)
{
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


uint32 OS_FindCreator(void)
{
	RT_TASK    *task_id;
    uint32 i;

    task_id = rt_task_self();

    /*
    ** Get RT Task Id
    */
    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if (rt_task_same(task_id, &OS_task_table[i].id) != 0 )
        {
            break;
        }
    }

    return i;
}
