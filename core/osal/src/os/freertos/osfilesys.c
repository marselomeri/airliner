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

#include "FreeRTOS.h"
#include "semphr.h"
#include "osapi.h"
#include <string.h>
#include "ff.h"
#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include "xil_printf.h"
#include "xil_cache.h"
#include "xplatform_info.h"
#ifdef OS_DEBUG_PRINTF
#include <errno.h>
#endif



#define OS_BYTES_PER_CLUSTER (512)



extern SemaphoreHandle_t OS_VolumeTableSem;
/*
** This is the volume table reference. It is defined in the BSP/startup code for the board
*/
extern OS_VolumeInfo_t   OS_VolumeTable[NUM_TABLE_ENTRIES];

/*
** Fd Table
*/
extern OS_FDTableEntry   OS_FDTable[OS_MAX_NUM_OPEN_FILES];

/*
** A semaphore to guard the file system calls.
*/
extern SemaphoreHandle_t OS_VolumeTableSem;


BYTE OS_VolumeWorkBuffer[NUM_TABLE_ENTRIES][FF_MAX_SS];


int32 OS_GetPhysDeviceFromPath(const char *VirtualPath, char *PhysDevice);


int32 OS_mkfs(char *address, const char *devname, const char * volname, uint32 blocksize,
              uint32 numblocks)
{
    int      i;
    uint32   ReturnCode = 0;

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

    /*
    ** Lock
    */
    xSemaphoreTakeRecursive(OS_VolumeTableSem, OS_INTERNAL_MUTEX_TIMEOUT);

    /* find an open entry in the Volume Table */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == TRUE && OS_VolumeTable[i].IsMounted == FALSE
            && strcmp(OS_VolumeTable[i].DeviceName, devname) == 0)
        {
            break;
        }
    }

    if (i >= NUM_TABLE_ENTRIES)
    {
        xSemaphoreGiveRecursive(OS_VolumeTableSem);
        return OS_FS_ERR_DEVICE_NOT_FREE;
    }

    /*
    ** Create the RAM disk and format it with the RFS file system.
    ** This requires RTEMS 4.10
    */
    if (OS_VolumeTable[i].VolumeType == RAM_DISK)
    {
    	char physDevPath[10] = {0};
    	sprintf(physDevPath, "%s:\\", OS_VolumeTable[i].PhysDevName);
    	FRESULT result = f_mkfs(physDevPath, FM_FAT, 0, &OS_VolumeWorkBuffer[i], FF_MAX_SS);
    	if(result != FR_OK)
    	{
#ifdef OS_DEBUG_PRINTF
            OS_printf("f_mkfs failed with %u.  errno = %i.  address = %p, blocksize = %u, numblocks = %u\n",
            		result, errno, address, blocksize, (unsigned int)numblocks);
#endif
            vPortFree(address);

    		return OS_FS_ERR_DRIVE_NOT_CREATED;
    	}

        /*
        ** Success
        */
        OS_VolumeTable[i].FreeFlag = FALSE;
        strcpy(OS_VolumeTable[i].VolumeName, volname);
        OS_VolumeTable[i].BlockSize = blocksize;
        ReturnCode = OS_FS_SUCCESS;
    }
    else if (OS_VolumeTable[i].VolumeType == FS_BASED)
    {
       /*
       ** FS_BASED will map the OSAL Volume to an already mounted host filesystem
       */

       /*
       ** Enter the info in the table
       */
       OS_VolumeTable[i].FreeFlag = FALSE;
       strcpy(OS_VolumeTable[i].VolumeName, volname);
       OS_VolumeTable[i].BlockSize = blocksize;

       ReturnCode = OS_FS_SUCCESS;
    }
    else
    {
        /*
        ** The VolumeType is something else that is not supported right now
        */
        ReturnCode = OS_FS_ERROR;
    }

    /*
    ** Unlock
    */
    xSemaphoreGiveRecursive(OS_VolumeTableSem);

    return ReturnCode;
}



int32 OS_rmfs(const char *devname)
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
}



int32 OS_initfs(char *address, const char *devname, const char *volname,
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
}



