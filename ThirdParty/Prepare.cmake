
set(GLFW_DIR ${TOP}/ThirdParty/glfw/)
set(GLFW_SOURCE_DIR ${GLFW_DIR}Sources/)
set(GLFW_BUILD_DIR ${GLFW_DIR}Build/${BUILD_ARCHITECTURE}/)

set(GLEW_DIR ${TOP}/ThirdParty/glew/)
set(GLEW_SOURCE_DIR ${GLEW_DIR}Sources/)
set(GLEW_BUILD_DIR ${GLEW_DIR}Build/${BUILD_ARCHITECTURE}/)

function(BuildGlfw Configuration)
    if(NOT EXISTS ${GLFW_BUILD_DIR}/${Configuration}/${BUILD_ARCHITECTURE})
        #Compile
        execute_process(
            COMMAND ${TOP}/ThirdParty/BuildGlfwWindows.bat GLFW.sln ${Configuration}
            WORKING_DIRECTORY ${GLFW_BUILD_DIR})
    
        #copy libraries
        file(
            COPY ${GLFW_BUILD_DIR}/src/${Configuration}/glfw3.lib
            DESTINATION ${GLFW_DIR}/${Configuration}/${BUILD_ARCHITECTURE}/)
    endif()
endfunction()

if(${BUILD_ARCHITECTURE} STREQUAL X32)
    set(GENERATOR_NAME "Visual Studio 14 2015")
else()
    set(GENERATOR_NAME "Visual Studio 14 2015 Win64")
endif()

#glfw
if(NOT EXISTS ${GLFW_DIR}/Debug/${Configuration}/${BUILD_ARCHITECTURE})
    #Generate build files
    if(NOT EXISTS ${GLFW_BUILD_DIR})

        #Download glwf sources
        if(NOT EXISTS ${GLFW_SOURCE_DIR})
            execute_process(COMMAND git clone https://github.com/glfw/glfw.git ${GLFW_SOURCE_DIR})
        endif()

        file(MAKE_DIRECTORY ${GLFW_BUILD_DIR})
        execute_process(COMMAND cmake -G${GENERATOR_NAME} ${GLFW_SOURCE_DIR} WORKING_DIRECTORY ${GLFW_BUILD_DIR})
    endif()

    #copy include files
    if(NOT EXISTS ${GLFW_SOURCE_DIR}/include)
        file(COPY ${GLFW_SOURCE_DIR}/include DESTINATION ${GLFW_DIR})
    endif()
    
    BuildGlfw(Debug)
    BuildGlfw(Release)
    
    file(REMOVE_RECURSE ${GLFW_BUILD_DIR})
endif()