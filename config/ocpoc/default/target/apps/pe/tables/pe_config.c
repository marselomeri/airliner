/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "pe_tbldefs.h"

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

    "PE_ConfigTbl", "PE.CONFIG_TBL", "PE default config table",
    "pe_config.tbl", (sizeof(PE_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default ULR config table data */
PE_ConfigTbl_t PE_ConfigTbl =
{
	/* TODO:  Define table. */
    //FUSION
    145,
	//VXY_PUB_THRESH
    .3f,
	//Z_PUB_THRESH
    1.0f,
	//ACCEL_XY_STDDEV
    .012f,
	//ACCEL_Z_STDDEV
    .02f,
	//BARO_STDDEV
    3.0f,
	//GPS_DELAY
    .29f,
	//GPS_XY_STDDEV
    1.0f,
	//GPS_Z_STDDEV
    3.0f,
	//GPS_VXY_STDDEV
    .25f,
	//GPS_VZ_STDDEV
    .25f,
	//GPS_EPH_MAX
    3.0f,
	//GPS_EPV_MAX
    5.0f,
	//LAND_Z_STDDEV
    .03f,
	//LAND_VXY_STDDEV
    .05f,
	//PN_P_NOISE_DENSITY
    .1f,
	//PN_V_NOISE_DENSITY
    .1f,
	//PN_B_NOISE_DENSITY
    .001f,
	//PN_T_NOISE_DENSITY
    .001f,
	//T_MAX_GRADE
    0.0f,
	//FAKE_ORIGIN
    1,
	//INIT_ORIGIN_LAT
    29.562144f,
	//INIT_ORIGIN_LON
    -95.144554,
    //ULR_STDDEV
    .05f,
    //ULR_OFF_Z
    0.15f
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
** End of file pe_config.c
**=====================================================================================*/
    
