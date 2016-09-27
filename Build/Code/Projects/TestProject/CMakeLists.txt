cmake_minimum_required (VERSION 3.5.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
project (TestProject CXX)
include (${TOP}/Build/Modules/CompilerDefinitions.cmake)
include (${TOP}/Build/Modules/OperatingSystemDefinitions.cmake)

add_subdirectory(${TOP}/Build/Code/KGL_Engine/KGL_Core ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/KGL_Core)
add_subdirectory(${TOP}/Build/Code/KGL_Engine/KGL_Graphics ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/KGL_Graphics)

add_executable(TestProject ${TOP}/Code/Projects/TestProject/main.cpp)
target_compile_definitions(TestProject PRIVATE -D${CMAKE_CXX_COMPILER_ID})

target_include_directories(TestProject PUBLIC ${TOP}/Code/KGL_Engine/KGL_Core/include/)
target_include_directories(TestProject PUBLIC ${TOP}/Code/KGL_Engine/KGL_Graphics/include/)

target_link_libraries (TestProject KGL_Core)
target_link_libraries (TestProject KGL_Graphics)