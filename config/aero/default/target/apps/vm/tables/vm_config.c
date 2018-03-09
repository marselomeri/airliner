/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "vm_tbldefs.h"

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

    "VM_ConfigTbl", "VM.CONFIG_TBL", "VM default config table",
    "vm_config.tbl", (sizeof(VM_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default ULR config table data */
VM_ConfigTbl_t VM_ConfigTbl =
{
		6001,
		2,
		0,
		1,
		0,
		1000,
		13,
		1,
		1,
		0,
		0
		0,
		284953,
		0,
		121212,
		0,
		2,
		2,
		10,
		0.5,
		12.0,
		0,
		0,
		0.5,
		0.5,
		10.0,
		1,
		3,
		1,
		0.0,
		0,
		0,
		5.0,
		10.0,
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		0.5,
		0.5,
		1.0,
		0.5,
		0.0050,
		0.0009,
		0.7,
		0.2,
		0

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
** End of file vm_config.c
**=====================================================================================*/
    
