#include "uttest.h"

#include "ci_custom_test.h"

int main(void)
{   
	CI_Custom_Test_AddTestCases();

    return(UtTest_Run());
}

