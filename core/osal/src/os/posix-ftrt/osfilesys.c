/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

/****************************************************************************************
                                    INCLUDE FILES
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/statvfs.h>

#include "common_types.h"
#include "osapi.h"

#include <sys/vfs.h>
/****************************************************************************************
                                     DEFINES
****************************************************************************************/

# define ERROR (-1)

/****************************************************************************************
                                   GLOBAL DATA
****************************************************************************************/

/* 
** This is the volume table reference. It is defined in the BSP/startup code for the board
*/
extern OS_VolumeInfo_t OS_VolumeTable [NUM_TABLE_ENTRIES]; 

/*
** Fd Table
*/
extern OS_FDTableEntry OS_FDTable[OS_MAX_NUM_OPEN_FILES];

/****************************************************************************************
                                Filesys API
****************************************************************************************/

/*
** System Level API 
*/

/*---------------------------------------------------------------------------------------
    Name: OS_mkfs

    Purpose: Makes a file system on the target

    Returns: OS_FS_ERR_INVALID_POINTER if devname is NULL
             OS_FS_ERR_DRIVE_NOT_CREATED if the OS calls to create the the drive failed
             OS_FS_ERR_DEVICE_NOT_FREE if the volume table is full
             OS_FS_SUCCESS on creating the disk
    
---------------------------------------------------------------------------------------*/

int32 OS_mkfs (char *address, const char *devname, const char * volname, uint32 blocksize,
               uint32 numblocks)
{
    int i;
    
    /*
    ** Check parameters
    */
    if ( devname == NULL || volname == NULL )
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if( strlen(devname) >= OS_FS_DEV_NAME_LEN || strlen(volname) >= OS_FS_VOL_NAME_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /* find an open entry in the Volume Table */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == TRUE && OS_VolumeTable[i].IsMounted == FALSE
            && strcmp(OS_VolumeTable[i].DeviceName, devname) == 0)
            break;
    }

    if (i >= NUM_TABLE_ENTRIES)
    {
        return OS_FS_ERR_DEVICE_NOT_FREE;
    }

    /* make a disk if it is FS based */
    /*------------------------------- */
    if (OS_VolumeTable[i].VolumeType == FS_BASED)
    {
       /* now enter the info in the table */
       OS_VolumeTable[i].FreeFlag = FALSE;
       strcpy(OS_VolumeTable[i].VolumeName, volname);
       OS_VolumeTable[i].BlockSize = blocksize;
    
    }  
    else
    {
        return OS_FS_ERR_DRIVE_NOT_CREATED;
    }
    return OS_FS_SUCCESS; 
    
} /* end OS_mkfs */

/*---------------------------------------------------------------------------------------
    Name: OS_rmfs

    Purpose: Inititalizes a file system on the target
    
    Returns: OS_FS_ERR_INVALID_POINTER if devname is NULL
             OS_FS_ERROR is the drive specified cannot be located
             OS_FS_SUCCESS on removing  the disk
---------------------------------------------------------------------------------------*/

int32 OS_rmfs (const char *devname)
{
    int i;
    int32 ReturnCode;

    if (devname ==NULL)
    {
        ReturnCode =  OS_FS_ERR_INVALID_POINTER;
    }
    else if ( strlen(devname) >= OS_FS_DEV_NAME_LEN )
    {
        ReturnCode = OS_FS_ERR_PATH_TOO_LONG;
    }
    else
    {
        /* find this entry in the Volume Table */
        for (i = 0; i < NUM_TABLE_ENTRIES; i++)
        {
            if (OS_VolumeTable[i].FreeFlag == FALSE && OS_VolumeTable[i].IsMounted == FALSE
                && strcmp(OS_VolumeTable[i].DeviceName, devname) == 0)
            {
                break;
            }
        }

        /* We can't find that entry in the table */
        if (i >= NUM_TABLE_ENTRIES)
        {
            ReturnCode =  OS_FS_ERROR;
        }
        else
        {
            /* Free this entry in the table */
            OS_VolumeTable[i].FreeFlag = TRUE;
            
            /* desconstruction of the filesystem to come later */

            ReturnCode = OS_FS_SUCCESS;
        }

    }
    return ReturnCode;
}/* end OS_rmfs */

