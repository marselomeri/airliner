set(APP_NAME amc)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_pwmcfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_pwmcfg.c
    INCLUDES ${PROJECT_SOURCE_DIR}/mavlink/include/mavlink/v1.0/common/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME amc_mixercfg
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/amc_mixercfg.c
)
