
#ifndef PARAMS_TEST_UTILS_H
#define PARAMS_TEST_UTILS_H

/*
 * Includes
 */

#include "params_app.h"

extern PARAMS_AppData_t  PARAMS_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void PARAMS_Test_Setup(void);
void PARAMS_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* PARAMS_TEST_UTILS_H */

