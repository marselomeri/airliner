
#ifndef PMC_TEST_UTILS_H
#define PMC_TEST_UTILS_H

/*
 * Includes
 */

#include "pmc_app.h"

extern PMC_AppData_t  PMC_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void PMC_Test_Setup(void);
void PMC_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* PMC_TEST_UTILS_H */

