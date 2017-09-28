#ifndef MAC_TEST_UTILS_H
#define MAC_TEST_UTILS_H

/*
 * Includes
 */

#include "mac_app.h"

extern MAC_AppData_t  MAC_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void MAC_Test_Setup(void);
void MAC_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* MAC_TEST_UTILS_H */

