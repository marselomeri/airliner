# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_GPS_AppCustomData_t.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='_py_GPS_AppCustomData_t.proto',
  package='',
  serialized_pb=_b('\n\x1d_py_GPS_AppCustomData_t.proto\"\xb1\x01\n\x15GPS_ParserStatus_t_pb\x12\x0f\n\x07\x43lassID\x18\x01 \x02(\r\x12\x15\n\rPayloadCursor\x18\x02 \x02(\r\x12\x11\n\tMsgLength\x18\x03 \x02(\r\x12\x11\n\tChecksumA\x18\x04 \x02(\r\x12\x12\n\nParseError\x18\x05 \x02(\r\x12\r\n\x05MsgID\x18\x06 \x02(\r\x12\x13\n\x0bMsgReceived\x18\x07 \x02(\r\x12\x12\n\nParseState\x18\x08 \x02(\r\"\x9d\x01\n\x19PX4_SatelliteInfoMsg_t_pb\x12\r\n\x05\x43ount\x18\x01 \x02(\r\x12\x0c\n\x04Used\x18\x02 \x03(\r\x12\x11\n\tElevation\x18\x03 \x03(\r\x12\x11\n\tTimestamp\x18\x04 \x02(\x04\x12\x0c\n\x04SVID\x18\x05 \x03(\r\x12\x11\n\tTlmHeader\x18\x06 \x03(\r\x12\x0b\n\x03SNR\x18\x07 \x03(\r\x12\x0f\n\x07\x41zimuth\x18\x08 \x03(\r\"\xd6\x03\n\x1ePX4_VehicleGpsPositionMsg_t_pb\x12\x0f\n\x07\x46ixType\x18\x01 \x02(\r\x12\x16\n\x0eSatellitesUsed\x18\x02 \x02(\r\x12\x0b\n\x03Lon\x18\x03 \x02(\x05\x12\x11\n\tVel_d_m_s\x18\x04 \x02(\x02\x12\x0b\n\x03\x43OG\x18\x05 \x02(\x02\x12\x11\n\tSVariance\x18\x06 \x02(\x02\x12\x18\n\x10JammingIndicator\x18\x07 \x02(\x05\x12\x11\n\tTimestamp\x18\x08 \x02(\x04\x12\x13\n\x0bVelNedValid\x18\t \x02(\x08\x12\x11\n\tTlmHeader\x18\n \x03(\r\x12\x0b\n\x03Lat\x18\x0b \x02(\x05\x12\x0c\n\x04VDOP\x18\x0c \x02(\x02\x12\x0c\n\x04HDOP\x18\r \x02(\x02\x12\x1d\n\x15TimestampTimeRelative\x18\x0e \x02(\x05\x12\x11\n\tCVariance\x18\x0f \x02(\x02\x12\x13\n\x0bTimeUtcUsec\x18\x10 \x02(\x04\x12\x14\n\x0c\x41ltEllipsoid\x18\x11 \x02(\x05\x12\x12\n\nNoisePerMs\x18\x12 \x02(\x05\x12\x0b\n\x03\x45pV\x18\x13 \x02(\x02\x12\x11\n\tVel_n_m_s\x18\x14 \x02(\x02\x12\x0f\n\x07Vel_m_s\x18\x15 \x02(\x02\x12\x0b\n\x03\x45pH\x18\x16 \x02(\x02\x12\x0b\n\x03\x41lt\x18\x17 \x02(\x05\x12\x11\n\tVel_e_m_s\x18\x18 \x02(\x02\"\x91\x04\n\x16GPS_AppCustomData_t_pb\x12\x0c\n\x04\x42\x61ud\x18\x01 \x02(\r\x12\x0e\n\x06Status\x18\x02 \x02(\r\x12\x31\n\rGpsSatInfoMsg\x18\x03 \x02(\x0b\x32\x1a.PX4_SatelliteInfoMsg_t_pb\x12\x14\n\x0c\x43ontinueFlag\x18\x04 \x02(\x08\x12\x17\n\x0fRateCountLatLon\x18\x05 \x02(\r\x12,\n\x0cParserStatus\x18\x06 \x02(\x0b\x32\x16.GPS_ParserStatus_t_pb\x12\x14\n\x0cRateCountVel\x18\x07 \x02(\r\x12\x13\n\x0b\x43hildTaskID\x18\x08 \x02(\r\x12\x15\n\rAckWaitingMsg\x18\t \x02(\r\x12\x14\n\x0cMutexSatInfo\x18\n \x02(\r\x12\x15\n\rStreamingTask\x18\x0b \x02(\r\x12\x10\n\x08\x41\x63kState\x18\x0c \x02(\r\x12\x11\n\tTaskFlags\x18\r \x02(\r\x12\x10\n\x08Priority\x18\x0e \x02(\r\x12\x11\n\tGotVelned\x18\x0f \x02(\x08\x12\x15\n\rMutexPosition\x18\x10 \x02(\r\x12\x16\n\x0e\x41\x63kWaitingRcvd\x18\x11 \x02(\x08\x12\x15\n\rAckRcvdMsgCls\x18\x12 \x02(\r\x12\x11\n\tGotPosllh\x18\x13 \x02(\x08\x12\x37\n\x0eGpsPositionMsg\x18\x14 \x02(\x0b\x32\x1f.PX4_VehicleGpsPositionMsg_t_pb')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_GPS_PARSERSTATUS_T_PB = _descriptor.Descriptor(
  name='GPS_ParserStatus_t_pb',
  full_name='GPS_ParserStatus_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ClassID', full_name='GPS_ParserStatus_t_pb.ClassID', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PayloadCursor', full_name='GPS_ParserStatus_t_pb.PayloadCursor', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MsgLength', full_name='GPS_ParserStatus_t_pb.MsgLength', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ChecksumA', full_name='GPS_ParserStatus_t_pb.ChecksumA', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ParseError', full_name='GPS_ParserStatus_t_pb.ParseError', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MsgID', full_name='GPS_ParserStatus_t_pb.MsgID', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MsgReceived', full_name='GPS_ParserStatus_t_pb.MsgReceived', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ParseState', full_name='GPS_ParserStatus_t_pb.ParseState', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=34,
  serialized_end=211,
)


