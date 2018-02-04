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

#ifndef QAE_APP_H
#define QAE_APP_H

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

#include "qae_platform_cfg.h"
#include "qae_mission_cfg.h"
#include "qae_perfids.h"
#include "qae_msgids.h"
#include "qae_msg.h"
#include "qae_events.h"
#include "qae_tbldefs.h"
#include "px4_msgs.h"

#include "Quaternion.hpp"
#include "Vector3F.hpp"
#include "Matrix3F3.hpp"

//using math::Quaternion;

/************************************************************************
 ** Local Defines
 *************************************************************************/
#define QAE_DELTA_TIME_MAX 0.02f

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/
 
/**
 * \brief application status
 */
typedef enum
{
    /*! App status uninitialized */
    QAE_UNINITIALIZED      = 0,
    /*! App status uninitialized */
    QAE_INITIALIZED        = 1,
    /*! App status sensor data received */
    QAE_SENSOR_DATA_RCVD   = 2
} QAE_Status_t;


/**
 * \brief message current value table
 */
typedef struct
{
    PX4_SensorCombinedMsg_t        SensorCombinedMsg;
    uint64                         LastSensorCombinedTime;
    PX4_VehicleGlobalPositionMsg_t VehicleGlobalPositionMsg;
    uint64                         LastGlobalPositionTime;
} QAE_CurrentValueTable_t;


/**
 * \brief application parameters
 */
typedef struct
{
    /** \brief magnetometer declination */
    float mag_declination;
    /** \brief magnetometer automatic GPS declination compensation */
    boolean mag_declination_auto;
    /** \brief acceleration compensation based on GPS velocity */
    boolean acc_compensation;
    
} QAE_Params_t;


/**
 **  \brief QAE Application Class
 */
class QAE
{
public:
    QAE();
    ~QAE();

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
    QAE_ConfigTbl_t* ConfigTblPtr;
    /** \brief Output Data published at the end of cycle */
    PX4_VehicleAttitudeMsg_t VehicleAttitudeMsg;
    PX4_ControlStateMsg_t ControlStateMsg;

    /** \brief Housekeeping Telemetry for downlink */
    QAE_HkTlm_t HkTlm;
    /** \brief Current Value Table */
    QAE_CurrentValueTable_t CVT;
    /** \brief QAE parameters Table */
    QAE_Params_t m_Params;
    /** \brief The current quaternion */
    math::Quaternion m_Quaternion;
    /** \brief The current gyro values */
    math::Vector3F m_gyro;
    /** \brief The current accel values */
    math::Vector3F m_accel;
    /** \brief The current mag values */
    math::Vector3F m_mag;
    /** \brief The last velocity value */
    math::Vector3F m_LastVelocity;
    /** The last velocity timestamp */
    uint64         m_LastVelocityTime;
    /** \brief The current pos acc value */
    math::Vector3F m_PositionAcc;
    /************************************************************************/
    /** \brief Q Attitude Estimator (QAE) application entry point
     **
     **  \par Description
     **       Q Attitude Estimator Task application entry point.  This function
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
    /** \brief Initialize the Q Attitude Estimator (QAE) application
     **
     **  \par Description
     **       Q Attitude Estimator application initialization routine. This
     **       function performs all the required startup steps to
     **       initialize (or restore from CDS) QAE data structures and get
     **       the application registered with the cFE services so it can
     **       begin to receive command messages and send events.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \returns
     **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
     **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
     **  \retstmt Return codes from #QAE_InitEvent               \endcode
     **  \retstmt Return codes from #QAE_InitPipe                \endcode
     **  \retstmt Return codes from #QAE_InitData                \endcode
     **  \retstmt Return codes from #QAE_InitConfigTbl           \endcode
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
     **       cFE Event Services for use by the QAE application.
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
    /** \brief Initialize global variables used by QAE application
     **
     **  \par Description
     **       This function performs the steps required to initialize
     **       the QAE application data.
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
     **       messages for the QAE application.
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
     **       for the QAE application from the SCH pipe.  This function
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
    /** \brief Q Attitude Estimator Task incoming command processing
     **
     **  \par Description
     **       This function processes incoming commands subscribed
     **       by QAE application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ProcessCmdPipe(void);

    /************************************************************************/
    /** \brief Q Attitude Estimator Task application commands
     **
     **  \par Description
     **       This function processes command messages
     **       specific to the QAE application
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
    /** \brief Sends QAE housekeeping message
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
    /** \brief Sends the VehicleAttitudeMsg message.
     **
     **  \par Description
     **       This function publishes the VehicleAttitudeMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendVehicleAttitudeMsg(void);
    /************************************************************************/
    /** \brief Sends the ControlStateMsg message.
     **
     **  \par Description
     **       This function publishes the ControlStateMsg message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendControlStateMsg(void);
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
    
    void EstimateAttitude(void);
    boolean InitEstimateAttitude(void);
    boolean UpdateEstimateAttitude(float dt);
    void UpdateMagDeclination(const float new_declination);


private:
    /************************************************************************/
    /** \brief Initialize the QAE configuration tables.
    **
    **  \par Description
    **       This function initializes QAE's configuration tables.  This
    **       includes <TODO>.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \retstmt Return codes from #CFE_TBL_Register          \endcode
    **  \retstmt Return codes from #CFE_TBL_Load              \endcode
    **  \retstmt Return codes from #QAE_AcquireConfigPointers \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  InitConfigTbl(void);

    /************************************************************************/
    /** \brief Obtain QAE configuration tables data pointers.
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
    /** \brief Validate QAE configuration table
    **
    **  \par Description
    **       This function validates QAE's configuration table
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

#endif /* QAE_APP_H */

/************************/
/*  End of File Comment */
/************************/
