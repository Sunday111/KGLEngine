include (${TOP}/CMakeModules/GatherKGLTargetSources.cmake)

set(ModuleName KGL_Base)

GatherKGLTargetSources(${ModuleName} MODULE moduleSources)
add_library(${ModuleName} STATIC ${moduleSources})

target_include_directories(${ModuleName} PUBLIC
    ${TOP}/ThirdParty/eigen/
    ${TOP}/KGL_Engine/${ModuleName}/code/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(${ModuleName} PUBLIC ${compileOptions})
target_compile_definitions(${ModuleName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

#solution folder
set_target_properties (${ModuleName} PROPERTIES FOLDER "KGL Engine")