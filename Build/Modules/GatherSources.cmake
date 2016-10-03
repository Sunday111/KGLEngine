cmake_minimum_required(VERSION 3.3)

function(GetAllFolders path out)
	set(tempList)
	file(GLOB pathFiles RELATIVE ${path} ${path}/*)
	
	foreach(pathFile ${pathFiles})
		if(IS_DIRECTORY ${path}/${pathFile})
			list(APPEND tempList ${pathFile})
			
			GetAllFolders(${path}/${pathFile} internalFolders)
			
			foreach(internalFolder ${internalFolders})
				list(APPEND tempList ${pathFile}/${internalFolder})
			endforeach()			
		endif()
	endforeach()
	
	set(${out} ${tempList} PARENT_SCOPE)
endfunction()

function(GatherSourcesImpl relSourceFolder root folderSources)
	if (NOT ${relSourceFolder} STREQUAL "")
		set(sourceFolder ${root}/${relSourceFolder})
	else()
		set(sourceFolder ${root})
	endif()

	file(GLOB sourceFolderFiles ${sourceFolder}/*.*)
	set(filterName ${relSourceFolder})
	
	if (NOT ${filterName} STREQUAL "")
		FILE(TO_NATIVE_PATH ${filterName} filterName)
	endif()
	
	source_group("${filterName}" FILES ${sourceFolderFiles})
	set(${folderSources} ${sourceFolderFiles} PARENT_SCOPE)
endfunction()

function(GatherSources _root folderSources)
    if ("${_root}" STREQUAL "")
        message(FATAL_ERROR "GatherSources function needs root folder")
    endif()

	GetAllFolders(${_root} sourceFolders)
	GatherSourcesImpl("" ${_root} _allSources)
	
	foreach(sourceFolder ${sourceFolders})
		GatherSourcesImpl(${sourceFolder} ${_root} tmpSources)
		list(APPEND _allSources ${tmpSources})
	endforeach()
	
	set(${folderSources} ${_allSources} PARENT_SCOPE)
endfunction()