set(APP_NAME bat)

add_airliner_app_table(
    ${APP_NAME}
    NAME bat_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/bat_config.c
)

target_sources(bat-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tables/bat_config.c)