set(APP_NAME rcin)

add_airliner_app_table(
    ${APP_NAME}
    NAME rcin_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/rcin_config.c
)
