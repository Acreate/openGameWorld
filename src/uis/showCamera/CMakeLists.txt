
MESSAGE("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("name =" ${CURRENT_FOLDER})
PROJECT(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
MESSAGE("============ ${CURRENT_FOLDER}")


FIND_PACKAGE( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
FIND_PACKAGE( Qt${QT_VERSION_MAJOR}   REQUIRED COMPONENTS Multimedia) 
FIND_PACKAGE( Qt${QT_VERSION_MAJOR}   REQUIRED COMPONENTS MultimediaWidgets) 
FIND_PACKAGE( Qt${QT_VERSION_MAJOR}  COMPONENTS Widgets REQUIRED )
FIND_PACKAGE( Qt${QT_VERSION_MAJOR}  COMPONENTS Gui REQUIRED )
FIND_PACKAGE( Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED )

# 当前目录下也有代码
FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h" "*.ui")


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

target_link_libraries(
	${PROJECT_NAME} 
PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Multimedia
	Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

set(MY_APP ${PROJECT_NAME})
## opencv dll
# set(opencv $<TARGET_FILE:opencv_world>)
# set(opencvTarget $<TARGET_FILE_DIR:${PROJECT_NAME}>)
if(APPLE)
  set(executable_path "$<TARGET_FILE_NAME:${MY_APP}>.app")
else()
  set(executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:${MY_APP}>")
endif()
set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${MY_APP}.cmake")
message("===========>\n\t"${deploy_script})

file(GENERATE OUTPUT ${deploy_script} CONTENT "
include(\"${QT_DEPLOY_SUPPORT}\")
qt_deploy_runtime_dependencies(
    EXECUTABLE \"${executable_path}\"
	PLUGINS_DIR .
)
message(\"=========== out msg ===========\")
message(\"============= QT_DEPLOY_BIN_DIR => \"\${QT_DEPLOY_BIN_DIR})
message(\"============= CMAKE_INSTALL_BINDIR => \"\${CMAKE_INSTALL_BINDIR})
message(\"============= CMAKE_INSTALL_LIBDIR => \"\${CMAKE_INSTALL_LIBDIR})
message(\"============= CMAKE_INSTALL_PREFIX => \"\${CMAKE_INSTALL_PREFIX})
message(\"=========== out msg ===========\")
")
install(TARGETS ${MY_APP} DESTINATION bin)
install(SCRIPT ${deploy_script})
