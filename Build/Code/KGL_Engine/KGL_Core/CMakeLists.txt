include(${TOP}/Build/Code/KGL_Engine/GatherKGLModuleSources.cmake)

set(ModuleName KGL_Core)
set(MODULE_NAME KGL_CORE)
configure_file("${TOP}/Build/Code/Common.h.in" "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}/Common.h")

GatherKGLModuleSources(${ModuleName} moduleSources)
add_library(${ModuleName} SHARED ${moduleSources})

target_include_directories(${ModuleName} PUBLIC
    ${TOP}/Code/KGL_Engine/KGL_Base/include/
    ${TOP}/Code/KGL_Engine/${ModuleName}/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(${ModuleName} PRIVATE -D${MODULE_NAME}_SHARED -D${CMAKE_CXX_COMPILER_ID})
target_link_libraries (${ModuleName} KGL_Base)

#solution folder
set_target_properties (${ModuleName} PROPERTIES FOLDER "KGL Engine")