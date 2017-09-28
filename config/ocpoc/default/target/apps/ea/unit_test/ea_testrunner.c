#include "uttest.h"

#include "ea_custom_test.h"

int main(void)
{   
	EA_Custom_Test_AddTestCases();

    return(UtTest_Run());
}

