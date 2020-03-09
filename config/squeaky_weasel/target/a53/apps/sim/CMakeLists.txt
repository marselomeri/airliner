set(APP_NAME sim)

add_airliner_app_table(
    ${APP_NAME}
    NAME sim_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/sim_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)