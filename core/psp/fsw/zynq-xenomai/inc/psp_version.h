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

/*
**  $Id: psp_version.h 1.2.2.3 2014/10/01 15:41:26GMT-05:00 sstrege Exp  $
**
**
**      Copyright (c) 2004-2011, United States Government as represented by 
**      Administrator for The National Aeronautics and Space Administration. 
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement. 
**
**
**
**  Purpose:
**  Provide version identifiers for the cFE Platform Support Packages (PSP).
**
*/

#ifndef _psp_version_
#define _psp_version_


/*
** Macro Definitions
*/
#define CFE_PSP_IMPL_MAJOR_VERSION          1
#define CFE_PSP_IMPL_MINOR_VERSION          3
#define CFE_PSP_IMPL_REVISION               0
#define CFE_PSP_IMPL_MISSION_REV            0

#ifndef _ENHANCED_BUILD_

#define CFE_PSP_MAJOR_VERSION          CFE_PSP_IMPL_MAJOR_VERSION
#define CFE_PSP_MINOR_VERSION          CFE_PSP_IMPL_MINOR_VERSION
#define CFE_PSP_REVISION               CFE_PSP_IMPL_REVISION
#define CFE_PSP_MISSION_REV            CFE_PSP_IMPL_MISSION_REV

/* For backwards compatibility */
#define CFE_PSP_SUBMINOR_VERSION       CFE_PSP_IMPL_REVISION 

#endif

#endif  /* _psp_version_ */

