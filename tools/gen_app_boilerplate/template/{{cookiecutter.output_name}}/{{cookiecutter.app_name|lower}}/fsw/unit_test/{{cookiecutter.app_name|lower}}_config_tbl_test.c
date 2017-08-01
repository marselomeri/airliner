
#include "{{cookiecutter.app_name|lower}}_config_tbl_test.h"
#include "{{cookiecutter.app_name|lower}}_test_utils.h"

#include "{{cookiecutter.app_name|lower}}_msg.h"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"


void {{cookiecutter.app_name}}_Config_Tbl_Test_Case1(void)
{

}


void {{cookiecutter.app_name}}_Config_Tbl_Test_AddTestCases(void)
{
    UtTest_Add({{cookiecutter.app_name}}_Config_Tbl_Test_Case1, {{cookiecutter.app_name}}_Test_Setup, {{cookiecutter.app_name}}_Test_TearDown, "{{cookiecutter.app_name}}_Config_Tbl_Test_Case1");
}


