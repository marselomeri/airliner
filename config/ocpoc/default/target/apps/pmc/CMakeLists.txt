set(APP_NAME pmc)

add_airliner_app_table(
    ${APP_NAME}
    NAME pmc_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/pmc_config.c
)