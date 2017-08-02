set(APP_NAME vc)

add_airliner_app_src(
    ${APP_NAME}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vc_transmit_udp.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/vc_dev_io_v4l.c
)


