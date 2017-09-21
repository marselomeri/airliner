#ifndef PMC_APP_H
#define PMC_APP_H

/************************************************************************
 ** Pragmas
 *************************************************************************/

/************************************************************************
 ** Includes
 *************************************************************************/
#include "cfe.h"

#include "pmc_platform_cfg.h"
#include "pmc_mission_cfg.h"
#include "pmc_private_ids.h"
#include "pmc_private_types.h"
#include "pmc_perfids.h"
#include "pmc_msgids.h"
#include "pmc_msg.h"
#include "pmc_events.h"
#include "pmc_config_utils.h"
#include "pmc_cds_utils.h"
#include "px4_msgs.h"
#include "mixer.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************************************************************
 ** Local Defines
 *************************************************************************/
#define PMC_TIMEOUT_MSEC        (1000)
#define PMC_MAX_ZYNQ_PWMS       (8)
#define PMC_RCOUT_ZYNQ_PWM_BASE (0x43c00000)
#define PMC_FREQUENCY_PWM       (400)
#define PMC_TICK_PER_S          (50000000)
#define PMC_TICK_PER_US         (50)
#define PMC_DEVICE_PATH         "/dev/mem"

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/

typedef struct
{
    PX4_ActuatorControlsMsg_t ActuatorControls0;
    PX4_ActuatorArmedMsg_t    ActuatorArmed;
    PX4_RcChannelsMsg_t       RcChannels;
} PMC_CurrentValueTable_t;

typedef struct {
    uint32 Period;
    uint32 Hi;
} PMC_PeriodHi_t;

typedef struct
{
     PMC_PeriodHi_t PeriodHi[PMC_MAX_ZYNQ_PWMS];
} PMC_SharedMemCmd_t;

/**
 **  \brief PMC Operational Data Structure
 */
typedef struct
{
    /** \brief CFE Event Table */
    CFE_EVS_BinFilter_t EventTbl[PMC_EVT_CNT];

    /**\brief Scheduling Pipe ID */
    CFE_SB_PipeId_t SchPipeId;

    /** \brief Command Pipe ID */
    CFE_SB_PipeId_t CmdPipeId;

    /** \brief Data Pipe ID */
    CFE_SB_PipeId_t DataPipeId;

    /* Task-related */

    /** \brief Task Run Status */
    uint32 uiRunStatus;

    /* Config table-related */

    /** \brief Config Table Handle */
    CFE_TBL_Handle_t ConfigTblHdl;

    /** \brief Config Table Pointer */
    PMC_ConfigTblEntry_t* ConfigTblPtr;

    /* Critical Data Storage (CDS) table-related */

    /** \brief CDS Table Handle */
    CFE_ES_CDSHandle_t CdsTblHdl;

    /** \brief CDS Table data */
    PMC_CdsTbl_t CdsTbl;

    /* Inputs/Outputs */

    /** \brief Input Data from I/O or other apps */
    PMC_InData_t InData;

    /** \brief Output Data published at the end of cycle */
    PX4_ActuatorOutputsMsg_t OutData;

    /** \brief Housekeeping Telemetry for downlink */
    PMC_HkTlm_t HkTlm;

    PMC_CurrentValueTable_t CVT;

    volatile PMC_SharedMemCmd_t *SharedMemCmd;

    MIXER_Data_t  MixerData;
    PwmLimit_Data_t PwmLimit;

} PMC_AppData_t;

/************************************************************************
 ** External Global Variables
 *************************************************************************/

/************************************************************************
 ** Global Variables
 *************************************************************************/

/************************************************************************
 ** Local Variables
 *************************************************************************/

/************************************************************************
 ** Local Function Prototypes
 *************************************************************************/

/************************************************************************/
/** \brief CFS PWM Motor Controller Task (PMC) application entry point
 **
 **  \par Description
 **       CFS PWM Motor Controller Task application entry point.  This function
 **       performs app initialization, then waits for the cFE ES Startup
 **       Sync, then executes the RPR main processing loop.
 **
 **  \par Assumptions, External Events, and Notes:
 **       If there is an unrecoverable failure during initialization the
 **       main loop is never executed and the application will exit.
 **
 *************************************************************************/
void PMC_AppMain(void);

