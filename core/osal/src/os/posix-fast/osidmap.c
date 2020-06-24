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
#include "common_types.h"
#include "osapi.h"
#include "osapi_private.h"



#ifndef OS_MAX_FILE_SYSTEMS
#define OS_MAX_FILE_SYSTEMS         NUM_TABLE_ENTRIES
#endif



extern OS_task_record_t        OS_task_table      [OS_MAX_TASKS];
extern OS_queue_record_t       OS_queue_table     [OS_MAX_QUEUES];
extern OS_bin_sem_record_t     OS_bin_sem_table   [OS_MAX_BIN_SEMAPHORES];
extern OS_count_sem_record_t   OS_count_sem_table [OS_MAX_COUNT_SEMAPHORES];
extern OS_mut_sem_record_t     OS_mut_sem_table   [OS_MAX_MUTEXES];
extern OS_timer_record_t       OS_timer_table     [OS_MAX_TIMERS];
extern OS_open_file_record_t   OS_open_file_table [OS_MAX_NUM_OPEN_FILES];
extern OS_open_dir_record_t    OS_open_dir_table  [OS_MAX_NUM_OPEN_DIRS];
extern OS_module_record_priv_t OS_module_table    [OS_MAX_MODULES];

extern pthread_mutex_t OS_task_table_mut;
extern pthread_mutex_t OS_queue_table_mut;
extern pthread_mutex_t OS_bin_sem_table_mut;
extern pthread_mutex_t OS_mut_sem_table_mut;
extern pthread_mutex_t OS_count_sem_table_mut;
extern pthread_mutex_t OS_object_count_mut;
extern pthread_mutex_t OS_open_file_table_mut;
extern pthread_mutex_t OS_open_dir_table_mut;
extern pthread_mutex_t OS_module_table_mut;


/* Object Counter */
uint32 OS_ObjectCount;



void  OS_IDMapInit(void)
{
	OS_ObjectCount = 1;
}



