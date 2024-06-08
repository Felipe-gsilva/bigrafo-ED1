cmake_minimum_required(VERSION 3.8)

project(bigrafo)

set(CMAKE_C_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw/include")

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.h")

add_executable(bigrafo ${SOURCES})

target_include_directories(bigrafo PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${GLFW_INCLUDE_DIR}
)

