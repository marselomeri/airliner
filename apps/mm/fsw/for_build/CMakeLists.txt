
add_airliner_app_def(mm
    FILE MM
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_dump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_load.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem16.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem8.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(mm-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_dump_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_load_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem16_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem32_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem8_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_utils_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_dump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_load.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem16.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem8.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

