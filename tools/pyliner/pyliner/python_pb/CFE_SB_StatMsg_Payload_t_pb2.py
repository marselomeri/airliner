# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_CFE_SB_StatMsg_Payload_t.proto

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
  name='_py_CFE_SB_StatMsg_Payload_t.proto',
  package='',
  serialized_pb=_b('\n\"_py_CFE_SB_StatMsg_Payload_t.proto\"l\n\x1a\x43\x46\x45_SB_PipeDepthStats_t_pb\x12\x11\n\tPeakInUse\x18\x01 \x02(\r\x12\r\n\x05\x44\x65pth\x18\x02 \x02(\r\x12\r\n\x05Spare\x18\x03 \x02(\r\x12\x0e\n\x06PipeId\x18\x04 \x02(\t\x12\r\n\x05InUse\x18\x05 \x02(\r\"\xcc\x03\n\x1b\x43\x46\x45_SB_StatMsg_Payload_t_pb\x12\x17\n\x0fMaxPipesAllowed\x18\x01 \x02(\r\x12\x16\n\x0ePeakPipesInUse\x18\x02 \x02(\r\x12\x15\n\rMaxMemAllowed\x18\x03 \x02(\r\x12\x1b\n\x13MaxPipeDepthAllowed\x18\x04 \x02(\r\x12\x17\n\x0fPeakMsgIdsInUse\x18\x05 \x02(\r\x12\x1f\n\x17MaxSubscriptionsAllowed\x18\x06 \x02(\r\x12\x1a\n\x12PeakSBBuffersInUse\x18\x07 \x02(\r\x12\x33\n\x0ePipeDepthStats\x18\x08 \x03(\x0b\x32\x1b.CFE_SB_PipeDepthStats_t_pb\x12\x10\n\x08MemInUse\x18\t \x02(\r\x12\x12\n\nPipesInUse\x18\n \x02(\r\x12\x1e\n\x16PeakSubscriptionsInUse\x18\x0b \x02(\r\x12\x18\n\x10MaxMsgIdsAllowed\x18\x0c \x02(\r\x12\x16\n\x0eSBBuffersInUse\x18\r \x02(\r\x12\x1a\n\x12SubscriptionsInUse\x18\x0e \x02(\r\x12\x14\n\x0cPeakMemInUse\x18\x0f \x02(\r\x12\x13\n\x0bMsgIdsInUse\x18\x10 \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CFE_SB_PIPEDEPTHSTATS_T_PB = _descriptor.Descriptor(
  name='CFE_SB_PipeDepthStats_t_pb',
  full_name='CFE_SB_PipeDepthStats_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='PeakInUse', full_name='CFE_SB_PipeDepthStats_t_pb.PeakInUse', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Depth', full_name='CFE_SB_PipeDepthStats_t_pb.Depth', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Spare', full_name='CFE_SB_PipeDepthStats_t_pb.Spare', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PipeId', full_name='CFE_SB_PipeDepthStats_t_pb.PipeId', index=3,
      number=4, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='InUse', full_name='CFE_SB_PipeDepthStats_t_pb.InUse', index=4,
      number=5, type=13, cpp_type=3, label=2,
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
  serialized_start=38,
  serialized_end=146,
)


_CFE_SB_STATMSG_PAYLOAD_T_PB = _descriptor.Descriptor(
  name='CFE_SB_StatMsg_Payload_t_pb',
  full_name='CFE_SB_StatMsg_Payload_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='MaxPipesAllowed', full_name='CFE_SB_StatMsg_Payload_t_pb.MaxPipesAllowed', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PeakPipesInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PeakPipesInUse', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MaxMemAllowed', full_name='CFE_SB_StatMsg_Payload_t_pb.MaxMemAllowed', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MaxPipeDepthAllowed', full_name='CFE_SB_StatMsg_Payload_t_pb.MaxPipeDepthAllowed', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PeakMsgIdsInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PeakMsgIdsInUse', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MaxSubscriptionsAllowed', full_name='CFE_SB_StatMsg_Payload_t_pb.MaxSubscriptionsAllowed', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PeakSBBuffersInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PeakSBBuffersInUse', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PipeDepthStats', full_name='CFE_SB_StatMsg_Payload_t_pb.PipeDepthStats', index=7,
      number=8, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MemInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.MemInUse', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PipesInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PipesInUse', index=9,
      number=10, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PeakSubscriptionsInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PeakSubscriptionsInUse', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MaxMsgIdsAllowed', full_name='CFE_SB_StatMsg_Payload_t_pb.MaxMsgIdsAllowed', index=11,
      number=12, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SBBuffersInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.SBBuffersInUse', index=12,
      number=13, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SubscriptionsInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.SubscriptionsInUse', index=13,
      number=14, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PeakMemInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.PeakMemInUse', index=14,
      number=15, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MsgIdsInUse', full_name='CFE_SB_StatMsg_Payload_t_pb.MsgIdsInUse', index=15,
      number=16, type=13, cpp_type=3, label=2,
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
  serialized_start=149,
  serialized_end=609,
)

_CFE_SB_STATMSG_PAYLOAD_T_PB.fields_by_name['PipeDepthStats'].message_type = _CFE_SB_PIPEDEPTHSTATS_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_PipeDepthStats_t_pb'] = _CFE_SB_PIPEDEPTHSTATS_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_StatMsg_Payload_t_pb'] = _CFE_SB_STATMSG_PAYLOAD_T_PB

CFE_SB_PipeDepthStats_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_PipeDepthStats_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_PIPEDEPTHSTATS_T_PB,
  __module__ = '_py_CFE_SB_StatMsg_Payload_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_PipeDepthStats_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_PipeDepthStats_t_pb)

CFE_SB_StatMsg_Payload_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_StatMsg_Payload_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_STATMSG_PAYLOAD_T_PB,
  __module__ = '_py_CFE_SB_StatMsg_Payload_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_StatMsg_Payload_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_StatMsg_Payload_t_pb)


# @@protoc_insertion_point(module_scope)
