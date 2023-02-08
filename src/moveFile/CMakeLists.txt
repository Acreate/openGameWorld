project(moveFile LANGUAGES CXX)

include_directories(../processArgs)
include_directories(../processPath)

find_package(Qt6 REQUIRED COMPONENTS Core) 

# 当前目录下也有代码
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME}
  ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}   
    PRIVATE
         Qt${QT_VERSION_MAJOR}::Core  
        processArgs 
        processPath 
        )


install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

