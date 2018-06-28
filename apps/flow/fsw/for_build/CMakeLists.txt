
add_airliner_app_def(flow
    FILE FLOW
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/flow_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)


