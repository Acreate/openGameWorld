project(editResources  VERSION 0.1 LANGUAGES CXX)

include_directories(../libs/processArgs)
include_directories(../libs/processPath)
include_directories(../libs/typeFile)
include_directories(../libs/bitConver)


# 当前目录下也有代码

FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable( ${PROJECT_NAME}
		MANUAL_FINALIZATION
		${SRC_LIST}
	)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
	if(ANDROID)
		add_library(${PROJECT_NAME} SHARED
			${SRC_LIST}
		)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
	else()
		add_executable(${PROJECT_NAME} ${SRC_LIST})
	endif()
endif()

target_link_libraries(${PROJECT_NAME} 
PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	bitConver
	processArgs
	processPath
	typeFile
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

#install(TARGETS ${PROJECT_NAME}
#	BUNDLE DESTINATION .
#	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(${PROJECT_NAME})
endif()
