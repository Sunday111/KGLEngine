include(${TOP}/CMakeModules/GatherSources.cmake)

FUNCTION(GatherInSpecificFolder targetName folder description out)
    if(EXISTS ${folder})
        MESSAGE(STATUS "Gathering ${description} for ${targetName}")
        GatherSources(${folder} _localOut)
        set(${out} ${_localOut} PARENT_SCOPE)
    else()
        MESSAGE(STATUS "${targetName} doesn't have any ${description}")
    endif()
ENDFUNCTION()

FUNCTION(GatherKGLTargetSources targetName targetType gathered)
    set(targetsPath)

    if(${targetType} STREQUAL MODULE)
        set(targetsPath ${TOP}/KGL_Engine)
    elseif(${targetType} STREQUAL PROJECT)
        set(targetsPath ${TOP}/Projects)
    else()
        MESSAGE(FATAL_ERROR "Invalid target type value passed (${targetType}). It should be 'MODULE' or 'PROJECT'")
    endif()
    
    set(targetCodePath ${targetsPath}/${targetName}/code)
    
    message(STATUS "Gathering sources for ${targetName}")
    
    GatherInSpecificFolder(
        ${targetName}
        ${targetCodePath}/include
        "public headers"
        targetPublicHeaders)
    
    GatherInSpecificFolder(
        ${targetName}
        ${targetCodePath}/src/common
        "crossplatform private sources"
        targetCommonPrivateSources)
    
    GatherInSpecificFolder(
        ${targetName}
        ${targetCodePath}/src/OS_Specific/${SYSTEM_TYPE}
        "platform specific private sources"
        targetPlatformSpecificPrivateSources)

    SET(${gathered}
        ${targetPublicHeaders}
        ${targetCommonPrivateSources}
        ${targetPlatformSpecificPrivateSources}
        PARENT_SCOPE)
    
    message(STATUS "")

ENDFUNCTION()