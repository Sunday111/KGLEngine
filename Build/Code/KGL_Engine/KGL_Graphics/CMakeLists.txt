include(${TOP}/ThirdParty/Prepare.cmake)

set(ModuleName KGL_Graphics)
set(MODULE_NAME KGL_GRAPHICS)
configure_file("${TOP}/Build/Code/Common.h.in" "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}/Common.h")

add_library(${ModuleName} SHARED ${TOP}/Code/KGL_Engine/${ModuleName}/src/GraphicsTestFunction.cpp)
target_include_directories(${ModuleName} PUBLIC
    ${TOP}/Code/KGL_Engine/${ModuleName}/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(${ModuleName} PRIVATE -DKGL_GRAPHICS_SHARED -D${CMAKE_CXX_COMPILER_ID})