
add_airliner_app_def(md
    FILE MD
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)

add_airliner_app_unit_test(md-ut-1
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_unit_test1.c
        
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfileapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memory.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memrange.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memutils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_ram.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_support.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_utils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_internal.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/ccsds.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/cfe_sb_util.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/es/cfe_es_cds_mempool.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/fs/cfe_fs_api.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_timer.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_watchdog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/utf/inc/
)


add_airliner_app_unit_test(md-ut-2
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_unit_test2.c
        
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfileapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memory.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memrange.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memutils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_ram.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_support.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_utils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_internal.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/ccsds.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/cfe_sb_util.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/es/cfe_es_cds_mempool.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/fs/cfe_fs_api.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_timer.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_watchdog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/utf/inc/
)


add_airliner_app_unit_test(md-ut-3
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_unit_test3.c
        
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfileapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memory.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memrange.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memutils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_ram.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_support.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_utils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_internal.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/ccsds.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/cfe_sb_util.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/es/cfe_es_cds_mempool.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/fs/cfe_fs_api.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_timer.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_watchdog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/utf/inc/
)


add_airliner_app_unit_test(md-ut-4
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_unit_test4.c
        
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfileapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memory.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memrange.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memutils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_ram.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_support.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_utils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_internal.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/ccsds.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/cfe_sb_util.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/es/cfe_es_cds_mempool.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/fs/cfe_fs_api.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_timer.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_watchdog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/utf/inc/
)