/************************************************************************/
/** \brief Initialize the CFS PWM Motor Controller (PMC) application
 **
 **  \par Description
 **       PWM Motor Controller application initialization routine. This
 **       function performs all the required startup steps to
 **       initialize (or restore from CDS) PMC data structures and get
 **       the application registered with the cFE services so it can
 **       begin to receive command messages and send events.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \returns
 **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
 **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
 **  \retstmt Return codes from #PMC_InitEvent               \endcode
 **  \retstmt Return codes from #PMC_InitPipe                \endcode
 **  \retstmt Return codes from #PMC_InitData                \endcode
 **  \retstmt Return codes from #PMC_InitConfigTbl           \endcode
 **  \retstmt Return codes from #PMC_InitCdsTbl              \endcode
 **  \retstmt Return codes from #OS_TaskInstallDeleteHandler \endcode
 **  \endreturns
 **
 *************************************************************************/
int32 PMC_InitApp(void);

/************************************************************************/
/** \brief Initialize Event Services and Event tables
 **
 **  \par Description
 **       This function performs the steps required to setup
 **       cFE Event Services for use by the PMC application.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \returns
 **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
 **  \retstmt Return codes from #CFE_EVS_Register  \endcode
 **  \endreturns
 **
 *************************************************************************/
int32 PMC_InitEvent(void);

/************************************************************************/
/** \brief Initialize global variables used by PMC application
 **
 **  \par Description
 **       This function performs the steps required to initialize
 **       the PMC application data.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \returns
 **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
 **  \retstmt Return codes from #CFE_EVS_Register  \endcode
 **  \endreturns
 **
 *************************************************************************/
int32 PMC_InitData(void);

/************************************************************************/
/** \brief Initialize message pipes
 **
 **  \par Description
 **       This function performs the steps required to setup
 **       initialize the cFE Software Bus message pipes and subscribe to
 **       messages for the PMC application.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \returns
 **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
 **  \retstmt Return codes from #CFE_SB_CreatePipe        \endcode
 **  \retstmt Return codes from #CFE_SB_SubscribeEx       \endcode
 **  \retstmt Return codes from #CFE_SB_Subscribe         \endcode
 **  \endreturns
 **
 *************************************************************************/
int32 PMC_InitPipe(void);

/************************************************************************/
/** \brief Receive and process messages
 **
 **  \par Description
 **       This function receives and processes messages
 **       for the PMC application
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \param [in]   iBlocking    A #CFE_SB_PEND_FOREVER, #CFE_SB_POLL or
 **                             millisecond timeout
 **
 **  \returns
 **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
 **  \retstmt Return codes from #CFE_SB_RcvMsg            \endcode
 **  \endreturns
 **
 *************************************************************************/
int32 PMC_RcvMsg(int32 iBlocking);

/************************************************************************/
/** \brief PWM Motor Controller Task incoming data processing
 **
 **  \par Description
 **       This function processes incoming data subscribed
 **       by PMC application
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 *************************************************************************/
void PMC_ProcessNewData(void);

/************************************************************************/
/** \brief PWM Motor Controller Task incoming command processing
 **
 **  \par Description
 **       This function processes incoming commands subscribed
 **       by PMC application
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 *************************************************************************/
void PMC_ProcessNewCmds(void);

/************************************************************************/
/** \brief PWM Motor Controller Task application commands
 **
 **  \par Description
 **       This function processes command messages
 **       specific to the PMC application
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \param [in]   MsgPtr       A #CFE_SB_Msg_t pointer that
 **                             references the software bus message
 **
 *************************************************************************/
void PMC_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr);

/************************************************************************/
/** \brief Sends PMC housekeeping message
 **
 **  \par Description
 **       This function sends the housekeeping message
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 *************************************************************************/
void PMC_ReportHousekeeping(void);

/************************************************************************/
/** \brief Sends PMC output data
 **
 **  \par Description
 **       This function publishes the PMC application output data.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 *************************************************************************/
void PMC_SendOutData(void);

/************************************************************************/
/** \brief Verify Command Length
 **
 **  \par Description
 **       This function verifies the command message length.
 **
 **  \par Assumptions, External Events, and Notes:
 **       None
 **
 **  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
 **                              references the software bus message
 **  \param [in]   usExpectedLen The expected length of the message
 **
 **  \returns
 **  TRUE if the message length matches expectations, FALSE if it does not.
 **  \endreturns
 **
 *************************************************************************/
boolean PMC_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen);

#ifdef __cplusplus
}
#endif 

#endif /* PMC_APP_H */

/************************/
/*  End of File Comment */
/************************/
