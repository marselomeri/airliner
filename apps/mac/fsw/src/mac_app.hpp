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

#ifndef MAC_APP_H
#define MAC_APP_H


#include <math/Vector3F.hpp>

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

#include "mac_platform_cfg.h"
#include "mac_mission_cfg.h"
#include "mac_private_ids.h"
#include "mac_private_types.h"
#include "mac_perfids.h"
#include "mac_msgids.h"
#include "mac_msg.h"
#include "mac_events.h"
#include "mac_tbldefs.h"
#include "px4_msgs.h"


/************************************************************************
 ** Local Defines
 *************************************************************************/

/** \brief Pipe depth for the data pipe
**
**  \par Limits:
**       minimum of 1, max of CFE_SB_MAX_PIPE_DEPTH.
*/
#define MAC_DATA_PIPE_DEPTH            (11)

/** \brief Pipe name for the Scheduler pipe
**
**  \par Limits:
**       Note, this name must fit in OS_MAX_API_NAME.
*/
#define MAC_DATA_PIPE_NAME             ("MAC_DATA_PIPE")

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/

typedef struct
{
	PX4_ActuatorArmedMsg_t				Armed;			  /**< actuator arming status */
	PX4_BatteryStatusMsg_t				BatteryStatus;	  /**< battery status */
	PX4_ControlStateMsg_t				ControlState;
	PX4_ManualControlSetpointMsg_t		ManualControlSp;  /**< manual control setpoint */
	PX4_MultirotorMotorLimitsMsg_t		MotorLimits;	  /**< motor limits */
	PX4_SensorCorrectionMsg_t			SensorCorrection; /**< sensor thermal corrections */
	PX4_SensorGyroMsg_t					SensorGyro;		  /**< gyro data before thermal correctons and ekf bias estimates are applied */
	PX4_VehicleAttitudeSetpointMsg_t	VAttSp;			  /**< vehicle attitude setpoint */
	PX4_VehicleControlModeMsg_t			VControlMode;	  /**< vehicle control mode */
	PX4_VehicleRatesSetpointMsg_t		VRatesSp;		  /**< vehicle rates setpoint */
	PX4_VehicleStatusMsg_t				VehicleStatus;	  /**< vehicle status */
} MAC_CurrentValueTable_t;


typedef struct
{
	math::Vector3F att_p;               /**< P gain for angular error */
	math::Vector3F rate_p;    			/**< P gain for angular rate error */
	math::Vector3F rate_i;    			/**< I gain for angular rate error */
	math::Vector3F rate_int_lim;    	/**< integrator state limit for rate loop */
	math::Vector3F rate_d;    			/**< D gain for angular rate error */
	math::Vector3F rate_ff;    			/**< Feedforward gain for desired rates */
	float yaw_ff;						/**< yaw control feed-forward */

	float tpa_breakpoint_p;				/**< Throttle PID Attenuation breakpoint */
	float tpa_breakpoint_i;				/**< Throttle PID Attenuation breakpoint */
	float tpa_breakpoint_d;				/**< Throttle PID Attenuation breakpoint */
	float tpa_rate_p;					/**< Throttle PID Attenuation slope */
	float tpa_rate_i;					/**< Throttle PID Attenuation slope */
	float tpa_rate_d;					/**< Throttle PID Attenuation slope */

	float roll_rate_max;
	float pitch_rate_max;
	float yaw_rate_max;
	float yaw_auto_max;
	math::Vector3F mc_rate_max;    		/**< attitude rate limits in stabilized modes */
	math::Vector3F auto_rate_max;    	/**< attitude rate limits in auto modes */
	math::Vector3F acro_rate_max;    	/**< max attitude rates in acro mode */
	float rattitude_thres;
	MAC_VTOL_Type_t vtol_type;			/**< 0 = Tailsitter, 1 = Tiltrotor, 2 = Standard airframe */
	boolean vtol_opt_recovery_enabled;
	float vtol_wv_yaw_rate_scale;		/**< Scale value [0, 1] for yaw rate setpoint  */

	boolean bat_scale_en;

	int board_rotation;

	float board_offset[3];
} MAC_Params_t;


/**
 **  \brief MAC Operational Data Structure
 */
class MAC
{
public:
    MAC();
    ~MAC();

    /** \brief CFE Event Table */
    CFE_EVS_BinFilter_t EventTbl[MAC_EVT_CNT];

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

    /** \brief Param Table Handle */
    CFE_TBL_Handle_t ParamTblHdl;

