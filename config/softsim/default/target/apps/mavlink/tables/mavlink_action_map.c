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
    **              used in cfe_es_startup.scr, and MAVLINK_ActionMapTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "MAVLINK_ActionMapTbl", "MAVLINK.ACTION_MAP", "MAVLINK default action map table",
    "mavlink_action.tbl", (sizeof(MAVLINK_ActionMapTblEntry_t) * MAVLINK_ACTION_MAP_ENTRIES)
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default MAVLINK config table data */
MAVLINK_ActionMapTblEntry_t MAVLINK_ActionMapTbl[MAVLINK_ACTION_MAP_ENTRIES] =
{
	    {0 , ACTION_HANDLE},
	    {20 , ACTION_HANDLE},
	    {21 , ACTION_HANDLE},
	    {23 , ACTION_HANDLE},
	    {43 , ACTION_HANDLE},
	    {47 , ACTION_HANDLE},
	    {76 , ACTION_HANDLE}
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
    
