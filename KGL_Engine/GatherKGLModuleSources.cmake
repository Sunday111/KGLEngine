include(${TOP}/CMakeModules/GatherSources.cmake)

FUNCTION(GatherKGLModuleSources moduleName gathered)

    #Gather module headers
    MESSAGE(STATUS "Gathering public sources for ${moduleName}")
    GatherSources(${TOP}/KGL_Engine/${moduleName}/include modulePublicSources)

    #Gather sources with platform independent code
    SET(moduleCommonPrivateSources)
    SET(moduleCommonPrivateSourcesPath ${TOP}/KGL_Engine/${moduleName}/src/common)
    IF(EXISTS ${moduleCommonPrivateSourcesPath})
        MESSAGE(STATUS "Gathering common private sources for ${moduleName}")
        GatherSources(${moduleCommonPrivateSourcesPath} moduleCommonPrivateSources)
    ELSE()
        MESSAGE(STATUS "${moduleName} doesn't have any common private sources")
    ENDIF()

    #gather sources with platform specific code
    SET(modulePlatformSpecificPrivateSources)
    SET(modulePlatformSpecificPrivateSourcesPath ${TOP}/KGL_Engine/${moduleName}/src/OS_Specific/${SYSTEM_TYPE})
    IF(EXISTS ${modulePlatformSpecificPrivateSourcesPath})
        MESSAGE(STATUS "Gathering platform specific sources for ${moduleName}")
        GatherSources(${modulePlatformSpecificPrivateSourcesPath} modulePlatformSpecificPrivateSources)
    ELSE()
        MESSAGE(STATUS "${moduleName} doesn't have any platform specific private sources")
    ENDIF()

    SET(${gathered}
        ${modulePublicSources}
        ${moduleCommonPrivateSources}
        ${modulePlatformSpecificPrivateSources}
        PARENT_SCOPE)

ENDFUNCTION()