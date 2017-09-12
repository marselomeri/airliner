
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
	struct sockaddr_in address;

    if((CI_AppCustomData.Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
    	CFE_EVS_SendEvent(CI_SOCKET_ERR_EID, CFE_EVS_ERROR,
    		   "Socket errno: %i", errno);
    		Status = -1;
    		goto end_of_function;
    }

    bzero((char *) &address, sizeof(address));
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = htonl (INADDR_ANY);
    address.sin_port        = htons(CI_AppCustomData.Port);

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
	*size = recv(CI_AppCustomData.Socket,
					   (char *)buffer,
					   size, 0);
}


int32 CI_CleanupCustom(void)
{
    return close(CI_AppCustomData.Socket);
}

