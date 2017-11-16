
add_airliner_app_def(rcin
    FILE RCIN
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(rcin-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rcin_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rcin_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
