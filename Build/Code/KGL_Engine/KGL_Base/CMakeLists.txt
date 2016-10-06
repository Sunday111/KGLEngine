include(${TOP}/Build/Code/KGL_Engine/GatherKGLModuleSources.cmake)

set(ModuleName KGL_Base)

GatherKGLModuleSources(${ModuleName} moduleSources)
add_library(${ModuleName} STATIC ${moduleSources})

target_include_directories(${ModuleName} PUBLIC
    ${TOP}/ThirdParty/eigen/
    ${TOP}/Code/KGL_Engine/${ModuleName}/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(${ModuleName} PUBLIC ${compileOptions})
target_compile_definitions(${ModuleName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

#solution folder
set_target_properties (${ModuleName} PROPERTIES FOLDER "KGL Engine")