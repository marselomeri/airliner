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

#include "osapi.h"



int32           OS_FS_Init(void)
{
	return OS_ERROR;
}



int32           OS_creat  (const char *path, int32  access)
{
	return OS_ERROR;
}



int32           OS_open   (const char *path,  int32 access,  uint32 mode)
{
	return OS_ERROR;
}



int32           OS_close  (int32  filedes)
{
	return OS_ERROR;
}



int32           OS_read   (int32  filedes, void *buffer, uint32 nbytes)
{
	return OS_ERROR;
}



int32           OS_write  (int32  filedes, void *buffer, uint32 nbytes)
{
	return OS_ERROR;
}



int32           OS_chmod  (const char *path, uint32 access)
{
	return OS_ERROR;
}



int32           OS_stat   (const char *path, os_fstat_t  *filestats)
{
	return OS_ERROR;
}



int32           OS_lseek  (int32  filedes, int32 offset, uint32 whence)
{
	return OS_ERROR;
}



int32           OS_remove (const char *path)
{
	return OS_ERROR;
}



int32           OS_rename (const char *old_filename, const char *new_filename)
{
	return OS_ERROR;
}



int32 OS_cp (const char *src, const char *dest)
{
	return OS_ERROR;
}



int32 OS_mv (const char *src, const char *dest)
{
	return OS_ERROR;
}



int32 OS_FDGetInfo (int32 filedes, OS_FDTableEntry *fd_prop)
{
	return OS_ERROR;
}



int32 OS_FileOpenCheck(char *Filename)
{
	return OS_ERROR;
}



int32 OS_CloseAllFiles(void)
{
	return OS_ERROR;
}



int32 OS_CloseFileByName(char *Filename)
{
	return OS_ERROR;
}


/******************************************************************************
** Directory API
******************************************************************************/

int32           OS_mkdir   (const char *path, uint32 access)
{
	return OS_ERROR;
}



os_dirp_t       OS_opendir (const char *path)
{
	return OS_ERROR;
}



int32           OS_closedir(os_dirp_t directory)
{
	return OS_ERROR;
}



void           OS_rewinddir(os_dirp_t directory)
{
}



os_dirent_t *   OS_readdir (os_dirp_t directory)
{
	return OS_ERROR;
}



int32           OS_rmdir   (const char *path)
{
	return OS_ERROR;
}




/******************************************************************************
** Shell API
******************************************************************************/

int32 OS_ShellOutputToFile(char* Cmd, int32 OS_fd)
{
	return OS_ERROR;
}


