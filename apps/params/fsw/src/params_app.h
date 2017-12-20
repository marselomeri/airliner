    
#ifndef PARAMS_APP_H
#define PARAMS_APP_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

#include "params_platform_cfg.h"
#include "params_mission_cfg.h"
#include "params_private_ids.h"
#include "params_private_types.h"
#include "params_perfids.h"
#include "params_msgids.h"
#include "params_msg.h"
#include "params_events.h"
#include "params_config_utils.h"
#include "params_cds_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/
#define PARAMS_TIMEOUT_MSEC             	(1000)

/************************************************************************
** Local Structure Definitions
*************************************************************************/
/**
**  \brief PARAMS Operational Data Structure
*/
typedef struct
{
    /** \brief CFE Event Table */
    CFE_EVS_BinFilter_t  EventTbl[PARAMS_EVT_CNT];

    /**\brief Scheduling Pipe ID */
    CFE_SB_PipeId_t  SchPipeId;

    /** \brief Command Pipe ID */
    CFE_SB_PipeId_t  CmdPipeId;

    /** \brief Data Pipe ID */
    CFE_SB_PipeId_t  DataPipeId;

    /* Task-related */

    /** \brief Task Run Status */
    uint32  uiRunStatus;

    /* Config table-related */

    /** \brief Config Table Handle */
    CFE_TBL_Handle_t  ParamTblHdl;

    /** \brief Config Table Pointer */
    PARAMS_ParamsTblEntry_t*  ParamTblPtr;

    /* Critical Data Storage (CDS) table-related */

    /** \brief CDS Table Handle */
    CFE_ES_CDSHandle_t  CdsTblHdl;

    /** \brief CDS Table data */
    PARAMS_CdsTbl_t  CdsTbl;

    /* Inputs/Outputs */

    /** \brief Input Data from I/O or other apps */
    PARAMS_InData_t   InData;

    /** \brief Output Data published at the end of cycle */
    PARAMS_OutData_t  OutData;

    /** \brief Housekeeping Telemetry for downlink */
    PARAMS_HkTlm_t  HkTlm;

} PARAMS_AppData_t;

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
/** \brief CFS Params Task (PARAMS) application entry point
**
**  \par Description
**       CFS Params Task application entry point.  This function
**       performs app initialization, then waits for the cFE ES Startup
**       Sync, then executes the RPR main processing loop.
**
**  \par Assumptions, External Events, and Notes:
**       If there is an unrecoverable failure during initialization the
**       main loop is never executed and the application will exit.
**
*************************************************************************/
void  PARAMS_AppMain(void);

/************************************************************************/
/** \brief Initialize the CFS Params (PARAMS) application
**
**  \par Description
**       Params application initialization routine. This
**       function performs all the required startup steps to
**       initialize (or restore from CDS) PARAMS data structures and get
**       the application registered with the cFE services so it can
**       begin to receive command messages and send events.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
**  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
**  \retstmt Return codes from #PARAMS_InitEvent               \endcode
**  \retstmt Return codes from #PARAMS_InitPipe                \endcode
**  \retstmt Return codes from #PARAMS_InitData                \endcode
**  \retstmt Return codes from #PARAMS_InitConfigTbl           \endcode
**  \retstmt Return codes from #PARAMS_InitCdsTbl              \endcode
**  \retstmt Return codes from #OS_TaskInstallDeleteHandler \endcode
**  \endreturns
**
*************************************************************************/
int32  PARAMS_InitApp(void);

/************************************************************************/
/** \brief Initialize Event Services and Event tables
**
**  \par Description
**       This function performs the steps required to setup
**       cFE Event Services for use by the PARAMS application.
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
int32  PARAMS_InitEvent(void);

/************************************************************************/
/** \brief Initialize global variables used by PARAMS application
**
**  \par Description
**       This function performs the steps required to initialize
**       the PARAMS application data.
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
int32  PARAMS_InitData(void);

/************************************************************************/
/** \brief Initialize message pipes
**
**  \par Description
**       This function performs the steps required to setup
**       initialize the cFE Software Bus message pipes and subscribe to
**       messages for the PARAMS application.
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
int32  PARAMS_InitPipe(void);

/************************************************************************/
/** \brief Receive and process messages
**
**  \par Description
**       This function receives and processes messages
**       for the PARAMS application
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
int32  PARAMS_RcvMsg(int32 iBlocking);

/************************************************************************/
/** \brief Params Task incoming data processing
**
**  \par Description
**       This function processes incoming data subscribed
**       by PARAMS application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  PARAMS_ProcessNewData(void);

/************************************************************************/
/** \brief Params Task incoming command processing
**
**  \par Description
**       This function processes incoming commands subscribed
**       by PARAMS application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  PARAMS_ProcessNewCmds(void);

/************************************************************************/
/** \brief Params Task application commands
**
**  \par Description
**       This function processes command messages
**       specific to the PARAMS application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr       A #CFE_SB_Msg_t pointer that
**                             references the software bus message
**
*************************************************************************/
void  PARAMS_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr);

/************************************************************************/
/** \brief Sends PARAMS housekeeping message
**
**  \par Description
**       This function sends the housekeeping message
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  PARAMS_ReportHousekeeping(void);

/************************************************************************/
/** \brief Sends PARAMS output data
**
**  \par Description
**       This function publishes the PARAMS application output data.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  PARAMS_SendOutData(void);

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
boolean  PARAMS_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen);

void PARAMS_AddParam(PARAMS_ParamData_t param);
void PARAMS_SetParam(PARAMS_SetParamCmd_t* SetParamMsg);

#ifdef __cplusplus
}
#endif 

#endif /* PARAMS_APP_H */

/************************/
/*  End of File Comment */
/************************/
