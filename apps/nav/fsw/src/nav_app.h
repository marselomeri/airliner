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
#include <math.h>
#include <float.h>

#include "cfe.h"
#include "nav_platform_cfg.h"
#include "nav_mission_cfg.h"
#include "nav_perfids.h"
#include "nav_msgids.h"
#include "nav_msg.h"
#include "nav_events.h"
#include "nav_tbldefs.h"
#include "px4_msgs.h"
#include "lib/px4lib.h"
#include "geo/geo.h"
#include "math/Limits.hpp"

/************************************************************************
 ** Local Defines
 *************************************************************************/
#define PX4_ISFINITE(x) isfinite(x)
#define NAV_EPSILON_POSITION	0.001f
#define M_PI_2_F	1.57079632f

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
    PX4_VehicleCommandMsg_t VehicleCommandMsg;
} NAV_CurrentValueTable_t;


typedef struct{
	float nav_acc_rad = 2.0f; /*default accepted radius*/
	float nav_mc_alt_rad = 0.8f; /*altitude accepted radius for multi-copters*/
	float nav_loiter_rad = 50.0f;


	//takeoff
	float nav_mis_takeoff_alt = 2.5f;
	float nav_mis_yaw_err = 12.0f;
	float nav_mis_yaw_tmt = -1.0f;


}NAV_Params_t;

typedef struct{
	double Lat;					/**< latitude in degrees				*/
	double Lon;					/**< longitude in degrees				*/
	float TimeInside;			/**< time that the MAV should stay inside the radius before advancing in seconds */
	float PitchMin;				/**< minimal pitch angle for fixed wing takeoff waypoints */
	float AcceptanceRadius;		/**< default radius in which the mission is accepted as reached in meters */
	float LoiterRadius;			/**< loiter radius in meters, 0 for a VTOL to hover, negative for counter-clockwise */
	float Yaw;					/**< in radians NED -PI..+PI, NAN means don't change yaw		*/
	float LatFloatPadding;		/**< padding */
	float LonFloatPadding;		/**< padding */
	float Altitude;				/**< altitude in meters	(AMSL)			*/
	float Params[7];			/**< array to store mission command values for MAV_FRAME_MISSION ***/
	uint16 NavCmd;				/**< navigation command					*/
	int16 DoJumpMissionIndex;	/**< index where the do jump will go to                 */
	uint16 DoJumpRepeatCount;	/**< how many times do jump needs to be done            */
	uint16 DoJumpCurrentCount;	/**< count how many times the jump has been done	*/
	struct{
		uint16 Frame : 4;
		uint16 Origin : 3;
		uint16 LoiterExitXTrack : 1;
		uint16 ForceHeading : 1;
		uint16 AltitudeIsRelative : 1;
		uint16 AutoContinue : 1;
		uint16 DisableMcYaw : 1;
	};
}NAV_MissionItem_t;

typedef enum {
	ORIGIN_MAVLINK = 0,
	ORIGIN_ONBOARD =1
} NAV_Origin_t;


