/****************************************************************************
*
*   Copyright (c) 2020 Windhover Labs, L.L.C. All rights reserved.
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

#ifndef ICM20689_APP_H
#define ICM20689_APP_H

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
#include <math.h>
#include "icm20689_platform_cfg.h"
#include "icm20689_mission_cfg.h"
#include "icm20689_perfids.h"
#include "icm20689_msgids.h"
#include "icm20689_msg.h"
#include "icm20689_events.h"
#include "icm20689_tbldefs.h"
#include "px4_msgs.h"
#include "math/filters/LowPassFilter2p.hpp"
#include "math/Integrator.hpp"

/************************************************************************
 ** Local Defines
 *************************************************************************/

/************************************************************************
 ** Local Structure Definitions
 *************************************************************************/
/**
 * \brief application status
 */
typedef enum
{
    /*! App status uninitialized */
    ICM20689_UNINITIALIZED = 0,
    /*! App status uninitialized */
    ICM20689_INITIALIZED   = 1
} ICM20689_Status_t;


/**
 * \brief application parameters
 */
typedef struct
{
    float AccXScale;
    float AccYScale;
    float AccZScale;
    float AccXOffset;
    float AccYOffset;
    float AccZOffset;
    float GyroXScale;
    float GyroYScale;
    float GyroZScale;
    float GyroXOffset;
    float GyroYOffset;
    float GyroZOffset;
} ICM20689_Params_t;


/**
 **  \brief ICM20689 Application Class
 */
class ICM20689
{
public:
    ICM20689();
    ~ICM20689();

    /**\brief Scheduling Pipe ID */
    CFE_SB_PipeId_t SchPipeId;

    /** \brief Command Pipe ID */
    CFE_SB_PipeId_t CmdPipeId;

    /** \brief Param Pipe ID */
    CFE_SB_PipeId_t ParamPipeId;

    /* Task-related */

    /** \brief Task Run Status */
    uint32 uiRunStatus;

   /* Config table-related */

    /** \brief Config Table Handle */
    CFE_TBL_Handle_t ConfigTblHdl;

    /** \brief Config Table Pointer */
    ICM20689_ConfigTbl_t* ConfigTblPtr;

    /** \brief Output Data published at the end of cycle */
    PX4_SensorAccelMsg_t SensorAccel;
    PX4_SensorGyroMsg_t SensorGyro;

    /** \brief Housekeeping Telemetry for downlink */
    ICM20689_HkTlm_t HkTlm;

    /** \brief Diagnostic data for downlink */
    ICM20689_DiagPacket_t Diag;
    
    /* Params related */
    /** \brief params from the config table */
    ICM20689_Params_t m_Params;
    
    /************************************************************************/
    /** \brief ICM20689 (ICM20689) application entry point
     **
     **  \par Description
     **       ICM20689 Task application entry point.  This function
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
    /** \brief Initialize the ICM20689 (ICM20689) application
     **
     **  \par Description
     **       ICM20689 application initialization routine. This
     **       function performs all the required startup steps to
     **       initialize (or restore from CDS) ICM20689 data structures and get
     **       the application registered with the cFE services so it can
     **       begin to receive command messages and send events.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     **  \returns
     **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
     **  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
     **  \retstmt Return codes from #ICM20689_InitEvent          \endcode
     **  \retstmt Return codes from #ICM20689_InitPipe           \endcode
     **  \retstmt Return codes from #ICM20689_InitData           \endcode
     **  \retstmt Return codes from #ICM20689_InitConfigTbl      \endcode
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
     **       cFE Event Services for use by the ICM20689 application.
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
    /** \brief Initialize global variables used by ICM20689 application
     **
     **  \par Description
     **       This function performs the steps required to initialize
     **       the ICM20689 application data.
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
     **       messages for the ICM20689 application.
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
     **       for the ICM20689 application from the SCH pipe.  This function
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
    /** \brief ICM20689 Task incoming command processing
     **
     **  \par Description
     **       This function processes incoming commands subscribed
     **       by ICM20689 application
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ProcessCmdPipe(void);

    /************************************************************************/
    /** \brief ICM20689 Task application commands
     **
     **  \par Description
     **       This function processes command messages
     **       specific to the ICM20689 application
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
    /** \brief Sends ICM20689 housekeeping message
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
    /** \brief Sends the SensorAccel message.
     **
     **  \par Description
     **       This function publishes the SensorAccel message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendSensorAccel(void);

    /************************************************************************/
    /** \brief Sends the SensorGyro message.
     **
     **  \par Description
     **       This function publishes the SensorGyro message containing
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendSensorGyro(void);
    
    /************************************************************************/
    /** \brief Sends a diagnostic message.
     **
     **  \par Description
     **       This function publishes the diagnostic message.
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void SendDiag(void);

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
    /** \brief Read from the ICM20689 and send PX4 messages.
     **
     **  \par Description
     **       This function publishes to the associated PX4 messages.
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **
     *************************************************************************/
    void ReadDevice(void);

    /** \brief Validate device IDs.
     **
     **  \par Description
     **       This function validates the device IDs of the IMU and Mag.
     **       <TODO>
     **
     **  \par Assumptions, External Events, and Notes:
     **       None
     **  \returns
     **  TRUE if the device IDs are asexpectated, FALSE if they are not.
     **  \endreturns
     **
     *************************************************************************/
    boolean ValidateDevice(void);

private:
    /************************************************************************/
    /** \brief Initialize the GPS configuration tables.
    **
    **  \par Description
    **       This function initializes GPS's configuration tables.  This
    **       includes <TODO>.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \retstmt Return codes from #CFE_TBL_Register          \endcode
    **  \retstmt Return codes from #CFE_TBL_Load              \endcode
    **  \retstmt Return codes from #GPS_AcquireConfigPointers \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32  InitConfigTbl(void);

    /************************************************************************/
    /** \brief Obtain GPS configuration tables data pointers.
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

    math::LowPassFilter2p   _accel_filter_x;
    math::LowPassFilter2p   _accel_filter_y;
    math::LowPassFilter2p   _accel_filter_z;
    math::LowPassFilter2p   _gyro_filter_x;
    math::LowPassFilter2p   _gyro_filter_y;
    math::LowPassFilter2p   _gyro_filter_z;
    Integrator              _accel_int;
    Integrator              _gyro_int;

public:
    /************************************************************************/
    /** \brief Validate configuration table
    **
    **  \par Description
    **       This function validates GPS's configuration table
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
    
    /************************************************************************/
    /** \brief Update parameters from the configuration table.
     **
     **  \par Description
     **       This function updates the current paramamters from the 
     **       currently loaded configuration table.
     **
     *************************************************************************/
    void UpdateParamsFromTable(void);

    /************************************************************************/
    /** \brief Set sensor calibation values
    **
    **  \par Description
    **       Updates the sensor calibration table with passed values.
    **
    **  \par Assumptions, External Events, and Notes:
    **       None
    **
    **  \param [in]   CalibrationMsgPtr   A pointer to the calibration messsage
    **
    **  \returns
    **  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
    **  \endreturns
    **
    *************************************************************************/
    int32 UpdateCalibrationValues(ICM20689_SetCalibrationCmd_t* CalibrationMsgPtr);

};


/************************************************************************/
/** \brief Cleanup prior to exit
**
**  \par Description
**       This function handles any necessary cleanup prior
**       to application exit.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void ICM20689_CleanupCallback(void);


#ifdef __cplusplus
}
#endif 

#endif /* ICM20689_APP_H */

/************************/
/*  End of File Comment */
/************************/
