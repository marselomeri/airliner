
#include "uttest.h"

#include "{{cookiecutter.app_name|lower}}_app_test.h"
#include "{{cookiecutter.app_name|lower}}_cmds_test.h"
#include "{{cookiecutter.app_name|lower}}_config_tbl_test.h"
#include "{{cookiecutter.app_name|lower}}_cds_tbl_test.h"

int main(void)
{   
    {{cookiecutter.app_name}}_App_Test_AddTestCases();
    {{cookiecutter.app_name}}_Cmds_Test_AddTestCases();
    {{cookiecutter.app_name}}_Config_Tbl_Test_AddTestCases();
    {{cookiecutter.app_name}}_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

