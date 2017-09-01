
#ifndef VC_TRANSMIT_UDP_H
#define VC_TRANSMIT_UDP_H

#include "cfe.h"
#include "vc_transmit.h"
#include "vc_perfids.h"
#include <arpa/inet.h>
#include "vc_app.h"


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

extern VC_AppCustomData_t VC_AppCustomData;

#endif
