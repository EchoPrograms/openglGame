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
add_subdirectory(lib/glm)
add_subdirectory(lib/GLFW)
add_subdirectory(lib/assimp)

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

# Copy shader directory into build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/res
            ${CMAKE_CURRENT_BINARY_DIR}/bin/res
)

# Link libraries. Ensure we link the bundled Assimp target so its include dirs and
# link settings are propagated. Use PRIVATE for modern CMake usage.
target_link_libraries(${PROJECT_NAME} PRIVATE
    assimp
    ${OPENGL_LIBRARIES}
    glad
    glfw
)

# Fallback: if for some reason the assimp target doesn't export include dirs,
# explicitly add the bundled include path (harmless if redundant).
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/assimp/include
)

# Optionally enable warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
######################
# /AI CODE - ChatGPT #
######################
