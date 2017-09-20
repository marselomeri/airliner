
add_airliner_app_def(mixer
    FILE MIXER
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer.c

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    # This application has a public include header.  Add it so all the other applications can access it.        
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)