bool OS_IsIDValid(uint32 object_id)
{
	bool valid = true;
	uint32 objectType = OS_IdentifyObject(object_id);
	uint32 index = 0x0000ffff & object_id;

    switch(objectType)
    {
        /* Fallthru */
        case OS_OBJECT_TYPE_UNDEFINED:
        {
        	valid = false;
        	break;
        }

        case OS_OBJECT_TYPE_OS_TASK:
        {
            if(index >= OS_MAX_TASKS ||
               OS_task_table[index].free == true ||
			   OS_task_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_QUEUE:
        {
            if(index >= OS_MAX_QUEUES ||
               OS_queue_table[index].free == true ||
			   OS_queue_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_COUNTSEM:
        {
            if(index >= OS_MAX_COUNT_SEMAPHORES ||
               OS_count_sem_table[index].free == true ||
			   OS_count_sem_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_BINSEM:
        {
            if(index >= OS_MAX_BIN_SEMAPHORES ||
               OS_bin_sem_table[index].free == true ||
			   OS_bin_sem_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_MUTEX:
        {
            if(index >= OS_MAX_MUTEXES ||
               OS_mut_sem_table[index].free == true ||
			   OS_mut_sem_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_STREAM:
        {
            if(index >= OS_MAX_NUM_OPEN_FILES ||
               OS_open_file_table[index].free == true ||
			   OS_open_file_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_DIR:
        {
            if(index >= OS_MAX_NUM_OPEN_DIRS ||
               OS_open_dir_table[index].free == true ||
			   OS_open_dir_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_TIMEBASE:
        {
        	valid = false;
        	break;
        }

        case OS_OBJECT_TYPE_OS_TIMECB:
        {
            if(index >= OS_MAX_TIMERS ||
               OS_timer_table[index].free == true ||
			   OS_timer_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_MODULE:
        {
            if(index >= OS_MAX_MODULES ||
               OS_module_table[index].free == true ||
			   OS_module_table[index].ID != object_id)
            {
            	valid = false;
            }
        	break;
        }

        case OS_OBJECT_TYPE_OS_FILESYS:
        {
        	valid = false;
        	break;
        }

        case OS_OBJECT_TYPE_OS_CONSOLE:
        {
        	valid = false;
        	break;
        }

        case OS_OBJECT_TYPE_USER:
        {
        	valid = true;
        	break;
        }

        default:
        {
        	valid = false;
        	break;
        }
    }

    return valid;
}



int32 OS_ConvertToArrayIndex(uint32 object_id, uint32 *ArrayIndex)
{
    int32  rc = OS_SUCCESS;
    uint32 offset = 0;
    uint32 objectType = OS_IdentifyObject(object_id);

	if(ArrayIndex == 0)
	{
		rc = OS_INVALID_POINTER;
	}
	else
	{
		bool isValid = OS_IsIDValid(object_id);

		if(isValid == false)
		{
			rc = OS_ERR_INVALID_ID;
		}
		else
		{
		    *ArrayIndex = 0x0000ffff & object_id;
			rc = OS_SUCCESS;
		}
	}

	return rc;
} /* end OS_ConvertToArrayIndex */



uint32 OS_IdentifyObject(uint32 object_id)
{
	return ((0xf8000000) & object_id) >> 27;
}



void OS_ForEachObject(uint32 creator_id, OS_ArgCallback_t callback_ptr, void *callback_arg)
{
	uint32 i = 0;

    for(i = 0; i < OS_MAX_TASKS; i++)
    {
    	if(OS_task_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_task_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_QUEUES; i++)
    {
    	if(OS_queue_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_queue_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_BIN_SEMAPHORES; i++)
    {
    	if(OS_bin_sem_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_bin_sem_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_COUNT_SEMAPHORES; i++)
    {
    	if(OS_count_sem_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_count_sem_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_MUTEXES; i++)
    {
    	if(OS_mut_sem_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_mut_sem_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_TIMERS; i++)
    {
    	if(OS_timer_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_timer_table[i].ID, callback_arg);
    	}
	}

    for(i = 0; i < OS_MAX_NUM_OPEN_DIRS; i++)
    {
    	if(OS_open_dir_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_open_dir_table[i].ID, callback_arg);
    	}
	}


    for(i = 0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
    	if(OS_open_file_table[i].creator == creator_id)
    	{
            (*callback_ptr)(OS_open_file_table[i].ID, callback_arg);
    	}
	}
}



int32 OS_AllocateID(uint32 objectType, uint16 localIndex, uint32 *newID)
{
    sigset_t previous;
    sigset_t mask;
    int32    rc = OS_SUCCESS;

	if(newID == 0)
	{
		return OS_INVALID_POINTER;
	}

	switch(objectType)
	{
	    /* Fallthru */
        case OS_OBJECT_TYPE_UNDEFINED:
        case OS_OBJECT_TYPE_OS_TASK:
        case OS_OBJECT_TYPE_OS_QUEUE:
        case OS_OBJECT_TYPE_OS_COUNTSEM:
        case OS_OBJECT_TYPE_OS_BINSEM:
        case OS_OBJECT_TYPE_OS_MUTEX:
        case OS_OBJECT_TYPE_OS_STREAM:
        case OS_OBJECT_TYPE_OS_DIR:
        case OS_OBJECT_TYPE_OS_TIMEBASE:
        case OS_OBJECT_TYPE_OS_TIMECB:
        case OS_OBJECT_TYPE_OS_MODULE:
        case OS_OBJECT_TYPE_OS_FILESYS:
        case OS_OBJECT_TYPE_OS_CONSOLE:
        case OS_OBJECT_TYPE_USER:
        {
        	/* Increment the object count, and pass it back as reference
        	 * via the count argument.
        	 */
            OS_InterruptSafeLock(&OS_object_count_mut, &mask, &previous);

            *newID = (objectType << 27) | (OS_ObjectCount << 16) | localIndex;

            OS_ObjectCount++;
            if(OS_ObjectCount > OS_MAX_OBJECT_COUNT)
            {
            	OS_ObjectCount = 1;
            }

            OS_InterruptSafeUnlock(&OS_object_count_mut, &previous);

            rc = OS_SUCCESS;
            break;
        }

        default:
        {
        	rc =  OS_ERR_INCORRECT_OBJ_TYPE;
        }
	}

	return rc;
}
