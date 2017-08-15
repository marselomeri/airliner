
add_airliner_app_def({{cookiecutter.app_name|lower}}
    FILE {{cookiecutter.app_name}}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/{{cookiecutter.app_name|lower}}_app.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)

