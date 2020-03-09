#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "osapi.h"
#include "common_types.h"
#include "xil_printf.h"
#include "osconfig.h"



/*
** Defines
*/
#define UNINITIALIZED 0
#define MAX_PRIORITY 255

#define OS_API_UNINITIALIZED 0
#define OS_API_INITIALIZED   1

uint32 OS_API_Initialized = OS_API_UNINITIALIZED;

int32 OS_TICKS_OFFSET = 0;


/*tasks */
typedef struct
{
    int          free;
    TaskHandle_t handle;
    int          creator;
    char         name [OS_MAX_API_NAME];
    uint32       stack_size;
    uint32       priority;
    void         *delete_hook_pointer;
    void         *entry_point;
}OS_task_record_t;

typedef struct
{
    int    			free;
    uint32 			max_size;
    char   			name [OS_MAX_API_NAME];
    int    			creator;
    QueueHandle_t   handle;
    uint32   		width;
    uint32   		depth;
}OS_queue_record_t;

/* Binary Semaphores */
typedef struct
{
    int               free;
    SemaphoreHandle_t handle;
    char              name [OS_MAX_API_NAME];
    int               creator;
    int               max_value;
    StaticSemaphore_t pxSemaphoreBuffer;
}OS_bin_sem_record_t;

/*Counting Semaphores */
typedef struct
{
    int               free;
    SemaphoreHandle_t handle;
    char              name [OS_MAX_API_NAME];
    int               creator;
    int               max_value;
    int               current_value;
    StaticSemaphore_t pxSemaphoreBuffer;
}OS_count_sem_record_t;

/* Mutexes */
typedef struct
{
    int               free;
    SemaphoreHandle_t handle;
    char              name [OS_MAX_API_NAME];
    int               creator;
    StaticSemaphore_t pxMutexBuffer;
}OS_mut_sem_record_t;

/* function pointer type */
typedef void (*FuncPtr_t)(void);

/* Tables where the OS object information is stored */
OS_task_record_t      OS_task_table          [OS_MAX_TASKS];
OS_queue_record_t     OS_queue_table         [OS_MAX_QUEUES];
OS_bin_sem_record_t   OS_bin_sem_table       [OS_MAX_BIN_SEMAPHORES];
OS_count_sem_record_t OS_count_sem_table     [OS_MAX_COUNT_SEMAPHORES];
OS_mut_sem_record_t   OS_mut_sem_table       [OS_MAX_MUTEXES];

SemaphoreHandle_t OS_task_table_mut;
SemaphoreHandle_t OS_queue_table_mut;
SemaphoreHandle_t OS_bin_sem_table_mut;
SemaphoreHandle_t OS_mut_sem_table_mut;
SemaphoreHandle_t OS_count_sem_table_mut;

uint32 OS_printf_enabled = TRUE;

UBaseType_t OS_PriorityRemap(uint32 InputPri);
uint32      OS_FindCreator(void);



void OS_TaskEntryPoint(void * pvParameters)
{
	uint32 *taskID = (uint32*) pvParameters;

	if(*taskID >= OS_MAX_TASKS)
	{
		/* TODO:  Log this. */
	}
	else
	{
		if(OS_task_table[*taskID].entry_point == 0)
		{
			/* TODO:  Log this. */
		}
		else
		{
		    FuncPtr_t ptrFunc;

		    ptrFunc = (FuncPtr_t)(OS_task_table[*taskID].entry_point);
		    (*ptrFunc)();

		    /* FreeRTOS requires you call this next function BEFORE the task terminates. */
		    vTaskDelete(OS_task_table[*taskID].handle);

		    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

		    OS_task_table[*taskID].free = TRUE;
		    strcpy(OS_task_table[*taskID].name, "");
		    OS_task_table[*taskID].creator = UNINITIALIZED;
		    OS_task_table[*taskID].stack_size = UNINITIALIZED;
		    OS_task_table[*taskID].priority = UNINITIALIZED;
		    OS_task_table[*taskID].handle = UNINITIALIZED;
		    OS_task_table[*taskID].delete_hook_pointer = NULL;

		    xSemaphoreGiveRecursive(OS_task_table_mut);
		}
	}
}



int32 OS_API_InitEx(OS_RunTimeModeEnum_t Mode)
{
    unsigned int i;
    int32        return_code = OS_SUCCESS;

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
        return return_code;
    }