_PX4_SATELLITEINFOMSG_T_PB = _descriptor.Descriptor(
  name='PX4_SatelliteInfoMsg_t_pb',
  full_name='PX4_SatelliteInfoMsg_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Count', full_name='PX4_SatelliteInfoMsg_t_pb.Count', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Used', full_name='PX4_SatelliteInfoMsg_t_pb.Used', index=1,
      number=2, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Elevation', full_name='PX4_SatelliteInfoMsg_t_pb.Elevation', index=2,
      number=3, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='PX4_SatelliteInfoMsg_t_pb.Timestamp', index=3,
      number=4, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SVID', full_name='PX4_SatelliteInfoMsg_t_pb.SVID', index=4,
      number=5, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TlmHeader', full_name='PX4_SatelliteInfoMsg_t_pb.TlmHeader', index=5,
      number=6, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SNR', full_name='PX4_SatelliteInfoMsg_t_pb.SNR', index=6,
      number=7, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Azimuth', full_name='PX4_SatelliteInfoMsg_t_pb.Azimuth', index=7,
      number=8, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=214,
  serialized_end=371,
)


_PX4_VEHICLEGPSPOSITIONMSG_T_PB = _descriptor.Descriptor(
  name='PX4_VehicleGpsPositionMsg_t_pb',
  full_name='PX4_VehicleGpsPositionMsg_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='FixType', full_name='PX4_VehicleGpsPositionMsg_t_pb.FixType', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SatellitesUsed', full_name='PX4_VehicleGpsPositionMsg_t_pb.SatellitesUsed', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Lon', full_name='PX4_VehicleGpsPositionMsg_t_pb.Lon', index=2,
      number=3, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Vel_d_m_s', full_name='PX4_VehicleGpsPositionMsg_t_pb.Vel_d_m_s', index=3,
      number=4, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='COG', full_name='PX4_VehicleGpsPositionMsg_t_pb.COG', index=4,
      number=5, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SVariance', full_name='PX4_VehicleGpsPositionMsg_t_pb.SVariance', index=5,
      number=6, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='JammingIndicator', full_name='PX4_VehicleGpsPositionMsg_t_pb.JammingIndicator', index=6,
      number=7, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='PX4_VehicleGpsPositionMsg_t_pb.Timestamp', index=7,
      number=8, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VelNedValid', full_name='PX4_VehicleGpsPositionMsg_t_pb.VelNedValid', index=8,
      number=9, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TlmHeader', full_name='PX4_VehicleGpsPositionMsg_t_pb.TlmHeader', index=9,
      number=10, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Lat', full_name='PX4_VehicleGpsPositionMsg_t_pb.Lat', index=10,
      number=11, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VDOP', full_name='PX4_VehicleGpsPositionMsg_t_pb.VDOP', index=11,
      number=12, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HDOP', full_name='PX4_VehicleGpsPositionMsg_t_pb.HDOP', index=12,
      number=13, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TimestampTimeRelative', full_name='PX4_VehicleGpsPositionMsg_t_pb.TimestampTimeRelative', index=13,
      number=14, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CVariance', full_name='PX4_VehicleGpsPositionMsg_t_pb.CVariance', index=14,
      number=15, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TimeUtcUsec', full_name='PX4_VehicleGpsPositionMsg_t_pb.TimeUtcUsec', index=15,
      number=16, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AltEllipsoid', full_name='PX4_VehicleGpsPositionMsg_t_pb.AltEllipsoid', index=16,
      number=17, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='NoisePerMs', full_name='PX4_VehicleGpsPositionMsg_t_pb.NoisePerMs', index=17,
      number=18, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EpV', full_name='PX4_VehicleGpsPositionMsg_t_pb.EpV', index=18,
      number=19, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Vel_n_m_s', full_name='PX4_VehicleGpsPositionMsg_t_pb.Vel_n_m_s', index=19,
      number=20, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Vel_m_s', full_name='PX4_VehicleGpsPositionMsg_t_pb.Vel_m_s', index=20,
      number=21, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EpH', full_name='PX4_VehicleGpsPositionMsg_t_pb.EpH', index=21,
      number=22, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Alt', full_name='PX4_VehicleGpsPositionMsg_t_pb.Alt', index=22,
      number=23, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Vel_e_m_s', full_name='PX4_VehicleGpsPositionMsg_t_pb.Vel_e_m_s', index=23,
      number=24, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=374,
  serialized_end=844,
)


