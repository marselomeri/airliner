
#include "pmc_cds_tbl_test.h"
#include "pmc_test_utils.h"

#include "pmc_msg.h"

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


void PMC_CDS_Tbl_Test_Case1(void)
{

}


void PMC_CDS_Tbl_Test_AddTestCases(void)
{
    UtTest_Add(PMC_CDS_Tbl_Test_Case1, PMC_Test_Setup, PMC_Test_TearDown, "PMC_CDS_Tbl_Test_Case1");
}


