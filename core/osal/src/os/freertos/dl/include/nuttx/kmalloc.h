#include <stdlib.h>


#define kumm_malloc(s)          pvPortMalloc(s)
#define kmm_malloc(s)           pvPortMalloc(s)
#define kumm_free(s)            vPortFree(s)
#define kmm_free(s)             vPortFree(s)
#define kumm_realloc(s, b)      realloc(s, b)
#define kmm_realloc(s, b)       realloc(s, b)
