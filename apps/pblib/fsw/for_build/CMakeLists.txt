 #############################################################################
 #
 #   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 #
 # Redistribution and use in source and binary forms, with or without
 # modification, are permitted provided that the following conditions
 # are met:
 #
 # 1. Redistributions of source code must retain the above copyright
 #    notice, this list of conditions and the following disclaimer.
 # 2. Redistributions in binary form must reproduce the above copyright
 #    notice, this list of conditions and the following disclaimer in
 #    the documentation and/or other materials provided with the
 #    distribution.
 # 3. Neither the name PX4 nor the names of its contributors may be
 #    used to endorse or promote products derived from this software
 #    without specific prior written permission.
 #
 # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 # "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 # LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 # FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 # COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 # INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 # BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 # OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 # AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 # LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 # ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 # POSSIBILITY OF SUCH DAMAGE.
 #
 #############################################################################
 
 
set(ES_PROTOBUF_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf)

add_airliner_app_def(pblib
    FILE PBLIB
    SOURCES
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_common.c
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_common.h
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_decode.c
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_decode.h
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_encode.c
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_encode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${PROJECT_SOURCE_DIR}/tools/nanopb/pb.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/es_serialization.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/es_serialization.h
		${ES_PROTOBUF_MSGS_DIR}/es_log.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_log.pb.h

    INCLUDES
		${ES_PROTOBUF_MSGS_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_log.proto

    PROTOBUF_MSGS_DIR        
        ${ES_PROTOBUF_MSGS_DIR}

    # This application has a public include header.  Add it so all the other applications can access it.
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
        ${PROJECT_SOURCE_DIR}/tools/nanopb/
)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools/nanopb nanopb)
