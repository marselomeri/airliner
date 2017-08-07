#include "cfe.h"
#include "vc_platform_cfg.h"

/* Command packet command codes */
#define VC_NOOP_CC            0  /* no-op command */
#define VC_RESET_CC           1  /* reset counters */
#define VC_STARTSTREAMING_CC  2  /* start streaming command */
#define VC_STOPSTREAMING_CC   3  /* stop streaming command */


/**
 * @brief No Arguments Command
 */
typedef struct
{
    uint8                 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} VC_NoArgsCmd_t;


/**
 * @brief Housekeeping packet structure
 */
typedef struct
{
    uint8                 TlmHeader[CFE_SB_TLM_HDR_SIZE];
    /* Command interface counters */
    uint8                 CmdCounter;
    uint8                 ErrCounter;
    uint8                 State;
} VC_HkPacket_t;


/**
 * @brief Start Streaming Command
 */
typedef struct 
{
    uint8                  CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint16                 Port;
    char                   Address[VC_ADDRESS_LENGTH];
} VC_StartStreamCmd_t;

