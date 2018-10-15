/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "vm_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static OS_USED CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
    **    ObjName - variable name of config table, e.g., CI_ConfigDefTbl[]
    **    TblName - app's table name, e.g., CI.CONFIG_TBL, where CI is the same app name
    **              used in cfe_es_startup.scr, and CI_defConfigTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "VM_ConfigTbl", "VM.CONFIG_TBL", "VM default config table",
    "vm_config.tbl", (sizeof(VM_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default ULR config table data */
VM_ConfigTbl_t VM_ConfigTbl =
{
        /** \brief Auto-start script index
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 99999, default 0.
         */
        6001,
        /** \brief RC control input mode
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 2, default 0.
         */
        2,
        /** \brief Arm switch is only a button
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 1, default 0.
         */
        0,
        /** \brief Allow arming without GPS
         *
         *  \par Limits:
         *       default 1.
         */
        1,
        /** \brief Require valid mission to arm
         *
         *  \par Limits:
         *       default 0.
         */
        0,
        /** \brief RC input arm/disarm command duration
         *
         *  \par Limits:
         *       Min > Max (incr.) 100 > 1500, default 1000.
         */
        1000,
        /** \brief Airframe type
         *      0: Generic micro air vehicle
         *      1: Fixed wing aircraft
         *      2: Quadrotor
         *      3: Coaxial helicopter
         *      4: Normal helicopter with tail rotor
         *      5: Ground installation
         *      6: Operator control unit / ground control station
         *      7: Airship, controlled
         *      8: Free balloon, uncontrolled
         *      9: Rocket
         *      10: Ground rover
         *      11: Surface vessel, boat, ship
         *      12: Submarine
         *      13: Hexarotor
         *      14: Octorotor
         *      15: Tricopter
         *      16: Flapping wing
         *      17: Kite
         *      18: Onboard companion controller
         *      19: Two-rotor VTOL using control surfaces in vertical operation in addition. Tailsitter.
         *      20: Quad-rotor VTOL using a V-shaped quad config in vertical operation. Tailsitter.
         *      21: Tiltrotor VTOL
         *      22: VTOL reserved 2
         *      23: VTOL reserved 3
         *      24: VTOL reserved 4
         *      25: VTOL reserved 5
         *      26: Onboard gimbal
         *      27: Onboard ADSB peripheral
         *
         *  \par Limits:
         *       Min > Max (incr.) 1 > 27, default 2.
         */
        13,
        /** \brief System ID
         *
         *  \par Limits:
         *       Min > Max (incr.) 1 > 250, default 1.
         */
        1,
        /** \brief Component ID
         *
         *  \par Limits:
         *       Min > Max (incr.) 1 > 250, default 1.
         */
        1,
        /** \brief Circuit breaker for power supply check
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 894281, default 0.
         */
        0,
        /** \brief Circuit breaker for USB link check
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 197848, default 0.
         */
        0,
        /** \brief Circuit breaker for airspeed sensor
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 162128, default 0.
         */
        0,
        /** \brief Circuit breaker for engine failure detection
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 284953, default 0.
         */
        284953,
        /** \brief Circuit breaker for GPS failure detection
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 240024, default 0.
         */
        0,
        /** \brief Circuit breaker for flight termination
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 121212, default 121212.
         */
        121212,
        /** \brief Circuit breaker for position error check
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 201607, default 0.
         */
        0,
        /** \brief Set data link loss failsafe mode
         *
         *  \par Limits:
         *       default 0.
         */
        2,
        /** \brief Set RC loss failsafe mode
         *      0: Disabled
         *      1: Loiter
         *      2: Return to Land
         *      3: Land at current position
         *      4: RC Auto Recovery (CASA Outback Challenge rules)
         *      5: Terminate
         *      6: Lockdown
         *
         *  \par Limits:
         *       default 2.
         */
        2,
        /** \brief Datalink loss time threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 5 > 300 , default 10.
         */
        10,
        /** \brief RC loss time threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 35, default 0.5.
         */
        0.5,
        /** \brief RC stick override threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 5 > 40, default 12.0.
         */
        12.0,
        /** \brief Enable RC stick override of auto modes
         *
         *  \par Limits:
         *       default 0.
         */
        0,
        /** \brief Datalink regain time threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 3 , default 0.
         */
        0,
        /** \brief Engine Failure Throttle Threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.0 > 1.0 , default 0.5.
         */
        0.5,
        /** \brief Engine Failure Current/Throttle Threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.0 > 50.0, default 5.0.
         */
        0.5,
        /** \brief Engine Failure Time Threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.0 > 60.0, default 10.0.
         */
        10,
        /** \brief Geofence violation action
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 4, default 1.
         */
        1,
        /** \brief Time-out for auto disarm after landing
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 20, default 0.
         */
        3,
        /** \brief Battery failsafe mode
         *
         *  \par Limits:
         *       default 0.
         */
        1,
        /** \brief Time-out to wait when offboard connection is lost before triggering offboard lost action
         *
         *  \par Limits:
         *       Min > Max (incr.) 0 > 60, default 0.0.
         */
        0.0,
        /** \brief Set offboard loss failsafe mode
         *      0: Land at current position
         *      1: Loiter
         *      2: Return to Land
         *
         *  \par Limits:
         *       default 0.
         */
        0,
        /** \brief Set offboard loss failsafe mode when RC is available
         *      0: Position control
         *      1: Altitude control
         *      2: Manual
         *      3: Return to Land
         *      4: Land at current position
         *      5: Loiter
         *
         *  \par Limits:
         *       default 0.
         */
        0,
        /** \brief Home set horizontal threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 2 > 15, default 5.0.
         */
        5.0,
        /** \brief Home set vertical threshold
         *
         *  \par Limits:
         *       Min > Max (incr.) 5 > 25, default 10.0.
         */
        10.0,
        /** \brief First flightmode slot (1000-1160)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Second flightmode slot (1160-1320)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Third flightmode slot (1320-1480)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Fourth flightmode slot (1480-1640)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Fifth flightmode slot (1640-1800)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Sixth flightmode slot (1800-2000)
         *      -1: Unassigned
         *      0: Manual
         *      1: Altitude
         *      2: Position
         *      3: Mission
         *      4: Hold
         *      5: Return
         *      6: Acro
         *      7: Offboard
         *      8: Stabilized
         *      9: Rattitude
         *      10: Takeoff
         *      11: Land
         *      12: Follow Me
         *
         *  \par Limits:
         *       default -1.
         */
        -1,
        /** \brief Maximum EKF position innovation test ratio that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.1 > 1.0, default 0.5.
         */
        0.5,
        /** \brief Maximum EKF velocity innovation test ratio that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.1 > 1.0, default 0.5.
         */
        0.5,
        /** \brief Maximum EKF height innovation test ratio that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.1 > 1.0, default 1.0.
         */
        1.0,
        /** \brief Maximum EKF yaw innovation test ratio that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.1 > 1.0, default 0.5.
         */
        0.5,
        /** \brief Maximum value of EKF gyro delta angle bias estimate that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.001 > 0.01, default 2.4e-3 .
         */
        0.0050,
        /** \brief Maximum value of EKF gyro delta angle bias estimate that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.0001 > 0.0017, default 8.7e-4 .
         */
        0.0009,
        /** \brief Maximum accelerometer inconsistency between IMU units that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.1 > 1.0, default 0.7.
         */
        0.7,
        /** \brief Maximum rate gyro inconsistency between IMU units that will allow arming
         *
         *  \par Limits:
         *       Min > Max (incr.) 0.02 > 0.3, default 0.25.
         */
        0.2,
        /** \brief Position control navigation loss response
         *
         *  \par Limits:
         *       default 0.
         */
        0,
        /** \brief Padding for home position altitude message, to avoid hover above ground.
         *
         *  \par Limits:
         *       default 1.0.
         */
        1.0


};

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/

/*=======================================================================================
** End of file vm_config.c
**=====================================================================================*/
    
