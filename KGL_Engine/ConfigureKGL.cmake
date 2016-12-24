include(${TOP}/CMakeModules/ReadKGLTargetDependencies.cmake)

FUNCTION(ConfigureKGL)
    cmake_parse_arguments(
        PARSED_ARGS           # prefix of output variables
        ""                    # list of names of the boolean arguments (only defined ones will be true)
        "INCLUDES;LIBRARIES"  # list of names of mono-valued arguments
        "MODULES"             # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}               # arguments of the function to parse, here we take the all original ones
    )
    
    # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_MODULES)
        message(FATAL_ERROR "You must provide modules to configure")
    endif()
    
    if(NOT PARSED_ARGS_INCLUDES)
        message(FATAL_ERROR "You must specify variable to retrieve the list of directories to include")
    endif()
    
    if(NOT PARSED_ARGS_LIBRARIES)
        message(FATAL_ERROR "You must specify variable to retrieve the list of libraries to link")
    endif()

    set(ExternDeps)
    set(EngineDeps)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    FOREACH(module ${PARSED_ARGS_MODULES})
        ReadKGLTargetDependencies(
            TARGET_NAME ${module}
            TARGET_TYPE MODULE
        )
        
        list(APPEND ExternDeps ${${module}_EXTERN_DEPS})
        list(APPEND EngineDeps ${${module}_ENGINE_DEPS})
        list(APPEND EngineDeps ${module})
    ENDFOREACH()
    
    #Manage every external dependency in the list if it is not empty
    if(ExternDeps)
        #Remove duplicates from external dependencies list
        list(REMOVE_DUPLICATES ExternDeps)
        
        message(STATUS "Configuring external dependencies...")
        foreach(externDep ${ExternDeps})
            include(${TOP}/ThirdParty/${externDep}.cmake)
        endforeach()
        
        message(STATUS "")
    endif()
    
    #Manage every engine dependency in the list if it is not empty
    if(EngineDeps)
        #Remove duplicates from engine dependencies list
        list(REMOVE_DUPLICATES EngineDeps)
        
        message(STATUS "Configuring engine dependencies...")
    
        foreach(engineDep ${EngineDeps})
            message(STATUS "Configuring ${engineDep}...")
            
            set(engineDepPath ${TOP}/KGL_Engine/${engineDep})
            set(engineDepInclude ${engineDepPath}/code/include)
            set(engineDepBuild ${engineDepPath}/build)
            
            if(NOT ${engineDep} STREQUAL KGL_Launcher AND EXISTS ${engineDepInclude})
                list(APPEND _includeDirs ${engineDepInclude})
                list(APPEND _linkLibs ${engineDep})
            endif()
            
            add_subdirectory(${engineDepBuild} ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/${engineDep})
        endforeach()
        
        set(${PARSED_ARGS_INCLUDES} ${_includeDirs} PARENT_SCOPE)
        set(${PARSED_ARGS_LIBRARIES} ${_linkLibs} PARENT_SCOPE)
    endif()
ENDFUNCTION()