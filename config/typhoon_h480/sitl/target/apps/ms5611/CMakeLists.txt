set(APP_NAME ms5611)

add_airliner_app_table(
    ${APP_NAME}
    NAME ms5611_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ms5611_config.c
)
