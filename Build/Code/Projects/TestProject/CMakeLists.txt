cmake_minimum_required (VERSION 3.5.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
SET(projectName TestProject)
SET(USE_KGL_CORE)
SET(USE_KGL_GRAPHICS)
project (${projectName} CXX)
INCLUDE (${TOP}/Build/Modules/CompilerDefinitions.cmake)
INCLUDE (${TOP}/Build/Modules/OperatingSystemDefinitions.cmake)
INCLUDE (${TOP}/Build/Code/KGL_Engine/ConfigureKGL.cmake)

add_executable(${projectName} ${TOP}/Code/Projects/${projectName}/main.cpp)

set(Modules
    KGL_CORE,
    KGL_GRAPHICS)

ConfigureKGL(${Modules})

target_compile_definitions(${projectName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

target_include_directories(${projectName} PUBLIC
    ${TOP}/Code/KGL_Engine/KGL_Core/include/
    ${TOP}/Code/KGL_Engine/KGL_Graphics/include/)

target_link_libraries (${projectName} KGL_Core)
target_link_libraries (${projectName} KGL_Graphics)

#solution folder
set_target_properties (${projectName} PROPERTIES FOLDER "Projects")