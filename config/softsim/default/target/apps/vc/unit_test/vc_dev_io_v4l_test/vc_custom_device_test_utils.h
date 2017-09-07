
#ifndef VC_CUSTOM_DEVICE_TEST_UTILS_H
#define VC_CUSTOM_DEVICE_TEST_UTILS_H

/*
 * Includes
 */

#include "vc_dev_io_v4l.h"


extern VC_AppCustomDevice_t VC_AppCustomDevice;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void VC_Custom_Device_Test_Setup(void);
void VC_Custom_Device_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* VC_CUSTOM_DEVICE_TEST_UTILS_H */
