include(../set-vars.cmake)

# Put host specific functions here.  This allows us to build things like elf2cfetbl which are built using the host
# toolchain, not the cross toolchain.
build_airliner_cfe_host_tools(
    PSP ${PSP}
    OSAL ${OSAL}
    CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc
)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools/sitl_gazebo gazebo)
set(GAZEBO_PLUGIN_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/gazebo)
set(GAZEBO_WORLDS_DIR ${PROJECT_SOURCE_DIR}/tools/sitl_gazebo/worlds)
set(GAZEBO_MODELS_DIR ${PROJECT_SOURCE_DIR}/tools/sitl_gazebo/models)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-gazebo.in ${CMAKE_CURRENT_BINARY_DIR}/start-gazebo @ONLY)




