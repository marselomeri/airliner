include(../set-vars.cmake)

# Put target specific functions here.  This is where we build most everything.  Everything that either uses the
# cross toolchain or has target independent functions.

initialize_airliner_build(
    PSP ${TARGET_PSP}
    OSAL ${TARGET_OSAL}
    CORE_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/airliner
    CORE_TOOLS ${CMAKE_CURRENT_SOURCE_DIR}/tools
    CONFIG
        $ENV{AIRLINER_ROOT}/core/mission_inc/
        $ENV{AIRLINER_ROOT}/core/platform_inc/
    FILESYS
        /cf/apps
        /cf/download
        /cf/log
        /cf/upload
        /ram
    STARTUP_SCRIPT
        ${CMAKE_CURRENT_SOURCE_DIR}/cfe_es_startup.scr
    
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/core/mission_inc/cfe_mission_cfg.h
        $ENV{AIRLINER_ROOT}/core/mission_inc/cfe_msgids.h
        $ENV{AIRLINER_ROOT}/core/platform_inc/osconfig.h
        $ENV{AIRLINER_ROOT}/core/platform_inc/cfe_platform_cfg.h
        
    REFERENCE
)



add_airliner_app(
    cfs_lib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/cfs_lib/fsw/for_build
)

add_airliner_app(
    px4lib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/px4lib/fsw/for_build
)

add_airliner_app(
    pblib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/pblib/fsw/for_build
)

add_airliner_app(
    prmlib
    DEFINITION $ENV{AIRLINER_ROOT}/apps/prmlib/fsw/for_build
)

add_airliner_app(
    sim
    DEFINITION $ENV{AIRLINER_ROOT}/apps/sim/fsw/for_build
)

add_airliner_app(
    sch
    DEFINITION $ENV{AIRLINER_ROOT}/apps/sch/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/sch/fsw/mission_inc/sch_perfids.h
        $ENV{AIRLINER_ROOT}/apps/sch/fsw/platform_inc/sch_msgids.h
        $ENV{AIRLINER_ROOT}/apps/sch/fsw/platform_inc/sch_platform_cfg.h
)

add_airliner_app(
    cf
    DEFINITION $ENV{AIRLINER_ROOT}/apps/cf/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/cf/fsw/mission_inc/cf_perfids.h
        $ENV{AIRLINER_ROOT}/apps/cf/fsw/platform_inc/cf_msgids.h
        $ENV{AIRLINER_ROOT}/apps/cf/fsw/platform_inc/cf_platform_cfg.h
    )

add_airliner_app(
    cs
    DEFINITION $ENV{AIRLINER_ROOT}/apps/cs/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/cs/fsw/mission_inc/cs_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/cs/fsw/mission_inc/cs_perfids.h
        $ENV{AIRLINER_ROOT}/apps/cs/fsw/platform_inc/cs_msgids.h
        $ENV{AIRLINER_ROOT}/apps/cs/fsw/platform_inc/cs_platform_cfg.h
)

add_airliner_app(
    ds
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ds/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ds/fsw/mission_inc/ds_perfids.h
        $ENV{AIRLINER_ROOT}/apps/ds/fsw/platform_inc/ds_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ds/fsw/platform_inc/ds_platform_cfg.h
)

add_airliner_app(
    fm
    DEFINITION $ENV{AIRLINER_ROOT}/apps/fm/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/fm/fsw/mission_inc/fm_perfids.h
        $ENV{AIRLINER_ROOT}/apps/fm/fsw/platform_inc/fm_msgids.h
        $ENV{AIRLINER_ROOT}/apps/fm/fsw/platform_inc/fm_platform_cfg.h
)

add_airliner_app(
    hk
    DEFINITION $ENV{AIRLINER_ROOT}/apps/hk/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/hk/fsw/mission_inc/hk_perfids.h
        $ENV{AIRLINER_ROOT}/apps/hk/fsw/platform_inc/hk_msgids.h
        $ENV{AIRLINER_ROOT}/apps/hk/fsw/platform_inc/hk_platform_cfg.h
)

add_airliner_app(
    hs
    DEFINITION $ENV{AIRLINER_ROOT}/apps/hs/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/hs/fsw/mission_inc/hs_perfids.h
        $ENV{AIRLINER_ROOT}/apps/hs/fsw/platform_inc/hs_msgids.h
        $ENV{AIRLINER_ROOT}/apps/hs/fsw/platform_inc/hs_platform_cfg.h
)

