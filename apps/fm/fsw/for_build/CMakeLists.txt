
add_airliner_app_def(fm
    FILE FM
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_child.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_cmd_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_tbl.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(FM-UT
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_child_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_cmd_utils_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fm_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_child.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_cmd_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/fm_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

