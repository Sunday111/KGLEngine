include(${TOP}/ThirdParty/Prepare.cmake)

add_library(KGL_Core SHARED ${TOP}/Code/KGL_Engine/KGL_Core/src/OS_Specific/${SYSTEM_TYPE}/GetUserName.cpp)
target_include_directories(KGL_Core PUBLIC ${TOP}/Code/KGL_Engine/KGL_Core/include/)
target_compile_definitions(KGL_Core PRIVATE -DKGL_CORE_SHARED -D${CMAKE_CXX_COMPILER_ID})