#include "pb_lib.h"

void AE_RegisterSerializationFuncs()
{
	int32 Status = CFE_SUCCESS;

	/* Register each message with PBL */
	Status = PBLIB_RegisterMessage(0x1c55, 1, "PX4_SensorBaroMsg_t")
	if (Status != CFE_SUCCESS)
	{
		goto AE_RegisterSerializationFuncs_Exit_Tag;
	}
	
	Status = PBLIB_RegisterMessage(0x1c76, 0, "PX4_SensorAccelMsg_t")
	if (Status != CFE_SUCCESS)
	{
		goto AE_RegisterSerializationFuncs_Exit_Tag;
	}
	
AE_RegisterSerializationFuncs_Exit_Tag:
    return Status;
}

uint32 PX4_SensorBaroMsg_t_Enc(const PX4_SensorBaroMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_baro_pb pbMsg;
	
	strcpy(pbMsg.pressure, inObject->Pressure);
	pbMsg.altitude = inObject->Altitude;
	pbMsg.error_count = inObject->ErrorCount;
	strcpy(pbMsg.temperature, inObject->Temperature);

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_baro_pb_fields, &pbMsg); 

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4_SensorBaroMsg_t_Dec(const char *inBuffer, uint32 inSize, PX4_SensorBaroMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_baro_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_baro_pb_fields, &pbMsg); 

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
	
	strcpy(inOutObject->Pressure, pbMsg.pressure);
	inOutObject->Altitude = pbMsg.altitude;
	inOutObject->ErrorCount = pbMsg.error_count;
	strcpy(inOutObject->Temperature, pbMsg.temperature);

	return sizeof(PX4_SensorBaroMsg_t);
}

uint32 PX4_SensorAccelMsg_t_Enc(const PX4_SensorAccelMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;
	
	strcpy(pbMsg.integral_dt, inObject->IntegralDt);
	pbMsg.x = inObject->X;
	pbMsg.temperature_raw_count = 3;
	pbMsg.temperature_raw[0] = inObject->TemperatureRaw[0];
	pbMsg.temperature_raw[1] = inObject->TemperatureRaw[1];
	pbMsg.temperature_raw[2] = inObject->TemperatureRaw[2];
	pbMsg.error_count_count = 3;
	strcpy(pbMsg.error_count[0], inObject->ErrorCount[0]);
	strcpy(pbMsg.error_count[1], inObject->ErrorCount[1]);
	strcpy(pbMsg.error_count[2], inObject->ErrorCount[2]);

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_accel_pb_fields, &pbMsg); 

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4_SensorAccelMsg_t_Dec(const char *inBuffer, uint32 inSize, PX4_SensorAccelMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_accel_pb_fields, &pbMsg); 

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
	
	strcpy(inOutObject->IntegralDt, pbMsg.integral_dt);
	inOutObject->X = pbMsg.x;
	inOutObject->TemperatureRaw[0] = pbMsg.temperature_raw[0];
	inOutObject->TemperatureRaw[1] = pbMsg.temperature_raw[1];
	inOutObject->TemperatureRaw[2] = pbMsg.temperature_raw[2];
	strcpy(inOutObject->ErrorCount[0], pbMsg.error_count[0]);
	strcpy(inOutObject->ErrorCount[1], pbMsg.error_count[1]);
	strcpy(inOutObject->ErrorCount[2], pbMsg.error_count[2]);

	return sizeof(PX4_SensorAccelMsg_t);
}

