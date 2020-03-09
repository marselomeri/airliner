set(APP_NAME sens)

add_airliner_app_table(
    ${APP_NAME}
    NAME sens_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/sens_config.c
)
