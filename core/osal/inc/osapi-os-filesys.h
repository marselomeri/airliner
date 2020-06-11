/*
** File: osapi-os-filesys.h
**
**      Copyright (c) 2004-2006, United States government as represented by the 
**      administrator of the National Aeronautics Space Administration.  
**      All rights reserved. This software was created at NASAs Goddard 
**      Space Flight Center pursuant to government contracts.
**
**      This is governed by the NASA Open Source Agreement and may be used, 
**      distributed and modified only pursuant to the terms of that agreement.
**
** Author:  Alan Cudmore Code 582
**
** Purpose: Contains functions prototype definitions and variables declarations
**          for the OS Abstraction Layer, File System module
**
*/

#ifndef _osapi_filesys_
#define _osapi_filesys_

#define OS_READ_ONLY        0
#define OS_WRITE_ONLY       1
#define OS_READ_WRITE       2

#define OS_SEEK_SET         0
#define OS_SEEK_CUR         1
#define OS_SEEK_END         2

#define OS_CHK_ONLY         0
#define OS_REPAIR           1

#define FS_BASED            0
#define RAM_DISK            1
#define EEPROM_DISK         2
#define ATA_DISK            3


/*
** Number of entries in the internal volume table
*/
#define NUM_TABLE_ENTRIES 14

/*
** Length of a Device and Volume name 
*/
#define OS_FS_DEV_NAME_LEN  32
#define OS_FS_PHYS_NAME_LEN 64
#define OS_FS_VOL_NAME_LEN  32


/*
** Defines for File System Calls
*/
/*
 * NOTE - these values used to overlap with the
 * other OSAPI error codes.  They now start at -100
 * to avoid this overlap.
 */
#define OS_FS_ERR_PATH_TOO_LONG        (-103)
#define OS_FS_ERR_NAME_TOO_LONG        (-104)
#define OS_FS_ERR_DRIVE_NOT_CREATED    (-106)
#define OS_FS_ERR_DEVICE_NOT_FREE      (-107)
#define OS_FS_ERR_PATH_INVALID         (-108)


/* 
 * Map some codes used by the file API back to the generic counterparts 
 * where there is overlap between them.  Do not duplicate error codes.
 */
#define OS_FS_SUCCESS                  OS_SUCCESS
#define OS_FS_ERROR                    OS_ERROR
#define OS_FS_ERR_INVALID_POINTER      OS_INVALID_POINTER
#define OS_FS_ERR_NO_FREE_FDS          OS_ERR_NO_FREE_IDS
#define OS_FS_ERR_INVALID_FD           OS_ERR_INVALID_ID
#define OS_FS_UNIMPLEMENTED            OS_ERR_NOT_IMPLEMENTED


/* This typedef is for the OS_FS_GetErrorName function, to ensure
 * everyone is making an array of the same length
 *
 * Implementation note for developers:
 *
 * os_fs_err_name_t is now equivalent to the OSAL "os_err_name_t" typedef, 
 * to preserve source code compatibility with anything using the OS_FS_GetErrorName api
 *
 * The sizes of strings in OSAL functions are built with os_fs_err_name_t's
 * limits in mind.  Always check the uses of os_fs_err_name_t when changing
 * os_err_name_t.
 */
typedef os_err_name_t os_fs_err_name_t;


/*
** Internal structure of the OS volume table for 
** mounted file systems and path translation
*/
typedef struct
{
    char   DeviceName [OS_FS_DEV_NAME_LEN];
    char   PhysDevName [OS_FS_PHYS_NAME_LEN];
    uint32 VolumeType;
    uint8  VolatileFlag;
    uint8  FreeFlag;
    uint8  IsMounted;
    char   VolumeName [OS_FS_VOL_NAME_LEN];
    char   MountPoint [OS_MAX_PATH_LEN];
    uint32 BlockSize;

} OS_VolumeInfo_t;

