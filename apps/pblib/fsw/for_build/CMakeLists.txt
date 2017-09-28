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
