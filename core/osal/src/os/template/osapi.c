#include "osapi.h"
#include "common_types.h"
#include "osconfig.h"



int32 OS_API_InitEx(OS_RunTimeModeEnum_t Mode)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_API_Init(void)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



void OS_IdleLoop(void)
{
    OS_printf("%s\n", __FUNCTION__);
}



void OS_DeleteAllObjects(void)
{
    OS_printf("%s\n", __FUNCTION__);
}



int32 OS_TaskCreate(uint32 *task_id, const char *task_name,
                    osal_task_entry function_pointer,
                    uint32 *stack_pointer,
                    uint32 stack_size,
                    uint32 priority, uint32 flags)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_TaskDelete(uint32 task_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



void OS_TaskExit(void)
{
    OS_printf("%s\n", __FUNCTION__);

}



int32 OS_TaskInstallDeleteHandler(osal_task_entry function_pointer)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_TaskDelay(uint32 millisecond)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_TaskSetPriority(uint32 task_id, uint32 new_priority)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_TaskRegister(void)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_SUCCESS;
}



uint32 OS_TaskGetId(void)
{
    OS_printf("%s\n", __FUNCTION__);

    return 0;
}



int32 OS_TaskGetIdByName(uint32 *task_id, const char *task_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_TaskGetInfo(uint32 task_id, OS_task_prop_t *task_prop)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueueCreate(uint32 *queue_id, const char *queue_name,
                     uint32 queue_depth, uint32 data_size, uint32 flags)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueueDelete(uint32 queue_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueueGet(uint32 queue_id, void *data, uint32 size,
                  uint32 *size_copied, int32 timeout)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueuePut(uint32 queue_id, const void *data, uint32 size,
                  uint32 flags)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueueGetIdByName(uint32 *queue_id, const char *queue_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_QueueGetInfo(uint32 queue_id, OS_queue_prop_t *queue_prop)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemCreate(uint32 *sem_id, const char *sem_name,
                      uint32 sem_initial_value, uint32 options)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemFlush(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_BinSemGive(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemTake(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemTimedWait(uint32 sem_id, uint32 msecs)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemDelete(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemGetIdByName(uint32 *sem_id, const char *sem_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_BinSemGetInfo(uint32 sem_id, OS_bin_sem_prop_t *bin_prop)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemCreate(uint32 *sem_id, const char *sem_name,
                        uint32 sem_initial_value, uint32 options)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemGive(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemTake(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemTimedWait(uint32 sem_id, uint32 msecs)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemDelete(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemGetIdByName(uint32 *sem_id, const char *sem_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_CountSemGetInfo(uint32 sem_id, OS_count_sem_prop_t *count_prop)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemCreate(uint32 *sem_id, const char *sem_name, uint32 options)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemGive(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemTake(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemDelete(uint32 sem_id)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemGetIdByName(uint32 *sem_id, const char *sem_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_MutSemGetInfo(uint32 sem_id, OS_mut_sem_prop_t *mut_prop)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_Milli2Ticks(uint32 milli_seconds)
{
    OS_printf("%s\n", __FUNCTION__);
}



int32 OS_Tick2Micros(void)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32  OS_GetLocalTime(OS_time_t *time_struct)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32  OS_SetLocalTime(OS_time_t *time_struct)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_ERROR;
}



int32 OS_ExcAttachHandler(uint32 ExceptionNumber,
                          void (*ExceptionHandler)(uint32, const void *,uint32),
                          int32 parameter)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ExcEnable(int32 ExceptionNumber)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ExcDisable(int32 ExceptionNumber)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



/*
** Floating Point Unit API
*/

int32 OS_FPUExcAttachHandler(uint32 ExceptionNumber, void * ExceptionHandler ,
                             int32 parameter)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_FPUExcEnable(int32 ExceptionNumber)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_FPUExcDisable(int32 ExceptionNumber)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_FPUExcSetMask(uint32 mask)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_FPUExcGetMask(uint32 *mask)
{
    OS_printf("%s\n", __FUNCTION__);

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



void OS_ApplicationShutdown(uint8 flag)
{
   exit(1);
}
