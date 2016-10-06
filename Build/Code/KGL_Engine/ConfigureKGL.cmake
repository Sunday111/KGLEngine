FUNCTION(AddModuleSubdirectory name)
    message(STATUS "Configure ${name}")
    add_subdirectory(${TOP}/Build/Code/KGL_Engine/${name} ${CMAKE_BINARY_DIR}/Deps/KGL_Engine/${name})
ENDFUNCTION()

FUNCTION(ConfigureKGL modules)
    set(USE_KGL_BASE 0)
    set(USE_KGL_CORE 0)
    set(USE_KGL_GRAPHICS 0)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    FOREACH(module ${modules})
        if(module EQUAL KGL_BASE)
            set(USE_KGL_BASE 1)    
        ELSEIF(module EQUAL KGL_CORE)
            set(USE_KGL_CORE 1)

            #dependencies
            set(USE_KGL_BASE 1)
        ELSEIF(module EQUAL KGL_GRAPHICS)
            set(USE_KGL_GRAPHICS 1)

            #dependencies
            set(USE_KGL_CORE 1)
            set(USE_KGL_BASE 1)
        endif()
    ENDFOREACH()

    message(STATUS "Configure KGL engine external dependencies")
    IF(DEFINED USE_KGL_BASE)
        #Download eigen, if it still not downloaded
        include(${TOP}/ThirdParty/eigen.cmake)
    ENDIF()
    
    IF(DEFINED USE_KGL_GRAPHICS)
        message(STATUS "Configure glew")
        include(${TOP}/ThirdParty/glew.cmake)
        add_subdirectory(${GLEW_DIR}/build/cmake ${GLEW_BINARY_DIR} EXCLUDE_FROM_ALL)
        set_target_properties (glew_s PROPERTIES FOLDER "Third Party")
    ENDIF()

    IF(DEFINED USE_KGL_GRAPHICS)
        message(STATUS "Configure glfw")
        include(${TOP}/ThirdParty/glfw.cmake)
        add_subdirectory(${GLFW_DIR} ${GLFW_BINARY_DIR} EXCLUDE_FROM_ALL)
        set_target_properties (glfw PROPERTIES FOLDER "Third Party")
    ENDIF()

    message(STATUS "Configure KGL engine used modules")
    IF(DEFINED USE_KGL_CORE)
        AddModuleSubdirectory(KGL_Core)
    ENDIF()

    IF(DEFINED USE_KGL_GRAPHICS)
        AddModuleSubdirectory(KGL_Graphics)
    ENDIF()

    IF(DEFINED USE_KGL_BASE)
        AddModuleSubdirectory(KGL_Base)
    ENDIF()
ENDFUNCTION()