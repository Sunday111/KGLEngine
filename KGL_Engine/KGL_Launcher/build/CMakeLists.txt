include(${TOP}/CMakeModules/GatherKGLTargetSources.cmake)

set(ModuleName KGL_Launcher)

GatherKGLTargetSources(${ModuleName} MODULE moduleSources)
add_executable(${ModuleName} ${moduleSources})

target_compile_options(${ModuleName} PUBLIC ${compileOptions})
target_compile_definitions(${ModuleName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

if(${SYSTEM_TYPE} STREQUAL Windows)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        set_target_properties(${ModuleName} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    endif()
endif()