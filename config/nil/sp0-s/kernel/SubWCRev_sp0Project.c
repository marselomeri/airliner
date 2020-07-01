#include <stdio.h>
#include "config.h"

extern int SubversionBSPInfo(void);

/* Template file for SubWCRevProj */

char *TSVN_ProjRevision = "6040";
char *TSVN_ProjModified = "Not modified";
char *TSVN_ProjDate     = "2019/07/02 17:10:59";
char *TSVN_ProjURL      = "https://svn/svn/sp0/trunk/Software/SP0-Upgrade/Code/Source/release/vxworks-6.9/project/sp0-s";

int SubversionProjectInfo(void)
{
    printf("\n\rSP0 Project Source Code Revision Information\n\n");
    printf("  Build Revision     : %s\n",   TSVN_ProjRevision);
    printf("  Build Commit Date  : %s\n",   TSVN_ProjDate);
    printf("  Build Working Copy : %s\n",   TSVN_ProjModified);
    printf("  Build URL          : %s\n\n", TSVN_ProjURL);
    
    return(0);
}

int AitechVersion(void)
{

    printf("\nSP0 VxWorks/BSP Version Information : %s%s\n",  BSP_VERSION, BSP_REV);

    SubversionBSPInfo();
    SubversionProjectInfo();

    return(0);
}
