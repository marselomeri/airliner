include(../set-vars.cmake)

add_subdirectory($ENV{AIRLINER_ROOT}/tools/sitl_gazebo gazebo)
set(GAZEBO_PLUGIN_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/gazebo)
set(GAZEBO_WORLDS_DIR $ENV{AIRLINER_ROOT}/tools/sitl_gazebo/worlds)
set(GAZEBO_MODELS_DIR $ENV{AIRLINER_ROOT}/tools/sitl_gazebo/models)
set(JMAVSIM_DIR $ENV{AIRLINER_ROOT}/tools/jmavsim)
target_include_directories(gazebo_gst_camera_plugin PRIVATE "/usr/include/gstreamer-1.0")
target_include_directories(gazebo_gst_camera_plugin PRIVATE "/usr/include/glib-2.0")
target_include_directories(gazebo_gst_camera_plugin PRIVATE "/usr/lib/x86_64-linux-gnu/glib-2.0/include")
target_include_directories(gazebo_gst_camera_plugin PRIVATE "/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-gazebo.in ${CMAKE_CURRENT_BINARY_DIR}/start-gazebo @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start-jmavsim.in ${CMAKE_CURRENT_BINARY_DIR}/start-jmavsim @ONLY)

# Build the 'Ground Node' for CFDP file transfer.
#initialize_airliner_build(
#    PREFIX gndnode-
#    PSP ${HOST_PSP}
#    OSAL ${HOST_OSAL}
#    CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/inc
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc
#    FILESYS
#        /cf/apps
#        /cf/download
#        /cf/log
#        /cf/upload
#        /ram
#    STARTUP_SCRIPT
#        ${CMAKE_CURRENT_SOURCE_DIR}/cfe_es_startup.scr
#    
#    CONFIG_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cfe_mission_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cfe_msgids.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/inc/osconfig.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/inc/cfe_platform_cfg.h
#)
#
#add_airliner_app(
#    px4lib
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/px4lib/fsw/for_build)
#    
#add_airliner_app(
#    pblib
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/pblib/fsw/for_build)
#
#add_airliner_app(
#    sch
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/sch/fsw/for_build
#    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch
#    CONFIG_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch/sch_custom_rt.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_platform_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_msgids.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sch_perfids.h
#    )
#
#add_airliner_app(
#    cf
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/cf/fsw/for_build
#    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/cf
#    CONFIG_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cf_platform_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cf_msgids.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cf_perfids.h
#    )
#
#add_airliner_app(
#    ci
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/ci/fsw/for_build
#    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ci
#    CONFIG_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ci/ci_custom.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ci_platform_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ci_msgids.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ci_mission_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ci_perfids.h
#    )
#
#add_airliner_app(
#    to
#    DEFINITION $ENV{AIRLINER_ROOT}/apps/to/fsw/for_build
#    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/to
#    CONFIG_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/to/to_custom.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/to/to_custom_udp.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/to_platform_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/to_msgids.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/to_mission_cfg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/to_perfids.h
#    )