/*---------------------------------------------------------------------------------------
    Name: OS_initfs

    Purpose: Inititalizes a file system on the target

    Returns: OS_FS_ERR_INVALID_POINTER if devname or volname are  NULL
             OS_FS_ERR_PATH_TOO_LONG if the name is too long
             OS_FS_ERR_DEVICE_NOT_FREE if the volume table is full
             OS_FS_ERR_DRIVE_NOT_CREATED on error
             OS_FS_SUCCESS on creating the disk
    
---------------------------------------------------------------------------------------*/
int32 OS_initfs (char *address,const char *devname, const char *volname,
                uint32 blocksize, uint32 numblocks)
{
    int i;
   
    if ( devname == NULL || volname == NULL )
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if( strlen(devname) >= OS_FS_DEV_NAME_LEN || strlen(volname) >= OS_FS_VOL_NAME_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /* find an open entry in the Volume Table */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == TRUE && OS_VolumeTable[i].IsMounted == FALSE
            && strcmp(OS_VolumeTable[i].DeviceName, devname) == 0)
            break;
    }

    if (i >= NUM_TABLE_ENTRIES)
    {
        return OS_FS_ERR_DEVICE_NOT_FREE;
    }

    /* make a disk if it is FS based */
    /*------------------------------- */
    if (OS_VolumeTable[i].VolumeType == FS_BASED)
    {
       /* now enter the info in the table */
       OS_VolumeTable[i].FreeFlag = FALSE;
       strcpy(OS_VolumeTable[i].VolumeName, volname);
       OS_VolumeTable[i].BlockSize = blocksize;
    } 
    else
    {
        return OS_FS_ERR_DRIVE_NOT_CREATED;
    }

   return OS_FS_SUCCESS; 

}/* end OS_initfs */

/*--------------------------------------------------------------------------------------
    Name: OS_mount
    
    Purpose: mounts a drive.

---------------------------------------------------------------------------------------*/

int32 OS_mount (const char *devname, const char* mountpoint)
{
    int i;

    /* Check parameters */
    if ( devname == NULL || mountpoint == NULL )
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if( strlen(devname) >= OS_FS_DEV_NAME_LEN || strlen(mountpoint) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /* find the device in the table */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE && OS_VolumeTable[i].IsMounted == FALSE
            && strcmp(OS_VolumeTable[i].DeviceName, devname) == 0)
            break;
    }

    /* make sure we found the device */
    if (i >= NUM_TABLE_ENTRIES)
    {
        return OS_FS_ERROR;
    }

    /* attach the mountpoint */
    strcpy(OS_VolumeTable[i].MountPoint, mountpoint);
    OS_VolumeTable[i].IsMounted = TRUE;

    return OS_FS_SUCCESS;

}/* end OS_mount */

/*--------------------------------------------------------------------------------------
    Name: OS_unmount
    
    Purpose: unmounts a drive. and therefore makes all file descriptors pointing into
             the drive obsolete.

    Returns: OS_FS_ERR_INVALID_POINTER if name is NULL
             OS_FS_ERR_PATH_TOO_LONG if the absolute path given is too long
             OS_FS_ERROR if the OS calls failed
             OS_FS_SUCCESS if success
---------------------------------------------------------------------------------------*/

int32 OS_unmount (const char *mountpoint)
{
    int i;
    
    if (mountpoint == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if (strlen(mountpoint) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE && OS_VolumeTable[i].IsMounted == TRUE
             && strcmp(OS_VolumeTable[i].MountPoint, mountpoint) == 0)
            break;
    }

    /* make sure we found the device */
    if (i >= NUM_TABLE_ENTRIES)
    {
        return OS_FS_ERROR;
    }

    /* release the informationm from the table */
    OS_VolumeTable[i].IsMounted = FALSE;
    strcpy(OS_VolumeTable[i].MountPoint, "");
    
    return OS_FS_SUCCESS;
    
}/* end OS_umount */

