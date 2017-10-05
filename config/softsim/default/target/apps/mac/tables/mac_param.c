/*
** Pragmas
*/

/*
** Include Files
*/
#include <mixer/MixerTables.h>
#include "cfe_tbl_filedef.h"
#include "mac_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
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

    "MAC_ParamTbl", "MAC.PARAM_TBL", "MAC default param table",
    "mac_param.tbl", (sizeof(MAC_ParamTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default MAC config table data */
MAC_ParamTbl_t MAC_ParamTbl =
{
	{1.0, 1.0, 1.0},						/**< P gain for angular error */
	{1.0, 1.0, 1.0},						/**< P gain for angular rate error */
	{1.0, 1.0, 1.0},						/**< I gain for angular rate error */
	{1.0, 1.0, 1.0},						/**< integrator state limit for rate loop */
	{1.0, 1.0, 1.0},						/**< D gain for angular rate error */
	{1.0, 1.0, 1.0},						/**< Feedforward gain for desired rates */
	1.0,									/**< yaw control feed-forward */

	1.0,									/**< Throttle PID Attenuation breakpoint */
	1.0,									/**< Throttle PID Attenuation breakpoint */
	1.0,									/**< Throttle PID Attenuation breakpoint */
	1.0,									/**< Throttle PID Attenuation slope */
	1.0,									/**< Throttle PID Attenuation slope */
	1.0,									/**< Throttle PID Attenuation slope */

	1.0,                                    /**< Roll rate maximum */
	1.0,                                    /**< Pitch rate maximum */
	1.0,                                    /**< Yaw rate maximum */
	1.0,                                    /**< Yaw auto maximum */
	{1.0, 1.0, 1.0},						/**< attitude rate limits in stabilized modes */
	{1.0, 1.0, 1.0},						/**< attitude rate limits in auto modes */
	{1.0, 1.0, 1.0},						/**< max attitude rates in acro mode */
	1.0,						/**< Rattitude threshold
	MAC_STANDARD,                           /**< 0 = Tailsitter, 1 = Tiltrotor, 2 = Standard airframe */
	FALSE,                                  /**< VTOL opt recovery enabled
	1.0,                                    /**< Scale value [0, 1] for yaw rate setpoint  */

	TRUE,                                   /**< Battery scale enabled */

	0,                                      /**< Board rotation */

	{1.0, 1.0, 1.0}                        /**< Board offset */
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
** End of file ci_config.c
**=====================================================================================*/
    
