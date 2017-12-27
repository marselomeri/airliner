
add_airliner_app_def(params
    FILE PARAMS
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_cds_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_config_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/params_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/params_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/params_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_private_ids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_private_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
        ${PROJECT_SOURCE_DIR}/mavlink/include/mavlink/v1.0/common/

    # This application has a public include header.  Add it so all the other applications can access it.
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in   
    DESIGN_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in   
)

#add_airliner_app_unit_test(PARAMS-UT
#    UTASSERT 
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_app_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_cds_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_cmds_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_config_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_testrunner.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/params_test_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_app.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_cds_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/params_config_utils.c
#        
#    INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
#)