typedef struct
{
   uint32   MaxFds;                /* Total number of file descriptors */
   uint32   FreeFds;               /* Total number that are free */
   uint32   MaxVolumes;            /* Maximum number of volumes */
   uint32   FreeVolumes;           /* Total number of volumes free */
} os_fsinfo_t;


typedef struct
{
    char Path[OS_MAX_PATH_LEN];
    uint32 User;
    uint8 IsValid;                /* For backward compatibility -- always true if OS_FDGetInfo returned true */
}OS_file_prop_t;


/*
 * NOTE: This used to be directly typedef'ed to the "struct stat" from the C library
 *
 * Some C libraries (glibc in particular) actually #define member names to reference into
 * sub-structures, so attempting to reuse a name like "st_mtime" might not work.
 */

typedef struct
{
   uint32   FileModeBits;
   int32    FileTime;
   uint32   FileSize;
} os_fstat_t;

/* We must also define replacements for the stat structure's mode bits.
 * This is currently just a small subset since the OSAL just presents a very
 * simplified view of the filesystem to the upper layers.  And since not all
 * OS'es are POSIX, the more POSIX-specific bits are not relevant anyway.
 */
enum
{
   OS_FILESTAT_MODE_EXEC  = 0x00001,
   OS_FILESTAT_MODE_WRITE = 0x00002,
   OS_FILESTAT_MODE_READ =  0x00004,
   OS_FILESTAT_MODE_DIR =   0x10000
};

#define OS_FILESTAT_MODE(x)   ((x).FileModeBits)
#define OS_FILESTAT_ISDIR(x)  ((x).FileModeBits & OS_FILESTAT_MODE_DIR)
#define OS_FILESTAT_EXEC(x)   ((x).FileModeBits & OS_FILESTAT_MODE_EXEC)
#define OS_FILESTAT_WRITE(x)  ((x).FileModeBits & OS_FILESTAT_MODE_WRITE)
#define OS_FILESTAT_READ(x)   ((x).FileModeBits & OS_FILESTAT_MODE_READ)
#define OS_FILESTAT_SIZE(x)   ((x).FileSize)
#define OS_FILESTAT_TIME(x)   ((x).FileTime)


typedef struct
{
   char FileName[OS_MAX_PATH_LEN];
} os_dirent_t;

/*
 * Preserve the old type names for compatibility;
 * but instead of DIR* it is now just a void*
 */
#ifndef OSAL_OMIT_DEPRECATED
/* Provide something to implement os_dirp_t */
typedef void * os_dirp_t;
#endif

/*
 * Macro to access filename part of the dirent structure
 */
#define OS_DIRENTRY_NAME(x)   ((x).FileName)

/*
 * Several old type names can be aliases for compatibility
 */
#ifndef OSAL_OMIT_DEPRECATED
typedef int32              os_fshealth_t;
typedef OS_file_prop_t     OS_FDTableEntry;
#endif

/*
 * Exported Functions
*/


/******************************************************************************
** Standard File system API
******************************************************************************/
/*
 * Initializes the File System functions 
*/
/************************************************************************/
/** \brief Initialization of API
**
**  \par Description
**       Initialize the tables that the OS FS API uses to keep track of information
**       about objects
**
**  \par Assumptions, External Events, and Notes:
**       None
**  
**  \returns
**  \retcode #OS_SUCCESS  \retdesc \copydoc OS_SUCCESS \endcode
**  \retcode #OS_ERROR  \retdesc \copydoc OS_ERROR \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_FS_Init(void);

/************************************************************************/
/** \brief Create file
**
**  \par Description
**       Creates a file specified by const char *path, with read/write 
**       permissions by access. The file is also automatically opened by the
**       create call.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   path         File path
**  \param [in]   access       #OS_WRITE_ONLY or #OS_READ_WRITE
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_ERR_NO_FREE_FDS if there are no free file descripors left \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_creat  (const char *path, int32  access);

/************************************************************************/
/** \brief Open file
**
**  \par Description
**       Opens a file. access parameters are OS_READ_ONLY,OS_WRITE_ONLY, or 
**       OS_READ_WRITE
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   path         File path
**  \param [in]   access       #OS_READ_ONLY, #OS_WRITE_ONLY, or #OS_READ_WRITE
**  \param [in]   mode         #uint32 bitmask for permissions
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_ERR_NO_FREE_FDS if there are no free file descripors left \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  File descriptor if success
**  \endreturns
**
*************************************************************************/
int32           OS_open   (const char *path,  int32 access,  uint32 mode);

