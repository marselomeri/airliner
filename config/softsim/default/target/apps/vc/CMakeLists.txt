set(APP_NAME vc)

add_airliner_app_unit_test(vc-custom-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_app_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_app_custom_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_device_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_device_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_transmit_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_transmit_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_platform_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/
        ${PROJECT_SOURCE_DIR}/apps/vc/fsw/src

#    WRAPPERS
#        ioctl
#        open
)

set_property(TARGET vc-custom-ut
        APPEND_STRING
        PROPERTY
        LINK_FLAGS
        "-Wl,--wrap=ioctl \
         -Wl,--wrap=open \
         -Wl,--wrap=select"
)

