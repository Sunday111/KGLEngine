cmake_minimum_required (VERSION 3.5.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
SET(projectName TestProject)
project (${projectName} CXX)
include (${TOP}/CMakeModules/CompilerDefinitions.cmake)
include (${TOP}/CMakeModules/CreateLauncher.cmake)
include (${TOP}/CMakeModules/OperatingSystemDefinitions.cmake)
include (${TOP}/KGL_Engine/ConfigureKGL.cmake)

add_library(${projectName} SHARED ${TOP}/Projects/${projectName}/main.cpp)

ConfigureKGL("KGL_Core;KGL_Graphics;KGL_Launcher")

target_compile_options(${projectName} PUBLIC ${compileOptions})
target_compile_definitions(${projectName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

target_include_directories(${projectName} PUBLIC
    ${TOP}/KGL_Engine/KGL_Base/include/
    ${TOP}/KGL_Engine/KGL_Core/include/
    ${TOP}/KGL_Engine/KGL_Graphics/include/)

target_link_libraries (${projectName} KGL_Base)
target_link_libraries (${projectName} KGL_Core)
target_link_libraries (${projectName} KGL_Graphics)

#solution folder
set_target_properties (${projectName} PROPERTIES FOLDER "Projects")

add_custom_command(
    TARGET ${projectName} POST_BUILD
    COMMAND 
        ${CMAKE_COMMAND}                         #Path to cmake executable file
        -E                                       #CMake in command mode
        copy_directory                           #CMake command for file copying
        "${TOP}/Projects/${projectName}/Data"    #Copy source
        "$<TARGET_FILE_DIR:${projectName}>/Data" #Copy destination
        
    COMMENT "Copying $<TARGET_FILE_DIR:${projectName}>/${targetFile}"
)

CreateLauncher(KGL_Launcher ${projectName})