/************************************************************************/
/** \brief Close file
**
**  \par Description
**       Closes a file. 
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   filedes         #int32 File descriptor
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid \endcode
**  \retcode #OS_FS_ERROR  if file  descriptor could not be closed \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  File descriptor if success
**  \endreturns
**
*************************************************************************/
int32           OS_close  (uint32  filedes);

/************************************************************************/
/** \brief Read file
**
**  \par Description
**       Reads up to nbytes from a file, and puts them into buffer. 
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       filedes        #int32 File descriptor
**  \param [in/out]   buffer         Pointer to buffer to populate
**  \param [in]       nbytes         #uint32 Bytes to read
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if buffer is a null pointer \endcode
**  \retcode #OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid \endcode
**  \retcode #OS_FS_ERROR  if file  descriptor could not be closed \endcode
**  Number of bytes read if success
**  \endreturns
**
*************************************************************************/
int32           OS_read   (uint32  filedes, void *buffer, uint32 nbytes);

/************************************************************************/
/** \brief Write to file
**
**  \par Description
**       Writes to a file. Copies up to a maximum of nbtyes of buffer to the file
**       described in filedes
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       filedes        #int32 File descriptor
**  \param [in/out]   buffer         Pointer to buffer to write from
**  \param [in]       nbytes         #uint32 Bytes to write
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if buffer is a null pointer \endcode
**  \retcode #OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid \endcode
**  \retcode #OS_FS_ERROR  if file  descriptor could not be closed \endcode
**  Number of bytes read if success
**  \endreturns
**
*************************************************************************/
int32           OS_write  (uint32  filedes, const void *buffer, uint32 nbytes);

/**
 * File/Stream input read with a timeout
 *
 * This implements a time-limited read and is primarily intended for use with
 * sockets but may also work with any other stream-like resource that the underlying
 * OS supports.
 *
 * If data is immediately available on the file/socket, this will return that data
 * along with the actual number of bytes that were immediately available.  It will
 * not block.
 *
 * If no data is immediately available, this will wait up to the given timeout for
 * data to appear.  If no data appears within the timeout period, then this returns
 * an error code (not zero).
 *
 * In all cases this will return successfully as soon as at least 1 byte of actual
 * data is available.  It will not attempt to read the entire input buffer.
 *
 * If an EOF condition occurs prior to timeout, this function returns zero.
 */
int32           OS_TimedRead(uint32  filedes, void *buffer, uint32 nbytes, int32 timeout);

/**
 * File/Stream output write with a timeout
 *
 * This implements a time-limited write and is primarily intended for use with
 * sockets but may also work with any other stream-like resource that the underlying
 * OS supports.
 *
 * If output buffer space is immediately available on the file/socket, this will
 * place data into the buffer and return the actual number of bytes that were
 * queued for output.  It will not block.
 *
 * If no output buffer space is immediately available, this will wait up to the
 * given timeout for space to become available.  If no space becomes available within
 * the timeout period, then this returns an error code (not zero).
 *
 * In all cases this will return successfully as soon as at least 1 byte of actual
 * data is output.  It will _not_ attempt to write the entire output buffer.
 *
 * If an EOF condition occurs prior to timeout, this function returns zero.
 */
int32           OS_TimedWrite(uint32  filedes, const void *buffer, uint32 nbytes, int32 timeout);

