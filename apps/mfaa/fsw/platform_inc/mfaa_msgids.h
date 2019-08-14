    
#ifndef MFAA_MSGIDS_H
#define MFAA_MSGIDS_H

#ifdef __cplusplus
extern "C" {
#endif

/***** TODO:  These Message ID values are default and may need to be changed
******        by the developer or mission integrator!
******/

#include "msg_ids.h"

/**
** \brief MFAA application-specific command MID
*/
#define MFAA_CMD_MID                 (0x18C0)

/**
** \brief Command for the application to send HK data
*/
#define MFAA_SEND_HK_MID             (0x18C1)

/**
** \brief Wakeup command for the application to perform processing
*/
#define MFAA_WAKEUP_MID              (0x18D0)

/**
** \brief Application-specific data output
*/
#define MFAA_OUT_DATA_MID            (0x18D1)

/**
** \brief Application housekeeping telemetry data
*/
#define MFAA_HK_TLM_MID              (0x08BB)


#ifdef __cplusplus
}
#endif

#endif /* MFAA_MSGIDS_H */

/************************/
/*  End of File Comment */
/************************/
