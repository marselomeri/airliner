
#include "{{cookiecutter.app_name|lower}}_test_utils.h"

#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_tbl_hooks.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"
#include "ut_osapi_stubs.h"
#include "ut_osfileapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_evs_stubs.h"

#include <time.h>

/*
 * Config table for testing
 */
{{cookiecutter.app_name}}_ConfigTblEntry_t {{cookiecutter.app_name}}_configtable = {
        1 /* iParam*/
};

/*
 * Function Definitions
 */

void {{cookiecutter.app_name}}_Test_Setup(void)
{
    /* initialize test environment to default state for every test */

    CFE_PSP_MemSet(&{{cookiecutter.app_name}}_AppData, 0x00, sizeof({{cookiecutter.app_name}}_AppData_t));

    Ut_CFE_EVS_Reset();
    Ut_CFE_FS_Reset();
    Ut_CFE_TIME_Reset();
    Ut_CFE_TBL_Reset();
    Ut_CFE_SB_Reset();
    Ut_CFE_ES_Reset();
    Ut_OSAPI_Reset();
    Ut_OSFILEAPI_Reset();

    Ut_CFE_TBL_AddTable({{cookiecutter.app_name}}_CONFIG_TABLE_FILENAME, (void *) &{{cookiecutter.app_name}}_configtable);
}

void {{cookiecutter.app_name}}_Test_TearDown(void) {
    CFE_PSP_MemSet(&{{cookiecutter.app_name}}_AppData, 0x00, sizeof({{cookiecutter.app_name}}_AppData_t));
}
