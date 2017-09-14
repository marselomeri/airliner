#ifndef EA_MOCK_OS_CALLS_H
#define EA_MOCK_OS_CALLS_H

#ifdef __cplusplus
extern "C" {
#endif

//#define fork() mock_fork()
//#define execvp(...) mock_execvp(__VA_ARGS__)
//#define kill(...) mock_kill(__VA_ARGS__)

extern int FORK_RET_CODE;
extern int EXECVP_RET_CODE;
extern int KILL_RET_CODE;
extern int WAITPID_RET_CODE
//int __wrap_fork();
//int __wrap_execvp(const char *file, char *const argv[]);
//int __wrap_kill(int pid, int signal);

#ifdef __cplusplus
}
#endif

#endif /* MOCK_OS_CALLS_H */
