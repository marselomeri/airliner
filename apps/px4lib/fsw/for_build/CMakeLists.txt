add_subdirectory(../src/ src)

add_airliner_app_def(px4lib
    FILE PX4LIB
    SOURCES
        ${PX4LIB_SOURCES}

    INCLUDES
        ${PX4LIB_INCLUDES}
        ${PX4LIB_PUBLIC_INCLUDES}

    # This application has a public include header.  Add it so all the other applications can access it.        
    PUBLIC_INCLUDES
        ${PX4LIB_PUBLIC_INCLUDES}
)
