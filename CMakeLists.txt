#####################
# AI CODE - ChatGPT #
#####################
cmake_minimum_required(VERSION 3.16)
project(opengl LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/GLAD)
add_subdirectory(lib/GLFW)

# Add include directories (for project headers)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/include/*.h
     ${PROJECT_SOURCE_DIR}/include/*.hpp)

# Define the executable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# Example: link with libraries (if any under lib/)
# add_subdirectory(lib)
target_link_libraries(opengl ${OPENGL_LIBRARIES} glad glfw)

# Optionally enable warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
######################
# /AI CODE - ChatGPT #
######################

