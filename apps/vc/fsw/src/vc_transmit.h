/*==============================================================================
Copyright (c) 2017, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of CmdIn nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY VCPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, VCEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @defgroup Transmit
 * @addtogroup Transmit
 * @file vc_transmit_udp.h
 * @brief Custom UDP layer for Video Controller.
 * @{
 */
 
#ifndef VC_TRANSMIT_H
#define VC_TRANSMIT_H

/**
 * @brief Initialize configured resources.
 * @return true if successful, otherwise false
 */
boolean VC_Transmit_Init(void);


/**
 * @brief Uninitialize previously initialized resources.
 * @return true if successful, otherwise false
 */
boolean VC_Transmit_Uninit(void);


/**
 * @brief Verify an address
 * @param Address the address to verify
 * @return true if successful, otherwise false
 */
boolean VC_Address_Verification(const char *Address);


/**
 * @brief Update the transmit destination
 * @param Address the address to update
 * @param Port the port to update
 * @return true if successful, otherwise false
 */
boolean VC_Update_Destination(const char *Address, uint16 Port);


/**
 * @brief Transmit data using a previously initialized handle.
 * @param buf points to a buffer containing the data to be sent.
 * @param len specifies the size of the data in bytes.
 * @return On success, returns the number of bytes sent. On error, -1 is
 * returned.
 */
int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size);

#endif

/* @} */
