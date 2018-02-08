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

#ifndef NAV_APP_H
#define NAV_APP_H

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

#include "nav_platform_cfg.h"
#include "nav_mission_cfg.h"
#include "nav_perfids.h"
#include "nav_msgids.h"
#include "nav_msg.h"
#include "nav_events.h"
#include "nav_tbldefs.h"
#include "px4_msgs.h"

/************************************************************************
 ** Local Defines
 *************************************************************************/

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/
typedef struct
{
    PX4_HomePositionMsg_t HomePositionMsg;
    PX4_SensorCombinedMsg_t SensorCombinedMsg;
    PX4_MissionMsg_t MissionMsg;
    PX4_VehicleGpsPositionMsg_t VehicleGpsPositionMsg;
    PX4_VehicleGlobalPositionMsg_t VehicleGlobalPosition;
    PX4_VehicleStatusMsg_t VehicleStatusMsg;
    PX4_VehicleLandDetectedMsg_t VehicleLandDetectedMsg;
    PX4_VehicleLocalPositionMsg_t VehicleLocalPositionMsg;
} NAV_CurrentValueTable_t;


typedef struct{
	float nav_acc_rad = 2.0f; /*default accepted radius*/
	float nav_mc_alt_rad = 0.8f; /*altitude accepted radius for multi-copters*/
}NAV_Params_t;

/**
 **  \brief NAV Application Class
 */
class NAV
{
public:
    NAV();
    ~NAV();

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
    NAV_ConfigTbl_t* ConfigTblPtr;
    /** \brief Output Data published at the end of cycle */
    PX4_VehicleLandDetectedMsg_t VehicleLandDetectedMsg;
    PX4_FenceMsg_t FenceMsg;
    PX4_ActuatorControlsMsg_t ActuatorControls3Msg;
    PX4_MissionResultMsg_t MissionResultMsg;
    PX4_GeofenceResultMsg_t GeofenceResultMsg;
    PX4_PositionSetpointTripletMsg_t PositionSetpointTripletMsg;

    /** \brief Housekeeping Telemetry for downlink */
    NAV_HkTlm_t HkTlm;
    /** \brief Current Value Table */
    NAV_CurrentValueTable_t CVT;

    /** \brief Navigator Parameter Table
     *	\par Description
     *		 initializing parameter table specific to navigator.
     */
    NAV_Params_t nav_params;
    int32 counter = 0;
    /************************************************************************/
    /** \brief Navigator (NAV) application entry point
     **
     **  \par Description
     **       Navigator Task application entry point.  This function
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
    /** \brief Initialize the Navigator (NAV) application
     **
     **  \par Description
     **       Navigator application initialization routine. This
     **       function performs all the required startup steps to
     **       initialize (or restore from CDS) NAV data structures and get
     **       the application registered with the cFE services so it can
     **       begin to receive command messages and send events.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \returns
     **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
     **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
     **  \retstmt Return codes from #NAV_InitEvent               \endcode
     **  \retstmt Return codes from #NAV_InitPipe                \endcode
     **  \retstmt Return codes from #NAV_InitData                \endcode
     **  \retstmt Return codes from #NAV_InitConfigTbl           \endcode
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
     **       cFE Event Services for use by the NAV application.
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
    /** \brief Initialize global variables used by NAV application
     **
     **  \par Description
     **       This function performs the steps required to initialize
     **       the NAV application data.
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
     **       messages for the NAV application.
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
     **       for the NAV application from the SCH pipe.  This function
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
    /** \brief Navigator Task incoming command processing
     **
     **  \par Description
     **       This function processes incoming commands subscribed
     **       by NAV application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ProcessCmdPipe(void);

    /************************************************************************/
    /** \brief Navigator Task application commands
     **
     **  \par Description
     **       This function processes command messages
     **       specific to the NAV application
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
    /** \brief Sends NAV housekeeping message
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
    /** \brief Sends the FenceMsg message.
     **
     **  \par Description
     **       This function publishes the FenceMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendFenceMsg(void);
    /************************************************************************/
    /** \brief Sends the ActuatorControls3Msg message.
     **
     **  \par Description
     **       This function publishes the ActuatorControls3Msg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendActuatorControls3Msg(void);
    /************************************************************************/
    /** \brief Sends the MissionResultMsg message.
     **
     **  \par Description
     **       This function publishes the MissionResultMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendMissionResultMsg(void);
    /************************************************************************/
    /** \brief Sends the GeofenceResultMsg message.
     **
     **  \par Description
     **       This function publishes the GeofenceResultMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendGeofenceResultMsg(void);
    /************************************************************************/
    /** \brief Sends the PositionSetpointTripletMsg message.
     **
     **  \par Description
     **       This function publishes the PositionSetpointTripletMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendPositionSetpointTripletMsg(void);
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



    /************************************************************************/
    /** KK
	*************************************************************************/
     void execute(void);
     float getDefaultAcceptedRadius(void);
     void setAcceptedRadius(float);
     float getAltitudeAcceptedRadius(void);
	/************************************************************************/
	/** KK_END
	*************************************************************************/








private:
    /************************************************************************/
    /** \brief Initialize the NAV configuration tables.
    **
    **  \par Description
    **       This function initializes NAV's configuration tables.  This
    **       includes <TODO>.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \retstmt Return codes from #CFE_TBL_Register          \endcode
    **  \retstmt Return codes from #CFE_TBL_Load              \endcode
    **  \retstmt Return codes from #NAV_AcquireConfigPointers \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  InitConfigTbl(void);

    /************************************************************************/
    /** \brief Obtain NAV configuration tables data pointers.
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
    /** \brief Validate NAV configuration table
    **
    **  \par Description
    **       This function validates NAV's configuration table
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

#endif /* NAV_APP_H */

/************************/
/*  End of File Comment */
/************************/
