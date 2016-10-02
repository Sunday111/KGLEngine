include(${TOP}/ThirdParty/Prepare.cmake)

set(ModuleName KGL_Graphics)
set(MODULE_NAME KGL_GRAPHICS)
configure_file("${TOP}/Build/Code/Common.h.in" "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}/Common.h")

if(NOT EXISTS ${GLFW_BINARY_DIR})
    add_subdirectory(${GLFW_DIR} ${GLFW_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT EXISTS ${GLEW_BINARY_DIR})
    add_subdirectory(${GLEW_DIR}/build/cmake ${GLEW_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library(${ModuleName} SHARED ${TOP}/Code/KGL_Engine/${ModuleName}/src/GraphicsTestFunction.cpp)
target_include_directories(${ModuleName} PUBLIC
    ${TOP}/Code/KGL_Engine/${ModuleName}/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(${ModuleName} PRIVATE -DKGL_GRAPHICS_SHARED -D${CMAKE_CXX_COMPILER_ID})
target_link_libraries (${ModuleName} glew_s)
target_link_libraries (${ModuleName} glfw)