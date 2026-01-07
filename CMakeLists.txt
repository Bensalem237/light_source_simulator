cmake_minimum_required(VERSION 3.10)

# project name
project(LightSourceSimulator VERSION 1.0)

# C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL3 on my PC
find_package(SDL3 REQUIRED)

# Indicate where the "Header" (.h) files are found
include_directories(include)
include_directories(third_party/imgui)
include_directories(third_party/stb_image)
# Note : 'find_package' already takes care of SDL3

# Gather the source files (.cpp)
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# We manually add the source files of imGui (for they are in third_party)
list(APPEND IMGUI_SOURCES
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_sdl3.cpp
    third_party/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

# Create the final executable
add_executable(LightSimulator ${PROJECT_SOURCES} ${IMGUI_SOURCES})

# Link the libraries
target_link_libraries(LightSimulator PRIVATE SDL3::SDL3)