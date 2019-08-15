set(APP_NAME gps)

add_airliner_app_table(
    ${APP_NAME}
    NAME gps_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/gps_config.c
)
