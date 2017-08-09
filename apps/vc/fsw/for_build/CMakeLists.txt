
add_airliner_app_def(vc
    FILE VC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
)

add_airliner_app_unit_test(VC-UT
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_custom_device_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_custom_transmit_stubs.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)