/************************************************************************/
/** \brief Chmod file
**
**  \par Description
**       Writes to a file. Copies up to a maximum of nbtyes of buffer to the file
**       described in filedes
**
**  \par Assumptions, External Events, and Notes:
**       Not implemented
**
**  \param [in]   path         File path
**  \param [in]   access       #OS_READ_ONLY, #OS_WRITE_ONLY, or #OS_READ_WRITE
**  
*************************************************************************/
int32           OS_chmod  (const char *path, uint32 access);

/************************************************************************/
/** \brief Open file
**
**  \par Description
**       Returns information about a file or directory in a os_fs_stat structure
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       path         File path
**  \param [in/out]   filestats    #os_fstat_t Stats struct
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  File descriptor if success
**  \endreturns
**
*************************************************************************/
int32           OS_stat   (const char *path, os_fstat_t  *filestats);

/************************************************************************/
/** \brief File offset
**
**  \par Description
**       Sets the read/write pointer to a specific offset in a specific file. 
**       Whence is either OS_SEEK_SET, OS_SEEK_CUR, or OS_SEEK_END
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       filedes        #int32 File descriptor
**  \param [in]       offset         #int32 Offset amount
**  \param [in]       whence         #uint32 Offset type
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid \endcode
**  the new offset from the beginning of the file
**  \endreturns
**
*************************************************************************/
int32           OS_lseek  (uint32  filedes, int32 offset, uint32 whence);

/************************************************************************/
/** \brief Remove file
**
**  \par Description
**       Removes a given filename from the drive
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       path         File path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_remove (const char *path);

/************************************************************************/
/** \brief Rename file
**
**  \par Description
**       Renames a file
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       path         File path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_rename (const char *old_filename, const char *new_filename);

/************************************************************************/
/** \brief Copy file
**
**  \par Description
**       Copies a single file from src to dest
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       src         Source file path
**  \param [in]       dest        Destination file path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_cp (const char *src, const char *dest);

/************************************************************************/
/** \brief Move file
**
**  \par Description
**       Moves a single file from src to dest
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       src         Source file path
**  \param [in]       dest        Destination file path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERR_NAME_TOO_LONG if the name of the file is too long \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_mv (const char *src, const char *dest);

/************************************************************************/
/** \brief Get file info
**
**  \par Description
**       Copies the information of the given file descriptor into a structure passed in
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       filedes        #int32 File descriptor
**  \param [in]       fd_prop        #OS_FDTableEntry Pointer to file property struct
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_FDGetInfo (uint32 filedes, OS_file_prop_t *fd_prop);

/************************************************************************/
/** \brief File open check
**
**  \par Description
**       Checks to see if a file is open 
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]       Filename         File path
**  
**  \returns
**  \retcode #OS_FS_ERROR if the file is not open  \endcode
**  \retcode #OS_FS_SUCCESS if the file is open  \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_FileOpenCheck(const char *Filename);

/************************************************************************/
/** \brief Close all files
**
**  \par Description
**       Closes All open files that were opened through the OSAL 
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #OS_FS_ERROR if one or more file close returned an error  \endcode
**  \retcode #OS_FS_SUCCESS if the files were all closed without error  \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_CloseAllFiles(void);

/************************************************************************/
/** \brief Close file by name
**
**  \par Description
**       Allows a file to be closed by name.
**
**  \par Assumptions, External Events, and Notes:
**       This will only work if the name passed in is the same name used to open 
**       the file.
**
**  \param [in]       src         Source file path
**  \param [in]       dest        Destination file path
**  
**  \returns
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERROR if the file close returned an error \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32 OS_CloseFileByName(const char *Filename);


/******************************************************************************
** Directory API 
******************************************************************************/

