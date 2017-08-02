set(APP_NAME ea)

add_airliner_app_table(
    ${APP_NAME}
    NAME ea_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ea_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
