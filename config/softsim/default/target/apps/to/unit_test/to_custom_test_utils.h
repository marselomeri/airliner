

#ifndef TO_CUSTOM_TEST_UTILS_H
#define TO_CUSTOM_TEST_UTILS_H

/*
 * Includes
 */

#include "to_custom_udp.h"


extern TO_AppCustomData_t TO_AppCustomData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void TO_Custom_Test_Setup(void);
void TO_Custom_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* TO_CUSTOM_TEST_UTILS_H */
