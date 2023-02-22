
message("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message("name =" ${CURRENT_FOLDER})
project(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# 当前目录下也有代码
FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)

STRING(SUBSTRING "${PROJECT_NAME}" 0 1 exportFileStartName)
STRING(SUBSTRING "${PROJECT_NAME}" 1 -1 exportFileName)
STRING(TOUPPER ${exportFileStartName} exportFileStartName)
SET(exportFileName ${CMAKE_CURRENT_SOURCE_DIR}/${exportFileStartName}${exportFileName}_export.h)
GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
	EXPORT_FILE_NAME 
		${exportFileName} 
)
TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )