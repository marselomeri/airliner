uint32 AE_SensorAccel_Enc(const PX4_SensorAccelMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;
	
	pbMsg.temperature = inObject->Temperature;
	pbMsg.integral_dt = inObject->IntegralDt;
	pbMsg.y_integral = inObject->YIntegral;
	pbMsg.range_m_s2 = inObject->Range_m_s2;
	pbMsg.z_integral = inObject->ZIntegral;
	pbMsg.scaling = inObject->Scaling;
	pbMsg.y_raw = inObject->YRaw;
	pbMsg.z_raw = inObject->ZRaw;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.device_id = inObject->DeviceID;
	pbMsg.y = inObject->Y;
	pbMsg.x = inObject->X;
	pbMsg.z = inObject->Z;
	pbMsg.temperature_raw = inObject->TemperatureRaw;
	pbMsg.x_raw = inObject->XRaw;
	pbMsg.x_integral = inObject->XIntegral;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_accel_pb_fields, &pbMsg); // TODO: Assumes [type]_fields is a standard
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 AE_SensorAccel_Dec(const char *inBuffer, uint32 inSize, PX4_SensorAccelMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_accel_pb_fields, &pbMsg); // TODO: Assumes [type]_fields is a standard

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
	
	inOutObject->Temperature = pbMsg.temperature;
	inOutObject->IntegralDt = pbMsg.integral_dt;
	inOutObject->YIntegral = pbMsg.y_integral;
	inOutObject->Range_m_s2 = pbMsg.range_m_s2;
	inOutObject->ZIntegral = pbMsg.z_integral;
	inOutObject->Scaling = pbMsg.scaling;
	inOutObject->YRaw = pbMsg.y_raw;
	inOutObject->ZRaw = pbMsg.z_raw;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->DeviceID = pbMsg.device_id;
	inOutObject->Y = pbMsg.y;
	inOutObject->X = pbMsg.x;
	inOutObject->Z = pbMsg.z;
	inOutObject->TemperatureRaw = pbMsg.temperature_raw;
	inOutObject->XRaw = pbMsg.x_raw;
	inOutObject->XIntegral = pbMsg.x_integral;

	return sizeof(PX4_SensorAccelMsg_t);
}