add_airliner_app(
    lc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/lc/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/lc/fsw/mission_inc/lc_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/lc/fsw/mission_inc/lc_perfids.h
        $ENV{AIRLINER_ROOT}/apps/lc/fsw/platform_inc/lc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/lc/fsw/platform_inc/lc_platform_cfg.h
)

add_airliner_app(
    md
    DEFINITION $ENV{AIRLINER_ROOT}/apps/md/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/md/fsw/mission_inc/md_perfids.h
        $ENV{AIRLINER_ROOT}/apps/md/fsw/platform_inc/md_msgids.h
        $ENV{AIRLINER_ROOT}/apps/md/fsw/platform_inc/md_platform_cfg.h
)

add_airliner_app(
    mm
    DEFINITION $ENV{AIRLINER_ROOT}/apps/mm/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/mm/fsw/mission_inc/mm_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/mm/fsw/mission_inc/mm_perfids.h
        $ENV{AIRLINER_ROOT}/apps/mm/fsw/platform_inc/mm_msgids.h
        $ENV{AIRLINER_ROOT}/apps/mm/fsw/platform_inc/mm_platform_cfg.h
)

add_airliner_app(
    sc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/sc/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/sc/fsw/mission_inc/sc_perfids.h
        $ENV{AIRLINER_ROOT}/apps/sc/fsw/platform_inc/sc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/sc/fsw/platform_inc/sc_platform_cfg.h
)

add_airliner_app(
    ci
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ci/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ci/fsw/mission_inc/ci_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/ci/fsw/mission_inc/ci_perfids.h
        $ENV{AIRLINER_ROOT}/apps/ci/fsw/platform_inc/ci_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ci/fsw/platform_inc/ci_platform_cfg.h
)

add_airliner_app(
    to
    DEFINITION $ENV{AIRLINER_ROOT}/apps/to/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/to/fsw/mission_inc/to_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/to/fsw/mission_inc/to_perfids.h
        $ENV{AIRLINER_ROOT}/apps/to/fsw/platform_inc/to_msgids.h
        $ENV{AIRLINER_ROOT}/apps/to/fsw/platform_inc/to_platform_cfg.h
)

add_airliner_app(
    ea
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ea/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ea/fsw/mission_inc/ea_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/ea/fsw/mission_inc/ea_perfids.h
        $ENV{AIRLINER_ROOT}/apps/ea/fsw/platform_inc/ea_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ea/fsw/platform_inc/ea_platform_cfg.h
)

add_airliner_app(
    vc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/vc/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/vc/fsw/mission_inc/vc_mission_cfg.h
        $ENV{AIRLINER_ROOT}/apps/vc/fsw/mission_inc/vc_perfids.h
        $ENV{AIRLINER_ROOT}/apps/vc/fsw/platform_inc/vc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/vc/fsw/platform_inc/vc_platform_cfg.h
)

add_airliner_app(
    amc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/amc/fsw/for_build
    INCLUDES
        $ENV{AIRLINER_ROOT}/apps/px4lib/fsw/platform_inc
        $ENV{AIRLINER_ROOT}/apps/prmlib/fsw/platform_inc
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/amc/fsw/platform_inc/amc_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/amc/fsw/platform_inc/amc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/amc/fsw/mission_inc/amc_perfids.h
)

add_airliner_app(
    mac
    DEFINITION $ENV{AIRLINER_ROOT}/apps/mac/fsw/for_build
    INCLUDES
        $ENV{AIRLINER_ROOT}/apps/px4lib/fsw/platform_inc
        $ENV{AIRLINER_ROOT}/apps/prmlib/fsw/platform_inc
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/mac/fsw/platform_inc/mac_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/mac/fsw/platform_inc/mac_msgids.h
        $ENV{AIRLINER_ROOT}/apps/mac/fsw/mission_inc/mac_perfids.h
)

add_airliner_app(
    ulr
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ulr/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ulr/fsw/platform_inc/ulr_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/ulr/fsw/platform_inc/ulr_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ulr/fsw/mission_inc/ulr_perfids.h
)

add_airliner_app(
    rgbled
    DEFINITION $ENV{AIRLINER_ROOT}/apps/rgbled/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/rgbled/fsw/platform_inc/rgbled_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/rgbled/fsw/platform_inc/rgbled_msgids.h
        $ENV{AIRLINER_ROOT}/apps/rgbled/fsw/mission_inc/rgbled_perfids.h
)

add_airliner_app(
    ms5611
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ms5611/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ms5611/fsw/platform_inc/ms5611_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/ms5611/fsw/platform_inc/ms5611_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ms5611/fsw/mission_inc/ms5611_perfids.h
)

