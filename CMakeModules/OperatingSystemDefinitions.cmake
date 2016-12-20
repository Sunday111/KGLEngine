if(WIN32)
	set(SYSTEM_TYPE Windows)
elseif(UNIX)
	set(SYSTEM_TYPE Unix)
else()
	message(FATAL_ERROR "Unsupported OS!")
endif()

message(STATUS "OS: " ${SYSTEM_TYPE})