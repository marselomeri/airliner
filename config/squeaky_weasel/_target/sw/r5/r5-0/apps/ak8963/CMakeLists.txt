set(APP_NAME ak8963)

add_airliner_app_table(
    ${APP_NAME}
    NAME ak8963_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ak8963_config.c
)
