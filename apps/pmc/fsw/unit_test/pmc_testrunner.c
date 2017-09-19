
#include "uttest.h"

#include "pmc_app_test.h"
#include "pmc_cmds_test.h"
#include "pmc_config_tbl_test.h"
#include "pmc_cds_tbl_test.h"

int main(void)
{   
    PMC_App_Test_AddTestCases();
    PMC_Cmds_Test_AddTestCases();
    PMC_Config_Tbl_Test_AddTestCases();
    PMC_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

