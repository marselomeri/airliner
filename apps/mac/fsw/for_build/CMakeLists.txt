
add_airliner_app_def(mac
    FILE MAC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_private_ids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_private_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${PX4_MSGS_DIR}
)

#add_airliner_app_unit_test(MAC-UT
#    UTASSERT
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_app_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_cds_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_cmds_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_config_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_testrunner.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_test_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_cds_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_config_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../mixer/fsw/src/mixer.c
#        
#    INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
#)
