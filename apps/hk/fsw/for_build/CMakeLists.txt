
add_airliner_app_def(hk
    FILE HK
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hk_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hk_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(HK-UT
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hk_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hk_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hk_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/hk_utils_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hk_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/hk_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

