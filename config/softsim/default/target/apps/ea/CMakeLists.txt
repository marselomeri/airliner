set(APP_NAME ea)

add_airliner_app_src(
    ${APP_NAME}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ea_custom.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME ea_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ea_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_src(
    ea-ut
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ea_custom.c
)

add_airliner_app_src(
    ea-ut-gcov
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ea_custom.c
)
