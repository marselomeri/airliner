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
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/cfs_lib/fsw/for_build
)

add_airliner_app(
    px4lib
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/px4lib/fsw/for_build
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/px4lib/px4_msg_overrides.json
)

add_airliner_app(
    pblib
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/pblib/fsw/for_build
)

add_airliner_app(
    prmlib
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/prmlib/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/prm
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/prm/prm_custom_overrides.json
)

add_airliner_app(
    cvt
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/cvt/fsw/for_build
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cvt_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cvt_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cvt_perfids.h
)

add_airliner_app(
    sim
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/sim/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sim
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sim_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sim_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sim_perfids.h
)

add_airliner_app(
    sch
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/sch/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch/sch_custom_rt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sch_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sch_perfids.h
    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/sch/sch_msg_overrides.json
)

add_airliner_app(
    cf
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/cf/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/cf
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cf_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cf_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cf_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/cf/cf_msg_overrides.json
)

add_airliner_app(
    cs
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/cs/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/cs
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cs_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/cs_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cs_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/cs_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/cs/cs_msg_overrides.json
)

add_airliner_app(
    ds
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ds/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ds
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ds_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ds_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ds_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/ds/ds_msg_overrides.json
)

add_airliner_app(
    fm
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/fm/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/fm
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/fm_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/fm_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/fm_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/fm/fm_msg_overrides.json
)
    
add_airliner_app(
    flow
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/flow/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/flow
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/flow_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/flow_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/flow_perfids.h
)

add_airliner_app(
    hk
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/hk/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/hk
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/hk_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/hk_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/hk_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/hk/hk_msg_overrides.json
)

add_airliner_app(
    hs
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/hs/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/hs
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/hs/hs_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/hs_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/hs_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/hs_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/hs/hs_msg_overrides.json
)

add_airliner_app(
    lc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/lc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/lc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/lc/src/lc_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/lc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/lc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/lc_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/lc_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/lc/lc_msg_overrides.json
)

add_airliner_app(
    md
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/md/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/md
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/md_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/md_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/md_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/md/md_msg_overrides.json
)

add_airliner_app(
    mm
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/mm/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/mm
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/mm_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/mm_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mm_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mm_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/mm/mm_msg_overrides.json
)

add_airliner_app(
    sc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/sc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sc_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/sc/sc_msg_overrides.json
)

add_airliner_app(
    ci
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ci/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ci
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ci/ci_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ci_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ci_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ci_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ci_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/ci/ci_msg_overrides.json
)

add_airliner_app(
    to
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/to/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/to
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/to/to_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/to/to_custom_udp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/to_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/to_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/to_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/to_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/to/to_msg_overrides.json
)

add_airliner_app(
    ea
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ea/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ea
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ea/src/ea_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ea_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ea_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ea_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/ea/ea_msg_overrides.json
)

add_airliner_app(
    vc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/vc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_dev_io_udp/vc_dev_io_udp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_dev_io_udp/vc_dev_io_udp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_transmit_udp/vc_transmit_udp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_transmit_udp/vc_transmit_udp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/src/vc_custom_shared.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/vc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/vc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/vc_mission_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/vc_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/vc/vc_msg_overrides.json
)

add_airliner_app(
    amc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/amc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/amc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/amc/amc_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/amc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/amc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/amc_perfids.h
    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/amc/amc_msg_overrides.json
)

add_airliner_app(
    mac
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/mac/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/mac
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/mac_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mac_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mac_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/mac/mac_msg_overrides.json
)

add_airliner_app(
    rgbled
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/rgbled/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/rgbled
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/rgbled/src/rgbled_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/rgbled/src/rgbled_driver.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/rgbled_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/rgbled_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/rgbled_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/rgbled/rgbled_msg_overrides.json
)

add_airliner_app(
    ms5607
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ms5607/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ms5607
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ms5607/src/ms5607_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ms5607_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ms5607_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ms5607_perfids.h
)

add_airliner_app(
    gps
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/gps/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_ubx_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_common.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_nav.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_nav.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_cfg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_ack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_ack.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_mon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_parser_ubx/gps_parser_ubx_mon.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_custom_shared.h
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/src/gps_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/gps_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/gps_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/gps_perfids.h
    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/gps/gps_msg_overrides.json
)

add_airliner_app(
    sens
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/sens/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/sens
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/sens_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sens_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/sens_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/sens/sens_msg_overrides.json
)

add_airliner_app(
    mpc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/mpc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/mpc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mpc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mpc_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpc/mpc_msg_overrides.json
)

add_airliner_app(
    vm
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/vm/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/vm
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/vm_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/vm_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/vm_perfids.h
    MSG_OVERRIDES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/vm/vm_msg_overrides.json
)

add_airliner_app(
    ld
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ld/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ld
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ld_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ld_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ld_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/ld/ld_msg_overrides.json
)

add_airliner_app(
    nav
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/nav/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/nav
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/nav_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/nav_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/nav_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/nav/nav_msg_overrides.json
)

add_airliner_app(
    rcin
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/rcin/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/rcin
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/rcin/src/rcin_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/rcin/src/rcin_sbus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/rcin_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/rcin_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/rcin_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/rcin/rcin_msg_overrides.json
)

add_airliner_app(
    bat
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/bat/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/bat
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/bat/bat_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/bat_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/bat_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/bat_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/bat/bat_msg_overrides.json
)

add_airliner_app(
    mpu6050
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/mpu6050/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpu6050
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpu6050/src/mpu6050_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpu6050/src/mpu6050_spi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/mpu6050_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mpu6050_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/mpu6050_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/mpu6050/mpu6050_msg_overrides.json
)

add_airliner_app(
    ak8963
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/ak8963/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/ak8963
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ak8963/src/ak8963_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/ak8963/src/ak8963_i2c.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/ak8963_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ak8963_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/ak8963_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/ak8963/ak8963_msg_overrides.json
)

add_airliner_app(
    pe
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/pe/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/pe
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/pe_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/pe_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/pe_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/pe/pe_msg_overrides.json
)

add_airliner_app(
    qae
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/qae/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/qae
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/qae_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/qae_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/qae_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/qae/qae_msg_overrides.json
)

add_airliner_app(
    lgc
    DEFINITION ${PROJECT_SOURCE_DIR}/apps/lgc/fsw/for_build
    CONFIG     ${CMAKE_CURRENT_SOURCE_DIR}/apps/lgc
    CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/lgc/lgc_custom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/lgc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/lgc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/inc/lgc_perfids.h
    MSG_OVERRIDES ${CMAKE_CURRENT_SOURCE_DIR}/apps/lgc/lgc_msg_overrides.json
)

