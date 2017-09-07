set(APP_NAME vc)

add_airliner_app_unit_test(vc-custom-ut
    UTASSERT
    SOURCES
        # Unit test runner
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_custom_testrunner.c
        # Unit test for custom device module
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_dev_io_v4l_test/vc_app_custom_device_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_dev_io_v4l_test/vc_app_custom_device_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_dev_io_v4l_test/vc_custom_device_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_dev_io_v4l_test/vc_custom_device_test_utils.h
        # Unit test for custom transmit module
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_transmit_udp_test/vc_app_custom_transmit_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_transmit_udp_test/vc_app_custom_transmit_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_transmit_udp_test/vc_custom_transmit_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_transmit_udp_test/vc_custom_transmit_test_utils.h
        # Platform stubs
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_platform_stubs/vc_platform_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_platform_stubs/vc_platform_stubs.h
        # Custom code
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp/vc_transmit_udp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp/vc_transmit_udp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l/vc_dev_io_v4l.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l/vc_dev_io_v4l.h

    INCLUDES
        # Custom code under test
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp/
        # Test code
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_dev_io_v4l_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_transmit_udp_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/vc_platform_stubs/
        # Sealed code
        ${PROJECT_SOURCE_DIR}/apps/vc/fsw/src/

    WRAPPERS
        # Wrapped functions (see platform stubs)
        ioctl
        open
        close
        select
        socket
        bind
        sendto
)

