
message("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message("name =" ${CURRENT_FOLDER})
project(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")


include_directories(../libs/processArgs)
include_directories(../libs/processPath)


find_package(Qt6 REQUIRED COMPONENTS Core) 

# 当前目录下也有代码

FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")
add_executable(${PROJECT_NAME}
  ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    processArgs
    processPath)

    
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(${PROJECT_NAME})
endif()

#install(TARGETS ${PROJECT_NAME}
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


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

#execute_process(
#	# opencv DLL 复制
#    COMMAND \${CMAKE_COMMAND} -E copy_if_different \"${opencv}\" \"${CMAKE_INSTALL_PREFIX}\"
#	# 测试文件 复制
#	COMMAND \${CMAKE_COMMAND} -E copy_if_different \"${CMAKE_CURRENT_SOURCE_DIR}/test.jpg\" \"$#{CMAKE_INSTALL_PREFIX}/test.jpg\"
#)
")
install(TARGETS ${MY_APP} DESTINATION ${user_install_last_dir})
install(SCRIPT ${deploy_script})
