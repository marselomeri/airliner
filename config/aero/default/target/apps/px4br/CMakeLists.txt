set(APP_NAME px4br)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/PX4BridgeData.dat  ${CMAKE_CURRENT_BINARY_DIR}/exe/cf/apps/ COPYONLY)