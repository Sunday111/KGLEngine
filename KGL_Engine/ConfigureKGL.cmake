FUNCTION(ConfigureKGL modules includeDirs linkLibs)
    set(ExternDeps)
    set(EngineDeps)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    FOREACH(module ${modules})        
        set(depsPath ${TOP}/KGL_Engine/${module}/build/)
        
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
    
    message(STATUS "EngineDeps: ${EngineDeps}")
    
    #Manage every external dependency in the list if it is not empty
    if(ExternDeps)
        #Remove duplicates from external dependencies list
        list(REMOVE_DUPLICATES ExternDeps)
        
        message(STATUS "Configure KGL engine external dependencies")

        foreach(externDep ${ExternDeps})
            include(${TOP}/ThirdParty/${externDep}.cmake)
        endforeach()
    endif()
    
    #Manage every engine dependency in the list if it is not empty
    if(EngineDeps)
        #Remove duplicates from engine dependencies list
        list(REMOVE_DUPLICATES EngineDeps)
        
        message(STATUS "Configure KGL engine used modules")
        message(STATUS "")
    
        foreach(engineDep ${EngineDeps})
            message(STATUS "Configuring ${engineDep}")
            
            set(engineDepPath ${TOP}/KGL_Engine/${engineDep})
            set(engineDepInclude ${engineDepPath}/code/include)
            set(engineDepBuild ${engineDepPath}/build)
            
            if(NOT ${engineDep} STREQUAL KGL_Launcher AND EXISTS ${engineDepInclude})
                list(APPEND _includeDirs ${engineDepInclude})
                list(APPEND _linkLibs ${engineDep})
            endif()
            
            add_subdirectory(${engineDepBuild} ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/${engineDep})
            
            message(STATUS "")
        endforeach()
        
        set(${includeDirs} ${_includeDirs} PARENT_SCOPE)
        set(${linkLibs} ${_linkLibs} PARENT_SCOPE)
    endif()
ENDFUNCTION()