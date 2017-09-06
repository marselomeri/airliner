/*************************************************************************
** File:
**   $Id: cfs_utils.c 1.13 2011/05/20 13:24:20EDT lwalling Exp  $
**
** Purpose: 
**   Shared library functions for CFS applications
**
**   $Log: cfs_utils.c  $
**   Revision 1.13 2011/05/20 13:24:20EDT lwalling 
**   Modify packet filter to match algorithm used by SDO, GPM, etc.
**   Revision 1.12 2010/09/21 14:36:34EDT wmoleski 
**   The sequence count in a ccsds packet header consists of the lower 14 bits. The code was using
**   the entire 16 bit value to determine whether the packet should be filtered. This was changed to
**   extract only the lower 14 bits for the sequence count.
**   Revision 1.11 2010/09/21 08:50:05EDT wmoleski 
**   Deleted the line of code that checked if the currect character was a '%' for the valid filename check function.
**   Revision 1.10 2009/08/31 17:46:41EDT lwalling 
**   Add function CFS_VerifyString() to CFS Library
**   Revision 1.9 2009/08/13 10:04:30EDT lwalling 
**   Change test for (N >= X) to (N > X) in CFS_IsPacketFiltered()
**   Revision 1.8 2009/05/26 13:31:07EDT lwalling 
**   Create common packet filter function in global CFS library
**   Revision 1.7 2008/10/06 09:38:25EDT rjmcgraw 
**   DCR4400:1 Changed return on CFS_LibInit from void to int32
**   Revision 1.6 2008/09/19 15:30:51EDT rjmcgraw 
**   DCR4337:1 Added #include version.h and display version after initialization 
**     is complete
**   Revision 1.5 2008/09/09 10:59:32EDT njyanchik 
**   I accidentally  updated the list of allowable characters with a list of 
**     not-allowed characters. I
**   need to fix it.
**   Revision 1.4 2008/08/08 15:38:01BST njyanchik 
**   Since there was already a function for detecting invalid file names, I 
**     updated the list of the
**   invalid characters to the list that is specified in the DCR.
**   Revision 1.3 2008/05/15 14:40:33BST rjmcgraw 
**   DCR2179:1 Changed fucntion call OS_SymLookup to OS_SymbolLookup
**   Revision 1.2 2008/05/13 13:47:02EDT rjmcgraw 
**   DCR2179:1 Changed include filename from cfs_lib.h to cfs_utils.h
**   Revision 1.1 2008/05/13 13:13:28EDT rjmcgraw 
**   Initial revision
**   Member added to CFS project 
** 
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************
** Includes
*************************************************************************/

#include "pb_version.h"
#include "cfe.h"

/*************************************************************************
** Macro Definitions
*************************************************************************/


/*************************************************************************
** Private Function Prototypes
*************************************************************************/


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PBLIB_LibInit(void)
{
    OS_printf ("PBLIB Initialized.  Version %d.%d.%d.%d\n",
    		PBLIB_MAJOR_VERSION,
			PBLIB_MINOR_VERSION,
			PBLIB_REVISION,
			PBLIB_MISSION_REV);


    return OS_SUCCESS;
 
}/* End PBLIB_LibInit */

/************************/
/*  End of File Comment */
/************************/

