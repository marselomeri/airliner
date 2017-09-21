set(ES_PROTOBUF_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf)

add_airliner_app_def(pblib
    FILE PBLIB
	NANOPB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h
        ${ES_PROTOBUF_MSGS_DIR}/es_restart.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_restart.pb.c

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
        ${ES_PROTOBUF_MSGS_DIR}

	PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_restart.proto
        
    PROTOBUF_MSGS_DIR        
        ${ES_PROTOBUF_MSGS_DIR}

    # This application has a public include header.  Add it so all the other applications can access it.
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)

add_airliner_app_unit_test(pblib-ut
    UTASSERT
	NANOPB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_testrunner.c


	INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools/nanopb nanopb)
set(ES_PROTOBUF_MSGS_DIR ${ES_PROTOBUF_MSGS_DIR} PARENT_SCOPE)
