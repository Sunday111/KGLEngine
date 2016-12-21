cmake_minimum_required (VERSION 3.5.1)
FUNCTION(GenerateKGLProject projectName)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
    
    #used CMake modules
    include (${TOP}/CMakeModules/CompilerDefinitions.cmake)
    include (${TOP}/CMakeModules/CreateLauncher.cmake)
    include (${TOP}/CMakeModules/OperatingSystemDefinitions.cmake)
    include (${TOP}/CMakeModules/GatherKGLTargetSources.cmake)
    include (${TOP}/KGL_Engine/ConfigureKGL.cmake)
    
    #declare project
    project (${projectName} CXX)
    
    #declare path to project variable_requires
    set(projectPath ${TOP}/Projects/${projectName})
    
    #Select project sources
    GatherKGLTargetSources(${projectName} PROJECT projectSources)
    add_library(${projectName} SHARED ${projectSources})
    
    #Declare variable with path to EngineDeps file for project
    set(projectEngineDeps ${projectPath}/build/EngineDeps.txt)
    
    #configure KGL if file with dependencies is exists
    if(EXISTS ${projectEngineDeps})
        file(READ ${projectEngineDeps} projectDeps)
        
        #Manage KGL engine dependencies
        ConfigureKGL("${projectDeps}" KGLInclude KGLLibraries)
        
        target_include_directories(${projectName} PUBLIC ${KGLInclude})    
        target_link_libraries (${projectName} ${KGLLibraries})
    endif()
    
    target_compile_options(${projectName} PUBLIC ${compileOptions})
    target_compile_definitions(${projectName} PRIVATE -D${CMAKE_CXX_COMPILER_ID})
    
    #solution folder
    set_target_properties (${projectName} PROPERTIES FOLDER "Projects")
    
    add_custom_command(
        TARGET ${projectName} POST_BUILD
        COMMAND 
            ${CMAKE_COMMAND}                         #Path to cmake executable file
            -E                                       #CMake in command mode
            copy_directory                           #CMake command for file copying
            "${TOP}/Projects/${projectName}/Data"    #Copy source
            "$<TARGET_FILE_DIR:${projectName}>/Data" #Copy destination
            
        COMMENT "Copying $<TARGET_FILE_DIR:${projectName}>/${targetFile}"
    )
    
    CreateLauncher(KGL_Launcher ${projectName})
ENDFUNCTION() 
