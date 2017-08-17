/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "vc_transmit_udp.h"
#include "cfe.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/


/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

/**
 * Global data structure for custom device IO layer
 */
VC_AppCustomData_t VC_AppCustomData = {
    {
        { 
          .Mode = VC_CHANNEL_ENABLED, \
          .ChannelID = 0, \
          .DestPort = VC_DESTINATION_PORT, \
          .MyPort = VC_SOURCE_PORT, \
          .DestIP = VC_DESTINATION_IP, \
          .MyIP = VC_SOURCE_IP, \
          .SocketFd = 0 \
        }
    }
};


int32 VC_EnableChannel(uint8 ChannelID)
{
    int32 returnCode = 0;
    uint32 i = 0;
    struct sockaddr_in servaddr;
    int status;
    int reuseaddr=1;

    if((VC_AppCustomData.Channel[ChannelID].Mode == VC_CHANNEL_ENABLED) &&
        (VC_AppCustomData.Channel[ChannelID].SocketFd != 0))
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC UDP for channel %u already enabled.", (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    if(ChannelID >= VC_MAX_OUTPUT_CHANNELS)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC ChannelID (%u) invalid.", (unsigned int)ChannelID);
        returnCode = -1;
        goto end_of_function;
    }

    if((VC_AppCustomData.Channel[ChannelID].SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        VC_AppCustomData.Channel[ChannelID].Mode = VC_CHANNEL_DISABLED;
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC socket errno: %i on channel %u", errno, (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }

    /* Set the Reuse Address flag.  If we don't set this flag, the socket will
     * lock the port on termination and the kernel won't unlock it until it
     * times out after a minute or so.
     */
    setsockopt(VC_AppCustomData.Channel[ChannelID].SocketFd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    /* Set the input arguments to the socket bind.
     */
     
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(VC_AppCustomData.Channel[ChannelID].MyPort);
    
    if (inet_aton(VC_AppCustomData.Channel[ChannelID].MyIP, &servaddr.sin_addr) == 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC inet_aton errno: %i on channel %u", errno, (unsigned int)i);
        returnCode = -1;
        goto end_of_function;
    }
    
    status = bind(VC_AppCustomData.Channel[ChannelID].SocketFd,
            (struct sockaddr *)&servaddr,sizeof(servaddr));
    if(status < 0)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                        "VC bind errno: %i on channel %u", errno, (unsigned int)i);
        VC_AppCustomData.Channel[ChannelID].Mode = VC_CHANNEL_DISABLED;
        returnCode = -1;
    }

end_of_function:
    return returnCode;
}


int32 VC_Init_CustomTransmitters(void)
{
    uint32 i = 0;
    int32 returnCode = 0;

    for (i=0; i < VC_MAX_OUTPUT_CHANNELS; i++)
    {
        if(VC_AppCustomData.Channel[i].Mode == VC_CHANNEL_ENABLED)
        {
            if(VC_EnableChannel(i))
            {
                returnCode = -1;
                VC_AppCustomData.Channel[i].Mode = VC_CHANNEL_DISABLED;
            }
            else
            {
                CFE_EVS_SendEvent(VC_CHA_INF_EID, CFE_EVS_INFORMATION,
                        "VC UDP output enabled channel %u to %s:%u",
                        (unsigned int)i, VC_AppCustomData.Channel[i].DestIP,
                        (unsigned int)VC_AppCustomData.Channel[i].DestPort);
            }
        }
    }
    return returnCode;
}


int32 VC_DisableChannel(uint8 ChannelID)
{
    int32 returnCode = 0;

    if(VC_AppCustomData.Channel[ChannelID].Mode != VC_CHANNEL_ENABLED)
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                            "UDP VC for channel %u is not enabled.", (unsigned int)ChannelID);
        returnCode = -1;
        goto end_of_function;
    }

    close(VC_AppCustomData.Channel[ChannelID].SocketFd);
    VC_AppCustomData.Channel[ChannelID].SocketFd = 0;

end_of_function:
    return returnCode;
}


int32 VC_CleanupCustom(void)
{
    uint32 i = 0;
    int32 returnCode = 0;
    
    for(i=0; i < VC_MAX_OUTPUT_CHANNELS; i++)
    {
        if(VC_AppCustomData.Channel[i].Mode == VC_CHANNEL_ENABLED)
        {
            if(-1 == VC_DisableChannel(i))
            {
                returnCode = -1;
            }
        }
    }
return returnCode;
}


boolean VC_Transmit_Init(void)
{
    if(-1 == VC_Init_CustomTransmitters())
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC_Transmit_Init Failed");
        return FALSE;
    }
    return TRUE;
}


boolean VC_Transmit_Uninit(void)
{
    if(-1 == VC_CleanupCustom())
    {
        CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR, \
                "VC_Transmit_Uninit Failed");
        return FALSE;
    }
    return TRUE;
}


int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size)
{
    static struct sockaddr_in s_addr;
    int status = 0;
    int32 returnCode = 0;

    bzero((char *) &s_addr, sizeof(s_addr));
    s_addr.sin_family      = AF_INET;

    if(ChannelID < VC_MAX_OUTPUT_CHANNELS)
    {
        VC_Transmit_Handle_t *channel = &VC_AppCustomData.Channel[ChannelID];

        if(channel->Mode == VC_CHANNEL_ENABLED)
        {
            CFE_ES_PerfLogEntry(VC_SOCKET_SEND_PERF_ID);
            /* Send message via UDP socket */
            s_addr.sin_addr.s_addr = inet_addr(channel->DestIP);
            s_addr.sin_port        = htons(channel->DestPort);
            status = sendto(channel->SocketFd, (char *)Buffer, Size, 0,
                                    (struct sockaddr *) &s_addr,
                                    sizeof(s_addr));
            if (status < 0)
            {
                if(errno == 90)
                {
                    CFE_EVS_SendEvent(VC_SOCKET_ERR_EID,CFE_EVS_ERROR,
                                "L%d VC sendto errno %d.  Message too long.  Size=%u", __LINE__, errno, (unsigned int)Size);
                }
                else
                {
                    CFE_EVS_SendEvent(VC_SOCKET_ERR_EID, CFE_EVS_ERROR,
                                "L%d VC sendto errno %d.", __LINE__, errno);
                    channel->Mode = VC_CHANNEL_DISABLED;
                }
                returnCode = -1;
            }
            CFE_ES_PerfLogExit(VC_SOCKET_SEND_PERF_ID);
        }
    }
    return returnCode;
}


boolean VC_Address_Verification(const char *Address)
{
    static struct sockaddr_in s_addr;
    if(0 != inet_aton(Address, &s_addr.sin_addr))
    {
        return TRUE;
    }
    return FALSE;
}


boolean VC_Update_Destination(const char *Address, uint16 Port)
{
    uint32 i = 0;
    
    for (i=0; i < VC_MAX_OUTPUT_CHANNELS; i++)
    {
        if(VC_AppCustomData.Channel[i].Mode == VC_CHANNEL_ENABLED)
        {
            VC_AppCustomData.Channel[i].DestPort = Port;
            
            if(strncpy(VC_AppCustomData.Channel[i].DestIP, Address, sizeof(Address)))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}