#endif

    /*
    ** Initialize the Timer API
    */
    return_code = OS_TimerAPIInit();
    if ( return_code == OS_ERROR )
    {
        return return_code;
    }

    /*
    ** Create the mutexes that protect the OSAPI structures the function
    ** returns on error, since we don't want to go through the extra
    ** trouble of creating and deleting resources for nothing
    */
    OS_task_table_mut = xSemaphoreCreateRecursiveMutex();
    if ( OS_task_table_mut == NULL )
    {
        return_code = OS_ERROR;
        return return_code;
    }

    OS_queue_table_mut = xSemaphoreCreateRecursiveMutex();
    if ( OS_queue_table_mut == NULL )
    {
        return_code = OS_ERROR;
        return return_code;
    }

    OS_bin_sem_table_mut = xSemaphoreCreateRecursiveMutex();
    if ( OS_bin_sem_table_mut == NULL )
    {
        return_code = OS_ERROR;
        return return_code;
    }

    OS_count_sem_table_mut = xSemaphoreCreateRecursiveMutex();
    if ( OS_count_sem_table_mut == NULL )
    {
        return_code = OS_ERROR;
        return return_code;
    }

    OS_mut_sem_table_mut = xSemaphoreCreateRecursiveMutex();
    if ( OS_mut_sem_table_mut == NULL )
    {
        return_code = OS_ERROR;
        return return_code;
    }

    /*
    ** File system init
    */
    return_code = OS_FS_Init();

    OS_API_Initialized = OS_API_INITIALIZED;

    return return_code;
}



int32 OS_API_Init(void)
{
	return OS_API_InitEx(OS_RUNTIME_MODE_REALTIME);
}



void OS_IdleLoop(void)
{
    for(;;)
    {
    	vTaskDelay(10);
    }
}



void OS_DeleteAllObjects(void)
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



