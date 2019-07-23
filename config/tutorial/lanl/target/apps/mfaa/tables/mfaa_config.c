
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe_tbl_filedef.h"
#include "mfaa_tbldefs.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Definitions
*************************************************************************/

/**
** \brief The cFE MFAA config table definition.
**
** Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
**    ObjName - variable name of config table, e.g., MFAA_ConfigDefTbl[]
**    TblName - app's table name, e.g., MFAA.CONFIG_TBL, where MFAA is the same app name
**              used in cfe_es_startup.scr, and MFAA_defConfigTbl is the same table
**              name passed in to CFE_TBL_Register()
**    Desc - description of table in string format
**    TgtFileName[20] - table file name, compiled as .tbl file extension
**    ObjSize - size of the entire table
**
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "MFAA_ConfigTbl", "MFAA.CONFIG_TBL", "MFAA default config table",
    "mfaa_config.tbl", (sizeof(MFAA_ConfigTblEntry_t) * MFAA_CONFIG_TABLE_MAX_ENTRIES)
};

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/**
**  \brief Default MFAA config table data
*/
MFAA_ConfigTblEntry_t MFAA_ConfigTbl[MFAA_CONFIG_TABLE_MAX_ENTRIES] =
{
    /* Entry 1 */
    {
        1.0,
		0.0
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
    