add_airliner_app(
    gps
    DEFINITION $ENV{AIRLINER_ROOT}/apps/gps/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/gps/fsw/platform_inc/gps_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/gps/fsw/platform_inc/gps_msgids.h
        $ENV{AIRLINER_ROOT}/apps/gps/fsw/mission_inc/gps_perfids.h
)

add_airliner_app(
    sens
    DEFINITION $ENV{AIRLINER_ROOT}/apps/sens/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/sens/fsw/platform_inc/sens_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/sens/fsw/platform_inc/sens_msgids.h
        $ENV{AIRLINER_ROOT}/apps/sens/fsw/mission_inc/sens_perfids.h
)

add_airliner_app(
    mpc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/mpc/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/mpc/fsw/platform_inc/mpc_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/mpc/fsw/platform_inc/mpc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/mpc/fsw/mission_inc/mpc_perfids.h
)

add_airliner_app(
    vm
    DEFINITION $ENV{AIRLINER_ROOT}/apps/vm/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/vm/fsw/platform_inc/vm_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/vm/fsw/platform_inc/vm_msgids.h
        $ENV{AIRLINER_ROOT}/apps/vm/fsw/mission_inc/vm_perfids.h
)

add_airliner_app(
    ld
    DEFINITION $ENV{AIRLINER_ROOT}/apps/ld/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/ld/fsw/platform_inc/ld_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/ld/fsw/platform_inc/ld_msgids.h
        $ENV{AIRLINER_ROOT}/apps/ld/fsw/mission_inc/ld_perfids.h
)

add_airliner_app(
    nav
    DEFINITION $ENV{AIRLINER_ROOT}/apps/nav/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/nav/fsw/platform_inc/nav_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/nav/fsw/platform_inc/nav_msgids.h
        $ENV{AIRLINER_ROOT}/apps/nav/fsw/mission_inc/nav_perfids.h
)

add_airliner_app(
    rcin
    DEFINITION $ENV{AIRLINER_ROOT}/apps/rcin/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/rcin/fsw/platform_inc/rcin_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/rcin/fsw/platform_inc/rcin_msgids.h
        $ENV{AIRLINER_ROOT}/apps/rcin/fsw/mission_inc/rcin_perfids.h
)

add_airliner_app(
    bat
    DEFINITION $ENV{AIRLINER_ROOT}/apps/bat/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/bat/fsw/platform_inc/bat_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/bat/fsw/platform_inc/bat_msgids.h
        $ENV{AIRLINER_ROOT}/apps/bat/fsw/mission_inc/bat_perfids.h
)

add_airliner_app(
    mpu9250
    DEFINITION $ENV{AIRLINER_ROOT}/apps/mpu9250/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/mpu9250/fsw/platform_inc/mpu9250_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/mpu9250/fsw/platform_inc/mpu9250_msgids.h
        $ENV{AIRLINER_ROOT}/apps/mpu9250/fsw/mission_inc/mpu9250_perfids.h
)

add_airliner_app(
    hmc5883
    DEFINITION $ENV{AIRLINER_ROOT}/apps/hmc5883/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/hmc5883/fsw/platform_inc/hmc5883_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/hmc5883/fsw/platform_inc/hmc5883_msgids.h
        $ENV{AIRLINER_ROOT}/apps/hmc5883/fsw/mission_inc/hmc5883_perfids.h
)

add_airliner_app(
    pe
    DEFINITION $ENV{AIRLINER_ROOT}/apps/pe/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/pe/fsw/platform_inc/pe_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/pe/fsw/platform_inc/pe_msgids.h
        $ENV{AIRLINER_ROOT}/apps/pe/fsw/mission_inc/pe_perfids.h
)

add_airliner_app(
    qae
    DEFINITION $ENV{AIRLINER_ROOT}/apps/qae/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/qae/fsw/platform_inc/qae_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/qae/fsw/platform_inc/qae_msgids.h
        $ENV{AIRLINER_ROOT}/apps/qae/fsw/mission_inc/qae_perfids.h
)

add_airliner_app(
    lgc
    DEFINITION $ENV{AIRLINER_ROOT}/apps/lgc/fsw/for_build
    CONFIG_SOURCES
        $ENV{AIRLINER_ROOT}/apps/lgc/fsw/platform_inc/lgc_platform_cfg.h
        $ENV{AIRLINER_ROOT}/apps/lgc/fsw/platform_inc/lgc_msgids.h
        $ENV{AIRLINER_ROOT}/apps/lgc/fsw/mission_inc/lgc_perfids.h
)
