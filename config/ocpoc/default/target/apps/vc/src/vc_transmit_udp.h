
#ifndef VC_TRANSMIT_UDP_H
#define VC_TRANSMIT_UDP_H

/************************************************************************
** Includes
*************************************************************************/

#include "cfe.h"
#include "vc_transmit.h"
#include "vc_perfids.h"
#include <arpa/inet.h>
#include "vc_app.h"

/************************************************************************
** Structure Declarations
*************************************************************************/

/**
 * Channel modes
 */
typedef enum
{
    /*! Channel state unused  */
    VC_CHANNEL_UNUSED       = 0,
    /*! Channel state disabled */
    VC_CHANNEL_DISABLED     = 1,
    /*! Channel state enabled */
    VC_CHANNEL_ENABLED      = 2
} VC_ChannelMode_t;


/**
 * Transmit struct handle for user defined source and/or destination
 * configuration information and initialized resource reference.
 */
typedef struct
{
    /*! Channel mode */
    VC_ChannelMode_t    Mode;
    /*! Channel identifier */
    uint8               ChannelID;
    /*! Destination port */
    uint16              DestPort;
    /*! Local port to bind */
    uint16              MyPort;
    /*! Destination IP address */
    char                DestIP[INET_ADDRSTRLEN];
    /*! Local IP address to allow interface choices */
    char                MyIP[INET_ADDRSTRLEN];
    /*! Socket file descriptor for the channel */
    int                 SocketFd;
} VC_Transmit_Handle_t;

/**
 * Transmit handles
 */
typedef struct
{
    VC_Transmit_Handle_t Channel[VC_MAX_OUTPUT_CHANNELS];
} VC_AppCustomData_t;

/************************************************************************
** External Global Variables
*************************************************************************/

extern VC_AppCustomData_t VC_AppCustomData;

/************************************************************************
** Function Prototypes
*************************************************************************/

/**
 * @brief Custom function to initialize custom transmit data structure.
 * @return CFE_SUCCESS
 */
int32 VC_CustomTransmit_InitData(void);


/**
 * @brief Initialize all enabled transmit resources
 * @return 0 for success -1 for failure
 */
int32 VC_Init_CustomTransmitters(void);


/**
 * @brief Initialize a transmit channel
 * @return 0 for success -1 for failure
 */
int32 VC_EnableChannel(uint8 ChannelID);


/**
 * @brief Cleanup all transmit resources 
 * @return 0 for success -1 for failure
 */
int32 VC_CleanupCustom(void);


/**
 * @brief Disable a transmit channel
 * @param ChannelID the channel to disable
 * @return 0 for success -1 for failure
 */
int32 VC_DisableChannel(uint8 ChannelID);


#endif
