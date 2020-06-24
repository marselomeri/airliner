#include "common_types.h"
#include <dirent.h>


#define OS_MAX_OBJECT_COUNT  (0x07ff)


/*tasks */
typedef struct
{
    uint32    ID;
    bool      free;
    pthread_t osId;
    char      name [OS_MAX_API_NAME];
    int       creator;
    uint32    stack_size;
    uint32    priority;
    void     *delete_hook_pointer;
} OS_task_record_t;

/* queues */
typedef struct
{
	uint32	size;
	char buffer[OS_MAX_QUEUE_WIDTH];
} OS_queue_data_t;

typedef struct
{
    uint32          ID;
    bool   			free;
    OS_queue_data_t	qData[OS_MAX_QUEUE_DEPTH];
    uint32 			max_size;
    char   			name [OS_MAX_API_NAME];
    int    			creator;
    pthread_cond_t  cv;
    int32	  		head;
    int32   		tail;
    uint32   		width;
    uint32   		depth;
} OS_queue_record_t;

/* Binary Semaphores */
typedef struct
{
    uint32          ID;
    bool            free;
    pthread_mutex_t osId;
    pthread_cond_t  cv;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
} OS_bin_sem_record_t;

/*Counting Semaphores */
typedef struct
{
    uint32          ID;
    bool            free;
    pthread_mutex_t osId;
    pthread_cond_t  cv;
    char            name [OS_MAX_API_NAME];
    int             creator;
    int             max_value;
    int             current_value;
} OS_count_sem_record_t;

/* Mutexes */
typedef struct
{
    uint32          ID;
    bool            free;
    pthread_mutex_t osId;
    char            name [OS_MAX_API_NAME];
    int             creator;
} OS_mut_sem_record_t;

typedef struct
{
    uint32              ID;
    bool                free;
    char                name[OS_MAX_API_NAME];
    uint32              creator;
    uint32              start_time;
    uint32              interval_time;
    uint32              accuracy;
    OS_TimerCallback_t  callback_ptr;
    uint32              host_timerid;
} OS_timer_record_t;

/* Open file objects */
typedef struct
{
    uint32  ID;
    bool    free;
    int32   OSfd;
    int     creator;
    char    Path[OS_MAX_PATH_LEN];
} OS_open_file_record_t;

/* Open directory objects */
typedef struct
{
    uint32         ID;
    char           Name[OS_MAX_PATH_LEN];
    DIR            *Desc;
    bool           free;
    int            creator;
#ifndef OSAL_OMIT_DEPRECATED
    struct dirent  *entry;
#endif
} OS_open_dir_record_t;

/* Module objects */
typedef struct
{
    uint32             ID;
    char               Name[OS_MAX_PATH_LEN];
    OS_module_prop_t   Module;
    bool               free;
} OS_module_record_priv_t;




void  OS_IDMapInit(void);
int   OS_InterruptSafeLock(pthread_mutex_t *lock, sigset_t *set, sigset_t *previous);
void  OS_InterruptSafeUnlock(pthread_mutex_t *lock, sigset_t *previous);

int32 OS_ModuleTableInit(void);
int32 OS_TimerAPIInit(void);
int32 OS_FS_Init(void);
int32 OS_AllocateID(uint32 objectType, uint16 localIndex, uint32 *newID);
uint32 OS_TaskGetIndex (void);
