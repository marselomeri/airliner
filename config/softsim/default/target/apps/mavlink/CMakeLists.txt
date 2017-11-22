set(APP_NAME mavlink)

add_airliner_app_table(
    ${APP_NAME}
    NAME mavlink_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mavlink_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

