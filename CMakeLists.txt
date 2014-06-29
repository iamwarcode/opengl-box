cmake_minimum_required(VERSION 2.8)
PROJECT(BOX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BOX_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SOIL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})
include_directories(include)

file(GLOB source "src/*.cpp")
add_executable(box ${source})
target_link_libraries(box
                      ${SDL2_LIBRARY}
                      ${OPENGL_LIBRARIES}
                      ${GLEW_LIBRARY}
                      ${SOIL_LIBRARY})
