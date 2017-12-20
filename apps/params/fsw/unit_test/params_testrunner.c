
#include "uttest.h"

#include "params_app_test.h"
#include "params_cmds_test.h"
#include "params_config_tbl_test.h"
#include "params_cds_tbl_test.h"

int main(void)
{   
    PARAMS_App_Test_AddTestCases();
    PARAMS_Cmds_Test_AddTestCases();
    PARAMS_Config_Tbl_Test_AddTestCases();
    PARAMS_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

