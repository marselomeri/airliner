set(APP_NAME mac)

add_airliner_app_table(
    ${APP_NAME}
    NAME mac_pwmcfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mac_pwmcfg.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME mac_mixercfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mac_mixercfg.c
)