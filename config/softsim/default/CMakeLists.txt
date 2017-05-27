cmake_minimum_required(VERSION 2.6.4)

set(PSP pc-linux)
set(OSAL posix)

if(BUILD_TARGET STREQUAL "HOST")
    # Put host specific functions here.  This allows us to build things like elf2cfetbl which are built using the host
    # toolchain, not the cross toolchain.
    build_airliner_cfe_host_tools(
        PSP ${PSP}
        OSAL ${OSAL}
        CONFIG
            ${CMAKE_CURRENT_SOURCE_DIR}/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/../../shared/inc
    )
else()
    # Put target specific functions here.  This is where we build most everything.  Everything that either uses the
    # cross toolchain or has target independent functions.

    build_airliner_cfe(
        PSP ${PSP}
        OSAL ${OSAL}
        CONFIG
            ${CMAKE_CURRENT_SOURCE_DIR}/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/../../shared/inc
        FILESYS
            /cf/apps
            /cf/download
            /cf/log
            /cf/upload
            /ram
        STARTUP_SCRIPT
            ${CMAKE_CURRENT_SOURCE_DIR}/cfe_es_startup.scr
    )

    add_airliner_app(
        cfs_lib
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/cfs_lib/fsw/for_build)

    add_airliner_app(
        sch
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/sch/fsw/for_build
        CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch)

    add_airliner_app(
        cf
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/cf/fsw/for_build
        CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/cf)

    add_airliner_app(
        cs
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/cs/fsw/for_build
        CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/cs)

    add_airliner_app(
        ds
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/ds/fsw/for_build
        CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ds)

    add_airliner_app(
        fm
        DEFINITION ${PROJECT_SOURCE_DIR}/apps/fm/fsw/for_build
        CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/fm)

endif()