    /** \brief Param Table Pointer */
    MAC_ParamTbl_t* ParamTblPtr;

    /** \brief Output Data published at the end of cycle */
    PX4_ActuatorControlsMsg_t m_ActuatorControls0;

    /** \brief Housekeeping Telemetry for downlink */
    MAC_HkTlm_t HkTlm;

    MAC_CurrentValueTable_t CVT;

    math::Vector3F m_AngularRatesPrevious;
    math::Vector3F m_AngularRatesSetpointPrevious;
	math::Vector3F m_AngularRatesSetpoint;
	math::Vector3F m_AngularRatesIntegralError;
	math::Vector3F m_AttControl;




	uint32 m_GyroCount;
	int32 m_SelectedGyro;

	//PX4_McVirtualRatesSetpointMsg_t m_RatesSetpoint;

	boolean m_Actuators0CircuitBreakerEnabled;


	MAC_Params_t m_Params;



    /************************************************************************/
    /** \brief CFS PWM Motor Controller Task (MAC) application entry point
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
    void AppMain(void);

    /************************************************************************/
    /** \brief Initialize the CFS PWM Motor Controller (MAC) application
     **
     **  \par Description
     **       PWM Motor Controller application initialization routine. This
     **       function performs all the required startup steps to
     **       initialize (or restore from CDS) MAC data structures and get
     **       the application registered with the cFE services so it can
     **       begin to receive command messages and send events.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \returns
     **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
     **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
     **  \retstmt Return codes from #MAC_InitEvent               \endcode
     **  \retstmt Return codes from #MAC_InitPipe                \endcode
     **  \retstmt Return codes from #MAC_InitData                \endcode
     **  \retstmt Return codes from #MAC_InitConfigTbl           \endcode
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
     **       cFE Event Services for use by the MAC application.
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
    /** \brief Initialize global variables used by MAC application
     **
     **  \par Description
     **       This function performs the steps required to initialize
     **       the MAC application data.
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
    int32 InitData(void);

    /************************************************************************/
    /** \brief Initialize message pipes
     **
     **  \par Description
     **       This function performs the steps required to setup
     **       initialize the cFE Software Bus message pipes and subscribe to
     **       messages for the MAC application.
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
     **       for the MAC application from the SCH pipe.  This function
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
    /** \brief PWM Motor Controller Task incoming data processing
     **
     **  \par Description
     **       This function processes incoming data subscribed
     **       by MAC application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    osalbool ProcessIncomingData(void);

    /************************************************************************/
    /** \brief PWM Motor Controller Task incoming command processing
     **
     **  \par Description
     **       This function processes incoming commands subscribed
     **       by MAC application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ProcessNewCmds(void);

    /************************************************************************/
    /** \brief PWM Motor Controller Task application commands
     **
     **  \par Description
     **       This function processes command messages
     **       specific to the MAC application
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
    /** \brief Sends MAC housekeeping message
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
    /** \brief Sends the Actuator Output message.
     **
     **  \par Description
     **       This function publishes the actuator output message containing
     **       the commanding values to the motors.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendActuatorControls(void);

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

//private:

    /************************************************************************/
    /** \brief Initialize the MAC configuration tables.
    **
    **  \par Description
    **       This function initializes MAC's configuration tables.  This
    **       includes the PWM and the Mixer configuration table.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \retstmt Return codes from #CFE_TBL_Register          \endcode
    **  \retstmt Return codes from #CFE_TBL_Load              \endcode
    **  \retstmt Return codes from #MAC_AcquireConfigPointers \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  InitConfigTbl(void);

    /************************************************************************/
    /** \brief Obtain MAC configuration tables data pointers.
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

    void DisplayInputs(void);

    void DisplayOutputs(void);

public:
    /************************************************************************/
    /** \brief Validate MAC PWM configuration table
    **
    **  \par Description
    **       This function validates MAC's PWM configuration table
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
    static int32  ValidateParamTbl(void*);

//private:
    void RunController(void);
    void UpdateParams(void);

	/**
	 * Attitude controller.
	 */
	void ControlAttitude(float dt);

	/**
	 * Attitude rates controller.
	 */
	void ControlAttitudeRates(float dt);

	math::Vector3F PidAttenuations(float tpa_breakpoint, float tpa_rate);

//private:
	float m_ThrustSp;		/**< thrust setpoint */

};


extern MAC oMAC;

#ifdef __cplusplus
}
#endif 

#endif /* MAC_APP_H */

/************************/
/*  End of File Comment */
/************************/
