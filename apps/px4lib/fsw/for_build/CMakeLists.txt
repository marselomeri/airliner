add_subdirectory(../src/ src)

add_airliner_app_def(px4lib
    FILE PX4LIB
    SOURCES
        ${PX4LIB_SOURCES}

    INCLUDES
        ${PX4LIB_INCLUDES}
        ${PX4LIB_PUBLIC_INCLUDES}
   
    PUBLIC_INCLUDES
        ${PX4LIB_PUBLIC_INCLUDES}
)
