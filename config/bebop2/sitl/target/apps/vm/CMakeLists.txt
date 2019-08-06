set(APP_NAME vm)

add_airliner_app_table(
    ${APP_NAME}
    NAME vm_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/vm_config.c
)


target_sources(vm-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tables/vm_config.c)