/*--------------------------------------------------------------------------------------
    Name: OS_fsBlocksFree

    Purpose: Returns the number of free blocks in a volume
 
    Returns: OS_FS_ERR_INVALID_POINTER if name is NULL
             OS_FS_ERR_PATH_TOO_LONG if the name is too long
             OS_FS_ERROR if the OS call failed
             The number of blocks free in a volume if success
---------------------------------------------------------------------------------------*/
int32 OS_fsBlocksFree (const char *name)
{

   int            status;
   int32          NameStatus;
   struct statvfs stat_buf;
   char           tmpFileName[OS_MAX_LOCAL_PATH_LEN +1];
   
   if ( name == NULL )
   {
      return(OS_FS_ERR_INVALID_POINTER);
   }
   
   /*
   ** Check the length of the volume name
   */
   if ( strlen(name) >= OS_MAX_PATH_LEN )
   {
      return(OS_FS_ERR_PATH_TOO_LONG);
   }

   /*
   ** Translate the path
   */
   NameStatus = OS_TranslatePath(name, tmpFileName);
   
   status = statvfs(tmpFileName, &stat_buf);
   
   if ( status == 0 )
   {
      return(stat_buf.f_bfree);
   }
   return OS_FS_ERROR;

}/* end OS_fsBlocksFree */

/*--------------------------------------------------------------------------------------
    Name: OS_fsBytesFree

    Purpose: Returns the number of free bytes in a volume
 
    Returns: OS_FS_ERR_INVALID_POINTER if name is NULL
             OS_FS_ERR_PATH_TOO_LONG if the name is too long
             OS_FS_ERROR if the OS call failed
             OS_FS_SUCCESS if success
---------------------------------------------------------------------------------------*/
int32 OS_fsBytesFree (const char *name, uint64 *bytes_free)
{
   int             status;
   int32           NameStatus;
   struct statvfs  stat_buf;
   uint64          bytes_free_local;
   char            tmpFileName[OS_MAX_LOCAL_PATH_LEN +1];

   if ( name == NULL || bytes_free == NULL )
   {
      return(OS_FS_ERR_INVALID_POINTER);
   }

   /*
   ** Check the length of the volume name
   */
   if ( strlen(name) >= OS_MAX_PATH_LEN )
   {
      return(OS_FS_ERR_PATH_TOO_LONG);
   }

   /*
   ** Translate the path
   */
   NameStatus = OS_TranslatePath(name, tmpFileName);

   status = statvfs(tmpFileName, &stat_buf);
   if ( status == 0 )
   {
      bytes_free_local = stat_buf.f_bfree * stat_buf.f_bsize;
      *bytes_free = bytes_free_local;
      return(OS_FS_SUCCESS);
   }
   return(OS_FS_ERROR);

}/* end OS_fsBytesFree */


