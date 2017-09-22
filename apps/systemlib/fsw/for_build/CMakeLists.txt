
add_airliner_app_def(systemlib
    FILE SYSTEMLIB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/systemlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/mixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/mixer_group.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/mixer_helicopter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/mixer_multirotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/mixer_simple.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib/math/Limits.cpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    # This application has a public include header.  Add it so all the other applications can access it.        
    #PUBLIC_INCLUDES
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)
