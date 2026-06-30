cmake_minimum_required(VERSION 3.20)
project(voxel_ds LANGUAGES C CXX)

# C++ standard and compile flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/glfw)

file(GLOB SRCS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS} ${SRCS})

# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.hpp")
set_source_files_properties(thirdparty/glad/src/glad.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
    thirdparty/glad/include
    thirdparty/imgui
    thirdparty/imgui/backends
)

target_sources(${PROJECT_NAME} PRIVATE
    thirdparty/glad/src/glad.c
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_demo.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/imgui_impl_glfw.cpp
    thirdparty/imgui/imgui_impl_opengl3.cpp
)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}
)

