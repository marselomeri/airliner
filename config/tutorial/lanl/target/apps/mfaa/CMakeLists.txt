set(APP_NAME mfaa)

add_airliner_app_table(
    ${APP_NAME}
    NAME mfaa_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mfaa_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME mfaa_config2
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mfaa_config2.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)