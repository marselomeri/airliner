
add_airliner_app_def(systemlib
    FILE SYSTEMLIB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/systemlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/Mixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/Mixer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/MixerGroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/MixerGroup.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/HelicopterMixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/HelicopterMixer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/MultirotorMixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/MultirotorMixer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/SimpleMixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/SimpleMixer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/NullMixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/NullMixer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib/math/Limits.cpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mixer/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    # This application has a public include header.  Add it so all the other applications can access it.        
    #PUBLIC_INCLUDES
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)