int32 OS_TaskCreate(uint32 *task_id, const char *task_name,
                    osal_task_entry function_pointer,
                    uint32 *stack_pointer,
                    uint32 stack_size,
                    uint32 priority, uint32 flags)
{
	BaseType_t  xReturned = 0;
    int         possible_taskid;
    int         i;
    uint32      local_stack_size;
    UBaseType_t os_priority;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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
    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

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
        xSemaphoreGiveRecursive(OS_task_table_mut);

        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if ((OS_task_table[i].free == FALSE) &&
           ( strcmp((char*) task_name, OS_task_table[i].name) == 0))
        {
            xSemaphoreGiveRecursive(OS_task_table_mut);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /*
    ** Set the possible task Id to not free so that
    ** no other task can try to use it
    */
    OS_task_table[possible_taskid].free = FALSE;

    if ( stack_size < configMINIMAL_STACK_SIZE )
    {
        local_stack_size = configMINIMAL_STACK_SIZE;
    }
    else
    {
        local_stack_size = stack_size;
    }

    OS_task_table[possible_taskid].entry_point = (void *) function_pointer;

    /*
    ** Create thread
    */
    xReturned = xTaskCreate( OS_TaskEntryPoint,
    		                 task_name,
							 local_stack_size,
                             (void*)possible_taskid,
                             os_priority,
							 &(OS_task_table[possible_taskid].handle)
                          );
    if (xReturned != pdPASS)
    {
        OS_task_table[possible_taskid].free = TRUE;
        xSemaphoreGiveRecursive(OS_task_table_mut);
        #ifdef OS_DEBUG_PRINTF
           OS_printf("pthread_create error in OS_TaskCreate, Task ID = %d\n",possible_taskid);
        #endif
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

    xSemaphoreGiveRecursive(OS_task_table_mut);

    return OS_SUCCESS;
}



int32 OS_TaskDelete(uint32 task_id)
{
    FuncPtr_t FunctionPointer;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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
    vTaskDelete(OS_task_table[task_id].handle);

    /*
    ** Now that the task is deleted, remove its
    ** "presence" in OS_task_table
    */
    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    OS_task_table[task_id].free = TRUE;
    strcpy(OS_task_table[task_id].name, "");
    OS_task_table[task_id].creator = UNINITIALIZED;
    OS_task_table[task_id].stack_size = UNINITIALIZED;
    OS_task_table[task_id].priority = UNINITIALIZED;
    OS_task_table[task_id].handle = UNINITIALIZED;
    OS_task_table[task_id].delete_hook_pointer = NULL;

    xSemaphoreGiveRecursive(OS_task_table_mut);

    return OS_SUCCESS;
}



void OS_TaskExit(void)
{
    uint32    task_id;

    task_id = OS_TaskGetId();

    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    OS_task_table[task_id].free = TRUE;
    strcpy(OS_task_table[task_id].name, "");
    OS_task_table[task_id].creator = UNINITIALIZED;
    OS_task_table[task_id].stack_size = UNINITIALIZED;
    OS_task_table[task_id].priority = UNINITIALIZED;
    OS_task_table[task_id].handle = UNINITIALIZED;
    OS_task_table[task_id].delete_hook_pointer = NULL;

    xSemaphoreGiveRecursive(OS_task_table_mut);

    vTaskDelete(NULL);
}



int32 OS_TaskInstallDeleteHandler(osal_task_entry function_pointer)
{
    uint32    task_id;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    task_id = OS_TaskGetId();

    if ( task_id >= OS_MAX_TASKS )
    {
        return(OS_ERR_INVALID_ID);
    }

    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    if ( OS_task_table[task_id].free != FALSE )
    {
        /*
        ** Somehow the calling task is not registered
        */
        xSemaphoreGiveRecursive(OS_task_table_mut);
        return(OS_ERR_INVALID_ID);
    }

    /*
    ** Install the pointer
    */
    OS_task_table[task_id].delete_hook_pointer = (void *)function_pointer;

    xSemaphoreGiveRecursive(OS_task_table_mut);

    return(OS_SUCCESS);

}



int32 OS_TaskDelay(uint32 millisecond)
{
	TickType_t ticks;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    ticks = OS_Milli2Ticks(millisecond);

    vTaskDelay(ticks);

    return OS_SUCCESS;
}



int32 OS_TaskSetPriority(uint32 task_id, uint32 new_priority)
{
    int os_priority;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    if(task_id >= OS_MAX_TASKS || OS_task_table[task_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if(new_priority > MAX_PRIORITY)
    {
        return OS_ERR_INVALID_PRIORITY;
    }

    /* Change OSAL priority into a priority that will work for this OS */
    os_priority = OS_PriorityRemap(new_priority);

    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /* Use the abstracted priority, not the OS one */
    /* Change the priority in the table as well */
    OS_task_table[task_id].priority = new_priority;

    vTaskPrioritySet(NULL, os_priority);

    xSemaphoreGiveRecursive(OS_task_table_mut);

    return OS_SUCCESS;
}



int32 OS_TaskRegister(void)
{
    /* No need to do anything with this OSAL. */

    return OS_SUCCESS;
}



uint32 OS_TaskGetId(void)
{
	unsigned int i = 0;
	xTaskHandle xHandle;
	uint32 id = 0;

    xHandle = xTaskGetCurrentTaskHandle();

    for(i = 0; i < OS_MAX_TASKS; i++)
    {
        if(OS_task_table[i].handle == xHandle)
        {
        	id = i;
        }
    }

	return id;
}



int32 OS_TaskGetIdByName(uint32 *task_id, const char *task_name)
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

}



int32 OS_TaskGetInfo(uint32 task_id, OS_task_prop_t *task_prop)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /*
    ** Check to see that the id given is valid
    */
    if (task_id >= OS_MAX_TASKS || OS_task_table[task_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if( task_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* put the info into the stucture */
    xSemaphoreTakeRecursive(OS_task_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    task_prop -> creator =    OS_task_table[task_id].creator;
    task_prop -> stack_size = OS_task_table[task_id].stack_size;
    task_prop -> priority =   OS_task_table[task_id].priority;
    task_prop -> OStask_id =  (uint32) OS_task_table[task_id].handle;

    strcpy(task_prop-> name, OS_task_table[task_id].name);

    xSemaphoreGiveRecursive(OS_task_table_mut);

    return OS_SUCCESS;

}



int32 OS_QueueCreate(uint32 *queue_id, const char *queue_name,
                     uint32 queue_depth, uint32 data_size, uint32 flags)
{
    unsigned int i;
    uint32       possible_qid;

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
    if(queue_depth > OS_MAX_QUEUE_DEPTH)
    {
    	return OS_QUEUE_INVALID_SIZE;
    }

    xSemaphoreTakeRecursive(OS_queue_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    for(possible_qid = 0; possible_qid < OS_MAX_QUEUES; possible_qid++)
    {
        if (OS_queue_table[possible_qid].free == TRUE)
            break;
    }

    if( possible_qid >= OS_MAX_QUEUES || OS_queue_table[possible_qid].free != TRUE)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_QUEUES; i++)
    {
        if ((OS_queue_table[i].free == FALSE) &&
            strcmp ((char*) queue_name, OS_queue_table[i].name) == 0)
        {
            xSemaphoreGiveRecursive(OS_queue_table_mut);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /* Set the possible task Id to not free so that
     * no other task can try to use it */
    *queue_id = possible_qid;

    OS_queue_table[*queue_id].handle = xQueueCreate(queue_depth, data_size);
    if(NULL == OS_queue_table[*queue_id].handle)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_ERROR;
    }

    vQueueAddToRegistry(OS_queue_table[*queue_id].handle, queue_name);

    OS_queue_table[*queue_id].free = FALSE;
    OS_queue_table[*queue_id].max_size = data_size;
    strcpy( OS_queue_table[*queue_id].name, (char*) queue_name);
    OS_queue_table[*queue_id].creator = OS_FindCreator();
	OS_queue_table[*queue_id].width = data_size;
	OS_queue_table[*queue_id].depth = queue_depth;

    xSemaphoreGiveRecursive(OS_queue_table_mut);

    return OS_SUCCESS;

}



int32 OS_QueueDelete(uint32 queue_id)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check to see if the queue_id given is valid */

    if (queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
       return OS_ERR_INVALID_ID;
    }

    /*
     * Now that the queue is deleted, remove its "presence"
     * in OS_message_q_table and OS_message_q_name_table
     */
    xSemaphoreTakeRecursive(OS_queue_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    vQueueUnregisterQueue(OS_queue_table[queue_id].handle);
    vQueueDelete(OS_queue_table[queue_id].handle);

    OS_queue_table[queue_id].free = TRUE;
    strcpy(OS_queue_table[queue_id].name, "");
    OS_queue_table[queue_id].creator = UNINITIALIZED;
    OS_queue_table[queue_id].max_size = 0;

    xSemaphoreGiveRecursive(OS_queue_table_mut);

    return OS_SUCCESS;
}



int32 OS_QueueGet(uint32 queue_id, void *data, uint32 size,
                  uint32 *size_copied, int32 timeout)
{
	BaseType_t funcStatus;
	TickType_t timeoutInTicks;
	int32      returnCode = OS_ERROR;


    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    xSemaphoreTakeRecursive(OS_queue_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /*
    ** Check Parameters
    */
    if(queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_ERR_INVALID_ID;
    }
    else if( (data == NULL) || (size_copied == NULL) )
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_INVALID_POINTER;
    }
    else if( size < OS_queue_table[queue_id].max_size )
    {
        /*
        ** The buffer that the user is passing in is potentially too small.  Reject
        ** the request.
        */
        *size_copied = 0;
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_QUEUE_INVALID_SIZE;
    }

    if (timeout == OS_PEND)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        funcStatus = xQueueReceive(OS_queue_table[queue_id].handle, data, portMAX_DELAY);
    	if(pdFALSE == funcStatus)
    	{
        	*size_copied = 0;
        	returnCode = OS_ERROR;
    	}
    	else
    	{
    	    *size_copied = OS_queue_table[queue_id].max_size;
        	returnCode = OS_SUCCESS;
    	}
    }
    else if (timeout == OS_CHECK)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        funcStatus = xQueueReceive(OS_queue_table[queue_id].handle, data, 0);
    	if(pdFALSE == funcStatus)
    	{
        	*size_copied = 0;
        	returnCode = OS_QUEUE_EMPTY;
    	}
    	else
    	{
        	*size_copied = OS_queue_table[queue_id].max_size;
        	returnCode = OS_SUCCESS;
    	}
    }
    else /* timeout */
    {
    	timeoutInTicks = OS_Milli2Ticks(timeout);

        xSemaphoreGiveRecursive(OS_queue_table_mut);

        funcStatus = xQueueReceive(OS_queue_table[queue_id].handle, data, timeoutInTicks);
    	if(pdFALSE == funcStatus)
    	{
        	*size_copied = 0;
        	returnCode = OS_QUEUE_TIMEOUT;
    	}
    	else
    	{
        	*size_copied = OS_queue_table[queue_id].max_size;
        	returnCode = OS_SUCCESS;
    	}
    }

	return returnCode;
}



int32 OS_QueuePut(uint32 queue_id, const void *data, uint32 size,
                  uint32 flags)
{
	BaseType_t funcStatus;
	int32      returnCode = OS_ERROR;


    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    xSemaphoreTakeRecursive(OS_queue_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /*
    ** Check Parameters
    */
    if(queue_id >= OS_MAX_QUEUES || OS_queue_table[queue_id].free == TRUE)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_ERR_INVALID_ID;
    }

    if (data == NULL)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
        return OS_INVALID_POINTER;
    }

    if(size > OS_queue_table[queue_id].width)
    {
        xSemaphoreGiveRecursive(OS_queue_table_mut);
    	return OS_QUEUE_INVALID_SIZE;
    }

    funcStatus = xQueueSendToBack(OS_queue_table[queue_id].handle, data, 0);
    if(errQUEUE_FULL == funcStatus)
    {
        returnCode = OS_QUEUE_FULL;
    }
    else if(funcStatus != pdTRUE)
    {
        returnCode = OS_ERROR;
    }
    else
    {
        returnCode = OS_SUCCESS;
    }

    xSemaphoreGiveRecursive(OS_queue_table_mut);

    return returnCode;
}



int32 OS_QueueGetIdByName(uint32 *queue_id, const char *queue_name)
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
}



int32 OS_QueueGetInfo(uint32 queue_id, OS_queue_prop_t *queue_prop)
{
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
    xSemaphoreTakeRecursive(OS_queue_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    queue_prop->creator = OS_queue_table[queue_id].creator;
    strncpy(queue_prop->name, OS_queue_table[queue_id].name, sizeof(queue_prop->name));

    xSemaphoreGiveRecursive(OS_queue_table_mut);

    return OS_SUCCESS;

}



int32 OS_BinSemCreate(uint32 *sem_id, const char *sem_name,
                      uint32 sem_initial_value, uint32 options)
{
    uint32 possible_semid;
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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
    if (strnlen(sem_name, OS_MAX_API_NAME+1) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Lock table */
    xSemaphoreTakeRecursive(OS_bin_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    for (possible_semid = 0; possible_semid < OS_MAX_BIN_SEMAPHORES; possible_semid++)
    {
        if (OS_bin_sem_table[possible_semid].free == TRUE)
        {
            break;
        }
    }

    if((possible_semid >= OS_MAX_BIN_SEMAPHORES) ||
       (OS_bin_sem_table[possible_semid].free != TRUE))
    {
        xSemaphoreGiveRecursive(OS_bin_sem_table_mut);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
        if ((OS_bin_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_bin_sem_table[i].name) == 0)
        {
            xSemaphoreGiveRecursive(OS_bin_sem_table_mut);
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
    ** fill out the proper OSAL table fields
    */
    *sem_id = possible_semid;

#if configSUPPORT_STATIC_ALLOCATION
    OS_bin_sem_table[*sem_id].handle = xSemaphoreCreateBinaryStatic(&OS_bin_sem_table[*sem_id].pxSemaphoreBuffer);
#else
    OS_bin_sem_table[*sem_id].handle = xSemaphoreCreateBinary();
#endif

    if(NULL == OS_bin_sem_table[*sem_id].handle)
    {
        xSemaphoreGiveRecursive(OS_bin_sem_table_mut);
    	return OS_ERROR;
    }

    if(sem_initial_value == 1)
    {
        xSemaphoreGive(OS_bin_sem_table[*sem_id].handle);
    }

    strncpy(OS_bin_sem_table[*sem_id].name, (char*) sem_name, sizeof(OS_bin_sem_table[*sem_id].name));
    OS_bin_sem_table[*sem_id].creator = OS_FindCreator();
    OS_bin_sem_table[*sem_id].max_value = 1;
    OS_bin_sem_table[*sem_id].free = FALSE;

    /* Unlock table */
    xSemaphoreGiveRecursive(OS_bin_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_BinSemFlush(uint32 sem_id)
{
	return OS_ERROR;
}



int32 OS_BinSemGive(uint32 sem_id)
{
	BaseType_t status;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    status = xSemaphoreGive(OS_bin_sem_table[sem_id].handle);
    if(pdFALSE == status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_BinSemTake(uint32 sem_id)
{
	BaseType_t status;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    status = xSemaphoreTake(OS_bin_sem_table[sem_id].handle, portMAX_DELAY);
    if(pdFALSE == status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_BinSemTimedWait(uint32 sem_id, uint32 msecs)
{
	BaseType_t status;
	TickType_t xTicksToWait;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    xTicksToWait = OS_Milli2Ticks(msecs);
    status = xSemaphoreTake(OS_bin_sem_table[sem_id].handle, xTicksToWait);
    if(pdFALSE == status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_BinSemDelete(uint32 sem_id)
{
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
    xSemaphoreTakeRecursive(OS_bin_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    vSemaphoreDelete(OS_bin_sem_table[sem_id].handle);

    /* Remove the Id from the table, and its name, so that it cannot be found again */
    OS_bin_sem_table[sem_id].free = TRUE;
    strcpy(OS_bin_sem_table[sem_id].name , "");
    OS_bin_sem_table[sem_id].creator = UNINITIALIZED;
    OS_bin_sem_table[sem_id].max_value = 0;

    /* Unlock table */
    xSemaphoreGiveRecursive(OS_bin_sem_table_mut);

    return OS_SUCCESS;

}



int32 OS_BinSemGetIdByName(uint32 *sem_id, const char *sem_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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

    xSemaphoreTakeRecursive(OS_bin_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);
    for (i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
        if (OS_bin_sem_table[i].free != TRUE &&
                (strcmp (OS_bin_sem_table[i].name , (char*) sem_name) == 0))
        {
            *sem_id = i;
            xSemaphoreGiveRecursive(OS_bin_sem_table_mut);
            return OS_SUCCESS;
        }
    }
    xSemaphoreGiveRecursive(OS_bin_sem_table_mut);

    /*
    ** The name was not found in the table,
    ** or it was, and the sem_id isn't valid anymore
    */
    return OS_ERR_NAME_NOT_FOUND;

}



int32 OS_BinSemGetInfo(uint32 sem_id, OS_bin_sem_prop_t *bin_prop)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED) {
    	return OS_ERROR;
    }

    /* Check parameters */
    if (sem_id >= OS_MAX_BIN_SEMAPHORES || OS_bin_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }
    if (bin_prop == NULL)
    {
        return OS_INVALID_POINTER;
    }

    /* put the info into the stucture */
    xSemaphoreTakeRecursive(OS_bin_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    bin_prop->creator =    OS_bin_sem_table[sem_id].creator;
    bin_prop->value = uxSemaphoreGetCount(OS_bin_sem_table[sem_id].handle);
    strcpy(bin_prop-> name, OS_bin_sem_table[sem_id].name);

    xSemaphoreGiveRecursive(OS_bin_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_CountSemCreate(uint32 *sem_id, const char *sem_name,
                        uint32 sem_initial_value, uint32 options)
{
    uint32 possible_semid;
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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
    if (strnlen(sem_name, OS_MAX_API_NAME+1) >= OS_MAX_API_NAME)
    {
        return OS_ERR_NAME_TOO_LONG;
    }

    /* Lock table */
    xSemaphoreTakeRecursive(OS_count_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    for (possible_semid = 0; possible_semid < OS_MAX_COUNT_SEMAPHORES; possible_semid++)
    {
        if (OS_count_sem_table[possible_semid].free == TRUE)
        {
            break;
        }
    }

    if((possible_semid >= OS_MAX_COUNT_SEMAPHORES) ||
       (OS_count_sem_table[possible_semid].free != TRUE))
    {
        xSemaphoreGiveRecursive(OS_count_sem_table_mut);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
        if ((OS_count_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_count_sem_table[i].name) == 0)
        {
            xSemaphoreGiveRecursive(OS_count_sem_table_mut);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /*
    ** Check to make sure the value is between 0 and SEM_VALUE_MAX
    */
    if (sem_initial_value < 0)
    {
        sem_initial_value = 0;
    }

    /*
    ** fill out the proper OSAL table fields
    */
    *sem_id = possible_semid;

#if configSUPPORT_STATIC_ALLOCATION
    OS_count_sem_table[*sem_id].handle = xSemaphoreCreateCountingStatic(OS_COUNT_SEMAPHORES_MAX_VALUE, sem_initial_value, &OS_count_sem_table[*sem_id].pxSemaphoreBuffer);
#else
    OS_count_sem_table[*sem_id].handle = xSemaphoreCreateCounting(OS_COUNT_SEMAPHORES_MAX_VALUE, sem_initial_value);
#endif
    if(NULL == OS_count_sem_table[*sem_id].handle)
    {
        xSemaphoreGiveRecursive(OS_count_sem_table_mut);
    	return OS_ERROR;
    }

    strncpy(OS_count_sem_table[*sem_id].name, (char*) sem_name, sizeof(OS_count_sem_table[*sem_id].name));
    OS_count_sem_table[*sem_id].creator = OS_FindCreator();

    OS_count_sem_table[*sem_id].max_value = OS_COUNT_SEMAPHORES_MAX_VALUE;
    OS_count_sem_table[*sem_id].current_value = sem_initial_value;
    OS_count_sem_table[*sem_id].free = FALSE;

    /* Unlock table */
    xSemaphoreGiveRecursive(OS_count_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_CountSemGive(uint32 sem_id)
{
	BaseType_t status;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    status = xSemaphoreGive(OS_count_sem_table[sem_id].handle);
    if(pdTRUE != status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_CountSemTake(uint32 sem_id)
{
	BaseType_t status;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    status = xSemaphoreTake(OS_count_sem_table[sem_id].handle, portMAX_DELAY);
    if(pdTRUE != status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_CountSemTimedWait(uint32 sem_id, uint32 msecs)
{
	BaseType_t status;
	TickType_t xTicksToWait;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    xTicksToWait = OS_Milli2Ticks(msecs);
    status = xSemaphoreTake(OS_count_sem_table[sem_id].handle, xTicksToWait);
    if(pdTRUE != status)
    {
    	return OS_SEM_FAILURE;
    }

    return OS_SUCCESS;
}



int32 OS_CountSemDelete(uint32 sem_id)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check to see if this sem_id is valid */
    if (sem_id >= OS_MAX_COUNT_SEMAPHORES || OS_count_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /* Lock table */
    xSemaphoreTakeRecursive(OS_count_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    vSemaphoreDelete(OS_count_sem_table[sem_id].handle);

    /* Remove the Id from the table, and its name, so that it cannot be found again */
    OS_count_sem_table[sem_id].free = TRUE;
    strcpy(OS_count_sem_table[sem_id].name , "");
    OS_count_sem_table[sem_id].creator = UNINITIALIZED;
    OS_count_sem_table[sem_id].max_value = 0;
    OS_count_sem_table[sem_id].current_value = 0;

    /* Unlock table */
    xSemaphoreGiveRecursive(OS_count_sem_table_mut);

    return OS_SUCCESS;

}



int32 OS_CountSemGetIdByName(uint32 *sem_id, const char *sem_name)
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

    xSemaphoreTakeRecursive(OS_count_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);
    for (i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
        if (OS_count_sem_table[i].free != TRUE &&
                (strcmp (OS_count_sem_table[i].name , (char*) sem_name) == 0))
        {
            *sem_id = i;
            xSemaphoreGiveRecursive(OS_count_sem_table_mut);
            return OS_SUCCESS;
        }
    }
    xSemaphoreGiveRecursive(OS_count_sem_table_mut);

    /*
    ** The name was not found in the table,
    ** or it was, and the sem_id isn't valid anymore
    */
    return OS_ERR_NAME_NOT_FOUND;
}



int32 OS_CountSemGetInfo(uint32 sem_id, OS_count_sem_prop_t *count_prop)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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
    xSemaphoreTakeRecursive(OS_count_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /* put the info into the stucture */
    count_prop->value   = OS_count_sem_table[sem_id].current_value;
    count_prop->creator = OS_count_sem_table[sem_id].creator;
    strcpy(count_prop-> name, OS_count_sem_table[sem_id].name);

    /*
    ** Unlock
    */
    xSemaphoreGiveRecursive(OS_count_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_MutSemCreate(uint32 *sem_id, const char *sem_name, uint32 options)
{
    uint32 possible_semid;
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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

    xSemaphoreTakeRecursive(OS_mut_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    for (possible_semid = 0; possible_semid < OS_MAX_MUTEXES; possible_semid++)
    {
        if (OS_mut_sem_table[possible_semid].free == TRUE)
        {
            break;
        }
    }

    if( (possible_semid == OS_MAX_MUTEXES) ||
        (OS_mut_sem_table[possible_semid].free != TRUE) )
    {
        xSemaphoreGiveRecursive(OS_mut_sem_table_mut);
        return OS_ERR_NO_FREE_IDS;
    }

    /* Check to see if the name is already taken */
    for (i = 0; i < OS_MAX_MUTEXES; i++)
    {
        if ((OS_mut_sem_table[i].free == FALSE) &&
                strcmp ((char*) sem_name, OS_mut_sem_table[i].name) == 0)
        {
            xSemaphoreGiveRecursive(OS_mut_sem_table_mut);
            return OS_ERR_NAME_TAKEN;
        }
    }

    /* Set the free flag to false to make sure no other task grabs it */
    OS_mut_sem_table[possible_semid].free = FALSE;

#if configSUPPORT_STATIC_ALLOCATION
    OS_mut_sem_table[possible_semid].handle = xSemaphoreCreateRecursiveMutexStatic(&OS_mut_sem_table[possible_semid].pxMutexBuffer);
#else
    OS_mut_sem_table[possible_semid].handle = xSemaphoreCreateRecursiveMutex();
#endif
    if(NULL == OS_mut_sem_table[possible_semid].handle)
    {
        xSemaphoreGiveRecursive(OS_mut_sem_table_mut);
        return OS_SEM_FAILURE;
    }

    /*
    ** Mark mutex as initialized
    */
    *sem_id = possible_semid;

    strcpy(OS_mut_sem_table[*sem_id].name, (char*) sem_name);
    OS_mut_sem_table[*sem_id].free = FALSE;
    OS_mut_sem_table[*sem_id].creator = OS_FindCreator();

    xSemaphoreGiveRecursive(OS_mut_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_MutSemGive(uint32 sem_id)
{
    uint32 ret_val;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    /*
    ** Unlock the mutex
    */
    if(xSemaphoreGiveRecursive(OS_mut_sem_table[sem_id].handle) != pdTRUE)
    {
        ret_val = OS_SEM_FAILURE ;
    }
    else
    {
        ret_val = OS_SUCCESS ;
    }

    return ret_val;
}



int32 OS_MutSemTake(uint32 sem_id)
{
    uint32 ret_val;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    if(xSemaphoreTakeRecursive(OS_mut_sem_table[sem_id].handle, portMAX_DELAY) != pdTRUE)
    {
        ret_val = OS_SEM_FAILURE;
    }
    else
    {
        ret_val = OS_SUCCESS;
    }

    return ret_val;
}



int32 OS_MutSemDelete(uint32 sem_id)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
    	return OS_ERROR;
    }

    /* Check Parameters */
    if(sem_id >= OS_MAX_MUTEXES || OS_mut_sem_table[sem_id].free == TRUE)
    {
        return OS_ERR_INVALID_ID;
    }

    xSemaphoreTakeRecursive(OS_mut_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    /*
    ** Delete the mutex
    */
    vSemaphoreDelete(OS_mut_sem_table[sem_id].handle);
    OS_mut_sem_table[sem_id].free = TRUE;
    strcpy(OS_mut_sem_table[sem_id].name , "");
    OS_mut_sem_table[sem_id].creator = UNINITIALIZED;

    xSemaphoreGiveRecursive(OS_mut_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_MutSemGetIdByName(uint32 *sem_id, const char *sem_name)
{
    uint32 i;

    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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

    xSemaphoreTakeRecursive(OS_mut_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    for (i = 0; i < OS_MAX_MUTEXES; i++)
    {
        if ((OS_mut_sem_table[i].free != TRUE) &&
           (strcmp (OS_mut_sem_table[i].name, (char*) sem_name) == 0) )
        {
            *sem_id = i;
            return OS_SUCCESS;
        }
    }

    xSemaphoreGiveRecursive(OS_mut_sem_table_mut);

    /*
    ** The name was not found in the table,
    **  or it was, and the sem_id isn't valid anymore
    */
    return OS_ERR_NAME_NOT_FOUND;
}



int32 OS_MutSemGetInfo(uint32 sem_id, OS_mut_sem_prop_t *mut_prop)
{
    /* Ensure the OSAL API is initialized first. */
    if(OS_API_Initialized != OS_API_INITIALIZED)
    {
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

    xSemaphoreTakeRecursive(OS_mut_sem_table_mut, OS_INTERNAL_MUTEX_TIMEOUT);

    mut_prop->creator = OS_mut_sem_table[sem_id].creator;
    strcpy(mut_prop->name, OS_mut_sem_table[sem_id].name);

    xSemaphoreGiveRecursive(OS_mut_sem_table_mut);

    return OS_SUCCESS;
}



int32 OS_Milli2Ticks(uint32 milli_seconds)
{
	int32 ticks;

	ticks = pdMS_TO_TICKS(milli_seconds);

	return ticks;
}



int32 OS_Tick2Micros(void)
{
	int32 micros;

	micros = (int32)((int32)1000000 / (int32)configTICK_RATE_HZ);

	return micros;
}



int32 OS_GetLocalTime(OS_time_t *time_struct)
{
    TickType_t ticks;
    uint32     microsPerTick = OS_Tick2Micros();
    uint32     microsTotal;

    if (time_struct == NULL)
    {
        return OS_INVALID_POINTER;
    }

    ticks = xTaskGetTickCount() + OS_TICKS_OFFSET;

    microsTotal = microsPerTick * (uint32)ticks;
    time_struct->seconds = ((microsTotal) / (uint32)1000000);
    time_struct->microsecs = microsTotal - (time_struct->seconds * 1000000);

    return OS_SUCCESS;
}



int32 OS_SetLocalTime(OS_time_t *time_struct)
{
    TickType_t ticksNow;
    TickType_t ticksTarget;
    uint32     microsPerTick = OS_Tick2Micros();
    uint32     microsTotal;

    ticksNow = xTaskGetTickCount();

    microsTotal = time_struct->seconds * (uint32)1000000;
    microsTotal += time_struct->microsecs;

    ticksTarget = (uint32)((uint32)microsTotal / (uint32)microsPerTick);

    OS_TICKS_OFFSET = ticksTarget - ticksNow;

	return OS_SUCCESS;
}



int32 OS_ExcAttachHandler(uint32 ExceptionNumber,
                          void (*ExceptionHandler)(uint32, const void *,uint32),
                          int32 parameter)
{
	return OS_ERROR;
}



int32 OS_ExcEnable(int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_ExcDisable(int32 ExceptionNumber)
{
	return OS_ERROR;
}



/*
** Floating Point Unit API
*/

int32 OS_FPUExcAttachHandler(uint32 ExceptionNumber, void * ExceptionHandler ,
                             int32 parameter)
{
	return OS_ERROR;
}



int32 OS_FPUExcEnable(int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_FPUExcDisable(int32 ExceptionNumber)
{
	return OS_ERROR;
}



int32 OS_FPUExcSetMask(uint32 mask)
{
	return OS_ERROR;
}



int32 OS_FPUExcGetMask(uint32 *mask)
{
	return OS_ERROR;
}



/*
** Interrupt API
*/
int32 OS_IntAttachHandler(uint32 InterruptNumber, osal_task_entry InterruptHandler, int32 parameter)
{
    if (InterruptHandler == NULL)
    {
        return OS_INVALID_POINTER;
    }

    return(OS_ERR_NOT_IMPLEMENTED);
}



int32 OS_IntUnlock(int32 IntLevel)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_IntLock(void)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_IntEnable(int32 Level)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_IntDisable(int32 Level)
{
	return OS_ERROR;
}



int32 OS_IntSetMask(uint32 mask)
{
	return OS_ERROR;
}



int32 OS_IntGetMask(uint32 *mask)
{
	return OS_ERROR;
}



int32 OS_IntAck(int32 InterruptNumber)
{
	return OS_ERROR;
}



/*
** Shared memory API
*/

int32 OS_ShMemInit(void)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ShMemCreate(uint32 *Id, uint32 NBytes, const char* SegName)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ShMemSemTake(uint32 Id)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ShMemSemGive(uint32 Id)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ShMemAttach(cpuaddr * Address, uint32 Id)
{
	return OS_ERROR;
}



int32 OS_ShMemGetIdByName(uint32 *ShMemId, const char *SegName )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



/*
** Heap API
*/

int32 OS_HeapGetInfo(OS_heap_prop_t *heap_prop)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_GetErrorName(int32 error_num, os_err_name_t* err_name)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}


char OS_PrintBuffer[1024];

void OS_printf( const char *Spec, ...)
{
	va_list ptr;

    va_start(ptr, Spec);
    vsnprintf(OS_PrintBuffer, sizeof(OS_PrintBuffer), Spec, ptr);
    va_end(ptr);

	xil_printf("%s\r", OS_PrintBuffer);
}



void OS_printf_disable(void)
{
    OS_printf("%s\n", __FUNCTION__);

}



void OS_printf_enable(void)
{
    OS_printf("%s\n", __FUNCTION__);

}



void OS_ApplicationExit(int32 Status)
{
    OS_printf("%s\n", __FUNCTION__);

}



UBaseType_t OS_PriorityRemap(uint32 InputPri)
{
    int OutputPri;
    int pmax = configMAX_PRIORITIES - 1;
    int pmin = 0;
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
	TaskHandle_t  xHandle;
    uint32 i = 0;

    xHandle = xTaskGetCurrentTaskHandle();

    for (i = 0; i < OS_MAX_TASKS; i++)
    {
        if (xHandle == OS_task_table[i].handle)
        {
            break;
        }
    }

    return i;
}



void OS_ApplicationShutdown(uint8 flag)
{
   exit(1);
}