#ifndef OSAL_OMIT_DEPRECATED
/************************************************************************/
/** \brief Open directory
**
**  \par Description
**       Opens a directory for searching
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   path         File path
**  
**  \returns
**  NULL if there is an error  
**  Pointer to a directory if success
**  \endreturns
**
*************************************************************************/
os_dirp_t       OS_opendir (const char *path);

/************************************************************************/
/** \brief Close directory
**
**  \par Description
**       Closes a directory
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   path         File path
**  \param [in]   access       #OS_READ_ONLY, #OS_WRITE_ONLY, or #OS_READ_WRITE
**  
**  \returns
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_closedir(os_dirp_t directory);

/************************************************************************/
/** \brief Rewind directory
**
**  \par Description
**       Rewinds the directory pointer
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   directory         #os_dirp_t 
**  
*************************************************************************/
void            OS_rewinddir(os_dirp_t directory);

/************************************************************************/
/** \brief Get next directory entry
**
**  \par Description
**       Obtains directory entry data for the next file from an open directory
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   directory         #os_dirp_t 
**  
**  \returns
**  a pointer to the next entry for success
**  NULL if error or end of directory is reached
**  \endreturns
**
*************************************************************************/
os_dirent_t *   OS_readdir (os_dirp_t directory);

#endif


/*
 * Opens a directory for searching
 * Same as OS_opendir but with a OSAL-style API
 */
int32           OS_DirectoryOpen(uint32 *dir_id, const char *path);

/*
 * Closes an open directory
 * Same as OS_closedir but with a OSAL-style API
 */
int32           OS_DirectoryClose(uint32 dir_id);

/*
 * Rewinds an open directory
 * Same as OS_rewinddir but with a OSAL-style API
 */
int32           OS_DirectoryRewind(uint32 dir_id);

/*
 * Reads the next object in the directory
 * Same as OS_readdir but with a OSAL-style API
 */
int32           OS_DirectoryRead(uint32 dir_id, os_dirent_t *dirent);

/************************************************************************/
/** \brief Make directory
**
**  \par Description
**       Makes a directory specified by path.
**
**  \par Assumptions, External Events, and Notes:
**       The access parameter is currently unused.
**
**  \param [in]   path         File path
**  \param [in]   access       #OS_READ_ONLY, #OS_WRITE_ONLY, or #OS_READ_WRITE
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_mkdir   (const char *path, uint32 access);

/************************************************************************/
/** \brief Remove directory
**
**  \par Description
**       Removes a directory from  the structure (must be an empty directory)
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   path         File path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_rmdir   (const char *path);

/******************************************************************************
** System Level API 
******************************************************************************/

/************************************************************************/
/** \brief Make file system
**
**  \par Description
**       Makes a file system on the target
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   address         TODO: Not used
**  \param [in]   devname         Name of device
**  \param [in]   volname         Name of volume
**  \param [in]   blocksize       Block size for file system
**  \param [in]   numblocks       Number of blocks
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_DRIVE_NOT_CREATED if the OS calls to create the the drive failed \endcode
**  \retcode #OS_FS_ERR_DEVICE_NOT_FREE if the volume table is full \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_FileSysAddFixedMap(uint32 *filesys_id, const char *phys_path,
                                const char *virt_path);

/*
 * Makes a file system
*/
int32           OS_mkfs        (char *address, const char *devname, const char *volname,
                                uint32 blocksize, uint32 numblocks);

