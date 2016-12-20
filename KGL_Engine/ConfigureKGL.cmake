FUNCTION(AddModuleSubdirectory name)
    message(STATUS "Configure ${name}")
    add_subdirectory(${TOP}/KGL_Engine/${name} ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/${name})
ENDFUNCTION()

FUNCTION(ConfigureKGL modules)
    set(ExternDeps)
    set(EngineDeps)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    FOREACH(module ${modules})
        set(depsPath ${TOP}/KGL_Engine/${module})
        
        #Look for module's file with external dependencies
        set(ExternDepsPath ${depsPath}/ExternDeps.txt)
        if(EXISTS ${ExternDepsPath})
            file(READ ${ExternDepsPath} contents)
            
            foreach(externDep ${contents})
                list(APPEND ExternDeps ${externDep})
            endforeach()
        endif()
        
        #Look for module's engine dependencies
        set(EngineDepsPath ${depsPath}/EngineDeps.txt)
        if(EXISTS ${EngineDepsPath})        
            file(READ ${EngineDepsPath} contents)
            
            foreach(engineDep ${contents})
                list(APPEND EngineDeps ${engineDep})
            endforeach()
        endif()
        
        list(APPEND EngineDeps ${module})
    ENDFOREACH()
    
    list(REMOVE_DUPLICATES ExternDeps)
    if(ExternDeps)
        message(STATUS "Configure KGL engine external dependencies")

        foreach(externDep ${ExternDeps})
            include(${TOP}/ThirdParty/${externDep}.cmake)
        endforeach()
    endif()
    
    list(REMOVE_DUPLICATES EngineDeps)
    if(EngineDeps)
        message(STATUS "Configure KGL engine used modules ")
    
        foreach(engineDep ${EngineDeps})
            AddModuleSubdirectory(${engineDep})
        endforeach()
    endif()
ENDFUNCTION()