
add_airliner_app_def({{cookiecutter.app_name|lower}}
    FILE {{cookiecutter.app_name}}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test({{cookiecutter.app_name|lower}}-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/{{cookiecutter.app_name|lower}}_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_{{cookiecutter.app_name|lower}}_custom_hooks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_{{cookiecutter.app_name|lower}}_custom_hooks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_{{cookiecutter.app_name|lower}}_custom_stubs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_{{cookiecutter.app_name|lower}}_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