_GPS_APPCUSTOMDATA_T_PB = _descriptor.Descriptor(
  name='GPS_AppCustomData_t_pb',
  full_name='GPS_AppCustomData_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Baud', full_name='GPS_AppCustomData_t_pb.Baud', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Status', full_name='GPS_AppCustomData_t_pb.Status', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='GpsSatInfoMsg', full_name='GPS_AppCustomData_t_pb.GpsSatInfoMsg', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ContinueFlag', full_name='GPS_AppCustomData_t_pb.ContinueFlag', index=3,
      number=4, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RateCountLatLon', full_name='GPS_AppCustomData_t_pb.RateCountLatLon', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ParserStatus', full_name='GPS_AppCustomData_t_pb.ParserStatus', index=5,
      number=6, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RateCountVel', full_name='GPS_AppCustomData_t_pb.RateCountVel', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ChildTaskID', full_name='GPS_AppCustomData_t_pb.ChildTaskID', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AckWaitingMsg', full_name='GPS_AppCustomData_t_pb.AckWaitingMsg', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MutexSatInfo', full_name='GPS_AppCustomData_t_pb.MutexSatInfo', index=9,
      number=10, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StreamingTask', full_name='GPS_AppCustomData_t_pb.StreamingTask', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AckState', full_name='GPS_AppCustomData_t_pb.AckState', index=11,
      number=12, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TaskFlags', full_name='GPS_AppCustomData_t_pb.TaskFlags', index=12,
      number=13, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Priority', full_name='GPS_AppCustomData_t_pb.Priority', index=13,
      number=14, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='GotVelned', full_name='GPS_AppCustomData_t_pb.GotVelned', index=14,
      number=15, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MutexPosition', full_name='GPS_AppCustomData_t_pb.MutexPosition', index=15,
      number=16, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AckWaitingRcvd', full_name='GPS_AppCustomData_t_pb.AckWaitingRcvd', index=16,
      number=17, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AckRcvdMsgCls', full_name='GPS_AppCustomData_t_pb.AckRcvdMsgCls', index=17,
      number=18, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='GotPosllh', full_name='GPS_AppCustomData_t_pb.GotPosllh', index=18,
      number=19, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='GpsPositionMsg', full_name='GPS_AppCustomData_t_pb.GpsPositionMsg', index=19,
      number=20, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=847,
  serialized_end=1376,
)

