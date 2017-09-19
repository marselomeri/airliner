
add_airliner_app_def(pblib
    FILE PBLIB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_common.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_decode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_decode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_encode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_encode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    # This application has a public include header.  Add it so all the other applications can access it.
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools/nanopb nanopb)
