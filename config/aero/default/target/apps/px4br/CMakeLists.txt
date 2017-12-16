set(APP_NAME px4br)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/PX4BridgeData.dat  ${PROJECT_BINARY_DIR}/target/exe/cf/apps/ COPYONLY)