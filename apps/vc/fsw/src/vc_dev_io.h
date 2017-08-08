
/**
 * @defgroup Device_IO
 * @addtogroup Device_IO
 * @file vc_dev_ip.h
 * @brief Custom layer for Video Controller device input/output.
 * @{
 */
 
#ifndef VC_DEV_IO_H
#define VC_DEV_IO_H

/**
 * @brief Starts initialized resources.
 * @return true if successful, otherwise false
 */
boolean VC_Devices_Start(void);

/**
 * @brief Stops initialized resources.
 * @return true if successful, otherwise false
 */
boolean VC_Devices_Stop(void);

/**
 * @brief Initialize configured resources.
 * @return true if successful, otherwise false
 */
boolean VC_Devices_Init(void);

/**
 * @brief Uninitialize previously initialized resources.
 * @return true if successful, otherwise false
 */
boolean VC_Devices_Uninit(void);


#endif

/* @} */
