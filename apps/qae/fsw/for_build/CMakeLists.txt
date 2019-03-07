
add_airliner_app_def(qae
    FILE QAE
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_symbols.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_version.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
    
    MSG_OVERRIDES   ${CMAKE_CURRENT_SOURCE_DIR}/qae_msg_overrides.json 

    COMMANDER_PLUGIN
        ${CMAKE_CURRENT_SOURCE_DIR}/../../cdr
)

add_airliner_app_unit_test(qae-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_version.h
        ${PX4LIB_LIB_SOURCES}
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
