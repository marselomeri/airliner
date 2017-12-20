    
#ifndef PARAMS_VERSION_H
#define PARAMS_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Major version number for PARAMS application
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
#define PARAMS_MAJOR_VERSION    (0)

/** \brief Minor version number for PARAMS application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "params_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define PARAMS_MINOR_VERSION    (0)

/** \brief Revision version number for PARAMS application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "params_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define PARAMS_REVISION         (0)


#ifdef __cplusplus
}
#endif

#endif /* PARAMS_VERSION_H */

/************************/
/*  End of File Comment */
/************************/
