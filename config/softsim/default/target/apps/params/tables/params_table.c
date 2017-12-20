/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "params_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
    **    ObjName - variable name of config table, e.g., PARAMS_ConfigDefTbl[]
    **    TblName - app's table name, e.g., PARAMS.PARAM_TBL, where PARAMS is the same app name
    **              used in cfe_es_startup.scr, and PARAMS_defParamTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "PARAMS_ParamTbl", "PARAMS.PARAM_TBL", "PARAMS default param table",
    "params_table.tbl", (sizeof(PARAMS_ParamsTblEntry_t) * PARAMS_PARAM_TABLE_MAX_ENTRIES)
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default PARAMS config table data */
PARAMS_ParamsTblEntry_t PARAMS_ParamTbl[PARAMS_PARAM_TABLE_MAX_ENTRIES] =
{
	/* Table ID */
	1,
	{
		/* Default Parameters */
        {1, 1, 1, "DEFAULT_PARAM", 0.0, 9}
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
** End of file params_config.c
**=====================================================================================*/
    
