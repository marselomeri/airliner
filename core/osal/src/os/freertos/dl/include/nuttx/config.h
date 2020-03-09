#include <stdbool.h>

#define FAR
#define NEAR
#define DSEG
#define CODE

#define OK                                (0)



/* #define CONFIG_ARCH_ADDRENV                      */
/* #define CONFIG_ARCH_HEAP_VBASE                   */
/* #define CONFIG_ARCH_DCACHE                       */
/* #define CONFIG_ARCH_ICACHE                       */
/* #define CONFIG_ARCH_STACK_DYNAMIC                */
#define CONFIG_BINFMT_CONSTRUCTORS
/* #define CONFIG_BUILD_KERNEL                      */
/* #define CONFIG_CXX_EXCEPTION                     */
/* #define CONFIG_DEBUG_BINFMT                      */
/* #define CONFIG_DEBUG_INFO                        */
#define CONFIG_ELF_ALIGN_LOG2              (4)
#define CONFIG_ELF_BUFFERINCR              (32)
#define CONFIG_ELF_BUFFERSIZE              (32)
/* #define CONFIG_ELF_DUMPBUFFER                    */
/* #define CONFIG_ELF_EXIDX_SECTNAME                */
#define CONFIG_ELF_RELOCATION_BUFFERCOUNT  (256)
#define CONFIG_ELF_STACKSIZE               (2048)
#define CONFIG_ELF_SYMBOL_CACHECOUNT       (256)
#define CONFIG_LIBC_ARCH_ELF
#define CONFIG_SYMTAB_ORDEREDBYNAME



#define DEBUGASSERT(f) assert(f)


#define get_errno(e) errno

