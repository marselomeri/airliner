#ifndef EA_CUSTOM_TEST_H
#define EA_CUSTOM_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

void EA_Custom_Test_AddTestCases(void);
int EA_CalibrateTop(int pid);
int EA_GetPidUtil(int pid, int util_ndx);

#ifdef __cplusplus
}
#endif

#endif /* EA_CUSTOM_TEST_H */
