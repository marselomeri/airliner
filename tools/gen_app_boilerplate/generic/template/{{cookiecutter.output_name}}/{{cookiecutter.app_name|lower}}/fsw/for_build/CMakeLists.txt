
add_airliner_app_def({{cookiecutter.app_name|lower}}
    FILE {{cookiecutter.app_name}}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_config_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)

add_airliner_app_unit_test({{cookiecutter.app_name}}-UT
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_cds_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_config_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_config_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)
