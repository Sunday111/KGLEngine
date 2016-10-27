message(STATUS "Configure glfw")

set(GLFW_DIR ${TOP}/ThirdParty/glfw/)
set(GLFW_BINARY_DIR ${CMAKE_BINARY_DIR}/Deps/ThirdParty/glfw)

#glfw
if(NOT EXISTS ${GLFW_DIR})
    message(STATUS "Downloading glfw sources")
    execute_process(COMMAND git clone https://github.com/glfw/glfw.git ${GLFW_DIR})
endif()

add_subdirectory(${GLFW_DIR} ${GLFW_BINARY_DIR} EXCLUDE_FROM_ALL)
set_target_properties (glfw PROPERTIES FOLDER "Third Party")