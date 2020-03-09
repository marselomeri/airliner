
add_airliner_app_def(bat
    FILE BAT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_symbols.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_version.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in

    COMMANDER_PLUGIN
        ${CMAKE_CURRENT_SOURCE_DIR}/../../cdr
    MSG_OVERRIDES 
        ${CMAKE_CURRENT_SOURCE_DIR}/bat_msg_overrides.json
    
    REFERENCE_CONFIG
        $ENV{AIRLINER_ROOT}/apps/bat/fsw/mission_inc
        $ENV{AIRLINER_ROOT}/apps/bat/fsw/platform_inc
)

add_airliner_app_unit_test(bat-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/bat_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_bat_custom_hooks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_bat_custom_hooks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_bat_custom_stubs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_bat_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/bat_version.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/

    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
