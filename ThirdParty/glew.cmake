set(GLEW_DIR ${TOP}/ThirdParty/glew/)
set(GLEW_BINARY_DIR ${CMAKE_BINARY_DIR}/Deps/ThirdParty/glew)

if(NOT EXISTS ${GLEW_DIR})
    set(GLEW_SOURCE_ARCHIVE ${GLEW_DIR}/glew.tgz)
    
    if(NOT EXISTS ${GLEW_SOURCE_ARCHIVE})
        #download glew sources
        message(STATUS "Downloading glew sources")
        file(
            DOWNLOAD "http://heanet.dl.sourceforge.net/project/glew/glew/2.0.0/glew-2.0.0.tgz" ${GLEW_SOURCE_ARCHIVE}
            STATUS "Downloading glew")
        
        #unpack glew sources
        message(STATUS "Unpack glew...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${GLEW_SOURCE_ARCHIVE}
            WORKING_DIRECTORY ${GLEW_DIR})
        
        #gather files names
        file(GLOB GLEW_FILES ${GLEW_DIR}/glew-2.0.0/*)
        
        #copy files
        file(COPY ${GLEW_FILES} DESTINATION ${GLEW_DIR})
    endif()
endif()