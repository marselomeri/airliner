
add_airliner_app_def(gps
    FILE GPS
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(gps-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_custom_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/gps_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gps_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
