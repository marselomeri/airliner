
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe_tbl_filedef.h"
#include "mavlink_tbldefs.h"
#include "mavlink.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Definitions
*************************************************************************/

/**
** \brief The cFE MAVLINK config table definition.
**
** Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
**    ObjName - variable name of config table, e.g., MAVLINK_ConfigDefTbl[]
**    TblName - app's table name, e.g., MAVLINK.CONFIG_TBL, where MAVLINK is the same app name
**              used in cfe_es_startup.scr, and MAVLINK_defConfigTbl is the same table
**              name passed in to CFE_TBL_Register()
**    Desc - description of table in string format
**    TgtFileName[20] - table file name, compiled as .tbl file extension
**    ObjSize - size of the entire table
**
*/
static OS_USED CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "MAVLINK_ConfigTbl", "MAVLINK.ACTION_MAP", "MAVLINK default config table",
    "mavlink_action.tbl", (sizeof(MAVLINK_ActionMapTbl_t))
};

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/**
**  \brief Default MAVLINK config table data
*/
MAVLINK_ActionMapTbl_t MAVLINK_ConfigTbl =
{
    {
	    {MAVLINK_MSG_ID_HEARTBEAT, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_PARAM_REQUEST_READ, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_PARAM_REQUEST_LIST, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_PARAM_SET, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_MISSION_REQUEST_LIST, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_MISSION_ACK, ACTION_HANDLE},
	    {MAVLINK_MSG_ID_COMMAND_LONG, ACTION_PASSTHRU}
    }
};

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/

/************************************************************************
** Function Definitions
*************************************************************************/

/************************/
/*  End of File Comment */
/************************/
    
