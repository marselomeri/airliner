/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#ifndef LD_APP_H
#define LD_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** Pragmas
 *************************************************************************/

/************************************************************************
 ** Includes
 *************************************************************************/
#include "cfe.h"

#include "ld_platform_cfg.h"
#include "ld_mission_cfg.h"
#include "ld_perfids.h"
#include "ld_msgids.h"
#include "ld_msg.h"
#include "ld_events.h"
#include "ld_tbldefs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
#include "px4_msgs.h"
/************************************************************************
 ** Local Defines
 *************************************************************************/

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/
typedef struct
{
    PX4_ActuatorArmedMsg_t ActuatorArmedMsg;
    PX4_AirspeedMsg_t AirspeedMsg;
    PX4_ActuatorControlsMsg_t ActuatorControls0Msg;
    PX4_ControlStateMsg_t ControlStateMsg;
    PX4_BatteryStatusMsg_t BatteryStatusMsg;
    PX4_VehicleAttitudeMsg_t VehicleAttitudeMsg;
    PX4_ManualControlSetpointMsg_t ManualControlSetpointMsg;
    PX4_VehicleLocalPositionMsg_t VehicleLocalPositionMsg;
    PX4_VehicleControlModeMsg_t VehicleControlModeMsg;
} LD_CurrentValueTable_t;


/**
 **  \brief LD Application Class
 */
class LD
{
public:
    LD();
    ~LD();

    /**\brief Scheduling Pipe ID */
    CFE_SB_PipeId_t SchPipeId;

    /** \brief Command Pipe ID */
    CFE_SB_PipeId_t CmdPipeId;

    /* Task-related */

    /** \brief Task Run Status */
    uint32 uiRunStatus;

    /* Config table-related */

    /** \brief Config Table Handle */
    CFE_TBL_Handle_t ConfigTblHdl;

    /** \brief Config Table Pointer */
    LD_ConfigTbl_t* ConfigTblPtr;
    /** \brief Output Data published at the end of cycle */
    PX4_VehicleLandDetectedMsg_t VehicleLandDetectedMsg;

    /** \brief Housekeeping Telemetry for downlink */
    LD_HkTlm_t HkTlm;
    /** \brief Current Value Table */
    LD_CurrentValueTable_t CVT;
    /************************************************************************/
    /** \brief Landing Detector (LD) application entry point
     **
     **  \par Description
     **       Landing Detector Task application entry point.  This function
     **       performs app initialization, then waits for the cFE ES Startup
     **       Sync, then executes the main processing loop.
     **
     **  \par Assumptions, External Events, and Notes:
     **       If there is an unrecoverable failure during initialization the
     **       main loop is never executed and the application will exit.
     **
     *************************************************************************/
    void AppMain(void);

    /************************************************************************/
    /** \brief Initialize the Landing Detector (LD) application
     **
     **  \par Description
     **       Landing Detector application initialization routine. This
     **       function performs all the required startup steps to
     **       initialize (or restore from CDS) LD data structures and get
     **       the application registered with the cFE services so it can
     **       begin to receive command messages and send events.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \returns
     **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
     **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
     **  \retstmt Return codes from #LD_InitEvent               \endcode
     **  \retstmt Return codes from #LD_InitPipe                \endcode
     **  \retstmt Return codes from #LD_InitData                \endcode
     **  \retstmt Return codes from #LD_InitConfigTbl           \endcode
     **  \retstmt Return codes from #OS_TaskInstallDeleteHandler \endcode
     **  \endreturns
     **
     *************************************************************************/
    int32 InitApp(void);

    /************************************************************************/
    /** \brief Initialize Event Services and Event tables
     **
     **  \par Description
     **       This function performs the steps required to setup
     **       cFE Event Services for use by the LD application.
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
    int32 InitEvent(void);

    /************************************************************************/
    /** \brief Initialize global variables used by LD application
     **
     **  \par Description
     **       This function performs the steps required to initialize
     **       the LD application data.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void InitData(void);

    /************************************************************************/
    /** \brief Initialize message pipes
     **
     **  \par Description
     **       This function performs the steps required to setup
     **       initialize the cFE Software Bus message pipes and subscribe to
     **       messages for the LD application.
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
    int32 InitPipe(void);

    /************************************************************************/
    /** \brief Receive and process messages from the scheduler pipe.
     **
     **  \par Description
     **       This function receives and processes messages
     **       for the LD application from the SCH pipe.  This function
     **       will pend for the type defined by iBlocking, allowing
     **       it to wait for messages, i.e. wakeup messages from scheduler.
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
    int32 RcvSchPipeMsg(int32 iBlocking);

    /************************************************************************/
    /** \brief Landing Detector Task incoming command processing
     **
     **  \par Description
     **       This function processes incoming commands subscribed
     **       by LD application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ProcessCmdPipe(void);

    /************************************************************************/
    /** \brief Landing Detector Task application commands
     **
     **  \par Description
     **       This function processes command messages
     **       specific to the LD application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \param [in]   MsgPtr       A #CFE_SB_Msg_t pointer that
     **                             references the software bus message
     **
     *************************************************************************/
    void ProcessAppCmds(CFE_SB_Msg_t* MsgPtr);

    /************************************************************************/
    /** \brief Sends LD housekeeping message
     **
     **  \par Description
     **       This function sends the housekeeping message
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ReportHousekeeping(void);
    /************************************************************************/
    /** \brief Sends the VehicleLandDetectedMsg message.
     **
     **  \par Description
     **       This function publishes the VehicleLandDetectedMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendVehicleLandDetectedMsg(void);
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
    boolean VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen);

private:
    /************************************************************************/
    /** \brief Initialize the LD configuration tables.
    **
    **  \par Description
    **       This function initializes LD's configuration tables.  This
    **       includes <TODO>.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \retstmt Return codes from #CFE_TBL_Register          \endcode
    **  \retstmt Return codes from #CFE_TBL_Load              \endcode
    **  \retstmt Return codes from #LD_AcquireConfigPointers \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  InitConfigTbl(void);

    /************************************************************************/
    /** \brief Obtain LD configuration tables data pointers.
    **
    **  \par Description
    **       This function manages the configuration tables
    **       and obtains a pointer to their data.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  AcquireConfigPointers(void);

public:
    /************************************************************************/
    /** \brief Validate LD configuration table
    **
    **  \par Description
    **       This function validates LD's configuration table
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \param [in]   ConfigTblPtr    A pointer to the table to validate.
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \endreturns
    **
    *************************************************************************/
    static int32  ValidateConfigTbl(void*);
};

#ifdef __cplusplus
}
#endif 

#endif /* LD_APP_H */

/************************/
/*  End of File Comment */
/************************/
