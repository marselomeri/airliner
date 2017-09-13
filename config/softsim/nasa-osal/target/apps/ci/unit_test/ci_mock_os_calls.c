#ifdef __cplusplus
extern "C" {
#endif

int SOCK_RET_CODE = 0;
int HTONL_RET_CODE = 0;
int HTONS_RET_CODE = 0;
int BIND_RET_CODE = 0;

int __wrap_socket (int namespace, int style, int protocol)
{
	return SOCK_RET_CODE;
}

//int __wrap_htonl (int hostlong)
//{
//    return HTONL_RET_CODE;
//}
//
//int __wrap_htons (int hostshort)
//{
//    return HTONS_RET_CODE;
//}

int __wrap_bind (int socket, int *addr, int length)
{
    return BIND_RET_CODE;
}
