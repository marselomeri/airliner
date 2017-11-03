
add_airliner_app_def(rgbled
    FILE RGBLED
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_custom.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(rgbled-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/rgbled_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/rgbled_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
