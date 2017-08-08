#ifndef VC_EVENTS_H
#define VC_EVENTS_H
/* Event message ID's */
#define VC_RESERVED_EID       0
#define VC_INIT_INF_EID       1  /* start up message "informational" */
#define VC_NOOP_INF_EID       2  /* processed command "informational" */
#define VC_RESET_INF_EID      3
#define VC_PROCCESS_INF_EID   4
#define VC_MID_ERR_EID        5  /* invalid command packet "error" */
#define VC_CC1_ERR_EID        6
#define VC_LEN_ERR_EID        7
#define VC_PIPE_ERR_EID       8
#define VC_SOCKET_ERR_EID     9  /* socket error */
#define VC_DEVICE_ERR_EID     10 /* device error */
#define VC_INIT_ERR_EID       11 /* initialization error */
#define VC_UNINIT_ERR_EID     12 /* uninitialization error */
#define VC_CHA_INF_EID        13 /* channel init message "informational" */
#define VC_DEV_INF_EID        14 /* device init and info message "informational" */
#define VC_ADDR_ERR_EID       15 /* cmd address error */
#define VC_ADDR_NUL_ERR_EID   16 /* cmd address null error*/
#define VC_EVT_COUNT          16 /* count of event message ID's */

#endif
