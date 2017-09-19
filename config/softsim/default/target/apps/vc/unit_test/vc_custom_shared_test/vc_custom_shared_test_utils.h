
#ifndef VC_CUSTOM_DEVICE_SHARED_UTILS_H
#define VC_CUSTOM_DEVICE_SHARED_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Includes
 */

#include "vc_custom_shared.h"

extern VC_AppCustomDevice_t VC_AppCustomDevice;

/*
 * Function Definitions
 */

void VC_Custom_Shared_Test_Setup(void);
void VC_Custom_Shared_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* VC_CUSTOM_DEVICE_SHARED_UTILS_H */
