SET(compileOptions)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    SET(compileOptions /W4 /WX /MP /sdl-)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
else()
	message(FATAL_ERROR "Unsupported compiler ${CMAKE_CXX_COMPILER_ID}")
endif()

message(STATUS "Compiler used: " ${CMAKE_CXX_COMPILER_ID})