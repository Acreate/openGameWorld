
message("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message("name =" ${CURRENT_FOLDER})
project(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")


## 特别的输出
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/filter_plugins/ )
##SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/filter_plugins/ )

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core) 
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

# 当前目录下也有代码
FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE 
		Qt${QT_VERSION_MAJOR}::Core
		${OpenCV_LIBS}
)

STRING(SUBSTRING "${PROJECT_NAME}" 0 1 exportFileStartName)
STRING(SUBSTRING "${PROJECT_NAME}" 1 -1 exportFileName)
STRING(TOUPPER ${exportFileStartName} exportFileStartName)
SET(exportFileName ${CMAKE_CURRENT_SOURCE_DIR}/${exportFileStartName}${exportFileName}_export.h)
GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
	EXPORT_FILE_NAME 
		${exportFileName} 
)
TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
## 拷贝 dll

## SET( opencvVideoioFfmpegDllName opencv_videoio_ffmpeg${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}_64.dll )
## if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
## ## 调试模式使用的 dll
## 	SET( opencvDllName opencv_world${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}d.dll )
## 	SET( opencvVideoioMsmfDllName opencv_videoio_msmf${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}_64d.dll )
## elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
## ## 发布模式使用的 dll
## 	SET( opencvDllName opencv_world${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}.dll )
## 	SET( opencvVideoioMsmfDllName opencv_videoio_msmf${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}_64.dll )
## endif()
## 
## set( copyDlls ${opencvDllName} ${opencvVideoioMsmfDllName} ${opencvVideoioFfmpegDllName})
## 
## foreach( opencvLib ${copyDlls} )
## 	add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
## 		COMMAND ${CMAKE_COMMAND} -E copy "${OpenCV_DIR}/x64/vc16/bin/${opencvLib}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${opencvLib}" 
## 	)
## endforeach()

# DLL 复制
## add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
##     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:opencv_world> $<TARGET_FILE_DIR:${PROJECT_NAME}>
## )

## 