/*--------------------------------------------------------------------------------------
    Name: OS_chkfs
    
    Purpose: Checks the drives for inconsisenties and either repairs it or not

    Returns: OS_FS_ERR_INVALID_POINTER if name is NULL
             OS_FS_SUCCESS if success
             OS_FS_ERROR if the OS calls fail

---------------------------------------------------------------------------------------*/
os_fshealth_t OS_chkfs (const char *name, boolean repair)
{
 
    return OS_FS_UNIMPLEMENTED;

}/* end OS_chkfs */
/*--------------------------------------------------------------------------------------
    Name: OS_FS_GetPhysDriveName
    
    Purpose: Returns the name of the physical volume associated with the drive,
             when given the OSAL mount point of the drive

    Returns: OS_FS_ERR_INVALID_POINTER if either  parameter is NULL
             OS_SUCCESS if success
             OS_FS_ERROR if the mountpoint could not be found
---------------------------------------------------------------------------------------*/
int32 OS_FS_GetPhysDriveName(char * PhysDriveName, char * MountPoint)
{
    int32 ReturnCode;
    int   i;
    
    if (MountPoint == NULL || PhysDriveName == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }
 
    if( strlen(PhysDriveName) >= OS_FS_DEV_NAME_LEN || strlen(MountPoint) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** look for the CFS Mount Point in the VolumeTable 
    */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE &&
            strncmp(OS_VolumeTable[i].MountPoint, MountPoint, OS_MAX_PATH_LEN) == 0)
        {
            break;
        }
    }

    /* 
    ** Make sure we found a valid volume table entry 
    */
    if (i >= NUM_TABLE_ENTRIES)
    {
        ReturnCode = OS_FS_ERROR;
    }
    else
    {
       /*
       ** Yes, so copy the physical drive name  
       */
       strncpy(PhysDriveName, OS_VolumeTable[i].PhysDevName,OS_FS_PHYS_NAME_LEN);
       ReturnCode = OS_SUCCESS;
    }

    return ReturnCode;
}/* end OS_FS_GetPhysDriveName */

/*-------------------------------------------------------------------------------------
 * Name: OS_TranslatePath
 * 
 * Purpose: Because of the abstraction of the filesystem across OSes, we have to change
 *          the name of the {file, directory, drive} to be what the OS can actually 
 *          accept
---------------------------------------------------------------------------------------*/
int32 OS_TranslatePath(const char *VirtualPath, char *LocalPath)
{
    char devname [OS_MAX_PATH_LEN];
    char filename[OS_MAX_PATH_LEN];
    int  NumChars;
    int  DeviceLen;
    int  FilenameLen;
    int  i=0;

    /*
    ** Check to see if the path pointers are NULL
    */
    if (VirtualPath == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if (LocalPath == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }
   
    /*
    ** Check to see if the path is too long
    */
    if (strlen(VirtualPath) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** All valid Virtual paths must start with a '/' character
    */
    if ( VirtualPath[0] != '/' )
    {
       return OS_FS_ERR_PATH_INVALID;
    }

    /*
    ** Fill the file and device name to be sure they do not have garbage
    */
    memset((void *)devname,0,OS_MAX_PATH_LEN);
    memset((void *)filename,0,OS_MAX_PATH_LEN);
   
    /* 
    ** We want to find the number of chars to where the second "/" is.
    ** Since we know the first one is in spot 0, we start looking at 1, and go until
    ** we find it.
    */    
    NumChars = 1;
    while ((NumChars <= strlen(VirtualPath)) && (VirtualPath[NumChars] != '/'))
    {
        NumChars++;
    }
    
    /* 
    ** Don't let it overflow to cause a segfault when trying to get the highest level
    ** directory 
    */
    if (NumChars > strlen(VirtualPath))
    {
        NumChars = strlen(VirtualPath);
    }
  
    /*
    ** copy over only the part that is the device name 
    */
    strncpy(devname, VirtualPath, NumChars);
    devname[NumChars] = '\0'; /* Truncate it with a NULL. */
    DeviceLen = strlen(devname);
    
    /*
    ** Copy everything after the devname as the path/filename
    */
    strncpy(filename, &(VirtualPath[NumChars]), OS_MAX_PATH_LEN);
    FilenameLen = strlen(filename);
    
#ifdef OS_DEBUG_PRINTF 
    printf("VirtualPath: %s, Length: %d\n",VirtualPath, (int)strlen(VirtualPath));
    printf("NumChars: %d\n",NumChars);
    printf("devname: %s\n",devname);
    printf("filename: %s\n",filename);
#endif

    /*
    ** look for the dev name we found in the VolumeTable 
    */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE && 
            strncmp(OS_VolumeTable[i].MountPoint, devname,NumChars) == 0)
        {
            break;
        }
    }

    /* 
    ** Make sure we found a valid drive 
    */
    if (i >= NUM_TABLE_ENTRIES)
    {
        return OS_FS_ERR_PATH_INVALID;
    }
    
    /* 
    ** copy over the physical first part of the drive 
    */
    strncpy(LocalPath,OS_VolumeTable[i].PhysDevName,OS_MAX_LOCAL_PATH_LEN);
    NumChars = strlen(LocalPath);

    /*
    ** Add the file name
    */
    strncat(LocalPath, filename, (OS_MAX_LOCAL_PATH_LEN - NumChars));

#ifdef OS_DEBUG_PRINTF
    printf("Result of TranslatePath = %s\n",LocalPath);
#endif

    return OS_FS_SUCCESS;
    
} /* end OS_TranslatePath */

