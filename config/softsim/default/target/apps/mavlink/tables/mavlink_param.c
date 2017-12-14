/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "mavlink_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
    **    ObjName - variable name of config table, e.g., MAVLINK_ConfigDefTbl[]
    **    TblName - app's table name, e.g., MAVLINK.PARAM_TBL, where MAVLINK is the same app name
    **              used in cfe_es_startup.scr, and MAVLINK_defParamTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "MAVLINK_ParamTbl", "MAVLINK.PARAM_TBL", "MAVLINK default param table",
    "mavlink_param.tbl", (sizeof(MAVLINK_ParamTblEntry_t) * MAVLINK_PARAM_TABLE_MAX_ENTRIES)
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default MAVLINK config table data */
MAVLINK_ParamTblEntry_t MAVLINK_ParamTbl[MAVLINK_PARAM_TABLE_MAX_ENTRIES] =
{
	/* Table ID */
	1,
	{
		/* Default Parameters */
        {1, 1, "DEFAULT_PARAM", 0.0, 9}
/*		{0x1806, 2, STEP_2, UNAUTHORIZED, 0, LOG}, // CFE ES Proc/Power Reset*/
/*		{0x1c29, 0, STEP_1, UNAUTHORIZED, 0, LOG}, // EA Noop*/
/*		{0x1c29, 1, STEP_2, UNAUTHORIZED, 0, LOG}  // EA Reset*/
	}
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
** End of file mavlink_config.c
**=====================================================================================*/
    
