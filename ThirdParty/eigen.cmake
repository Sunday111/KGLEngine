message(STATUS "Configure eigen")

SET(EIGEN_DIR ${TOP}/ThirdParty/eigen/)

IF(NOT EXISTS ${EIGEN_DIR})
    SET(EIGEN_SOURCE_ARCHIVE ${EIGEN_DIR}/eigen.tgz)

    IF(NOT EXISTS ${EIGEN_SOURCE_ARCHIVE})
        #download eigen sources
        message(STATUS "Downloading eigen sources")
        file(
            DOWNLOAD "https://bitbucket.org/eigen/eigen/get/3.2.10.tar.gz" ${EIGEN_SOURCE_ARCHIVE}
            STATUS "Downloading eigen")
        
        #unpack EIGEN sources
        message(STATUS "Unpack eigen...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${EIGEN_SOURCE_ARCHIVE}
            WORKING_DIRECTORY ${EIGEN_DIR})
        
        SET(EIGEN_SRC_FOLDER_NAME "eigen-eigen-b9cd8366d4e8")
        
        #gather files names
        file(GLOB eigenFiles ${EIGEN_DIR}/${EIGEN_SRC_FOLDER_NAME}/*)
        
        #move files
        foreach(oldName ${eigenFiles})
            string(REPLACE ${EIGEN_SRC_FOLDER_NAME} "" newName ${oldName})
            file(RENAME ${oldName} ${newName})
        endforeach()
    ENDIF()

ENDIF()