
#ifndef VC_CUSTOM_TRANSMIT_TEST_UTILS_H
#define VC_CUSTOM_TRANSMIT_TEST_UTILS_H

/*
 * Includes
 */

#include "vc_transmit_udp.h"


extern VC_AppCustomData_t VC_AppCustomData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void VC_Custom_Transmit_Test_Setup(void);
void VC_Custom_Transmit_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* VC_CUSTOM_TRANSMIT_TEST_UTILS_H */
