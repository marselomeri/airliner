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