/************************************************************************/
/** \brief Mount file system
**
**  \par Description
**       Mounts a drive.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   devname         Name of device
**  \param [in]   mountpoint      Mount point for the file system
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_mount       (const char *devname, const char *mountpoint);

/************************************************************************/
/** \brief Initialize file system
**
**  \par Description
**       Inititalizes a file system on the target
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   address         TODO: Not used
**  \param [in]   devname         Name of device
**  \param [in]   volname         Name of volume
**  \param [in]   blocksize       Block size for file system
**  \param [in]   numblocks       Number of blocks
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_DEVICE_NOT_FREE if the volume table is full \endcode
**  \retcode #OS_FS_ERR_DRIVE_NOT_CREATED on error \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_initfs      (char *address, const char *devname, const char *volname,
                                uint32 blocksize, uint32 numblocks);

/************************************************************************/
/** \brief Initialize file system
**
**  \par Description
**       Inititalizes a file system on the target
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   devname         Name of device
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERROR is the drive specified cannot be located \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_rmfs        (const char *devname);

/************************************************************************/
/** \brief Unmount file system
**
**  \par Description
**       Unmounts a drive.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   mountpoint      Mount point for the file system
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32           OS_unmount     (const char *mountpoint);

/************************************************************************/
/** \brief Get blocks free
**
**  \par Description
**       Returns the number of free blocks in a volume
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   name         Name of volume
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  The number of blocks free in a volume if success
**  \endreturns
**
*************************************************************************/
int32           OS_fsBlocksFree (const char *name);

/************************************************************************/
/** \brief Get bytes free
**
**  \par Description
**       Returns the number of free bytes in a volume
**
**  \par Assumptions, External Events, and Notes:
**       The 64 bit data type to support filesystems that
**       are greater than 4 Gigabytes
**
**  \param [in]   name         Name of volume
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  The number of blocks free in a volume if success
**  \endreturns
**
*************************************************************************/
int32 OS_fsBytesFree (const char *name, uint64 *bytes_free);

/************************************************************************/
/** \brief Check filesystem
**
**  \par Description
**       Checks the drives for inconsisenties and either repairs it or not
**
**  \par Assumptions, External Events, and Notes:
**       Not implemented
**
**  \param [in]   name         Name of volume
**  \param [in]   repair       #boolean Repair flag
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32   OS_chkfs       (const char *name, bool repair);

/************************************************************************/
/** \brief Get drive name
**
**  \par Description
**       Returns the name of the physical volume associated with the drive,
**       when given the OSAL mount point of the drive
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in/out]   PhysDriveName         Name of volume
**  \param [in]       MountPoint            Mount point for the file system
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERROR if permissions are unknown or OS call fails \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32       OS_FS_GetPhysDriveName  (char * PhysDriveName, const char * MountPoint);

/************************************************************************/
/** \brief Translate path
**
**  \par Description
**       Because of the abstraction of the filesystem across OSes, we have to change
**       the name of the {file, directory, drive} to be what the OS can actually 
**       accept
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]           VirtualPath         Path to convert
**  \param [in/out]       LocalPath           Converted path
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_ERR_PATH_TOO_LONG if path exceeds the maximum number of chars \endcode
**  \retcode #OS_FS_ERR_PATH_INVALID if path cannot be parsed \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32       OS_TranslatePath ( const char *VirtualPath, char *LocalPath);


/************************************************************************/
/** \brief Get file system info
**
**  \par Description
**       Returns information about the file system in an os_fsinfo_t
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in/out]       filesys_info        #os_fsinfo_t Pointer to info struct
**  
**  \returns
**  \retcode #OS_FS_ERR_INVALID_POINTER if path is NULL \endcode
**  \retcode #OS_FS_SUCCESS if success \endcode
**  \endreturns
**
*************************************************************************/
int32       OS_GetFsInfo(os_fsinfo_t  *filesys_info);

/******************************************************************************
** Shell API
******************************************************************************/

/* executes the shell command passed into is and writes the output of that 
 * command to the file specified by the given OSAPI file descriptor */
/* --------------------------------------------------------------------------------------
    Name: OS_ShellOutputToFile
    
    Purpose: Takes a shell command in and writes the output of that command to the specified file
    
    Returns: OS_FS_ERROR if the command was not executed properly
             OS_FS_ERR_INVALID_FD if the file descriptor passed in is invalid
             OS_SUCCESS if success
 ---------------------------------------------------------------------------------------*/
int32 OS_ShellOutputToFile(const char* Cmd, uint32 filedes);

#endif
