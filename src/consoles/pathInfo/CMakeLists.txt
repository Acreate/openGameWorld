project(pathInfo LANGUAGES CXX)

include_directories(../libs/processArgs)
include_directories(../libs/processPath)


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# 当前目录下也有代码

FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")
add_executable(${PROJECT_NAME}
  ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}    
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core  
        processArgs 
        processPath 
        typeFile
        )

#install(TARGETS ${PROJECT_NAME}
 #   BUNDLE DESTINATION .
  #  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

  
#6.Qt DLL 复制
 set_target_properties(${PROJECT_NAME}  PROPERTIES
     WIN32_EXECUTABLE TRUE
     MACOSX_BUNDLE TRUE
 )
 
set(MY_APP ${PROJECT_NAME})
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
    PLUGINS_DIR \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\"
)"
)
install(TARGETS ${MY_APP} DESTINATION bin)
install(SCRIPT ${deploy_script})
