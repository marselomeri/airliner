# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_CFE_TIME_StateCmd_Payload_t.proto

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
  name='_py_CFE_TIME_StateCmd_Payload_t.proto',
  package='',
  serialized_pb=_b('\n%_py_CFE_TIME_StateCmd_Payload_t.proto\"4\n\x1e\x43\x46\x45_TIME_StateCmd_Payload_t_pb\x12\x12\n\nClockState\x18\x01 \x02(\x05')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CFE_TIME_STATECMD_PAYLOAD_T_PB = _descriptor.Descriptor(
  name='CFE_TIME_StateCmd_Payload_t_pb',
  full_name='CFE_TIME_StateCmd_Payload_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ClockState', full_name='CFE_TIME_StateCmd_Payload_t_pb.ClockState', index=0,
      number=1, type=5, cpp_type=1, label=2,
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
  serialized_start=41,
  serialized_end=93,
)

DESCRIPTOR.message_types_by_name['CFE_TIME_StateCmd_Payload_t_pb'] = _CFE_TIME_STATECMD_PAYLOAD_T_PB

CFE_TIME_StateCmd_Payload_t_pb = _reflection.GeneratedProtocolMessageType('CFE_TIME_StateCmd_Payload_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_TIME_STATECMD_PAYLOAD_T_PB,
  __module__ = '_py_CFE_TIME_StateCmd_Payload_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_TIME_StateCmd_Payload_t_pb)
  ))
_sym_db.RegisterMessage(CFE_TIME_StateCmd_Payload_t_pb)


# @@protoc_insertion_point(module_scope)
