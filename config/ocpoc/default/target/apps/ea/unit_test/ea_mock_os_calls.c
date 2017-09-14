#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

int FORK_RET_CODE = 0;
int EXECVP_RET_CODE = 0;
int KILL_RET_CODE = 0;
int WAITPID_RET_CODE = 0;

//void __real_fork();

pid_t __wrap_fork()
{
	return FORK_RET_CODE;
}

int __wrap_execvp(const char *file, char *const argv[])
{
	return EXECVP_RET_CODE;
}

int __wrap_kill(int pid, int signal)
{
	return KILL_RET_CODE;
}

pid_t __wrap_waitpid(pid_t pid, int *status, int options)
{
	*status = WAITPID_RET_CODE;
	return WAITPID_RET_CODE;
}
