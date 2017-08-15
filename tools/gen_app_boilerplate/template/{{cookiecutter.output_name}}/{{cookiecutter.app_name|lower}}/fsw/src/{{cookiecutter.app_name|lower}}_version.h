    
#ifndef {{cookiecutter.app_name}}_VERSION_H
#define {{cookiecutter.app_name}}_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Major version number for {{cookiecutter.app_name}} application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "ci_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define {{cookiecutter.app_name}}_MAJOR_VERSION    (0)

/** \brief Minor version number for {{cookiecutter.app_name}} application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "{{cookiecutter.app_name|lower}}_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define {{cookiecutter.app_name}}_MINOR_VERSION    (0)

/** \brief Revision version number for {{cookiecutter.app_name}} application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "{{cookiecutter.app_name|lower}}_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define {{cookiecutter.app_name}}_REVISION         (0)


#ifdef __cplusplus
}
#endif

#endif /* {{cookiecutter.app_name}}_VERSION_H */

/************************/
/*  End of File Comment */
/************************/
