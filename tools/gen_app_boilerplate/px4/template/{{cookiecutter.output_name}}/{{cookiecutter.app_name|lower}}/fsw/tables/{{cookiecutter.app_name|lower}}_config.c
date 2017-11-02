/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "{{cookiecutter.app_name|lower}}_tbldefs.h"

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

    "{{cookiecutter.app_name}}_ConfigTbl", "{{cookiecutter.app_name}}.CONFIG_TBL", "{{cookiecutter.app_name}} default config table",
    "{{cookiecutter.app_name|lower}}_config.tbl", (sizeof({{cookiecutter.app_name}}_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default {{cookiecutter.app_name}} config table data */
{{cookiecutter.app_name}}_ConfigTbl_t {{cookiecutter.app_name}}_ConfigTbl =
{
	/* TODO:  Define table. */
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
** End of file {{cookiecutter.app_name|lower}}_config.c
**=====================================================================================*/
    
