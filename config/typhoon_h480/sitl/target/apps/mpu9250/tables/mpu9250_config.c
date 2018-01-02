/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "mpu9250_tbldefs.h"

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

    "MPU9250_ConfigTbl", "MPU9250.CONFIG_TBL", "MPU9250 default config table",
    "mpu9250_config.tbl", (sizeof(MPU9250_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default MPU9250 config table data */
MPU9250_ConfigTbl_t MPU9250_ConfigTbl =
{
	/* TODO:  Define table. */
    1.0,    //AccDivider
    1.0,    //GyroDivider
    1.0,    //AccXScale
    1.0,    //AccYScale
    1.0,    //AccZScale
    0.0,    //AccXOffset
    0.0,    //AccYOffset
    0.0,    //AccZOffset
    1.0,    //GyroXScale
    1.0,    //GyroYScale
    1.0,    //GyroZScale
    0.0,    //GyroXOffset
    0.0,    //GyroYOffset
    0.0,    //GyroZOffset
    1.0,    //MagXScale
    1.0,    //MagYScale
    1.0,    //MagZScale
    0.0,    //MagXOffset
    0.0,    //MagYOffset
    0.0,    //MagZOffset
    0.0,    //MagXAdj
    0.0,    //MagYAdj
    0.0,    //MagZAdj
    0.0,    //RoomTempOffset
    361.0f, //TempSensitivity;
    MPU9250_ACC_SCALE, //AccScale
    MPU9250_GYRO_SCALE, //GyroScale
    (MPU9250_ACC_SCALE * MPU9250_ONE_G), //AccRange
    MPU9250_2000_DEG_S, //GyroRange
    MPU9250_ONE_G, //AccUnit
    MPU9250_RADIANS_PER_DEGREE //GyroUnit
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
** End of file mpu9250_config.c
**=====================================================================================*/
    
