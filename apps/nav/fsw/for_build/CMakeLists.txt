
add_airliner_app_def(nav
    FILE NAV
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_take_off.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_take_off.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(nav-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_custom_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/nav_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_take_off.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_take_off.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nav_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
