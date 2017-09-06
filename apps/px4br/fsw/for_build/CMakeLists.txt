
add_airliner_app_def(px4br
    FILE PX4BR
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmd_codes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_routes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_routes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_serialization.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_serialization.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4_msgs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4_serialization.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4_serialization.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_msgs/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4_msgs/
)

