FUNCTION(ReadKGLTargetDependencies)
    cmake_parse_arguments(
        PARSED_ARGS               # prefix of output variables
        ""                        # list of names of the boolean arguments (only defined ones will be true)
        "TARGET_NAME;TARGET_TYPE" # list of names of mono-valued arguments
        ""                        # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                   # arguments of the function to parse, here we take the all original ones
    )
    
    if(NOT PARSED_ARGS_TARGET_NAME)
        message(FATAL_ERROR "You must provide target name")
    endif()
    
    if(NOT PARSED_ARGS_TARGET_TYPE)
        message(FATAL_ERROR "You must provide target type")
    endif()
    
    set(targetsFolder)
    
    if("${PARSED_ARGS_TARGET_TYPE}" STREQUAL MODULE)
        set(targetsFolder ${TOP}/KGL_Engine)
    elseif("${PARSED_ARGS_TARGET_TYPE}" STREQUAL PROJECT)
        set(targetsFolder ${TOP}/Projects)
    else()
        message(FATAL_ERROR "Invalid target type passed: ${PARSED_ARGS_TARGET_TYPE}")
    endif()
    
    set(targetBuildPath ${targetsFolder}/${PARSED_ARGS_TARGET_NAME}/build)
    
    if("${${PARSED_ARGS_TARGET_NAME}_EXTERN_DEPS}" STREQUAL "")
        set(targetExternDepsFile ${targetBuildPath}/ExternDeps.txt)
        
        if(EXISTS ${targetExternDepsFile})
            file(READ ${targetExternDepsFile} _fileContent)
            set(${PARSED_ARGS_TARGET_NAME}_EXTERN_DEPS ${_fileContent} CACHE INTERNAL "" FORCE)
        endif()
    endif()
    
    if("${${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS}" STREQUAL "")
        set(targetEngineDepsFile ${targetBuildPath}/EngineDeps.txt)
        
        if(EXISTS ${targetEngineDepsFile})
            file(READ ${targetEngineDepsFile} _fileContent)
            
            if(NOT "${_fileContent}" STREQUAL "")
                foreach(dep ${_fileContent})
                    ReadKGLTargetDependencies(
                        TARGET_NAME ${dep}
                        TARGET_TYPE MODULE
                    )
                
                    list(APPEND ${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS ${dep})
                    list(APPEND ${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS ${${dep}_ENGINE_DEPS})
                endforeach()
                
                list(REMOVE_DUPLICATES ${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS)
            endif()
        endif()
        
        set(${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS "${${PARSED_ARGS_TARGET_NAME}_ENGINE_DEPS}" CACHE INTERNAL "" FORCE)
    endif()
ENDFUNCTION()