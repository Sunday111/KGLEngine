message(STATUS "Configure glew")

set(GLEW_DIR ${TOP}/ThirdParty/glew/)
set(GLEW_BINARY_DIR ${CMAKE_BINARY_DIR}/Deps/ThirdParty/glew)

if(NOT EXISTS ${GLEW_DIR})
    set(GLEW_SOURCE_ARCHIVE ${GLEW_DIR}/glew.tgz)
    
    if(NOT EXISTS ${GLEW_SOURCE_ARCHIVE})
        #download glew sources
        message(STATUS "Downloading glew sources")
        file(
            DOWNLOAD "https://netcologne.dl.sourceforge.net/project/glew/glew/2.0.0/glew-2.0.0.tgz" ${GLEW_SOURCE_ARCHIVE}
            STATUS "Downloading glew")
        
        #unpack glew sources
        message(STATUS "Unpack glew...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${GLEW_SOURCE_ARCHIVE}
            WORKING_DIRECTORY ${GLEW_DIR})
        
        SET(GLEW_SRC_FOLDER_NAME "glew-2.0.0")
        
        #gather files names
        file(GLOB glewFiles ${GLEW_DIR}/${GLEW_SRC_FOLDER_NAME}/*)
        
        #move files
        foreach(oldName ${glewFiles})
            string(REPLACE ${GLEW_SRC_FOLDER_NAME} "" newName ${oldName})
            file(RENAME ${oldName} ${newName})
        endforeach()
    endif()
endif()

add_subdirectory(${GLEW_DIR}/build/cmake ${GLEW_BINARY_DIR} EXCLUDE_FROM_ALL)
set_target_properties (glew_s PROPERTIES FOLDER "Third Party")