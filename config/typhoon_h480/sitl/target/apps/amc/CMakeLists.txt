set(APP_NAME amc)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_pwmcfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_pwmcfg.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_mixercfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_mixercfg_3f.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_mixercfg3a
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_mixercfg_3a.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_mixercfg30
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_mixercfg_30.c
)