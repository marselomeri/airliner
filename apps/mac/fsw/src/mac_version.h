#ifndef MAC_VERSION_H
#define MAC_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Major version number for MAC application
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
#define MAC_MAJOR_VERSION    (0)

/** \brief Minor version number for MAC application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "mac_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define MAC_MINOR_VERSION    (0)

/** \brief Revision version number for MAC application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined in "mac_platform_cfg.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define MAC_REVISION         (0)


#ifdef __cplusplus
}
#endif

#endif /* MAC_VERSION_H */

/************************/
/*  End of File Comment */
/************************/
