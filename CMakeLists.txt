cmake_minimum_required(VERSION 3.8)

project(bigrafo)

# Ensure C11 standard is used
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Disable unwanted GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW 
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/deps/glfw/lib")

# Add GLAD 
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/glad/include")
set(GLAD_SRC_DIR"${CMAKE_SOURCE_DIR}/deps/glad/src")

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.h")

cmake_minimum_required(VERSION 3.8)

project(bigrafo)

# Ensure C11 standard is used
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Disable unwanted GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW 
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/deps/glfw/lib")

# Add GLAD 
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/glad/include")
set(GLAD_SRC_DIR"${CMAKE_SOURCE_DIR}/deps/glad/src")

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.h")
# Add GLAD source file
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/deps/glad/src/glad.c")

# Add executable target
add_executable(bigrafo ${SOURCES})

# Include directories
target_include_directories(bigrafo PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${GLFW_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
)

# Define GLFW_INCLUDE_NONE globally
target_compile_definitions(bigrafo PUBLIC GLFW_INCLUDE_NONE)

# Link libraries
target_link_libraries(bigrafo X11 dl pthread)

# If GLFW is part of your project and needs to be built
add_subdirectory(deps/glfw)
target_link_libraries(bigrafo glfw)

