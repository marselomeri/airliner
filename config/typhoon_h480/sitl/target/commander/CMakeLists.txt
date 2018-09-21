
file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/commander_workspace" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMDR_WORKSPACE ${CMAKE_CURRENT_BINARY_DIR}/commander_workspace)
set(AIRLINER_MSG_DEF_PATH ${EXPLAIN_DIR})
set(AIRLINER_PROTO_PATH ${EXPLAIN_DIR}/src/protos)
set(COMMANDER_PATH ${PROJECT_SOURCE_DIR}/tools/commander)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start_commander.in ${CMAKE_CURRENT_BINARY_DIR}/start_commander @ONLY)

add_custom_target(start-commander)
add_custom_command(TARGET start-commander
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/start_commander
)
add_dependencies(ground_tools start-commander)

set(COMMANDER_WORKSPACE_PLUGINS_DIR ${CMDR_WORKSPACE}/plugins PARENT_SCOPE)
