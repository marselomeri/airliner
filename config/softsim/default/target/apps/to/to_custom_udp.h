
#ifndef TO_CUSTOM_H
#define TO_CUSTOM_H

/************************************************************************
** Includes
*************************************************************************/
#include "to_app.h"
#include "to_custom.h"
#include <arpa/inet.h>

/************************************************************************
** Local Defines
*************************************************************************/
#define TO_CUSTOM_RETURN_CODE_NULL_POINTER      (-1)
#define TO_CUSTOM_RETURN_CODE_MESSAGE_TOO_BIG   (-2)

/* TODO:  Add Doxygen markup. */
#define TO_ENABLE_CHANNEL_CC                    (10)
#define TO_DISABLE_CHANNEL_CC                   (11)

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8  ChannelID;
    char   DestinationAddress[INET_ADDRSTRLEN];
    uint16 DestinationPort;
} TO_EnableChannelCmd_t;

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8  ChannelID;
} TO_DisableChannelCmd_t;

typedef enum {
    /* TODO:  Add Doxygen markup. */
    TO_TLMOUTSOCKET_ERR_EID = TO_EVT_CNT,
    TO_TLMOUTENA_INF_EID,
    TO_TLMOUTENA_ERR_EID,
    TO_TLMOUTSTOP_ERR_EID,
    TO_CUSTOM_EVT_CNT
} TO_CustomEventIds_t;

typedef enum
{
    TO_CHANNEL_UNUSED       = 0,
    TO_CHANNEL_DISABLED     = 1,
    TO_CHANNEL_ENABLED      = 2
} TO_TLM_ChannelMode_t;

typedef struct
{
    TO_TLM_ChannelMode_t            Mode;
    char                            IP[INET_ADDRSTRLEN];
    uint16                          DstPort;
    uint8                           Priority;
    CFE_ES_ChildTaskMainFuncPtr_t   ListenerTask;
    int                             Socket;
    uint32                          ChildTaskID;
} TO_TlmChannels_t;

typedef struct
{
    TO_TlmChannels_t                Channel[TO_MAX_CHANNELS];
} TO_AppCustomData_t;

/************************************************************************
** External Global Variables
*************************************************************************/

extern TO_AppData_t TO_AppData;

/************************************************************************
** Local Function Definitions
*************************************************************************/



int32 TO_OutputChannel_Send(uint32 ChannelID, const char* Buffer, uint32 Size);

int32 TO_OutputChannel_Enable(uint8 ChannelID, const char *DestinationAddress, uint16 DestinationPort);
int32 TO_OutputChannel_Disable(uint8 ChannelID);
void  TO_OutputChannel_GroundChannelTask(void);
void  TO_OutputChannel_OnboardChannelTask(void);
void  TO_OutputChannel_ChannelHandler(uint32 ChannelIndex);

int32 TO_OutputChannel_CustomBuildupAll(uint32 index);
int32 TO_OutputChannel_CustomTeardownAll(uint32 index);

#endif
