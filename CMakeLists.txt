cmake_minimum_required(VERSION 3.16)
project(minecraft_copy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#GLFW paths
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)


#include directories
include_directories(
    ${INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Window/window.cpp
    src/Utils/utils.cpp
    src/Shaders/shaders.cpp
    src/Primitive/Triangle/triangle.cpp
    src/Primitive/Triangle/test_triangle.cpp
    src/Primitive/Cube/cube.cpp
    src/Primitive/Quad/quad.cpp
    src/Texture/texture.cpp
    src/Camera/camera.cpp
    src/InputHandler/input_handler.cpp
    src/Debug/CoordSystem.cpp
    src/Debug/WorldCoordSystem.cpp
    src/stb_lib.cpp
    external_ref/glad.c
    src/Primitive/Cube/ll_cube.cpp
)

target_link_libraries(${PROJECT_NAME}
      ${CMAKE_SOURCE_DIR}/lib/libglfw3.a
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)