int32 OS_mount(const char *devname, const char* mountpoint)
{
	FRESULT result;
	uint32 i = 0;
	char physDevPath[OS_FS_PHYS_NAME_LEN] = {0};

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

    /*
    ** Mount the RAM disk device
    */
	sprintf(physDevPath, "%s:\\", OS_VolumeTable[i].PhysDevName);
	result = f_mount((FATFS*)&OS_VolumeWorkBuffer[i], physDevPath, 0);
	if(result != FR_OK)
	{
#ifdef OS_DEBUG_PRINTF
        OS_printf("f_mount failed with %u.  errno = %i.  PhysDevName = %s\n",
        		result, errno, OS_VolumeTable[i].PhysDevName);
#endif

		return OS_FS_ERR_DRIVE_NOT_CREATED;
	}

    strcpy(OS_VolumeTable[i].MountPoint, mountpoint);
    OS_VolumeTable[i].IsMounted = TRUE;

    return OS_FS_SUCCESS;
}



int32 OS_unmount(const char *mountpoint)
{
	FRESULT result;
	uint32 i = 0;
	char physDevPath[OS_FS_PHYS_NAME_LEN] = {0};

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

	sprintf(physDevPath, "%s:\\", OS_VolumeTable[i].PhysDevName);
	result = f_unmount(physDevPath);
	if(result == FR_OK)
	{
        /* release the informationm from the table */
        OS_VolumeTable[i].IsMounted = FALSE;
        strcpy(OS_VolumeTable[i].MountPoint, "");

        return OS_FS_SUCCESS;
	}

	return OS_FS_ERROR;
}



int32 OS_fsBlocksFree(const char *name)
{
	FRESULT result;
    char    tmpFileName[OS_MAX_LOCAL_PATH_LEN +1];
    FATFS   *fatfs;
    DWORD   numClusters;

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
    OS_GetPhysDeviceFromPath(name, tmpFileName);

    result = f_getfree(tmpFileName, &numClusters, &fatfs);
    if ( result == FR_OK )
    {
        return numClusters;
    }

    return OS_FS_ERROR;
}



int32 OS_fsBytesFree(const char *name, uint64 *bytes_free)
{
	int32 result;

    if ( name == NULL )
    {
        return(OS_FS_ERR_INVALID_POINTER);
    }

    if ( bytes_free == NULL )
    {
        return(OS_FS_ERR_INVALID_POINTER);
    }

	result = OS_fsBlocksFree(name);
	if(result > 0)
	{
	    *bytes_free = result * OS_BYTES_PER_CLUSTER;
	}

	return OS_SUCCESS;
}



os_fshealth_t OS_chkfs(const char *name, boolean repair)
{
    return OS_FS_UNIMPLEMENTED;

}



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

}



int32 OS_TranslatePath(const char *VirtualPath, char *LocalPath)
{
    char devname [OS_MAX_PATH_LEN];
    char filename[OS_MAX_PATH_LEN];
    int  NumChars;
    int  FilenameLen;
    int  i=0;
	char physDevPath[10] = {0};

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
    /*
    ** Copy everything after the devname as the path/filename
    */
    strncpy(filename, &(VirtualPath[NumChars]), OS_MAX_PATH_LEN);
    FilenameLen = strlen(filename);

#ifdef OS_DEBUG_PRINTF
    OS_printf("VirtualPath: %s, Length: %d\n",VirtualPath, (int)strlen(VirtualPath));
    OS_printf("NumChars: %d\n",NumChars);
    OS_printf("devname: %s\n",devname);
    OS_printf("filename: %s\n",filename);
#endif

    /*
    ** look for the dev name we found in the VolumeTable
    */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE &&
            strncmp(OS_VolumeTable[i].MountPoint, devname, NumChars) == 0)
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
    sprintf(LocalPath, "%s:%s", OS_VolumeTable[i].PhysDevName, filename);

#ifdef OS_DEBUG_PRINTF
    OS_printf("Result of TranslatePath = %s\n",LocalPath);
#endif

    return OS_FS_SUCCESS;

}



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



int32 OS_GetPhysDeviceFromPath(const char *VirtualPath, char *PhysDevice)
{
    char devname [OS_MAX_PATH_LEN];
    char filename[OS_MAX_PATH_LEN];
    int  NumChars;
    int  i=0;

    /*
    ** Check to see if the path pointers are NULL
    */
    if (VirtualPath == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    if (PhysDevice == NULL)
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

    /*
    ** Copy everything after the devname as the path/filename
    */
    strncpy(filename, &(VirtualPath[NumChars]), OS_MAX_PATH_LEN);

    /*
    ** look for the dev name we found in the VolumeTable
    */
    for (i = 0; i < NUM_TABLE_ENTRIES; i++)
    {
        if (OS_VolumeTable[i].FreeFlag == FALSE &&
            strncmp(OS_VolumeTable[i].MountPoint, devname, NumChars) == 0)
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

    strcpy(PhysDevice, OS_VolumeTable[i].PhysDevName);

    return OS_FS_SUCCESS;

}
