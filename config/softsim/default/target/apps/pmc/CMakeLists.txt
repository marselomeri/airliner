set(APP_NAME pmc)

add_airliner_app_table(
    ${APP_NAME}
    NAME pmc_pwmcfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/pmc_pwmcfg.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME pmc_mixercfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/pmc_mixercfg.c
)