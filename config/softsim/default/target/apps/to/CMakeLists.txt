set(APP_NAME to)

add_airliner_app_src(
    ${APP_NAME}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/to_custom.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
