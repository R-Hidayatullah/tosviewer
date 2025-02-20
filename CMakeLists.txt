cmake_minimum_required(VERSION 3.10)

project("tosviewer")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensures strict standard compliance


# Include directories
include_directories(include)
include_directories(external/glad33core/include)
include_directories(external/imgui-docking)
include_directories(external/imgui-docking/backends)
include_directories(external/glm-1.0.1-light) 
include_directories(external/stb-master) 

# Find GLFW package
find_package(glfw3 REQUIRED)

# Source files for ImGui
set(IMGUI_SOURCES
    external/imgui-docking/imgui.cpp
    external/imgui-docking/imgui_demo.cpp
    external/imgui-docking/imgui_draw.cpp
    external/imgui-docking/imgui_widgets.cpp
    external/imgui-docking/imgui_tables.cpp
    external/imgui-docking/backends/imgui_impl_opengl3.cpp
    external/imgui-docking/backends/imgui_impl_glfw.cpp
)

# Set linker flags for static linking
# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

# Add source to the executable
add_executable(tosviewer ${IMGUI_SOURCES} external/glad33core/src/glad.c source/tosviewer.cpp)

# Link libraries
target_link_libraries(tosviewer glfw z)
