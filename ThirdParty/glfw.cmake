set(GLFW_DIR ${TOP}/ThirdParty/glfw/)
set(GLFW_BINARY_DIR ${CMAKE_BINARY_DIR}/Deps/ThirdParty/glfw)

#glfw
if(NOT EXISTS ${GLFW_DIR})
    message(STATUS "Downloading glfw sources")
    execute_process(COMMAND git clone https://github.com/glfw/glfw.git ${GLFW_DIR})
endif()