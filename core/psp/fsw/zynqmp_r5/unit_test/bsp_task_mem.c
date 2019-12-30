
#include <FreeRTOS.h>
#include <ff.h>
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "osapi.h"
#include "common_types.h"
#include "xil_printf.h"
#include "osconfig.h"

#if configSUPPORT_STATIC_ALLOCATION
#define IDLE_TASK_SIZE (16536)
/* static memory allocation for the IDLE task */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}


/* If static allocation is supported then the application must provide the
   following callback function - which enables the application to optionally
   provide the memory that will be used by the timer task as the task's stack
   and TCB. */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = &xTimerStack[0];
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif



char BSP_PrintBuffer[1024];

void __wrap_printf(const char *Spec, ...)
{
	va_list ptr;

    va_start(ptr, Spec);
    vsnprintf(BSP_PrintBuffer, sizeof(BSP_PrintBuffer), Spec, ptr);
    va_end(ptr);

	xil_printf("%s\r", BSP_PrintBuffer);
}