typedef struct{
	boolean loiter;
	boolean takeoff;
} NAV_Active, NAV_First_Time;


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
    PX4_VehicleLandDetectedMsg_t VehicleLandDetectedMsg = {};
    PX4_FenceMsg_t FenceMsg = {};
    PX4_ActuatorControlsMsg_t ActuatorControls3Msg = {};
    PX4_MissionResultMsg_t MissionResultMsg = {};
    PX4_GeofenceResultMsg_t GeofenceResultMsg = {};
    PX4_PositionSetpointTripletMsg_t PositionSetpointTripletMsg = {};
    PX4_VehicleCommandMsg_t VehicleCommandMsgOut = {};

    /** \brief Housekeeping Telemetry for downlink */
    NAV_HkTlm_t HkTlm;
    /** \brief Current Value Table */
    NAV_CurrentValueTable_t CVT = {};


    /** \brief Navigator Parameter Table
     *	\par Description
     *		 initializing parameter table specific to navigator.
     */
    NAV_Params_t nav_params;
    NAV_MissionItem_t mission_item;
    NAV_First_Time first_time {true,true};
    NAV_Active active {false,false};
    int32 counter = 0;
    int one_level_deep_memory = -1;
    PX4_VehicleStatusMsg_t* previous_state;

    //loiter
    boolean CanLoiterAtSetpoint{false};
    boolean PositionSetpointTripletUpdated{false};

    //mission
    boolean MissionResultUpdated{false};
    boolean WaypointPositionReached{false};
    boolean WaypointYawReached{false};
    uint64 TimeFirstInsideOrbit{0};
    uint64 ActionStart{0};
    uint64 TimeWpReached{0};
	float MissionCruisingSpeed{-1.0f};
	float MissionThrottle{-1.0f};



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

     float GetDefaultAcceptedRadius(void);
     void SetAcceptedRadius(float);
     float GetAltitudeAcceptedRadius(void);
     void SendVehicleCommandMsg(void);

     boolean HomePositionValid(void);
     float GetCruisingSpeed(void);
     float GetCruisingThrottle(void);
     int Execute(void);
     void Takeoff(boolean);
     void Loiter(void);
     boolean IsMissionItemReached(void);
     void SetLoiterItem(NAV_MissionItem_t *);
     void SetMissionFaliure(const char* );
     float GetTimeInside(NAV_MissionItem_t * );
     boolean StateChangeDetect(void);
     void ConvertMissionItemToCurrentSetpoint(PX4_PositionSetpoint_t *, NAV_MissionItem_t *);
     void DisplayInputs(int);
     void DisplayOutputs(int);


	/************************************************************************/
	/** KK_END MORE BELOW
	*************************************************************************/

      PX4_VehicleLandDetectedMsg_t* GetLandDetectedMsg(){ return &VehicleLandDetectedMsg;}
      PX4_FenceMsg_t* GetFenceMsg(){ return &FenceMsg;}
      PX4_ActuatorControlsMsg_t* GetActuatorControlMsg(){ return &ActuatorControls3Msg;}
      PX4_MissionResultMsg_t* GetMissionResultMsg(){ return &MissionResultMsg;}
      PX4_GeofenceResultMsg_t* GetGeoFenceResultMsg(){ return &GeofenceResultMsg;}
      PX4_PositionSetpointTripletMsg_t* GetPositionSetpointTripletMsg(){ return &PositionSetpointTripletMsg;}
      PX4_VehicleCommandMsg_t* GetVehicleCommandMsgOut(){ return &VehicleCommandMsgOut;}

     	PX4_HomePositionMsg_t* GetHomePosition(){return &CVT.HomePositionMsg;}
     	PX4_SensorCombinedMsg_t* GetSensorCombined(){return &CVT.SensorCombinedMsg;}
     	PX4_MissionMsg_t* GetMissionMsg(){return &CVT.MissionMsg;}
     	PX4_VehicleGpsPositionMsg_t* GetVehicleGpsPositionMsg(){return &CVT.VehicleGpsPositionMsg;}
     	PX4_VehicleGlobalPositionMsg_t* GetVehicleGlobalPositionMsg(){return &CVT.VehicleGlobalPosition;}
     	PX4_VehicleStatusMsg_t* GetVehicleStatusMsg(){return &CVT.VehicleStatusMsg;}
     	PX4_VehicleLandDetectedMsg_t* GetVehicleLandDetectedMsg(){return &CVT.VehicleLandDetectedMsg;}
     	PX4_VehicleLocalPositionMsg_t* GetVehicleLocalPositionMsg(){return &CVT.VehicleLocalPositionMsg;}
     	PX4_VehicleCommandMsg_t* GetVehicleCommandMsg(){return &CVT.VehicleCommandMsg;}

     	boolean IsPlannedMission(){return false;}
    	void SetCanLoiterAtSetpoint(boolean can_loiter) { CanLoiterAtSetpoint = can_loiter; }
    	void SetPositionSetpointTripletUpdated() { PositionSetpointTripletUpdated = true; }




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
