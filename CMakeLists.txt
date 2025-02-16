# CMakeList.txt : CMake project for tosviewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("tosviewer")
set(CMAKE_TOOLCHAIN_FILE "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(external/glad33corewithext/include)
include_directories(external/imgui-docking)
include_directories(external/imgui-docking/backends)

find_package(directxtex CONFIG REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(external/glad33corewithext)

set(IMGUI_SOURCES
    external/imgui-docking/imgui.cpp
    external/imgui-docking/imgui_demo.cpp
    external/imgui-docking/imgui_draw.cpp
    external/imgui-docking/imgui_widgets.cpp
    external/imgui-docking/imgui_tables.cpp
    external/imgui-docking/backends/imgui_impl_opengl3.cpp
    external/imgui-docking/backends/imgui_impl_glfw.cpp
)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lz")


# Add source to this project's executable.
add_executable (tosviewer 
    ${IMGUI_SOURCES}
    "source/tosviewer.cpp" "include/application.h" "include/ipf_formats.h" "include/ies_formats.h")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET tosviewer PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.

target_include_directories(${PROJECT_NAME} PRIVATE JPEG::JPEG)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

# Link libraries to your executable
target_link_libraries(${PROJECT_NAME} 
    Microsoft::DirectXTex
    glfw
    opengl32
    glad
    glm::glm
    PNG::PNG
    JPEG::JPEG
)