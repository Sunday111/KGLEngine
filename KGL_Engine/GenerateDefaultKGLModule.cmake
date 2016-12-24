include (${TOP}/CMakeModules/GatherKGLTargetSources.cmake)

FUNCTION(GenerateDefaultKGLModule moduleName includeDirectories linkLibraries)
    GatherKGLTargetSources(${moduleName} MODULE moduleSources)
    
    set(modulePath ${TOP}/KGL_Engine/${moduleName})
    set(moduleBuildPath ${modulePath}/build)
    set(moduleCodePath ${modulePath}/code)
    
    file(READ ${moduleBuildPath}/ModuleInfo.txt moduleInfo)
    
    set(add_fn)
    set(add_attribute)
    
    foreach(infoEntry "${moduleInfo}")
        if(${infoEntry} STREQUAL LIBRARY)
            set(add_fn ADD_LIBRARY)
        elseif(${infoEntry} STREQUAL EXECUTABLE)
            set(add_fn ADD_EXECUTABLE)
        elseif(${infoEntry} STREQUAL STATIC)
            set(add_attribute STATIC)
        elseif(${infoEntry} STREQUAL SHARED)
            set(add_attribute SHARED)
        else()
            MESSAGE(FATAL_ERROR "Invalid module info entry: ${infoEntry}")
        endif()
    endforeach()
    
    ${add_fn}(${moduleName} ${add_attribute} ${moduleSources})
    
    target_compile_options(${moduleName} PUBLIC ${compileOptions})
    target_compile_definitions(${moduleName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})
    
    target_include_directories(
        ${moduleName}
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${moduleCodePath}/include)
    
    if(NOT "${includeDirectories}" STREQUAL "")
        target_include_directories(
            ${moduleName}
            PUBLIC
            ${includeDirectories})
    endif()
    
    if(NOT "${linkLibraries}" STREQUAL "")
        target_link_libraries(
            ${moduleName}
            ${linkLibraries})
    endif()
    
ENDFUNCTION()