function(CreateLauncher targetName targetLibrary)
	message(STATUS "Generating launcher for target ${targetName} (target library is ${targetLibrary})")
	
	set(TemplatesDir ${TOP}/CMakeModules/LaunchersTemplates)
	
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		
		file(READ "${TemplatesDir}/Perconfig.vcxproj.user.in" PerConfig)
		
		set(USERFILE_CONFIGSECTIONS)
		
		foreach(USERFILE_CONFIGNAME ${CMAKE_CONFIGURATION_TYPES})
			set(USERFILE_${USERFILE_CONFIGNAME}_COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${USERFILE_CONFIGNAME}/${targetName})
			set(USERFILE_COMMAND_ARGUMENTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${USERFILE_CONFIGNAME}/${targetLibrary})
			set(USERFILE_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${USERFILE_CONFIGNAME})
			
			if(${BUILD_ARCHITECTURE} STREQUAL "X32")
				set(USERFILE_PLATFORM Win32)
			else()
				set(USERFILE_PLATFORM ${BUILD_ARCHITECTURE})
			endif()
			
			string(CONFIGURE "${PerConfig}" _temp @ONLY ESCAPE_QUOTES)
			string(CONFIGURE
				"${USERFILE_CONFIGSECTIONS}${_temp}"
				USERFILE_CONFIGSECTIONS
				ESCAPE_QUOTES)
		endforeach()
		
		configure_file("${TemplatesDir}/vcxproj.user.in"
						"ALL_BUILD.vcxproj.user"
						@ONLY
		)
		
	else()
		message(WARNING "Can't create launcher for ${COMPILER_NAME} compiler type.")
	endif()	
endfunction()