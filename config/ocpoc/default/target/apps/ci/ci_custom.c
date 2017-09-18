
#include "ci_custom.h"
#include "ci_platform_cfg.h"
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include "ci_events.h"

#define CI_CUSTOM_RETURN_CODE_NULL_POINTER      (-1)


typedef struct
{
	int32  Socket;
	uint32 Port;
} CI_AppCustomData_t;

CI_AppCustomData_t CI_AppCustomData = {0, 5010};



int32 CI_InitCustom(void)
{
    int32 Status = 0;
    int reuseaddr = 1;
	struct sockaddr_in address;

    if((CI_AppCustomData.Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
    	CFE_EVS_SendEvent(CI_SOCKET_ERR_EID, CFE_EVS_ERROR,
    		   "Socket errno: %i", errno);
    		Status = -1;
    		goto end_of_function;
    }

    setsockopt(CI_AppCustomData.Socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));

    // zero out the structure
    memset((char *) &address, 0, sizeof(address));

    address.sin_family      = AF_INET;
    address.sin_port        = htons(CI_AppCustomData.Port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( (bind(CI_AppCustomData.Socket, (struct sockaddr *) &address, sizeof(address)) < 0) )
	{
		CFE_EVS_SendEvent(CI_SOCKET_ERR_EID, CFE_EVS_ERROR,"Bind socket failed = %d", errno);
		Status = -1;
		goto end_of_function;
	}

	CFE_EVS_SendEvent(CI_ENA_INF_EID, CFE_EVS_INFORMATION,
					  "UDP command input enabled on port %u.",
					  CI_AppCustomData.Port);

end_of_function:
    return Status;

}


int32 CI_ReadMessage(char* buffer, uint32* size)
{
    struct sockaddr_in si_other;
    int recv_len = 0;
    int slen = sizeof(si_other);

    recv_len = recv(CI_AppCustomData.Socket, buffer, *size, 0);

    *size = recv_len;

    return CFE_SUCCESS;
}


int32 CI_CleanupCustom(void)
{
    return close(CI_AppCustomData.Socket);
}

