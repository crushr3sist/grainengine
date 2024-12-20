cmake_minimum_required(VERSION 3.10)

# Enable compilation database and debugging info
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Create symbolic link for compile_commands.json instead of copying
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()

# Set VS2022 toolset
set(CMAKE_GENERATOR_TOOLSET "v143")
set(CMAKE_VS_PLATFORM_TOOLSET "v143")
set(CMAKE_GENERATOR_PLATFORM "x64")

project(grainengine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add include directories first
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/GLFW/include")
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/glad/include")

# Add GLAD source
set(GLAD_SOURCE "${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c")

# Adjust the library path based on compiler
if(MINGW)
    set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/libs/GLFW/lib-mingw-w64/libglfw3.a")
else()
    set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/libs/GLFW/lib-vc2022/glfw3.lib")
endif()
# Add GLM
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/glm")

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SHADERS "src/*.shader")

file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# Create executable
add_executable(${PROJECT_NAME} 
    ${SOURCES} 
    ${HEADERS}
    ${SHADERS}
    ${GLAD_SOURCE}
)

# Add compile definitions for better intellisense
target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_NONE
    _CRT_SECURE_NO_WARNINGS
)

# Add these before the target_include_directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "/W4 /WX"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)
# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    ${GLFW_LIBRARY}
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles"
COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/*.cmake"
COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/CMakeCache.txt"
)

# Copy DLL to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/libs/GLFW/lib-vc2022/glfw3.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

file(GLOB_RECURSE SHADER_FILES "${CMAKE_SOURCE_DIR}/src/shaders/*.shader")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
