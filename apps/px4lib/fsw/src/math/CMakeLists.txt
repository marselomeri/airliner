add_subdirectory(filters filters)

set(PX4LIB_LIB_SOURCES
    ${PX4LIB_LIB_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrix3F3.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrix4F4.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix4F4.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector2F.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector2F.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector3F.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector4F.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector4F.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Quaternion.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Quaternion.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Derivative.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Derivative.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Integrator.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Integrator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Limits.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Limits.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Expo.cpp
    ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Expo.hpp
)
    
set(PX4LIB_LIB_SOURCES  ${PX4LIB_LIB_SOURCES} PARENT_SCOPE)
set(PX4LIB_INCLUDES ${PX4LIB_INCLUDES} PARENT_SCOPE)
