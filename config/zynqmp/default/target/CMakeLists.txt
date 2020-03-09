include(../set-vars.cmake)

# Put target specific functions here.  This is where we build most everything.  Everything that either uses the
# cross toolchain or has target independent functions.

initialize_airliner_build(
    PSP ${TARGET_PSP}
    OSAL ${TARGET_OSAL}
    CORE_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/airliner
    CORE_TOOLS ${CMAKE_CURRENT_SOURCE_DIR}/tools
    CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc
    FILESYS
        /cf/apps
        /cf/download
        /cf/log
        /cf/upload
        /ram
    STARTUP_SCRIPT
        ${CMAKE_CURRENT_SOURCE_DIR}/cfe_es_startup.scr
    
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cfe_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cfe_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/osconfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cfe_platform_cfg.h

    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/cfe/cfe_msg_overrides.json
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/defs/airliner_overrides.json
)


add_airliner_app(
    cfs_lib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/cfs_lib/fsw/for_build
)

add_airliner_app(
    px4lib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/px4lib/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/px4lib
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/px4lib/px4lib_custom.c
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/px4lib/px4_msg_overrides.json
)

add_airliner_app(
    pblib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/pblib/fsw/for_build
)

add_airliner_app(
    prmlib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/prmlib/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/prm
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/prm/prm_custom_overrides.json
)

add_airliner_app(
    sch
    DEFINITION $ENV{AIRLINER_ROOT}/apps/sch/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch/sch_custom_rt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sch_perfids.h
    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch/sch_msg_overrides.json
)
