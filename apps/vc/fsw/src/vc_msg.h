#include "cfe.h"

/* Example command packet command codes */
#define VC_NOOP_CC            0  /* no-op command */
#define VC_RESET_CC           1  /* reset counters */
#define VC_HELLOWORLD_CC      2  /* hello world command */

/* Type definition (generic "no arguments" command) */
typedef struct
{
    uint8                 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} VC_NoArgsCmd_t;


/* Type definition (VC housekeeping) */
typedef struct
{
    uint8                 TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /* Command interface counters */
    uint8                 CmdCounter;
    uint8                 ErrCounter;
} VC_HkPacket_t;
