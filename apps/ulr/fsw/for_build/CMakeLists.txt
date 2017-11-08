
add_airliner_app_def(ulr
    FILE ULR
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(ulr-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ulr_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ulr_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