_GPS_APPCUSTOMDATA_T_PB.fields_by_name['GpsSatInfoMsg'].message_type = _PX4_SATELLITEINFOMSG_T_PB
_GPS_APPCUSTOMDATA_T_PB.fields_by_name['ParserStatus'].message_type = _GPS_PARSERSTATUS_T_PB
_GPS_APPCUSTOMDATA_T_PB.fields_by_name['GpsPositionMsg'].message_type = _PX4_VEHICLEGPSPOSITIONMSG_T_PB
DESCRIPTOR.message_types_by_name['GPS_ParserStatus_t_pb'] = _GPS_PARSERSTATUS_T_PB
DESCRIPTOR.message_types_by_name['PX4_SatelliteInfoMsg_t_pb'] = _PX4_SATELLITEINFOMSG_T_PB
DESCRIPTOR.message_types_by_name['PX4_VehicleGpsPositionMsg_t_pb'] = _PX4_VEHICLEGPSPOSITIONMSG_T_PB
DESCRIPTOR.message_types_by_name['GPS_AppCustomData_t_pb'] = _GPS_APPCUSTOMDATA_T_PB

GPS_ParserStatus_t_pb = _reflection.GeneratedProtocolMessageType('GPS_ParserStatus_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _GPS_PARSERSTATUS_T_PB,
  __module__ = '_py_GPS_AppCustomData_t_pb2'
  # @@protoc_insertion_point(class_scope:GPS_ParserStatus_t_pb)
  ))
_sym_db.RegisterMessage(GPS_ParserStatus_t_pb)

PX4_SatelliteInfoMsg_t_pb = _reflection.GeneratedProtocolMessageType('PX4_SatelliteInfoMsg_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_SATELLITEINFOMSG_T_PB,
  __module__ = '_py_GPS_AppCustomData_t_pb2'
  # @@protoc_insertion_point(class_scope:PX4_SatelliteInfoMsg_t_pb)
  ))
_sym_db.RegisterMessage(PX4_SatelliteInfoMsg_t_pb)

PX4_VehicleGpsPositionMsg_t_pb = _reflection.GeneratedProtocolMessageType('PX4_VehicleGpsPositionMsg_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_VEHICLEGPSPOSITIONMSG_T_PB,
  __module__ = '_py_GPS_AppCustomData_t_pb2'
  # @@protoc_insertion_point(class_scope:PX4_VehicleGpsPositionMsg_t_pb)
  ))
_sym_db.RegisterMessage(PX4_VehicleGpsPositionMsg_t_pb)

GPS_AppCustomData_t_pb = _reflection.GeneratedProtocolMessageType('GPS_AppCustomData_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _GPS_APPCUSTOMDATA_T_PB,
  __module__ = '_py_GPS_AppCustomData_t_pb2'
  # @@protoc_insertion_point(class_scope:GPS_AppCustomData_t_pb)
  ))
_sym_db.RegisterMessage(GPS_AppCustomData_t_pb)


# @@protoc_insertion_point(module_scope)
