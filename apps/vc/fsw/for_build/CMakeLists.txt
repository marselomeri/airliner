
add_airliner_app_def(vc
    FILE VC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_dev_io.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_transmit.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(vc-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_device_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_device_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_transmit_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_transmit_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/vc_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_dev_io.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_transmit.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)
