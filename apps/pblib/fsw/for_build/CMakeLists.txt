add_airliner_app_def(pblib
    FILE PBLIB
	NANOPB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

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
