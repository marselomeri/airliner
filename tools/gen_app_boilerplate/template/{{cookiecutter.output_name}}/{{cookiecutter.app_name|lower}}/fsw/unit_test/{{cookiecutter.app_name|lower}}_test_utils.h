
#ifndef {{cookiecutter.app_name}}_TEST_UTILS_H
#define {{cookiecutter.app_name}}_TEST_UTILS_H

/*
 * Includes
 */

#include "{{cookiecutter.app_name|lower}}_app.h"

extern {{cookiecutter.app_name}}_AppData_t  {{cookiecutter.app_name}}_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void {{cookiecutter.app_name}}_Test_Setup(void);
void {{cookiecutter.app_name}}_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* {{cookiecutter.app_name}}_TEST_UTILS_H */

