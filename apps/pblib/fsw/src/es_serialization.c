/****************************************************************************
 *
 *   Copyright (c) 2016-2017 Windhover Labs, L.L.C. All rights reserved.
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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 ****************************************************************************/

#include "es_serialization.h"

uint32 CFE_ES_OverWriteSysLogCmd_t_Enc(const CFE_ES_OverWriteSysLogCmd_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	es_log_pb pbMsg;
	
    pbMsg.Mode = inObject->Payload.Mode;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, es_log_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 CFE_ES_OverWriteSysLogCmd_t_Dec(const char *inBuffer, uint32 inSize, CFE_ES_OverWriteSysLogCmd_t *inOutObject)
{
	bool status = false;
	es_log_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, es_log_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

    inOutObject->Payload.Mode = pbMsg.Mode;

	return sizeof(CFE_ES_OverWriteSysLogCmd_t);
}
