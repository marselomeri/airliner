
add_airliner_app_def(ae
    FILE AE
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(ae-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ae_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ae_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
