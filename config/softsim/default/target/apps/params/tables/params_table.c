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
        {1, {"TEST_PARAM", 1.0, 9, 1, 1}},
        {1, {"TEST_PARAM2", 2.0, 9, 1, 1}},
        {1, {"TEST_PARAM3", 3.0, 9, 1, 1}},
        {1, {"TEST_PARAM4", 4.0, 9, 1, 1}},
        {1, {"TEST_PARAM5", 5.0, 9, 1, 1}},
        {1, {"TEST_PARAM6", 6.0, 9, 1, 1}},
        {1, {"TEST_PARAM7", 7.0, 9, 1, 1}},
        {1, {"TEST_PARAM8", 8.0, 9, 1, 1}},
        {1, {"TEST_PARAM9", 9.0, 9, 1, 1}},
        {1, {"TEST_PARAM10", 10.0, 9, 1, 1}},
        {1, {"TEST_PARAM11", 11.0, 9, 1, 1}},
        {1, {"TEST_PARAM12", 12.0, 9, 1, 1}},
        {1, {"TEST_PARAM13", 13.0, 9, 1, 1}},
        {1, {"TEST_PARAM14", 14.0, 9, 1, 1}},
        {1, {"TEST_PARAM15", 15.0, 9, 1, 1}},
        {0, {"", 0.0, 0, 1, 1}},
        {0, {"", 0.0, 0, 1, 1}},
        {0, {"", 0.0, 0, 1, 1}},
        {0, {"", 0.0, 0, 1, 1}},
        {0, {"", 0.0, 0, 1, 1}},



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
    