/*---------------------------------------------------------------------------------------
    Name: OS_FS_GetErrorName()

    Purpose: a handy debugging tool that will copy the name of the error code to a buffer

    Returns: OS_FS_ERROR if given error number is unknown
             OS_FS_SUCCESS if given error is found and copied to the buffer
--------------------------------------------------------------------------------------- */
int32 OS_FS_GetErrorName(int32 error_num, os_fs_err_name_t * err_name)
{
    os_fs_err_name_t local_name;
    int32 return_code;

    return_code = OS_FS_SUCCESS;
    
    switch (error_num)
    {
        case OS_FS_SUCCESS: 
            strcpy(local_name,"OS_FS_SUCCESS"); break;
        case OS_FS_ERROR: 
            strcpy(local_name,"OS_FS_ERROR"); break;
        case OS_FS_ERR_INVALID_POINTER: 
            strcpy(local_name,"OS_FS_ERR_INVALID_POINTER"); break;
        case OS_FS_ERR_PATH_TOO_LONG: 
            strcpy(local_name,"OS_FS_ERR_PATH_TOO_LONG"); break;
        case OS_FS_ERR_NAME_TOO_LONG: 
            strcpy(local_name,"OS_FS_ERR_NAME_TOO_LONG"); break;
        case OS_FS_UNIMPLEMENTED: 
            strcpy(local_name,"OS_FS_UNIMPLEMENTED"); break;
        case OS_FS_ERR_PATH_INVALID:
            strcpy(local_name,"OS_FS_ERR_PATH_INVALID"); break;
        case OS_FS_ERR_DRIVE_NOT_CREATED: 
            strcpy(local_name,"OS_FS_ERR_DRIVE_NOT_CREATED"); break;
    
        default: strcpy(local_name,"ERROR_UNKNOWN");
                 return_code = OS_FS_ERROR;
    }

    strcpy((char*) err_name, local_name);
    return return_code;
}

/*--------------------------------------------------------------------------------------
     Name: OS_GetFsInfo
  
     Purpose: returns information about the file system in an os_fsinfo_t
                  
     Returns: OS_FS_ERR_INVALID_POINTER if filesys_info is NULL
              OS_FS_SUCCESS if success

     Note: The information returned is in the structure pointed to by filesys_info         
 ---------------------------------------------------------------------------------------*/
int32 OS_GetFsInfo(os_fsinfo_t  *filesys_info)
{
   int i;

   /*
   ** Check to see if the file pointers are NULL
   */
   if (filesys_info == NULL)
   {
       return OS_FS_ERR_INVALID_POINTER;
   }

   filesys_info->MaxFds = OS_MAX_NUM_OPEN_FILES;
   filesys_info->MaxVolumes = NUM_TABLE_ENTRIES;

   filesys_info->FreeFds = 0;
   for ( i = 0; i < OS_MAX_NUM_OPEN_FILES; i++ )
   {
      if ( OS_FDTable[i].IsValid == FALSE)
      {
         filesys_info->FreeFds++;
      }

   }

   filesys_info->FreeVolumes = 0;
   for ( i = 0; i < NUM_TABLE_ENTRIES; i++ )
   {
      if (OS_VolumeTable[i].FreeFlag == TRUE )
      {
         filesys_info->FreeVolumes++;
      }
   }

   return(OS_FS_SUCCESS);
}

