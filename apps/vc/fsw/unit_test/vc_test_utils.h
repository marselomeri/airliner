
#ifndef VC_TEST_UTILS_H
#define VC_TEST_UTILS_H

/*
 * Includes
 */

#include "vc_app.h"

extern VC_AppData_t  VC_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void VC_Test_Setup(void);
void VC_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* VC_TEST_UTILS_H */

