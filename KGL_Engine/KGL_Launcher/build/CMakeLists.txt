include(${TOP}/KGL_Engine/GatherKGLModuleSources.cmake)

set(ModuleName KGL_Launcher)

GatherKGLModuleSources(${ModuleName} moduleSources)
add_executable(${ModuleName} ${moduleSources})

target_include_directories(${ModuleName} PUBLIC
    ${TOP}/KGL_Engine/${ModuleName}/include/
    ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(${ModuleName} PUBLIC ${compileOptions})
target_compile_definitions(${ModuleName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})

if(${SYSTEM_TYPE} STREQUAL Windows)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        set_target_properties(${ModuleName} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    endif()
endif()