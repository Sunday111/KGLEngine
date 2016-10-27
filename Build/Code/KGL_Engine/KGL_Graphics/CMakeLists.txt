include(${TOP}/Build/Code/KGL_Engine/GatherKGLModuleSources.cmake)

set(ModuleName KGL_Graphics)
set(MODULE_NAME KGL_GRAPHICS)
configure_file("${TOP}/Build/Code/Common.h.in" "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}/Common.h")

GatherKGLModuleSources(${ModuleName} moduleSources)

add_library(${ModuleName} SHARED ${moduleSources})

target_include_directories(${ModuleName} PUBLIC
    ${TOP}/ThirdParty/glew/include/
    ${TOP}/Code/KGL_Engine/KGL_Base/include/
    ${TOP}/Code/KGL_Engine/KGL_Core/include/
    ${TOP}/Code/KGL_Engine/${ModuleName}/include/
    ${TOP}/Code/KGL_Engine/${ModuleName}/src/common/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(${ModuleName} PUBLIC ${compileOptions})
target_compile_definitions(${ModuleName} PRIVATE -D${MODULE_NAME}_SHARED -D${CMAKE_CXX_COMPILER_ID})
target_link_libraries (${ModuleName} glew_s)
target_link_libraries (${ModuleName} glfw)
target_link_libraries (${ModuleName} KGL_Base)
target_link_libraries (${ModuleName} KGL_Core)

#solution folder
set_target_properties (${ModuleName} PROPERTIES FOLDER "KGL Engine")