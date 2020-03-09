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
#include <string.h>



int32 OS_mkfs(char *address, const char *devname, const char * volname, uint32 blocksize,
              uint32 numblocks)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_rmfs(const char *devname)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_initfs(char *address, const char *devname, const char *volname,
                uint32 blocksize, uint32 numblocks)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_mount(const char *devname, const char* mountpoint)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_unmount(const char *mountpoint)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_fsBlocksFree(const char *name)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_fsBytesFree(const char *name, uint64 *bytes_free)
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



os_fshealth_t OS_chkfs(const char *name, boolean repair)
{
    OS_printf("%s\n", __FUNCTION__);

    return 0;

}



int32 OS_FS_GetPhysDriveName(char * PhysDriveName, char * MountPoint)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_FS_UNIMPLEMENTED;

}



int32 OS_TranslatePath(const char *VirtualPath, char *LocalPath)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_FS_UNIMPLEMENTED;

}



int32 OS_FS_GetErrorName(int32 error_num, os_fs_err_name_t * err_name)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_FS_UNIMPLEMENTED;

}



int32 OS_GetFsInfo(os_fsinfo_t  *filesys_info)
{
    OS_printf("%s\n", __FUNCTION__);

    return OS_FS_UNIMPLEMENTED;

}


