
/*
** Pragmas
*/

/*
** Include Files
*/
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

    "MAC_PwmCfgTbl", "MAC.PWMCFG_TBL", "MAC default mac config table",
    "mac_pwmcfg.tbl", (sizeof(MAC_PwmConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default CI config table data */
MAC_PwmConfigTbl_t MAC_PwmCfgTbl =
{
    900,  /* PwmDisarmed */
    1000, /* PwmMin      */
    2000  /* PwmMax      */
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
    
